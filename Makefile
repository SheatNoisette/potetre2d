################################################################################
# ** Makefile for potetre2d**
#
# Overridable variables:
#
#  CC: Compiler (default: clang)
#  PYTHON: Python interpreter (useful for macOS) (default from path: python)
#  UPX: UPX executable packer (default from path: upx)
#  STRIP: Strip executable (default from path: strip)
#  CUSTOM_CFLAGS: Custom CFLAGS added to the compilation (empty by default)
#  CUSTOM_LDFLAGS: Custom LDFLAGS added to the compilation (empty by default)
#  INSTALL_PATH: Path where the executable will be installed (make install)
#  BUILD_DIR: Build directory (default: build)
#  BIN_NAME: Executable name (without extension) (default: potetre2d)
#  EXECUTABLE_EXT: Executable extension (default: .elf)
#  CLANG: Use more agressive flags compression flags (default: autodetected)
#  DEBUG: Enable debug mode, add a lot of verbosity (default: 0)
#  SRC_FOLDER: Source folder (default: src)
#  EXTERNAL_PATH: External libraries folder (default: libs)
#  OS: Operating system (unix, windows, macos) (autodetected)
#      Windows can be forced with OS=windows
#
################################################################################

CC ?= clang
PYTHON ?= python
UPX ?= upx
STRIP ?= strip

CUSTOM_CFLAGS ?=
CUSTOM_LDFLAGS ?=

# Installation path for make install
INSTALL_PATH ?= /usr/local/bin

CFLAGS = -Wall -Wextra -std=c1x $(CUSTOM_CFLAGS)
LDFLAGS = $(CUSTOM_LDFLAGS)
EXECUTABLE_EXT ?= .elf

FEATURES_MACROS = -D_POSIX_C_SOURCE=200809L
AGRESSIVE_CLANG = -Oz -s -w -fno-stack-protector -fno-math-errno \
      -Wl,-z,norelro -Wl,--hash-style=gnu -Wl,--build-id=none \
      -fno-unwind-tables -fno-asynchronous-unwind-tables
DISABLE_AGRESSIVE ?= 0
CLANG ?= 0

# Building directory
BUILD_DIR ?= build

# Executable name
BIN_NAME ?= potetre2d

# SRC
SRC_FOLDER ?= src
SRC = $(SRC_FOLDER)/engine.c      \
	  $(SRC_FOLDER)/binding.c     \
	  $(SRC_FOLDER)/draw.c        \
	  $(SRC_FOLDER)/file_io.c     \
	  $(SRC_FOLDER)/input.c       \
	  $(SRC_FOLDER)/loader.c      \
	  $(SRC_FOLDER)/main.c        \
	  $(SRC_FOLDER)/random.c      \
	  $(SRC_FOLDER)/surface.c     \
	  $(SRC_FOLDER)/utils_vec.c   \
	  $(SRC_FOLDER)/utils.c       \
	  $(SRC_FOLDER)/audio.c
OBJ = $(SRC:.c=.o)

# External libraries
EXTERNAL_PATH ?= libs

# Include directories
INCLUDES = -I$(SRC_FOLDER)/includes \
		   -I$(EXTERNAL_PATH)/wren/ \
		   -I$(EXTERNAL_PATH)/tigr/ \
		   -I$(EXTERNAL_PATH)/pithy/ \
		   -I$(EXTERNAL_PATH)/fenster/ \
		   -I$(EXTERNAL_PATH)/stb/ \
		   -I$(EXTERNAL_PATH)/sts_mixer/

EXTERNAL_C = $(EXTERNAL_PATH)/wren/wren.c \
			 $(EXTERNAL_PATH)/tigr/tigr.c \
			 $(EXTERNAL_PATH)/pithy/pithy.c
EXTERNAL_O = $(EXTERNAL_C:.c=.o)

# Detect compiler
COMPILER_DETECT = $(shell $(CC) --version)
ifeq ($(findstring clang,$(COMPILER_DETECT)),clang)
	CLANG = 1
else ifeq ($(findstring MinGW,$(COMPILER_DETECT)),MinGW)
	OS = windows
endif

# OS specific support
ifeq ($(OS),windows)
	LDLIBS = -lgdi32 -lopengl32 -lwinmm -lpthread -mwindows
	EXECUTABLE_EXT = .exe
	CFLAGS += -ffunction-sections -fdata-sections -DOS_WINDOWS=1 -DWIN32=1 -D_WIN32
	LDFLAGS += -Wl,--gc-sections
	LDFLAGS += -Wl,-Bstatic,--whole-archive
	LDFLAGS += -lssp -lwinpthread
	LDFLAGS += -Wl,-Bdynamic,--no-whole-archive
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDLIBS = -framework Cocoa -framework OpenGL -framework AudioToolbox \
				  -lc -lpthread
		CFLAGS += -target x86_64-apple-macos10.12 \
				  -target aarch64-apple-macos11 -mmacosx-version-min=11.0 \
				  -DOS_MACOS=1 -D__APPLE__
		OS = macos
		EXECUTABLE_EXT = .macho
	else
		LDLIBS = -lGLU -lGL -lX11 -lasound -lpthread
		CFLAGS += -ffunction-sections -fdata-sections -DOS_UNIX=1
		LDFLAGS += -Wl,--gc-sections
		OS = unix
		EXECUTABLE_EXT = .elf
	endif
endif

ifeq ($(DEBUG),1)
	CFLAGS += -O0 -g3 -DDEBUG=1 -DENGINE_DEBUG=1
else
	ifeq ($(CLANG),1)
		ifdef DISABLE_AGRESSIVE
			CFLAGS += -Oz
		else
			CFLAGS += $(AGRESSIVE_CLANG)
		endif
	else
		CFLAGS += -Os
	endif
endif

# Linker
LDLIBS += -lm
LDFLAGS += $(LDLIBS)
SRC += $(EXTERNAL_C)

# Build ID

# Check if git exists
GIT_EXISTS := $(shell command -v git 2> /dev/null)
ifdef GIT_EXISTS
	BUILD_ID ?= $(shell git rev-parse --short HEAD)-$(shell git rev-parse --abbrev-ref HEAD)
	BUILD_NUMBER ?= $(shell git rev-list --count HEAD)
else
	BUILD_ID ?= unknown
	BUILD_NUMBER ?= 0
endif
# Add build id to the binary
CFLAGS += -DBUILD_ID=\"$(BUILD_ID)\" -DBUILD_NUMBER=$(BUILD_NUMBER)

all: prepare potetre2d tools

prepare:
	@echo "* Create build folders"
	mkdir -p $(BUILD_DIR)
	mkdir -p src/generated

	@echo "* Build engine Wren std library"
	cat src/wren/*.wren > src/generated/engine_std.wren
	$(PYTHON) scripts/remove_comments.py src/generated/engine_std.wren \
		src/generated/engine_std.wren
	$(PYTHON) scripts/gen_header_from_file.py \
		src/generated/engine_std.wren src/generated/engine_std.h

%.o: %.c
	$(CC) $(CFLAGS) $(FEATURES_MACROS) $(INCLUDES) -c $< -o $@

potetre2d: prepare $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(BIN_NAME)$(EXECUTABLE_EXT)

strip: potetre2d
	$(STRIP) -S --strip-unneeded --remove-section=.note.gnu.gold-version \
      	--remove-section=.comment --remove-section=.note \
      	--remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag \
		$(BUILD_DIR)/$(BIN_NAME)$(EXECUTABLE_EXT)

compress: potetre2d strip
	$(UPX) -9 $(BUILD_DIR)/$(BIN_NAME)$(EXECUTABLE_EXT)

tools: $(EXTERNAL_O)
	@echo "Building tools..."
	@mkdir -p $(BUILD_DIR)/tools/
	@for tool in $(shell ls tools | cut -d '.' -f 1); do \
		echo "* Build $$tool"; \
		$(CC) tools/$$tool.c $(EXTERNAL_O) \
			$(CFLAGS) \
			$(LDFLAGS) $(INCLUDES) \
			-o $(BUILD_DIR)/tools/$$tool-$(OS)$(EXECUTABLE_EXT); \
		$(STRIP) $(BUILD_DIR)/tools/$$tool-$(OS)$(EXECUTABLE_EXT); \
	done

cheatset:
	@$(PYTHON) scripts/generate_cheatset.py src/wren/ doc/CheatSheet.md

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(OBJ)
	$(RM) -r src/generated/

# Unix only
install: prepare potetre2d
	mkdir -p $(INSTALL_DIR)
	cp $(BUILD_DIR)/$(BIN_NAME)$(EXECUTABLE_EXT) $(INSTALL_DIR)/$(BIN_NAME)

.PHONY: all clean tools

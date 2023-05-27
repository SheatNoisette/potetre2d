CC ?= clang
PYTHON ?= python
UPX ?= upx
STRIP ?= strip

CUSTOM_CFLAGS ?=
CUSTOM_LDFLAGS ?=

CFLAGS = -Wall -Wextra -std=c2x $(CUSTOM_CFLAGS)
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
SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.c)
OBJ = $(SRC:.c=.o)

# External libraries
EXTERNAL_PATH ?= external

# Include directories
INCLUDES = -I$(SRC_FOLDER)/includes \
           -I$(EXTERNAL_PATH)/wren/src/include \
		   -I$(EXTERNAL_PATH)/tigr/ \
		   -I$(EXTERNAL_PATH)/pithy/ \
		   -I$(EXTERNAL_PATH)/fenster/ \
		   -I$(EXTERNAL_PATH)/stb/ \
		   -I$(EXTERNAL_PATH)/sts_mixer/

EXTERNAL_C = $(EXTERNAL_PATH)/wren/build/wren.c \
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
	CFLAGS += -ffunction-sections -fdata-sections -DOS_WINDOWS=1 -DWIN32=1
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
				  -DOS_MACOS=1
		OS = macos
		EXECUTABLE_EXT = .mach
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

compress: potetre2d
	$(STRIP) -S --strip-unneeded --remove-section=.note.gnu.gold-version \
      	--remove-section=.comment --remove-section=.note \
      	--remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag \
		$(BUILD_DIR)/$(BIN_NAME)$(EXECUTABLE_EXT)
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

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(OBJ)
	$(RM) -r src/generated/

.PHONY: all clean tools

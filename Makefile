CC ?= clang
PYTHON ?= python
UPX ?= upx
STRIP ?= strip

CFLAGS = -Wall -Wextra -std=c2x -ffunction-sections -fdata-sections
LDFLAGS ?=

FEATURES_MACROS = -D_POSIX_C_SOURCE=200809L
AGRESSIVE_CLANG = -Oz -s -w -fno-stack-protector -fno-math-errno \
      -Wl,-z,norelro -Wl,--hash-style=gnu \
      -Wl,--build-id=none -Wl,--gc-sections \
      -fno-unwind-tables -fno-asynchronous-unwind-tables
DISABLE_AGRESSIVE ?= 0
CLANG ?= 0

# Building directory
BUILD_DIR ?= build

# Executable name
BIN_NAME ?= picogine

# SRC
SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.c)
OBJ = $(SRC:.c=.o)

# External libraries
EXTERNAL_PATH = external

# Include directories
INCLUDES = -I$(SRC_FOLDER)/includes \
           -I$(EXTERNAL_PATH)/wren/src/include \
		   -I$(EXTERNAL_PATH)/fenster/ \
		   -I$(EXTERNAL_PATH)/ini/src/ \
		   -I$(EXTERNAL_PATH)/tigr/
EXTERNAL_C = $(EXTERNAL_PATH)/wren/build/wren.c \
			 $(EXTERNAL_PATH)/ini/src/ini.c \
			 $(EXTERNAL_PATH)/tigr/tigr.c

# Detect compiler
COMPILER_DETECT = $(shell $(CC) --version)
ifeq ($(findstring clang,$(COMPILER_DETECT)),clang)
	CLANG = 1
else ifeq ($(findstring MinGW,$(COMPILER_DETECT)),MinGW)
	OS = Windows_NT
endif

# OS specific support
ifeq ($(OS),Windows_NT)
	BIN_NAME := $(BIN_NAME).exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDLIBS = -framework Cocoa -framework OpenGL -lc
		CFLAGS += -target x86_64-apple-macos10.12 \
				  -target aarch64-apple-macos11 -mmacosx-version-min=11.0
	else
		LDLIBS = -lGLU -lGL -lX11 -lc
	endif
endif

ifdef DEBUG
	CFLAGS += -O0 -g3 -DDEBUG=1 -DENGINE_DEBUG=1
else
	ifdef CLANG
		ifdef DISABLE_AGRESSIVE
			CFLAGS += -Oz
		else
			CFLAGS += $(AGRESSIVE_CLANG)
		endif
	else
		CFLAGS += -Os
	endif
	CFLAGS += -DENGINE_DEBUG=0
endif

# Linker
LDLIBS += -lm
LDFLAGS += $(LDLIBS)
SRC += $(EXTERNAL_C)

all: prepare picogine

prepare:
	@echo "* Create build folders"
	mkdir -p $(BUILD_DIR)
	mkdir -p src/generated

	@echo "* Build engine Wren std library"
	cat src/wren/*.wren > src/generated/engine_std.wren
	$(PYTHON) tools/remove_comments.py src/generated/engine_std.wren \
		src/generated/engine_std.wren
	$(PYTHON) tools/gen_header_from_file.py \
		src/generated/engine_std.wren src/generated/engine_std.h

%.o: %.c
	$(CC) $(CFLAGS) $(FEATURES_MACROS) $(INCLUDES) -c $< -o $@

picogine: prepare $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(BIN_NAME)

compress: picogine
	$(STRIP) -S --strip-unneeded --remove-section=.note.gnu.gold-version \
      	--remove-section=.comment --remove-section=.note \
      	--remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag \
		$(BUILD_DIR)/$(BIN_NAME)
	$(UPX) -9 $(BUILD_DIR)/$(BIN_NAME)

clean:
	$(RM) -rf $(BUILD_DIR)
	$(RM) -f $(OBJ)
	$(RM) -rf src/generated/

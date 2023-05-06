CC ?= clang
CFLAGS = -Wall -Wextra -std=c2x -ffunction-sections -fdata-sections
LDFLAGS ?=

FEATURES_MACROS = -D_POSIX_C_SOURCE=200809L
AGRESSIVE_CLANG = -Oz -s -w -fno-stack-protector -fno-math-errno \
      -Wl,-z,norelro -Wl,--hash-style=gnu \
      -Wl,--build-id=none -Wl,--gc-sections \
      -fno-unwind-tables -fno-asynchronous-unwind-tables

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
	BIN_NAME := $(BIN_NAME).exe
	OS = Windows_NT
endif

# Libraries support
ifeq ($(OS),Windows_NT)
	LDLIBS = -lgdi32 -lopengl32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDLIBS = -framework Cocoa -framework OpenGL -lc
	else
		LDLIBS = -lGLU -lGL -lX11 -lc
	endif
endif

ifdef DEBUG
	CFLAGS += -O0 -g3 -DDEBUG=1
else
	ifdef CLANG
		CFLAGS += $(AGRESSIVE_CLANG) -DDEBUG=0
	else
		CFLAGS += -Os -DDEBUG=0
	endif
endif

# Linker
LDLIBS += -lm
LDFLAGS += $(LDLIBS)
SRC += $(EXTERNAL_C)

all: prepare picogine

prepare:
	@echo "* Create build folders"
	mkdir -p build
	mkdir -p src/generated

	@echo "* Build engine Wren std library"
	cat src/wren/*.wren > src/generated/engine_std.wren
	python tools/remove_comments.py src/generated/engine_std.wren \
		src/generated/engine_std.wren
	python tools/gen_header_from_file.py \
		src/generated/engine_std.wren src/generated/engine_std.h

%.o: %.c
	$(CC) $(CFLAGS) $(FEATURES_MACROS) $(INCLUDES) -c $< -o $@

picogine: prepare $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(BUILD_DIR)/$(BIN_NAME)

compress: picogine
	strip -S --strip-unneeded --remove-section=.note.gnu.gold-version \
      	--remove-section=.comment --remove-section=.note \
      	--remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag \
		$(BUILD_DIR)/$(BIN_NAME)
	upx -9 $(BUILD_DIR)/$(BIN_NAME)

clean:
	$(RM) -rf build
	$(RM) -f $(OBJ)
	$(RM) -rf src/generated/

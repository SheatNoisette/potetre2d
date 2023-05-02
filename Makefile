CC = clang
CFLAGS = -Wall -Wextra -std=c2x
LDFLAGS ?=

FEATURES_MACROS = -D_POSIX_C_SOURCE=200809L
AGRESSIVE_CLANG = -Oz -s -w -fno-stack-protector -fno-math-errno \
      -Wl,-z,norelro -Wl,--hash-style=gnu -fdata-sections \
      -ffunction-sections -Wl,--build-id=none -Wl,--gc-sections \
      -fno-unwind-tables -fno-asynchronous-unwind-tables

# SRC
SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.c)
OBJ = $(SRC:.c=.o)

# External libraries
EXTERNAL_PATH = external

# Include directories
INCLUDES = -I$(SRC_FOLDER)/includes \
           -I$(EXTERNAL_PATH)/wren/src/include \
		   -I$(EXTERNAL_PATH)/fenster/
EXTERNAL_C = $(EXTERNAL_PATH)/wren/build/wren.c

# Libraries support
ifeq ($(OS),Windows_NT)
	LDLIBS = -lgdi32
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		LDLIBS = -framework Cocoa
	else
		LDLIBS = -lX11
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
LDLIBS += -lm -lpthread -lc
LDFLAGS += $(LDLIBS)
SRC += $(EXTERNAL_C)

all: prepare picogine

prepare:
	@echo "* Create build folders"
	mkdir -p build
	mkdir -p src/generated

	@echo "* Build engine Wren std library"
	cat src/wren/*.wren > src/generated/engine_std.wren
	python tools/gen_header_from_file.py \
		src/generated/engine_std.wren src/generated/engine_std.h

%.o: %.c
	$(CC) $(CFLAGS) $(FEATURES_MACROS) $(INCLUDES) -c $< -o $@

picogine: prepare $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o build/picogine

compress: picogine
	strip -S --strip-unneeded --remove-section=.note.gnu.gold-version \
      	--remove-section=.comment --remove-section=.note \
      	--remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag \
		build/picogine
	upx -9 build/picogine

clean:
	$(RM) -rf build
	$(RM) -f $(OBJ)
	$(RM) -rf src/generated/

CC ?= clang
CFLAGS = -Wall -Wextra -std=c2x
LDFLAGS ?=
FEATURES_MACROS = -D_POSIX_C_SOURCE=200809L

# SRC
SRC_FOLDER = src
SRC = $(wildcard $(SRC_FOLDER)/*.c)
OBJ = $(SRC:.c=.o)

# External libraries
EXTERNAL_PATH = external

# Include directories
INCLUDES = -I$(SRC_FOLDER)/includes \
           -I$(EXTERNAL_PATH)/mujs/ \
		   -I$(EXTERNAL_PATH)/fenster/
EXTERNAL_C = $(EXTERNAL_PATH)/mujs/one.c

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
	CFLAGS += -O3 -DDEBUG=0
endif

# Linker
LDLIBS += -lm -lpthread -lc
LDFLAGS += $(LDLIBS)
SRC += $(EXTERNAL_C)

all: prepare picogine

prepare:
	mkdir -p build

%.o: %.c
	$(CC) $(CFLAGS) $(FEATURES_MACROS) $(INCLUDES) -c $< -o $@

picogine: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o build/picogine

compress: picogine
	upx -9 build/picogine

clean:
	rm -rf build
	rm -f $(OBJ)

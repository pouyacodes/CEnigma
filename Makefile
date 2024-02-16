INCLUDE_PATH  := $(realpath ./include)
SRC_PATH      := $(realpath ./src)
EXAMPLES_PATH := $(realpath ./examples)
TESTS_PATH    := $(realpath ./tests)

CC := gcc
CFLAGS := -g -Wall -Werror -Wextra -I$(INCLUDE_PATH)

VERSION := 1.0

.PHONY: all build install clean

all: build

include $(SRC_PATH)/Makefile
include $(EXAMPLES_PATH)/Makefile
include $(TESTS_PATH)/Makefile

build: build-lib build-tests build-examples

install:
	@echo 'TODO: Not Implemented Yet!'

clean: clean-lib clean-tests clean-examples

%.o: %.c
	@$(CC) -c -o $@ $^ $(CFLAGS)

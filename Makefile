SHELL = /bin/sh

rootdir := $(realpath .)

prefix ?= /usr/local
exec_prefix ?= ${prefix}

includedir  := ${rootdir}/include
srcdir      := ${rootdir}/src
examplesdir := ${rootdir}/examples
testsdir    := ${rootdir}/tests

CC := gcc
CFLAGS := -g
ALL_CFLAGS := -Wall -Werror -Wextra -I${includedir} ${CFLAGS}

INSTALL := install
INSTALL_PROGRAM := ${INSTALL}
INSTALL_DATA := ${INSTALL} -m 644

VERSION := 1.0

.PHONY: all build test examples install clean

all: build

build: build-lib

uninstall: uninstall-lib

tests: build-tests

examples: build-examples

install: install-lib

clean: clean-lib clean-tests clean-examples

%.o: %.c
	${CC} -c -o $@ $^ ${ALL_CFLAGS}

include ${srcdir}/Makefile
include ${examplesdir}/Makefile
include ${testsdir}/Makefile

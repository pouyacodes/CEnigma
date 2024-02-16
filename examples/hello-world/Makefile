.PHONY: run clean

CC ?= gcc
CFLAGS ?= -g -Wall -Wextra -I../../include -L../../src -lenigma

ROTOR_DATA_PATH := rotors.dat
CFLAGS += -DROTOR_DATA_PATH='"$(ROTOR_DATA_PATH)"'

all: main rotor_data

main: main.o
	$(CC) -o $@ $^ $(CFLAGS)

rotor_data: rotor_data.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $^ $(CFLAGS)

run: rotor_data main
	@LD_LIBRARY_PATH=../../src /bin/bash -c '([ -f "$(ROTOR_DATA_PATH)" ] || ./rotor_data) && ./main'

clean:
	rm -f rotor_data rotor_data.o main main.o rotors.dat

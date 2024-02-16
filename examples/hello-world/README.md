# Basic `"Hello, World!"` Sample

In this example we encode `Hello, World!` string using enigma machine.

before encoding process, we have to generate rotor data and feed them to the enigma machine.

We prepare another simple program called `rotor_data.c` that compiles from `Makefile` and generates three randomly rotors for each individual langauge sequences.

## `rotor_data.c`

Is responsible to generate rotors data.

This program uses `enigma_rotor_random` libenigma api to generate random rotor data using `en.h` language pack which is used for English.

for each individual sequence located there, it generates three rotors (By default, Configurable through `Makefile`). for English language pack there are three sequences. so:

- Alphabet (3 Rotors)
- Digits (3 Rotors)
- Punctuations (3 Rotors)

Then "serializes" rotors data to `./rotors.dat` file (By default, Configurable through `Makefile`) and Done!

## `main.c`

The logic of example is located in here.

This program first deserializes rotors data from `./rotors.dat` file and then instantiate a enigma engine and feeds the language and rotors stuff to engine and encodes `Hello, World!` string.

The output of this program is just encoded form of `Hello, World!` string with `./rotors.dat` rotors data.

# Building

Before building the examples, you have to make sure that you already builded the libenigma or installed.

If you didn't, go to project root directory and run:

```console
$ make build-lib
```

After building come back here and run:

```console
$ make
$ make run # Runs ./rotors_data && ./main
```


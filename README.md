# CEnigma (Enigma machine in C)

> The Enigma machine is a cipher device developed and used in the early- to mid-20th century to protect commercial, diplomatic, and military communication. It was employed extensively by Nazi Germany during World War II, in all branches of the German military. The Enigma machine was considered so secure that it was used to encipher the most top-secret messages.
>
> from [Wikipedia][wiki-enigma-machine]

## Description

CEnigma is a C library designed to simulate the functionality of the Enigma machine.

## Installaion

### Binary Releases

You can download the pre-compiled version of the library from the [releases][releases-page] page. Alternatively, you can manually compile the library.

### Manual Build

#### Building

1. Clone this project to your local machine:

```console
$ git clone https://github.com/pouyacodes/CEnigma
```

2. Navigate to the project directory:

```console
$ cd CEnigma/
```

3. Compile the library:

```console
$ make
```

This will create both static library and dynamic libraries in the `src/` directory.

#### Installing

To install the library:

```console
$ make install
```

By default, the library will be installed in the `/usr/local` (`prefix` variable) hierarchy: 

- `/usr/local/lib/enigma`: for both static and dynamic libraries
- `/usr/local/include/enigma`: for header files

but you can change it by specifying `prefix` variable:

```console
$ make prefix=/path/to/installation/hierarchy install
```

Additionally, ensure everything works as expected by running the tests:

```console
$ make tests && make run-tests
```

## Usage

### Getting started

#### Build the library

Before using the library, compile and install it as describe in the [Installaion](#installaion) section.

#### Basic objects

CEnigma provides several key objects for encoding:

- `Sequence` object represents a simple sequence of data (`wchar_t`) along with it's length.

```c
typedef struct Sequence {
    wchar_t *values;
    size_t len;
} Sequence;
```

- `Rotor` object represents a rotor with a sequence and the number of rotations.

```c
typedef struct Rotor {
    Sequence sequence;
    size_t rotations;
} Rotor;
```

- `Langauge` object contains information necessary for defining a language, such as alphabet, digits, punctuation, and case handling functions.

```c
typedef struct Language {
    Sequence *alphabet;
    Sequence *digit;
    Sequence *punctuation;

    int (*isupper)(wint_t wc);
    wint_t (*toupper)(wint_t wc);
    wint_t (*tolower)(wint_t wc);
} Language;
```

- `Engine` defines the Enigma machine's configuration, including the language used, rotor states, and plugboard settings.

```c
typedef struct Enigma {
    Language *language;
    PlugboardList *plugboard;

    RotorList *alphabet_rotors;
    RotorList *digit_rotors;
    RotorList *punctuation_rotors;
} Enigma;
```

There are `*List` structures in the library that all follow the same set of members and define a simple List with a length. For example, `RotorList`:

```c
typedef struct RotorList {
    Rotor *items;
    size_t length;
    size_t capcity; // used internally by allocator
} RotorList;
```

#### Basic example

Refer to the [example][hello-world-example] for a basic usage demonstration.

## Documentations

Documentation for each structure and function is provided in the doc blocks within the codebase.

## TODO

- [x] ~Implementing the basic logic (Just some functions that encode/decode)~
- [x] ~Implementing plugboard feature~
- [x] ~Implementing Object-Oriented API~
- [x] ~Support Unicode and other languages~
- [x] ~Command-line argument support~
- [x] ~Improve codebase structure~
- [x] ~Write tests~
- [x] ~Create REPL example~
- [x] ~Standard Makefile targets (install, uninstall, etc)~
- [x] ~Write docs~
- [x] ~Enhance README.md~
- [x] ~Release~


[wiki-enigma-machine]: https://en.wikipedia.org/wiki/Enigma_machine
[releases-page]: https://github.com/pouyacodes/CEnigma/releases
[hello-world-example]: examples/hello-world/

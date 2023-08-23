# CEngima (Engima machine in C)

## Description

Simulation of the [Enigma machine](https://en.wikipedia.org/wiki/Enigma_machine) in C Prorgramming Language.

## Usage

The current version doesn't have a well designed API and usage, becasue this project under development.

You can check the [TODO](#todo) and see future features and development state.

### Build and Use

There is no a lot of file yet in this project. Just a simple `enigma.c` file that contains the whole program. and only encodes `"Hello, World!"` string with preset of rotors settings and stuff.

You can change the macro `PLAIN_TEXT` with your plain text to encode.
Also you can change the rotors characters order. (`Rotor` structure instance array)

Finaly you can build the program with `make` build system:

```bash
$ make
```

And run it with:

```bash
$ make run
```

<div id="todo">

## TODO

- [x] Implementing the basic logic (Just some functions that encode/decode)
- [x] Implementing the Plugboard feature
- [ ] Implementing some Object Oriented API
- [ ] Support for Unicode (Other languages)
- [ ] Support for command line argument
- [ ] Better codebase structure

</div>

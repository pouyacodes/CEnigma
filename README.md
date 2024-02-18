# CEnigma (Enigma machine in C)

> [!WARNING]
> This project is under development and is not finished yet!

**Note:** Please do <em>not follow</em> this document at this time as it is currently under construction and may contain inaccuracies or wrong information.

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
- [x] Implementing some Object Oriented API
- [x] Support for Unicode (Other languages)
- [x] Support for command line argument
- [x] Better codebase structure
- [ ] Write some tests
- [x] Write REPL example
- [ ] Standard Makefile targets (install, uninstall, etc)
- [ ] Write docs
- [ ] Write a better README.md

</div>

# Enigma Repl

This example is a "repl" for libengima.

First you have to compile it and generate rotors data using [`rotor_data.c`](../hello-world).

After that you are be able to run. It will show you a prompt and you provide your text and engine encodes that for you.

You can also pipe stuff to it or use options like `-f|--from`, `-t|--to`, etc. (see `--help`)

Note that this example uses English language pack so the only language here is English.

## Building

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

It will show you a prompt similar to below and you can provide your input:

```console
./rotor_data: INFO: Working with rotors.dat file
./rotor_data: INFO: Serializing alpha_rotor
./rotor_data: INFO: Serializing digit_rotor
./rotor_data: INFO: Serializing punct_rotor
./rotor_data: INFO: Serializing Done!
enigma> Hello, World!
Rftze$ Hjpis=
enigma> 
```

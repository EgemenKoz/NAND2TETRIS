# Hack Assembler

This is a Hack Assembler for the Nand2Tetris course, which converts Hack assembly language (.asm files) to Hack machine code (.hack files).

## Building the Assembler

To build the assembler, simply run:

```bash
make
```

This will compile the source files and create the `HackAssembler` executable.

## Using the Assembler

To assemble a Hack assembly file, run:

```bash
./HackAssembler filename.asm
```

This will create a `filename.hack` file in the same directory, containing the machine code equivalent of your assembly program.

## File Structure

- `main.cpp` - Entry point of the application
- `HackAssambler.cpp`/`HackAssembler.h` - Main assembler logic
- `HackCode.cpp`/`HackCode.h` - Code generation
- `HackParser.cpp`/`HackParser.h` - Instruction parsing
- `HackSymbolTable.cpp`/`HackSymbolTable.h` - Symbol table management

## Note on Filenames

There is a naming inconsistency in the project files - the class is named `HackAssambler` (with two 's's) but some filenames use `HackAssembler` (with one 's'). The Makefile has been configured to handle this inconsistency.

## Cleaning Up

To remove the compiled executable, run:

```bash
make clean
``` 
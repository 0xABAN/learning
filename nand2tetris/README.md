# Nand2Tetris

The hardware exercises in projects 1, 2, 3, and 5 use SystemVerilog (`.sv`).
The existing Not implementation is preserved; the other 30 modules are empty
scaffolds. Original course descriptions and port widths are retained.

## Verilator

Install with `brew install verilator`. Run a test from this directory:

```sh
./test Not
```

A successful run prints `PASS Not_tb: 2 checks`. A failure identifies the signal,
reference row, expected value, and actual value, and exits unsuccessfully.
Verilator also prints its own simulation statistics after a successful run.

The runner builds a fresh simulation and finds dependencies in the hardware
exercise directories. It stops if compilation fails and never runs an old binary.
Build output is shown on failure. Generated files live in the ignored `obj_dir/`.

To run the same test directly:

```sh
verilator --binary projects/1/Not_tb.sv projects/1/Not.sv
./obj_dir/VNot_tb
```

There are 34 testbenches covering the 31 exercises. Each `<name>_tb.sv` embeds
its expected values from the original course comparison file. Run, for example:

```sh
./test And
./test ALU
./test ALU_basic
./test RAM8
./test CPU
./test Memory
./test ComputerAdd
./test ComputerMax
./test ComputerRect
```

The CPU test uses the original external-interface test, avoiding dependence on
its internal D register. The duplicate internal CPU test has been removed.
Comparison values marked as don't-care in the course are not checked.
The original hardware `.tst` and `.cmp` files have been replaced; software-project
tests and the computer's `.hack` programs remain.

The exercises are still scaffolds. Only Not currently has an implementation.
A failing test is expected until you implement the corresponding circuit.

## Hardware conventions

Ports keep their course names. A course bus `in[16]` becomes `logic [15:0] in`;
bit 0 remains the least significant bit. Use named port connections.

Modules in projects 3 and 5 have an explicit `input logic clk`. Use a shared
clock and rising-edge state updates throughout those projects. Combinational
modules in projects 1 and 2 have no clock. The course simulator's implicit clock
and tick/tock steps must be translated into explicit clock transitions in your
own simulation.

SystemVerilog has a built-in lowercase `nand` primitive, with output first:
`nand(out, a, b);`. Unlike the course simulator, Verilator does not automatically
supply missing course chips. DFF, ROM, screen, and keyboard models will need
SystemVerilog implementations or simulation support when those projects need
them. Preserve each exercise's allowed building blocks rather than replacing
its implementation with higher-level operators.

## Sequential tests and project 5

The course starts storage at zero. These tests likewise expect registers and
memory to start at zero in simulation; initialize your storage models explicitly.
This is a simulation convention, not a guarantee about physical hardware.

A course `tick` becomes a settling interval with `clk = 0`. A course `tock`
becomes a rising edge followed by settling, then a return to zero. Checks before
and after the edge preserve the course's old-state/new-state expectations.

Memory and full-computer tests need internal access, just as the original
simulator scripts did. Use these instance and storage names, or update the
hierarchical references in those testbenches to match your implementation:

| Path relative to the tested component | Required object |
| --- | --- |
| `keyboard.out` in Memory | 16-bit keyboard output, driven by the test using `force` |
| `rom.words` in Computer | ROM array: `logic [15:0] words [0:32767]` |
| `cpu.a_register.out` in Computer | 16-bit A-register output |
| `cpu.d_register.out` in Computer | 16-bit D-register output |
| `cpu.pc` in Computer | 15-bit program-counter output |
| `memory.ram.words` in Computer | RAM array: `logic [15:0] words [0:16383]` |
| `memory.screen.words` in Computer | Screen array: `logic [15:0] words [0:8191]` |

The computer tests load Add, Max, and Rect into ROM and check the original
cycle-by-cycle expected values. Rect additionally checks four screen words and
the next untouched row. Memory simulates the K and Y keys automatically;
there is no graphical screen or manual keyboard interaction.

The array paths assume behavioral storage models for these integration tests.
If you build RAM entirely from smaller components, adapt the testbench's RAM
access to that structure rather than adding a separate, disconnected array.
Memory and Computer testbenches cannot compile against their empty scaffolds
until these internal components exist. No exercise solutions are supplied.

## Original course tools

The official Nand2Tetris 2.7 desktop suite remains in `tools/`, with its original
built-in HDL chips and an isolated Eclipse Temurin 17 runtime in `.runtime/`.
The `hardware-simulator` launcher opens the Java simulator, which cannot load
`.sv` files. Use Verilator for the converted hardware exercises.

Other course projects are unchanged. To run the supplied Java tools, explicitly
set JAVA_HOME and PATH to this folder's `.runtime/java` and `.runtime/java/bin`
in your terminal session. The launcher does this without modifying shell profiles.

The test stimuli and expected values are adapted from Nand2Tetris by Nisan and
Schocken, accompanying The Elements of Computing Systems (MIT Press).

Sources:

- https://www.nand2tetris.org/software
- https://verilator.org/guide/latest/exe_verilator.html
- https://adoptium.net/installation/archives

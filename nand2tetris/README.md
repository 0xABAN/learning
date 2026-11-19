# Nand2Tetris

The hardware exercises in projects 1, 2, 3, and 5 use SystemVerilog (`.sv`).
The existing Not implementation is preserved; the other 30 modules are empty
scaffolds. Original course descriptions and port widths are retained.

## Verilator

Install with `brew install verilator`. Check the installation and lint Not:

```sh
verilator --version
verilator --lint-only -Wall --top-module Not projects/1/Not.sv
```

Lint checks syntax and wiring, not functional correctness. Empty scaffolds can
produce undriven-output and unused-input warnings with `-Wall`; implement the
exercise before expecting a clean detailed check.

For simulation, write a SystemVerilog testbench that supplies inputs, checks
outputs, and ends with `$finish`. Once you create `Not_tb.sv` declaring module
`Not_tb`, build and run it with:

```sh
verilator --binary --timing --top-module Not_tb Not_tb.sv projects/1/Not.sv
./obj_dir/VNot_tb
```

Supply the source files for every instantiated module when building larger
circuits. No testbenches or translated course tests are included.

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

## Original course tools

The official Nand2Tetris 2.7 desktop suite remains in `tools/`, with its original
built-in HDL chips and an isolated Eclipse Temurin 17 runtime in `.runtime/`.
The `hardware-simulator` launcher still opens the Java simulator, but it cannot
load the new `.sv` files. The supplied `.tst` and `.cmp` files remain as references;
they are not executable Verilator tests.

Other course projects are unchanged. To run the supplied Java tools, explicitly
set JAVA_HOME and PATH to this folder's `.runtime/java` and `.runtime/java/bin`
in your terminal session. The launcher does this without modifying shell profiles.

Sources:
- https://www.nand2tetris.org/software
- https://verilator.org/guide/latest/exe_verilator.html
- https://adoptium.net/installation/archives

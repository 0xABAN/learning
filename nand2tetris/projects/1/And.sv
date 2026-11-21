// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/And.sv
/**
 * And gate:
 * if (a and b) out = 1, else out = 0 
 */

module And(
    input logic a,
    input logic b,
    output logic out
);
    logic x;
    nand(x, a, b);
    nand(out, x, x);
endmodule

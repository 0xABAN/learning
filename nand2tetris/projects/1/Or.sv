// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Or.sv
/**
 * Or gate:
 * if (a or b) out = 1, else out = 0 
 */

module Or(
    input logic a,
    input logic b,
    output logic out
);
    logic not_a; 
    logic not_b; 

    nand(not_a, a, a); // not a 
    nand(not_b, b, b); // not b 

    nand(out, not_a, not_b); // (not a) nand (not b)
endmodule

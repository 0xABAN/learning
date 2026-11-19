// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Not.sv
/**
 * Not gate:
 * if (in) out = 0, else out = 1
 */
module Not(
    input logic in,
    output logic out
);

    nand(out, in, in);
endmodule

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Not16.sv
/**
 * 16-bit Not gate:
 * for i = 0, ..., 15:
 * out[i] = Not(a[i])
 */
module Not16(
    input logic [15:0] in,
    output logic [15:0] out
);
    for(genvar i = 0; i < 16; i++)
        Not inverter(.in(in[i]), .out(out[i]));
endmodule

// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Or16.sv
/**
 * 16-bit Or gate:
 * for i = 0, ..., 15:
 * out[i] = a[i] Or b[i] 
 */
module Or16(
    input logic [15:0] a,
    input logic [15:0] b,
    output logic [15:0] out
);
    for(genvar i = 0; i < 16; i++)
        Or or_gate(.a(a[i]), .b(b[i]), .out(out[i]));
endmodule

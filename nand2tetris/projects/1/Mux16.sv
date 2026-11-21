// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Mux16.sv
/**
 * 16-bit multiplexor: 
 * for i = 0, ..., 15:
 * if (sel = 0) out[i] = a[i], else out[i] = b[i]
 */
module Mux16(
    input logic [15:0] a,
    input logic [15:0] b,
    input logic sel,
    output logic [15:0] out
);
    for(genvar i = 0; i < 16; i++) 
        Mux mux_gate(.a(a[i]), .b(b[i]), .sel(sel), .out(out[i]));

endmodule

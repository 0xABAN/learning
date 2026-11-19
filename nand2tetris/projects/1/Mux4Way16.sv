// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Mux4Way16.sv
/**
 * 4-way 16-bit multiplexor:
 * out = a if sel = 00
 *       b if sel = 01
 *       c if sel = 10
 *       d if sel = 11
 */
module Mux4Way16(
    input logic [15:0] a,
    input logic [15:0] b,
    input logic [15:0] c,
    input logic [15:0] d,
    input logic [1:0] sel,
    output logic [15:0] out
);

endmodule

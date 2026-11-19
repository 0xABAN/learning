// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Mux8Way16.sv
/**
 * 8-way 16-bit multiplexor:
 * out = a if sel = 000
 *       b if sel = 001
 *       c if sel = 010
 *       d if sel = 011
 *       e if sel = 100
 *       f if sel = 101
 *       g if sel = 110
 *       h if sel = 111
 */
module Mux8Way16(
    input logic [15:0] a,
    input logic [15:0] b,
    input logic [15:0] c,
    input logic [15:0] d,
    input logic [15:0] e,
    input logic [15:0] f,
    input logic [15:0] g,
    input logic [15:0] h,
    input logic [2:0] sel,
    output logic [15:0] out
);

endmodule

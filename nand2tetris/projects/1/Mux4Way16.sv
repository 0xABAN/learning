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

/*
* a = 1 1 0 1 
* b = 0 1 0 1 
* sel = 0; -> 1 1 0 1  
* 
* c = 0 1 1 0
* d = 1 0 1 0 
* sel = 0; -> 0 1 1 0 
*
* a = 1 1 0 1 
* c = 0 1 1 0
* sel = 0; 
* */

module Mux4Way16(
    input logic [15:0] a,
    input logic [15:0] b,
    input logic [15:0] c,
    input logic [15:0] d,
    input logic [1:0] sel,
    output logic [15:0] out
);
    logic [15:0] mux_a_b; 
    logic [15:0] mux_c_d; 
    
    Mux16 mux1(.a(a), .b(b), .sel(sel[0]), .out(mux_a_b)); 
    Mux16 mux2(.a(c), .b(d), .sel(sel[0]), .out(mux_c_d)); 
    
    Mux16 mux3(.a(mux_a_b), .b(mux_c_d), .sel(sel[1]), .out(out));  
endmodule

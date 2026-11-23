// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/DMux8Way.sv
/**
 * 8-way demultiplexor:
 * [a, b, c, d, e, f, g, h] = [in, 0,  0,  0,  0,  0,  0,  0] if sel = 000
 *                            [0, in,  0,  0,  0,  0,  0,  0] if sel = 001
 *                            [0,  0, in,  0,  0,  0,  0,  0] if sel = 010
 *                            [0,  0,  0, in,  0,  0,  0,  0] if sel = 011
 *                            [0,  0,  0,  0, in,  0,  0,  0] if sel = 100
 *                            [0,  0,  0,  0,  0, in,  0,  0] if sel = 101
 *                            [0,  0,  0,  0,  0,  0, in,  0] if sel = 110
 *                            [0,  0,  0,  0,  0,  0,  0, in] if sel = 111
 */
module DMux8Way(
    input logic in,
    input logic [2:0] sel,
    output logic a,
    output logic b,
    output logic c,
    output logic d,
    output logic e,
    output logic f,
    output logic g,
    output logic h
);
    logic dmux_abcd; // 1 if in is in abcd, 0 o.w.
    logic dmux_efgh; 

    DMux dmux1(.in(in), .sel(sel[2]), .a(dmux_abcd), .b(dmux_efgh)); 
    
    DMux4Way dmux2(.in(dmux_abcd), .sel(sel[1:0]), .a(a), .b(b), .c(c), .d(d));
    DMux4Way dmux3(.in(dmux_efgh), .sel(sel[1:0]), .a(e), .b(f), .c(g), .d(h));
endmodule

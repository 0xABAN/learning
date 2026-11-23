// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/DMux4Way.sv
/**
 * 4-way demultiplexor:
 * [a, b, c, d] = [in, 0, 0, 0] if sel = 00
 *                [0, in, 0, 0] if sel = 01
 *                [0, 0, in, 0] if sel = 10
 *                [0, 0, 0, in] if sel = 11
 */


/*
* take a, b & find their dmux using sel[0]; 
* do the same with c, d 
* outputs: [in, 0], [0, in], ...
* 
*
* */

module DMux4Way(
    input logic in,
    input logic [1:0] sel,
    output logic a,
    output logic b,
    output logic c,
    output logic d
);
    
    logic ab; // 1 if ab, 0 otherwise. if it's 1, it becomes the new in
    logic cd; // 1 if cd, 0 otherwise. 
    
    DMux dmux1(.in(in), .sel(sel[1]), .a(ab), .b(cd));
    
    DMux dmux2(.in(ab), .sel(sel[0]), .a(a), .b(b)); 
    DMux dmux3(.in(cd), .sel(sel[0]), .a(c), .b(d)); 
endmodule

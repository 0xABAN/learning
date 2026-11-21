// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Mux.sv
/** 
 * Multiplexor:
 * if (sel = 0) out = a, else out = b
 */

/*
* out_a = (not sel and a) -> just outputs a -> if a = 0, output is 0 
* out_b = (sel and b) -> just outputs b -> just outputs 0
* 
* (out_a and a) OR (out_b and b)
*
*
* */

module Mux(
    input logic a,
    input logic b,
    input logic sel,
    output logic out
);
    logic not_sel; 
    logic out_a; 
    logic out_b; 

    Not flip(.in(sel), .out(not_sel)); 

    And get_a_output(.a(not_sel), .b(a), .out(out_a));
    And get_b_output(.a(sel), .b(b), .out(out_b)); 

    Or combine(.a(out_a), .b(out_b), .out(out)); 
endmodule

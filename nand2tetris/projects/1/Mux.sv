// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Mux.sv
/** 
 * Multiplexor:
 * if (sel = 0) out = a, else out = b
 */

/*
* 
* if sel == 1 we want a 
*
* sel and a; (but this doesn't work, since a can be 0. at the same time,
* choosing sel xor a won't work bc we should allow a to be 1. 
*
* a_out = (sel XOR 1) AND a; output: yes, you can output a
* b_out = (sel AND 1) AND b; 
*
* 
* fin1 = a_out AND a; 
* fin2 = b_out AND b; 
*
* combine both with an OR 
*
* 
* 
* */

module Mux(
    input logic a,
    input logic b,
    input logic sel,
    output logic out
);
    logic flip_sel; 
    logic sel_matches_a; 
    logic sel_matches_b; 
    logic out_a; 
    logic out_b; 
    
    Not not_sel(.in(sel), .out(flip_sel)); 
    
    And check_a(.a(flip_sel), .b(1), .out(sel_matches_a)); 
    And check_b(.a(sel), .b(1), .out(sel_matches_b)); 
    
    And get_a_output(.a(sel_matches_a), .b(a), .out(out_a)); 
    And get_b_output(.a(sel_matches_b), .b(b), .out(out_b)); 

    Or combine(.a(out_a), .b(out_b), .out(out)); 
endmodule

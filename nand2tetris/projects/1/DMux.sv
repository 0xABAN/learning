// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/DMux.sv
/**
 * Demultiplexor:
 * [a, b] = [in, 0] if sel = 0
 *          [0, in] if sel = 1
 */

/*
* let a through only if sel = 0 
*
* a_out = (not sel and 1) 
* a_out AND in = a; 
*
* b_out = (sel and 1) 
* b_out AND in = b; 
*
* */

module DMux(
    input logic in,
    input logic sel,
    output logic a,
    output logic b
);
    logic flip_sel; 
    logic sel_matches_a; 
    logic sel_matches_b; 
    logic a_out; 
    logic b_out; 
    
    Not not_sel(.in(sel), .out(flip_sel));  
    
    And check_a(.a(flip_sel), .b(1), .out(sel_matches_a));
    And check_b(.a(sel), .b(1), .out(sel_matches_b));
    
    And get_a_output(.a(sel_matches_a), .b(in), .out(a)); 
    And get_b_output(.a(sel_matches_b), .b(in), .out(b)); 
endmodule

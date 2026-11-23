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
*
* a = (not sel) and in 
* b = sel and in
*
* 
* 
* */

module DMux(
    input logic in,
    input logic sel,
    output logic a,
    output logic b
);
    logic not_sel; 
    
    Not flip(.in(sel), .out(not_sel)); 
    And gate_a(.a(not_sel), .b(in), .out(a)); 
    And gate_b(.a(sel), .b(in), .out(b)); 
endmodule

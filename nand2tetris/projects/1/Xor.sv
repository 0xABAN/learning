// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Xor.sv
/**
 * Exclusive-or gate:
 */

// if a and not(b) or not(a) and b 
module Xor(
    input logic a,
    input logic b,
    output logic out
);
    logic not_a; 
    logic not_b; 
    
    Not invert_a(.in(a), .out(not_a));
    Not invert_b(.in(b), .out(not_b)); 

    logic cond1; 
    logic cond2; 

    And and_cond1(.a(a), .b(not_b), .out(cond1));
    And and_cond2(.a(not_a), .b(b), .out(cond2));
    
    Or or_cond3(.a(cond1), .b(cond2), .out(out));  
endmodule

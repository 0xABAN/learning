// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/1/Or8Way.sv
/**
 * 8-way Or gate: 
 * out = in[0] Or in[1] Or ... Or in[7]
 */

/*
* use a variable called "pivot" 
* each new bit gets or'd with that gate 
* 
*
*
* */

module Or8Way(
    input logic [7:0] in,
    output logic out
);
    logic [7:0] partial;     
    assign partial[0] = in[0];     
    
    for(genvar i = 1; i < 8; i++)
        Or or_gate(.a(in[i]), .b(partial[i-1]), .out(partial[i]));
    
    assign out = partial[7];  
endmodule

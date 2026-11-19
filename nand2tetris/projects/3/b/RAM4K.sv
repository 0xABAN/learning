// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/3/b/RAM4K.sv
/**
 * Memory of 4K 16-bit registers.
 * If load is asserted, the value of the register selected by
 * address is set to in; Otherwise, the value does not change.
 * The value of the selected register is emitted by out.
 */
module RAM4K(
    input logic clk,
    input logic [15:0] in,
    input logic load,
    input logic [11:0] address,
    output logic [15:0] out
);

endmodule

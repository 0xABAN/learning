module Xor_tb;
    logic a = '0;
    logic b = '0;
    logic out;
    int checks = 0;

    Xor dut(
        .a(a),
        .b(b),
        .out(out)
    );

    task automatic check_value(
        input string signal_name,
        input logic [15:0] actual,
        input logic [15:0] expected
    );
        if (actual !== expected)
            $fatal(1, "Check %0d: %s expected 0x%04h, got 0x%04h", checks + 1, signal_name, expected, actual);
        checks++;
    endtask

    initial begin
        #1;
        a = 1'h0;
        b = 1'h0;
        #1;

        check_value("out (row 1)", {15'b0, out}, 16'h0);

        a = 1'h0;
        b = 1'h1;
        #1;

        check_value("out (row 2)", {15'b0, out}, 16'h1);

        a = 1'h1;
        b = 1'h0;
        #1;

        check_value("out (row 3)", {15'b0, out}, 16'h1);

        a = 1'h1;
        b = 1'h1;
        #1;

        check_value("out (row 4)", {15'b0, out}, 16'h0);

        $display("PASS Xor_tb: %0d checks", checks);
        $finish;
    end
endmodule

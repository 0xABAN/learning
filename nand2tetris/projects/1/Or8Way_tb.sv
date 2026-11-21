module Or8Way_tb;
    logic [7:0] in = '0;
    logic out;
    int checks = 0;

    Or8Way dut(
        .in(in),
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
        in = 8'h0;
        #1;

        check_value("out (row 1)", {15'b0, out}, 16'h0);

        in = 8'hff;
        #1;

        check_value("out (row 2)", {15'b0, out}, 16'h1);

        in = 8'h10;
        #1;

        check_value("out (row 3)", {15'b0, out}, 16'h1);

        in = 8'h1;
        #1;

        check_value("out (row 4)", {15'b0, out}, 16'h1);

        in = 8'h26;
        #1;

        check_value("out (row 5)", {15'b0, out}, 16'h1);

        $display("PASS Or8Way_tb: %0d checks", checks);
        $finish;
    end
endmodule

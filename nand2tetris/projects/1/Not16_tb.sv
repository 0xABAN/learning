module Not16_tb;
    logic [15:0] in = '0;
    logic [15:0] out;
    int checks = 0;

    Not16 dut(
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
        in = 16'h0;
        #1;

        check_value("out (row 1)", out, 16'hffff);

        in = 16'hffff;
        #1;

        check_value("out (row 2)", out, 16'h0);

        in = 16'haaaa;
        #1;

        check_value("out (row 3)", out, 16'h5555);

        in = 16'h3cc3;
        #1;

        check_value("out (row 4)", out, 16'hc33c);

        in = 16'h1234;
        #1;

        check_value("out (row 5)", out, 16'hedcb);

        $display("PASS Not16_tb: %0d checks", checks);
        $finish;
    end
endmodule

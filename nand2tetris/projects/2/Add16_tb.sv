module Add16_tb;
    logic [15:0] a = '0;
    logic [15:0] b = '0;
    logic [15:0] out;
    int checks = 0;

    Add16 dut(
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
        a = 16'h0;
        b = 16'h0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        a = 16'h0;
        b = 16'hffff;
        #1;

        check_value("out (row 2)", out, 16'hffff);

        a = 16'hffff;
        b = 16'hffff;
        #1;

        check_value("out (row 3)", out, 16'hfffe);

        a = 16'haaaa;
        b = 16'h5555;
        #1;

        check_value("out (row 4)", out, 16'hffff);

        a = 16'h3cc3;
        b = 16'hff0;
        #1;

        check_value("out (row 5)", out, 16'h4cb3);

        a = 16'h1234;
        b = 16'h9876;
        #1;

        check_value("out (row 6)", out, 16'haaaa);

        $display("PASS Add16_tb: %0d checks", checks);
        $finish;
    end
endmodule

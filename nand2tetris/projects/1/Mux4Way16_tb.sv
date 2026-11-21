module Mux4Way16_tb;
    logic [15:0] a = '0;
    logic [15:0] b = '0;
    logic [15:0] c = '0;
    logic [15:0] d = '0;
    logic [1:0] sel = '0;
    logic [15:0] out;
    int checks = 0;

    Mux4Way16 dut(
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .sel(sel),
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
        c = 16'h0;
        d = 16'h0;
        sel = 2'h0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        sel = 2'h1;
        #1;

        check_value("out (row 2)", out, 16'h0);

        sel = 2'h2;
        #1;

        check_value("out (row 3)", out, 16'h0);

        sel = 2'h3;
        #1;

        check_value("out (row 4)", out, 16'h0);

        a = 16'h1234;
        b = 16'h9876;
        c = 16'haaaa;
        d = 16'h5555;
        sel = 2'h0;
        #1;

        check_value("out (row 5)", out, 16'h1234);

        sel = 2'h1;
        #1;

        check_value("out (row 6)", out, 16'h9876);

        sel = 2'h2;
        #1;

        check_value("out (row 7)", out, 16'haaaa);

        sel = 2'h3;
        #1;

        check_value("out (row 8)", out, 16'h5555);

        $display("PASS Mux4Way16_tb: %0d checks", checks);
        $finish;
    end
endmodule

module Mux8Way16_tb;
    logic [15:0] a = '0;
    logic [15:0] b = '0;
    logic [15:0] c = '0;
    logic [15:0] d = '0;
    logic [15:0] e = '0;
    logic [15:0] f = '0;
    logic [15:0] g = '0;
    logic [15:0] h = '0;
    logic [2:0] sel = '0;
    logic [15:0] out;
    int checks = 0;

    Mux8Way16 dut(
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .e(e),
        .f(f),
        .g(g),
        .h(h),
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
        e = 16'h0;
        f = 16'h0;
        g = 16'h0;
        h = 16'h0;
        sel = 3'h0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        sel = 3'h1;
        #1;

        check_value("out (row 2)", out, 16'h0);

        sel = 3'h2;
        #1;

        check_value("out (row 3)", out, 16'h0);

        sel = 3'h3;
        #1;

        check_value("out (row 4)", out, 16'h0);

        sel = 3'h4;
        #1;

        check_value("out (row 5)", out, 16'h0);

        sel = 3'h5;
        #1;

        check_value("out (row 6)", out, 16'h0);

        sel = 3'h6;
        #1;

        check_value("out (row 7)", out, 16'h0);

        sel = 3'h7;
        #1;

        check_value("out (row 8)", out, 16'h0);

        a = 16'h1234;
        b = 16'h2345;
        c = 16'h3456;
        d = 16'h4567;
        e = 16'h5678;
        f = 16'h6789;
        g = 16'h789a;
        h = 16'h89ab;
        sel = 3'h0;
        #1;

        check_value("out (row 9)", out, 16'h1234);

        sel = 3'h1;
        #1;

        check_value("out (row 10)", out, 16'h2345);

        sel = 3'h2;
        #1;

        check_value("out (row 11)", out, 16'h3456);

        sel = 3'h3;
        #1;

        check_value("out (row 12)", out, 16'h4567);

        sel = 3'h4;
        #1;

        check_value("out (row 13)", out, 16'h5678);

        sel = 3'h5;
        #1;

        check_value("out (row 14)", out, 16'h6789);

        sel = 3'h6;
        #1;

        check_value("out (row 15)", out, 16'h789a);

        sel = 3'h7;
        #1;

        check_value("out (row 16)", out, 16'h89ab);

        $display("PASS Mux8Way16_tb: %0d checks", checks);
        $finish;
    end
endmodule

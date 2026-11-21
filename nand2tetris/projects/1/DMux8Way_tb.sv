module DMux8Way_tb;
    logic in = '0;
    logic [2:0] sel = '0;
    logic a;
    logic b;
    logic c;
    logic d;
    logic e;
    logic f;
    logic g;
    logic h;
    int checks = 0;

    DMux8Way dut(
        .in(in),
        .sel(sel),
        .a(a),
        .b(b),
        .c(c),
        .d(d),
        .e(e),
        .f(f),
        .g(g),
        .h(h)
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
        in = 1'h0;
        sel = 3'h0;
        #1;

        check_value("a (row 1)", {15'b0, a}, 16'h0);
        check_value("b (row 1)", {15'b0, b}, 16'h0);
        check_value("c (row 1)", {15'b0, c}, 16'h0);
        check_value("d (row 1)", {15'b0, d}, 16'h0);
        check_value("e (row 1)", {15'b0, e}, 16'h0);
        check_value("f (row 1)", {15'b0, f}, 16'h0);
        check_value("g (row 1)", {15'b0, g}, 16'h0);
        check_value("h (row 1)", {15'b0, h}, 16'h0);

        sel = 3'h1;
        #1;

        check_value("a (row 2)", {15'b0, a}, 16'h0);
        check_value("b (row 2)", {15'b0, b}, 16'h0);
        check_value("c (row 2)", {15'b0, c}, 16'h0);
        check_value("d (row 2)", {15'b0, d}, 16'h0);
        check_value("e (row 2)", {15'b0, e}, 16'h0);
        check_value("f (row 2)", {15'b0, f}, 16'h0);
        check_value("g (row 2)", {15'b0, g}, 16'h0);
        check_value("h (row 2)", {15'b0, h}, 16'h0);

        sel = 3'h2;
        #1;

        check_value("a (row 3)", {15'b0, a}, 16'h0);
        check_value("b (row 3)", {15'b0, b}, 16'h0);
        check_value("c (row 3)", {15'b0, c}, 16'h0);
        check_value("d (row 3)", {15'b0, d}, 16'h0);
        check_value("e (row 3)", {15'b0, e}, 16'h0);
        check_value("f (row 3)", {15'b0, f}, 16'h0);
        check_value("g (row 3)", {15'b0, g}, 16'h0);
        check_value("h (row 3)", {15'b0, h}, 16'h0);

        sel = 3'h3;
        #1;

        check_value("a (row 4)", {15'b0, a}, 16'h0);
        check_value("b (row 4)", {15'b0, b}, 16'h0);
        check_value("c (row 4)", {15'b0, c}, 16'h0);
        check_value("d (row 4)", {15'b0, d}, 16'h0);
        check_value("e (row 4)", {15'b0, e}, 16'h0);
        check_value("f (row 4)", {15'b0, f}, 16'h0);
        check_value("g (row 4)", {15'b0, g}, 16'h0);
        check_value("h (row 4)", {15'b0, h}, 16'h0);

        sel = 3'h4;
        #1;

        check_value("a (row 5)", {15'b0, a}, 16'h0);
        check_value("b (row 5)", {15'b0, b}, 16'h0);
        check_value("c (row 5)", {15'b0, c}, 16'h0);
        check_value("d (row 5)", {15'b0, d}, 16'h0);
        check_value("e (row 5)", {15'b0, e}, 16'h0);
        check_value("f (row 5)", {15'b0, f}, 16'h0);
        check_value("g (row 5)", {15'b0, g}, 16'h0);
        check_value("h (row 5)", {15'b0, h}, 16'h0);

        sel = 3'h5;
        #1;

        check_value("a (row 6)", {15'b0, a}, 16'h0);
        check_value("b (row 6)", {15'b0, b}, 16'h0);
        check_value("c (row 6)", {15'b0, c}, 16'h0);
        check_value("d (row 6)", {15'b0, d}, 16'h0);
        check_value("e (row 6)", {15'b0, e}, 16'h0);
        check_value("f (row 6)", {15'b0, f}, 16'h0);
        check_value("g (row 6)", {15'b0, g}, 16'h0);
        check_value("h (row 6)", {15'b0, h}, 16'h0);

        sel = 3'h6;
        #1;

        check_value("a (row 7)", {15'b0, a}, 16'h0);
        check_value("b (row 7)", {15'b0, b}, 16'h0);
        check_value("c (row 7)", {15'b0, c}, 16'h0);
        check_value("d (row 7)", {15'b0, d}, 16'h0);
        check_value("e (row 7)", {15'b0, e}, 16'h0);
        check_value("f (row 7)", {15'b0, f}, 16'h0);
        check_value("g (row 7)", {15'b0, g}, 16'h0);
        check_value("h (row 7)", {15'b0, h}, 16'h0);

        sel = 3'h7;
        #1;

        check_value("a (row 8)", {15'b0, a}, 16'h0);
        check_value("b (row 8)", {15'b0, b}, 16'h0);
        check_value("c (row 8)", {15'b0, c}, 16'h0);
        check_value("d (row 8)", {15'b0, d}, 16'h0);
        check_value("e (row 8)", {15'b0, e}, 16'h0);
        check_value("f (row 8)", {15'b0, f}, 16'h0);
        check_value("g (row 8)", {15'b0, g}, 16'h0);
        check_value("h (row 8)", {15'b0, h}, 16'h0);

        in = 1'h1;
        sel = 3'h0;
        #1;

        check_value("a (row 9)", {15'b0, a}, 16'h1);
        check_value("b (row 9)", {15'b0, b}, 16'h0);
        check_value("c (row 9)", {15'b0, c}, 16'h0);
        check_value("d (row 9)", {15'b0, d}, 16'h0);
        check_value("e (row 9)", {15'b0, e}, 16'h0);
        check_value("f (row 9)", {15'b0, f}, 16'h0);
        check_value("g (row 9)", {15'b0, g}, 16'h0);
        check_value("h (row 9)", {15'b0, h}, 16'h0);

        sel = 3'h1;
        #1;

        check_value("a (row 10)", {15'b0, a}, 16'h0);
        check_value("b (row 10)", {15'b0, b}, 16'h1);
        check_value("c (row 10)", {15'b0, c}, 16'h0);
        check_value("d (row 10)", {15'b0, d}, 16'h0);
        check_value("e (row 10)", {15'b0, e}, 16'h0);
        check_value("f (row 10)", {15'b0, f}, 16'h0);
        check_value("g (row 10)", {15'b0, g}, 16'h0);
        check_value("h (row 10)", {15'b0, h}, 16'h0);

        sel = 3'h2;
        #1;

        check_value("a (row 11)", {15'b0, a}, 16'h0);
        check_value("b (row 11)", {15'b0, b}, 16'h0);
        check_value("c (row 11)", {15'b0, c}, 16'h1);
        check_value("d (row 11)", {15'b0, d}, 16'h0);
        check_value("e (row 11)", {15'b0, e}, 16'h0);
        check_value("f (row 11)", {15'b0, f}, 16'h0);
        check_value("g (row 11)", {15'b0, g}, 16'h0);
        check_value("h (row 11)", {15'b0, h}, 16'h0);

        sel = 3'h3;
        #1;

        check_value("a (row 12)", {15'b0, a}, 16'h0);
        check_value("b (row 12)", {15'b0, b}, 16'h0);
        check_value("c (row 12)", {15'b0, c}, 16'h0);
        check_value("d (row 12)", {15'b0, d}, 16'h1);
        check_value("e (row 12)", {15'b0, e}, 16'h0);
        check_value("f (row 12)", {15'b0, f}, 16'h0);
        check_value("g (row 12)", {15'b0, g}, 16'h0);
        check_value("h (row 12)", {15'b0, h}, 16'h0);

        sel = 3'h4;
        #1;

        check_value("a (row 13)", {15'b0, a}, 16'h0);
        check_value("b (row 13)", {15'b0, b}, 16'h0);
        check_value("c (row 13)", {15'b0, c}, 16'h0);
        check_value("d (row 13)", {15'b0, d}, 16'h0);
        check_value("e (row 13)", {15'b0, e}, 16'h1);
        check_value("f (row 13)", {15'b0, f}, 16'h0);
        check_value("g (row 13)", {15'b0, g}, 16'h0);
        check_value("h (row 13)", {15'b0, h}, 16'h0);

        sel = 3'h5;
        #1;

        check_value("a (row 14)", {15'b0, a}, 16'h0);
        check_value("b (row 14)", {15'b0, b}, 16'h0);
        check_value("c (row 14)", {15'b0, c}, 16'h0);
        check_value("d (row 14)", {15'b0, d}, 16'h0);
        check_value("e (row 14)", {15'b0, e}, 16'h0);
        check_value("f (row 14)", {15'b0, f}, 16'h1);
        check_value("g (row 14)", {15'b0, g}, 16'h0);
        check_value("h (row 14)", {15'b0, h}, 16'h0);

        sel = 3'h6;
        #1;

        check_value("a (row 15)", {15'b0, a}, 16'h0);
        check_value("b (row 15)", {15'b0, b}, 16'h0);
        check_value("c (row 15)", {15'b0, c}, 16'h0);
        check_value("d (row 15)", {15'b0, d}, 16'h0);
        check_value("e (row 15)", {15'b0, e}, 16'h0);
        check_value("f (row 15)", {15'b0, f}, 16'h0);
        check_value("g (row 15)", {15'b0, g}, 16'h1);
        check_value("h (row 15)", {15'b0, h}, 16'h0);

        sel = 3'h7;
        #1;

        check_value("a (row 16)", {15'b0, a}, 16'h0);
        check_value("b (row 16)", {15'b0, b}, 16'h0);
        check_value("c (row 16)", {15'b0, c}, 16'h0);
        check_value("d (row 16)", {15'b0, d}, 16'h0);
        check_value("e (row 16)", {15'b0, e}, 16'h0);
        check_value("f (row 16)", {15'b0, f}, 16'h0);
        check_value("g (row 16)", {15'b0, g}, 16'h0);
        check_value("h (row 16)", {15'b0, h}, 16'h1);

        $display("PASS DMux8Way_tb: %0d checks", checks);
        $finish;
    end
endmodule

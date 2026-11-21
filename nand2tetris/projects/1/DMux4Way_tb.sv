module DMux4Way_tb;
    logic in = '0;
    logic [1:0] sel = '0;
    logic a;
    logic b;
    logic c;
    logic d;
    int checks = 0;

    DMux4Way dut(
        .in(in),
        .sel(sel),
        .a(a),
        .b(b),
        .c(c),
        .d(d)
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
        sel = 2'h0;
        #1;

        check_value("a (row 1)", {15'b0, a}, 16'h0);
        check_value("b (row 1)", {15'b0, b}, 16'h0);
        check_value("c (row 1)", {15'b0, c}, 16'h0);
        check_value("d (row 1)", {15'b0, d}, 16'h0);

        sel = 2'h1;
        #1;

        check_value("a (row 2)", {15'b0, a}, 16'h0);
        check_value("b (row 2)", {15'b0, b}, 16'h0);
        check_value("c (row 2)", {15'b0, c}, 16'h0);
        check_value("d (row 2)", {15'b0, d}, 16'h0);

        sel = 2'h2;
        #1;

        check_value("a (row 3)", {15'b0, a}, 16'h0);
        check_value("b (row 3)", {15'b0, b}, 16'h0);
        check_value("c (row 3)", {15'b0, c}, 16'h0);
        check_value("d (row 3)", {15'b0, d}, 16'h0);

        sel = 2'h3;
        #1;

        check_value("a (row 4)", {15'b0, a}, 16'h0);
        check_value("b (row 4)", {15'b0, b}, 16'h0);
        check_value("c (row 4)", {15'b0, c}, 16'h0);
        check_value("d (row 4)", {15'b0, d}, 16'h0);

        in = 1'h1;
        sel = 2'h0;
        #1;

        check_value("a (row 5)", {15'b0, a}, 16'h1);
        check_value("b (row 5)", {15'b0, b}, 16'h0);
        check_value("c (row 5)", {15'b0, c}, 16'h0);
        check_value("d (row 5)", {15'b0, d}, 16'h0);

        sel = 2'h1;
        #1;

        check_value("a (row 6)", {15'b0, a}, 16'h0);
        check_value("b (row 6)", {15'b0, b}, 16'h1);
        check_value("c (row 6)", {15'b0, c}, 16'h0);
        check_value("d (row 6)", {15'b0, d}, 16'h0);

        sel = 2'h2;
        #1;

        check_value("a (row 7)", {15'b0, a}, 16'h0);
        check_value("b (row 7)", {15'b0, b}, 16'h0);
        check_value("c (row 7)", {15'b0, c}, 16'h1);
        check_value("d (row 7)", {15'b0, d}, 16'h0);

        sel = 2'h3;
        #1;

        check_value("a (row 8)", {15'b0, a}, 16'h0);
        check_value("b (row 8)", {15'b0, b}, 16'h0);
        check_value("c (row 8)", {15'b0, c}, 16'h0);
        check_value("d (row 8)", {15'b0, d}, 16'h1);

        $display("PASS DMux4Way_tb: %0d checks", checks);
        $finish;
    end
endmodule

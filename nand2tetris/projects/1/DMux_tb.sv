module DMux_tb;
    logic in = '0;
    logic sel = '0;
    logic a;
    logic b;
    int checks = 0;

    DMux dut(
        .in(in),
        .sel(sel),
        .a(a),
        .b(b)
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
        sel = 1'h0;
        #1;

        check_value("a (row 1)", {15'b0, a}, 16'h0);
        check_value("b (row 1)", {15'b0, b}, 16'h0);

        sel = 1'h1;
        #1;

        check_value("a (row 2)", {15'b0, a}, 16'h0);
        check_value("b (row 2)", {15'b0, b}, 16'h0);

        in = 1'h1;
        sel = 1'h0;
        #1;

        check_value("a (row 3)", {15'b0, a}, 16'h1);
        check_value("b (row 3)", {15'b0, b}, 16'h0);

        sel = 1'h1;
        #1;

        check_value("a (row 4)", {15'b0, a}, 16'h0);
        check_value("b (row 4)", {15'b0, b}, 16'h1);

        $display("PASS DMux_tb: %0d checks", checks);
        $finish;
    end
endmodule

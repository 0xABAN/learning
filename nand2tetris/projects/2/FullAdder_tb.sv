module FullAdder_tb;
    logic a = '0;
    logic b = '0;
    logic c = '0;
    logic sum;
    logic carry;
    int checks = 0;

    FullAdder dut(
        .a(a),
        .b(b),
        .c(c),
        .sum(sum),
        .carry(carry)
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
        c = 1'h0;
        #1;

        check_value("sum (row 1)", {15'b0, sum}, 16'h0);
        check_value("carry (row 1)", {15'b0, carry}, 16'h0);

        c = 1'h1;
        #1;

        check_value("sum (row 2)", {15'b0, sum}, 16'h1);
        check_value("carry (row 2)", {15'b0, carry}, 16'h0);

        b = 1'h1;
        c = 1'h0;
        #1;

        check_value("sum (row 3)", {15'b0, sum}, 16'h1);
        check_value("carry (row 3)", {15'b0, carry}, 16'h0);

        c = 1'h1;
        #1;

        check_value("sum (row 4)", {15'b0, sum}, 16'h0);
        check_value("carry (row 4)", {15'b0, carry}, 16'h1);

        a = 1'h1;
        b = 1'h0;
        c = 1'h0;
        #1;

        check_value("sum (row 5)", {15'b0, sum}, 16'h1);
        check_value("carry (row 5)", {15'b0, carry}, 16'h0);

        c = 1'h1;
        #1;

        check_value("sum (row 6)", {15'b0, sum}, 16'h0);
        check_value("carry (row 6)", {15'b0, carry}, 16'h1);

        b = 1'h1;
        c = 1'h0;
        #1;

        check_value("sum (row 7)", {15'b0, sum}, 16'h0);
        check_value("carry (row 7)", {15'b0, carry}, 16'h1);

        c = 1'h1;
        #1;

        check_value("sum (row 8)", {15'b0, sum}, 16'h1);
        check_value("carry (row 8)", {15'b0, carry}, 16'h1);

        $display("PASS FullAdder_tb: %0d checks", checks);
        $finish;
    end
endmodule

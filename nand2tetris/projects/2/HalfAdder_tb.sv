module HalfAdder_tb;
    logic a = '0;
    logic b = '0;
    logic sum;
    logic carry;
    int checks = 0;

    HalfAdder dut(
        .a(a),
        .b(b),
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
        #1;

        check_value("sum (row 1)", {15'b0, sum}, 16'h0);
        check_value("carry (row 1)", {15'b0, carry}, 16'h0);

        a = 1'h0;
        b = 1'h1;
        #1;

        check_value("sum (row 2)", {15'b0, sum}, 16'h1);
        check_value("carry (row 2)", {15'b0, carry}, 16'h0);

        a = 1'h1;
        b = 1'h0;
        #1;

        check_value("sum (row 3)", {15'b0, sum}, 16'h1);
        check_value("carry (row 3)", {15'b0, carry}, 16'h0);

        a = 1'h1;
        b = 1'h1;
        #1;

        check_value("sum (row 4)", {15'b0, sum}, 16'h0);
        check_value("carry (row 4)", {15'b0, carry}, 16'h1);

        $display("PASS HalfAdder_tb: %0d checks", checks);
        $finish;
    end
endmodule

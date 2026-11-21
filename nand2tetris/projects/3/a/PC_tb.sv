module PC_tb;
    logic clk = '0;
    logic [15:0] in = '0;
    logic inc = '0;
    logic load = '0;
    logic reset = '0;
    logic [15:0] out;
    int checks = 0;

    PC dut(
        .clk(clk),
        .in(in),
        .inc(inc),
        .load(load),
        .reset(reset),
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
        reset = 1'h0;
        load = 1'h0;
        inc = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 2)", out, 16'h0);

        inc = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 3)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 4)", out, 16'h1);

        in = 16'h8285;
        clk = 0;
        #1;

        check_value("out (row 5)", out, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 6)", out, 16'h2);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 7)", out, 16'h2);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 8)", out, 16'h8285);

        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 9)", out, 16'h8285);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 10)", out, 16'h8286);

        clk = 0;
        #1;

        check_value("out (row 11)", out, 16'h8286);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 12)", out, 16'h8287);

        in = 16'h3039;
        load = 1'h1;
        inc = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 13)", out, 16'h8287);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 14)", out, 16'h3039);

        reset = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 15)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 16)", out, 16'h0);

        reset = 1'h0;
        inc = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 17)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 18)", out, 16'h3039);

        reset = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 19)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 20)", out, 16'h0);

        reset = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 21)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 22)", out, 16'h1);

        reset = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 23)", out, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 24)", out, 16'h0);

        in = 16'h0;
        reset = 1'h0;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 25)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 26)", out, 16'h0);

        load = 1'h0;
        inc = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 27)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 28)", out, 16'h1);

        in = 16'h56ce;
        reset = 1'h1;
        inc = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 29)", out, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 30)", out, 16'h0);

        $display("PASS PC_tb: %0d checks", checks);
        $finish;
    end
endmodule

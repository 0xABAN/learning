module Bit_tb;
    logic clk = '0;
    logic in = '0;
    logic load = '0;
    logic out;
    int checks = 0;

    Bit dut(
        .clk(clk),
        .in(in),
        .load(load),
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
        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 1)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 2)", {15'b0, out}, 16'h0);

        in = 1'h0;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 3)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 4)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 5)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 6)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 7)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 8)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 9)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 10)", {15'b0, out}, 16'h1);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 11)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 12)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 13)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 14)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 15)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 16)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 17)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 18)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 19)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 20)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 21)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 22)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 23)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 24)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 25)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 26)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 27)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 28)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 29)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 30)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 31)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 32)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 33)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 34)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 35)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 36)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 37)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 38)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 39)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 40)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 41)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 42)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 43)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 44)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 45)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 46)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 47)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 48)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 49)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 50)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 51)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 52)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 53)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 54)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 55)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 56)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 57)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 58)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 59)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 60)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 61)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 62)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 63)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 64)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 65)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 66)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 67)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 68)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 69)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 70)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 71)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 72)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 73)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 74)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 75)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 76)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 77)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 78)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 79)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 80)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 81)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 82)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 83)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 84)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 85)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 86)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 87)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 88)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 89)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 90)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 91)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 92)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 93)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 94)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 95)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 96)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 97)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 98)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 99)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 100)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 101)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 102)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 103)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 104)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 105)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 106)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 107)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 108)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 109)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 110)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 111)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 112)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 113)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 114)", {15'b0, out}, 16'h1);

        in = 1'h0;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 115)", {15'b0, out}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 116)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 117)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 118)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 119)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 120)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 121)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 122)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 123)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 124)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 125)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 126)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 127)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 128)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 129)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 130)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 131)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 132)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 133)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 134)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 135)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 136)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 137)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 138)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 139)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 140)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 141)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 142)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 143)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 144)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 145)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 146)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 147)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 148)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 149)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 150)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 151)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 152)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 153)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 154)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 155)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 156)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 157)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 158)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 159)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 160)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 161)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 162)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 163)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 164)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 165)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 166)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 167)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 168)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 169)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 170)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 171)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 172)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 173)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 174)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 175)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 176)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 177)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 178)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 179)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 180)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 181)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 182)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 183)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 184)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 185)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 186)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 187)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 188)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 189)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 190)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 191)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 192)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 193)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 194)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 195)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 196)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 197)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 198)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 199)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 200)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 201)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 202)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 203)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 204)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 205)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 206)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 207)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 208)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 209)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 210)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 211)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 212)", {15'b0, out}, 16'h0);

        in = 1'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 213)", {15'b0, out}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 214)", {15'b0, out}, 16'h0);

        $display("PASS Bit_tb: %0d checks", checks);
        $finish;
    end
endmodule

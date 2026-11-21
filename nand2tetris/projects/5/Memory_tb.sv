module Memory_tb;
    logic clk = '0;
    logic [15:0] in = '0;
    logic load = '0;
    logic [14:0] address = '0;
    logic [15:0] out;
    int checks = 0;

    Memory dut(
        .clk(clk),
        .in(in),
        .load(load),
        .address(address),
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
        in = 16'h3039;
        load = 1'h1;
        address = 15'h2000;
        clk = 0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 2)", out, 16'h3039);

        address = 15'h4000;
        clk = 0;
        #1;

        check_value("out (row 3)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 4)", out, 16'h3039);

        in = 16'hffff;
        load = 1'h1;
        address = 15'h0;
        clk = 0;
        #1;

        check_value("out (row 5)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 6)", out, 16'hffff);

        in = 16'h270f;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 7)", out, 16'hffff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 8)", out, 16'hffff);

        address = 15'h2000;
        #1;

        check_value("out (row 9)", out, 16'h3039);

        address = 15'h4000;
        #1;

        check_value("out (row 10)", out, 16'h3039);

        in = 16'h3039;
        load = 1'h1;
        address = 15'h0;
        clk = 0;
        #1;

        check_value("out (row 11)", out, 16'hffff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 12)", out, 16'h3039);

        address = 15'h4000;
        clk = 0;
        #1;

        check_value("out (row 13)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 14)", out, 16'h3039);

        in = 16'h8ae;
        load = 1'h1;
        address = 15'h2000;
        clk = 0;
        #1;

        check_value("out (row 15)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 16)", out, 16'h8ae);

        in = 16'h270f;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 17)", out, 16'h8ae);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 18)", out, 16'h8ae);

        address = 15'h0;
        #1;

        check_value("out (row 19)", out, 16'h3039);

        address = 15'h4000;
        #1;

        check_value("out (row 20)", out, 16'h3039);

        load = 1'h0;
        address = 15'h1;
        #1;

        check_value("out (row 21)", out, 16'h0);

        address = 15'h2;
        #1;

        check_value("out (row 22)", out, 16'h0);

        address = 15'h4;
        #1;

        check_value("out (row 23)", out, 16'h0);

        address = 15'h8;
        #1;

        check_value("out (row 24)", out, 16'h0);

        address = 15'h10;
        #1;

        check_value("out (row 25)", out, 16'h0);

        address = 15'h20;
        #1;

        check_value("out (row 26)", out, 16'h0);

        address = 15'h40;
        #1;

        check_value("out (row 27)", out, 16'h0);

        address = 15'h80;
        #1;

        check_value("out (row 28)", out, 16'h0);

        address = 15'h100;
        #1;

        check_value("out (row 29)", out, 16'h0);

        address = 15'h200;
        #1;

        check_value("out (row 30)", out, 16'h0);

        address = 15'h400;
        #1;

        check_value("out (row 31)", out, 16'h0);

        address = 15'h800;
        #1;

        check_value("out (row 32)", out, 16'h0);

        address = 15'h1000;
        #1;

        check_value("out (row 33)", out, 16'h0);

        address = 15'h2000;
        #1;

        check_value("out (row 34)", out, 16'h8ae);

        address = 15'h1234;
        in = 16'h4d2;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 35)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 36)", out, 16'h4d2);

        load = 1'h0;
        address = 15'h2234;
        #1;

        check_value("out (row 37)", out, 16'h0);

        address = 15'h6234;
        #1;

        check_value("out (row 38)", out, 16'h0);

        address = 15'h2345;
        in = 16'h929;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 39)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 40)", out, 16'h929);

        load = 1'h0;
        address = 15'h345;
        #1;

        check_value("out (row 41)", out, 16'h0);

        address = 15'h4345;
        #1;

        check_value("out (row 42)", out, 16'h0);

        in = 16'h0;
        load = 1'h1;
        address = 15'h4000;
        clk = 0;
        #1;

        check_value("out (row 43)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 44)", out, 16'h0);

        address = 15'h6000;
        force dut.keyboard.out = 16'd75;
        #1;

        check_value("out (row 45)", out, 16'h4b);

        in = 16'h3039;
        load = 1'h1;
        address = 15'hfcf;
        clk = 0;
        #1;

        check_value("out (row 46)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 47)", out, 16'h3039);

        address = 15'h2fcf;
        clk = 0;
        #1;

        check_value("out (row 48)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 49)", out, 16'h3039);

        load = 1'h1;
        in = 16'hffff;
        address = 15'h4fcf;
        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 50)", out, 16'hffff);

        address = 15'h504f;
        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 51)", out, 16'hffff);

        address = 15'hfcf;
        #1;

        check_value("out (row 52)", out, 16'h3039);

        address = 15'h2fcf;
        #1;

        check_value("out (row 53)", out, 16'h3039);

        load = 1'h0;
        address = 15'h4fce;
        #1;

        check_value("out (row 54)", out, 16'h0);

        address = 15'h4fcd;
        #1;

        check_value("out (row 55)", out, 16'h0);

        address = 15'h4fcb;
        #1;

        check_value("out (row 56)", out, 16'h0);

        address = 15'h4fc7;
        #1;

        check_value("out (row 57)", out, 16'h0);

        address = 15'h4fdf;
        #1;

        check_value("out (row 58)", out, 16'h0);

        address = 15'h4fef;
        #1;

        check_value("out (row 59)", out, 16'h0);

        address = 15'h4f8f;
        #1;

        check_value("out (row 60)", out, 16'h0);

        address = 15'h4f4f;
        #1;

        check_value("out (row 61)", out, 16'h0);

        address = 15'h4ecf;
        #1;

        check_value("out (row 62)", out, 16'h0);

        address = 15'h4dcf;
        #1;

        check_value("out (row 63)", out, 16'h0);

        address = 15'h4bcf;
        #1;

        check_value("out (row 64)", out, 16'h0);

        address = 15'h47cf;
        #1;

        check_value("out (row 65)", out, 16'h0);

        address = 15'h5fcf;
        #1;

        check_value("out (row 66)", out, 16'h0);

        load = 1'h0;
        address = 15'h6000;
        force dut.keyboard.out = 16'd89;
        #1;

        check_value("out (row 67)", out, 16'h59);

        release dut.keyboard.out;
        $display("PASS Memory_tb: %0d checks", checks);
        $finish;
    end
endmodule

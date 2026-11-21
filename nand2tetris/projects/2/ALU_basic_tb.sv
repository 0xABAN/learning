module ALU_basic_tb;
    logic [15:0] x = '0;
    logic [15:0] y = '0;
    logic zx = '0;
    logic nx = '0;
    logic zy = '0;
    logic ny = '0;
    logic f = '0;
    logic no = '0;
    logic [15:0] out;
    logic zr;
    logic ng;
    int checks = 0;

    ALU dut(
        .x(x),
        .y(y),
        .zx(zx),
        .nx(nx),
        .zy(zy),
        .ny(ny),
        .f(f),
        .no(no),
        .out(out),
        .zr(zr),
        .ng(ng)
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
        x = 16'h0;
        y = 16'hffff;
        zx = 1'h1;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 2)", out, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 3)", out, 16'hffff);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 4)", out, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 5)", out, 16'hffff);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 6)", out, 16'hffff);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 7)", out, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 8)", out, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 9)", out, 16'h1);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 10)", out, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 11)", out, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 12)", out, 16'hffff);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 13)", out, 16'hfffe);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 14)", out, 16'hffff);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 15)", out, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 16)", out, 16'hffff);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 17)", out, 16'h0);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 18)", out, 16'hffff);

        x = 16'h5ba0;
        y = 16'h1ed2;
        zx = 1'h1;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 19)", out, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 20)", out, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 21)", out, 16'hffff);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 22)", out, 16'h5ba0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 23)", out, 16'h1ed2);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 24)", out, 16'ha45f);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 25)", out, 16'he12d);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 26)", out, 16'ha460);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 27)", out, 16'he12e);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 28)", out, 16'h5ba1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 29)", out, 16'h1ed3);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 30)", out, 16'h5b9f);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 31)", out, 16'h1ed1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 32)", out, 16'h7a72);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 33)", out, 16'h3cce);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 34)", out, 16'hc332);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 35)", out, 16'h1a80);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 36)", out, 16'h5ff2);

        $display("PASS ALU_basic_tb: %0d checks", checks);
        $finish;
    end
endmodule

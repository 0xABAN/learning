module ALU_tb;
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
        check_value("zr (row 1)", {15'b0, zr}, 16'h1);
        check_value("ng (row 1)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 2)", out, 16'h1);
        check_value("zr (row 2)", {15'b0, zr}, 16'h0);
        check_value("ng (row 2)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 3)", out, 16'hffff);
        check_value("zr (row 3)", {15'b0, zr}, 16'h0);
        check_value("ng (row 3)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 4)", out, 16'h0);
        check_value("zr (row 4)", {15'b0, zr}, 16'h1);
        check_value("ng (row 4)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 5)", out, 16'hffff);
        check_value("zr (row 5)", {15'b0, zr}, 16'h0);
        check_value("ng (row 5)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 6)", out, 16'hffff);
        check_value("zr (row 6)", {15'b0, zr}, 16'h0);
        check_value("ng (row 6)", {15'b0, ng}, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 7)", out, 16'h0);
        check_value("zr (row 7)", {15'b0, zr}, 16'h1);
        check_value("ng (row 7)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 8)", out, 16'h0);
        check_value("zr (row 8)", {15'b0, zr}, 16'h1);
        check_value("ng (row 8)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 9)", out, 16'h1);
        check_value("zr (row 9)", {15'b0, zr}, 16'h0);
        check_value("ng (row 9)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 10)", out, 16'h1);
        check_value("zr (row 10)", {15'b0, zr}, 16'h0);
        check_value("ng (row 10)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 11)", out, 16'h0);
        check_value("zr (row 11)", {15'b0, zr}, 16'h1);
        check_value("ng (row 11)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 12)", out, 16'hffff);
        check_value("zr (row 12)", {15'b0, zr}, 16'h0);
        check_value("ng (row 12)", {15'b0, ng}, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 13)", out, 16'hfffe);
        check_value("zr (row 13)", {15'b0, zr}, 16'h0);
        check_value("ng (row 13)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 14)", out, 16'hffff);
        check_value("zr (row 14)", {15'b0, zr}, 16'h0);
        check_value("ng (row 14)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 15)", out, 16'h1);
        check_value("zr (row 15)", {15'b0, zr}, 16'h0);
        check_value("ng (row 15)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 16)", out, 16'hffff);
        check_value("zr (row 16)", {15'b0, zr}, 16'h0);
        check_value("ng (row 16)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 17)", out, 16'h0);
        check_value("zr (row 17)", {15'b0, zr}, 16'h1);
        check_value("ng (row 17)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 18)", out, 16'hffff);
        check_value("zr (row 18)", {15'b0, zr}, 16'h0);
        check_value("ng (row 18)", {15'b0, ng}, 16'h1);

        x = 16'h11;
        y = 16'h3;
        zx = 1'h1;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 19)", out, 16'h0);
        check_value("zr (row 19)", {15'b0, zr}, 16'h1);
        check_value("ng (row 19)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 20)", out, 16'h1);
        check_value("zr (row 20)", {15'b0, zr}, 16'h0);
        check_value("ng (row 20)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 21)", out, 16'hffff);
        check_value("zr (row 21)", {15'b0, zr}, 16'h0);
        check_value("ng (row 21)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 22)", out, 16'h11);
        check_value("zr (row 22)", {15'b0, zr}, 16'h0);
        check_value("ng (row 22)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 23)", out, 16'h3);
        check_value("zr (row 23)", {15'b0, zr}, 16'h0);
        check_value("ng (row 23)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 24)", out, 16'hffee);
        check_value("zr (row 24)", {15'b0, zr}, 16'h0);
        check_value("ng (row 24)", {15'b0, ng}, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 25)", out, 16'hfffc);
        check_value("zr (row 25)", {15'b0, zr}, 16'h0);
        check_value("ng (row 25)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 26)", out, 16'hffef);
        check_value("zr (row 26)", {15'b0, zr}, 16'h0);
        check_value("ng (row 26)", {15'b0, ng}, 16'h1);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 27)", out, 16'hfffd);
        check_value("zr (row 27)", {15'b0, zr}, 16'h0);
        check_value("ng (row 27)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 28)", out, 16'h12);
        check_value("zr (row 28)", {15'b0, zr}, 16'h0);
        check_value("ng (row 28)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 29)", out, 16'h4);
        check_value("zr (row 29)", {15'b0, zr}, 16'h0);
        check_value("ng (row 29)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h1;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 30)", out, 16'h10);
        check_value("zr (row 30)", {15'b0, zr}, 16'h0);
        check_value("ng (row 30)", {15'b0, ng}, 16'h0);

        zx = 1'h1;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 31)", out, 16'h2);
        check_value("zr (row 31)", {15'b0, zr}, 16'h0);
        check_value("ng (row 31)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h0;
        #1;

        check_value("out (row 32)", out, 16'h14);
        check_value("zr (row 32)", {15'b0, zr}, 16'h0);
        check_value("ng (row 32)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 33)", out, 16'he);
        check_value("zr (row 33)", {15'b0, zr}, 16'h0);
        check_value("ng (row 33)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h1;
        no = 1'h1;
        #1;

        check_value("out (row 34)", out, 16'hfff2);
        check_value("zr (row 34)", {15'b0, zr}, 16'h0);
        check_value("ng (row 34)", {15'b0, ng}, 16'h1);

        zx = 1'h0;
        nx = 1'h0;
        zy = 1'h0;
        ny = 1'h0;
        f = 1'h0;
        no = 1'h0;
        #1;

        check_value("out (row 35)", out, 16'h1);
        check_value("zr (row 35)", {15'b0, zr}, 16'h0);
        check_value("ng (row 35)", {15'b0, ng}, 16'h0);

        zx = 1'h0;
        nx = 1'h1;
        zy = 1'h0;
        ny = 1'h1;
        f = 1'h0;
        no = 1'h1;
        #1;

        check_value("out (row 36)", out, 16'h13);
        check_value("zr (row 36)", {15'b0, zr}, 16'h0);
        check_value("ng (row 36)", {15'b0, ng}, 16'h0);

        $display("PASS ALU_tb: %0d checks", checks);
        $finish;
    end
endmodule

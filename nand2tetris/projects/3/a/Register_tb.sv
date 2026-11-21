module Register_tb;
    logic clk = '0;
    logic [15:0] in = '0;
    logic load = '0;
    logic [15:0] out;
    int checks = 0;

    Register dut(
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
        in = 16'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 2)", out, 16'h0);

        in = 16'h0;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 3)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 4)", out, 16'h0);

        in = 16'h8285;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 5)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 6)", out, 16'h0);

        in = 16'h2b67;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 7)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 8)", out, 16'h0);

        in = 16'h8285;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 9)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 10)", out, 16'h8285);

        in = 16'h8285;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 11)", out, 16'h8285);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 12)", out, 16'h8285);

        in = 16'h8285;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 13)", out, 16'h8285);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 14)", out, 16'h8285);

        in = 16'h3039;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 15)", out, 16'h8285);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 16)", out, 16'h3039);

        in = 16'h0;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 17)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 18)", out, 16'h3039);

        in = 16'h0;
        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 19)", out, 16'h3039);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 20)", out, 16'h0);

        in = 16'h1;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 21)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 22)", out, 16'h0);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 23)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 24)", out, 16'h1);

        in = 16'h2;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 25)", out, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 26)", out, 16'h1);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 27)", out, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 28)", out, 16'h2);

        in = 16'h4;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 29)", out, 16'h2);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 30)", out, 16'h2);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 31)", out, 16'h2);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 32)", out, 16'h4);

        in = 16'h8;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 33)", out, 16'h4);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 34)", out, 16'h4);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 35)", out, 16'h4);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 36)", out, 16'h8);

        in = 16'h10;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 37)", out, 16'h8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 38)", out, 16'h8);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 39)", out, 16'h8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 40)", out, 16'h10);

        in = 16'h20;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 41)", out, 16'h10);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 42)", out, 16'h10);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 43)", out, 16'h10);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 44)", out, 16'h20);

        in = 16'h40;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 45)", out, 16'h20);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 46)", out, 16'h20);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 47)", out, 16'h20);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 48)", out, 16'h40);

        in = 16'h80;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 49)", out, 16'h40);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 50)", out, 16'h40);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 51)", out, 16'h40);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 52)", out, 16'h80);

        in = 16'h100;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 53)", out, 16'h80);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 54)", out, 16'h80);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 55)", out, 16'h80);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 56)", out, 16'h100);

        in = 16'h200;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 57)", out, 16'h100);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 58)", out, 16'h100);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 59)", out, 16'h100);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 60)", out, 16'h200);

        in = 16'h400;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 61)", out, 16'h200);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 62)", out, 16'h200);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 63)", out, 16'h200);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 64)", out, 16'h400);

        in = 16'h800;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 65)", out, 16'h400);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 66)", out, 16'h400);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 67)", out, 16'h400);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 68)", out, 16'h800);

        in = 16'h1000;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 69)", out, 16'h800);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 70)", out, 16'h800);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 71)", out, 16'h800);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 72)", out, 16'h1000);

        in = 16'h2000;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 73)", out, 16'h1000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 74)", out, 16'h1000);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 75)", out, 16'h1000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 76)", out, 16'h2000);

        in = 16'h4000;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 77)", out, 16'h2000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 78)", out, 16'h2000);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 79)", out, 16'h2000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 80)", out, 16'h4000);

        in = 16'h8000;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 81)", out, 16'h4000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 82)", out, 16'h4000);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 83)", out, 16'h4000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 84)", out, 16'h8000);

        in = 16'hfffe;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 85)", out, 16'h8000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 86)", out, 16'h8000);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 87)", out, 16'h8000);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 88)", out, 16'hfffe);

        in = 16'hfffd;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 89)", out, 16'hfffe);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 90)", out, 16'hfffe);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 91)", out, 16'hfffe);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 92)", out, 16'hfffd);

        in = 16'hfffb;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 93)", out, 16'hfffd);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 94)", out, 16'hfffd);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 95)", out, 16'hfffd);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 96)", out, 16'hfffb);

        in = 16'hfff7;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 97)", out, 16'hfffb);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 98)", out, 16'hfffb);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 99)", out, 16'hfffb);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 100)", out, 16'hfff7);

        in = 16'hffef;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 101)", out, 16'hfff7);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 102)", out, 16'hfff7);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 103)", out, 16'hfff7);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 104)", out, 16'hffef);

        in = 16'hffdf;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 105)", out, 16'hffef);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 106)", out, 16'hffef);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 107)", out, 16'hffef);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 108)", out, 16'hffdf);

        in = 16'hffbf;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 109)", out, 16'hffdf);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 110)", out, 16'hffdf);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 111)", out, 16'hffdf);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 112)", out, 16'hffbf);

        in = 16'hff7f;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 113)", out, 16'hffbf);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 114)", out, 16'hffbf);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 115)", out, 16'hffbf);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 116)", out, 16'hff7f);

        in = 16'hfeff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 117)", out, 16'hff7f);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 118)", out, 16'hff7f);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 119)", out, 16'hff7f);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 120)", out, 16'hfeff);

        in = 16'hfdff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 121)", out, 16'hfeff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 122)", out, 16'hfeff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 123)", out, 16'hfeff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 124)", out, 16'hfdff);

        in = 16'hfbff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 125)", out, 16'hfdff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 126)", out, 16'hfdff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 127)", out, 16'hfdff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 128)", out, 16'hfbff);

        in = 16'hf7ff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 129)", out, 16'hfbff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 130)", out, 16'hfbff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 131)", out, 16'hfbff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 132)", out, 16'hf7ff);

        in = 16'hefff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 133)", out, 16'hf7ff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 134)", out, 16'hf7ff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 135)", out, 16'hf7ff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 136)", out, 16'hefff);

        in = 16'hdfff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 137)", out, 16'hefff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 138)", out, 16'hefff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 139)", out, 16'hefff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 140)", out, 16'hdfff);

        in = 16'hbfff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 141)", out, 16'hdfff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 142)", out, 16'hdfff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 143)", out, 16'hdfff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 144)", out, 16'hbfff);

        in = 16'h7fff;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 145)", out, 16'hbfff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 146)", out, 16'hbfff);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 147)", out, 16'hbfff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 148)", out, 16'h7fff);

        $display("PASS Register_tb: %0d checks", checks);
        $finish;
    end
endmodule

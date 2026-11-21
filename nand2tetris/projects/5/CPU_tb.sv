module CPU_tb;
    logic clk = '0;
    logic [15:0] inM = '0;
    logic [15:0] instruction = '0;
    logic reset = '0;
    logic [15:0] outM;
    logic writeM;
    logic [14:0] addressM;
    logic [14:0] pc;
    int checks = 0;

    CPU dut(
        .clk(clk),
        .inM(inM),
        .instruction(instruction),
        .reset(reset),
        .outM(outM),
        .writeM(writeM),
        .addressM(addressM),
        .pc(pc)
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
        instruction = 16'h3039;
        clk = 0;
        #1;

        check_value("writeM (row 1)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 1)", {1'b0, addressM}, 16'h0);
        check_value("pc (row 1)", {1'b0, pc}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 2)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 2)", {1'b0, addressM}, 16'h3039);
        check_value("pc (row 2)", {1'b0, pc}, 16'h1);

        instruction = 16'hec10;
        clk = 0;
        #1;

        check_value("writeM (row 3)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 3)", {1'b0, addressM}, 16'h3039);
        check_value("pc (row 3)", {1'b0, pc}, 16'h1);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 4)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 4)", {1'b0, addressM}, 16'h3039);
        check_value("pc (row 4)", {1'b0, pc}, 16'h2);

        instruction = 16'h5ba0;
        clk = 0;
        #1;

        check_value("writeM (row 5)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 5)", {1'b0, addressM}, 16'h3039);
        check_value("pc (row 5)", {1'b0, pc}, 16'h2);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 6)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 6)", {1'b0, addressM}, 16'h5ba0);
        check_value("pc (row 6)", {1'b0, pc}, 16'h3);

        instruction = 16'he1f0;
        clk = 0;
        #1;

        check_value("writeM (row 7)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 7)", {1'b0, addressM}, 16'h5ba0);
        check_value("pc (row 7)", {1'b0, pc}, 16'h3);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 8)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 8)", {1'b0, addressM}, 16'h2b67);
        check_value("pc (row 8)", {1'b0, pc}, 16'h4);

        instruction = 16'h3eb;
        clk = 0;
        #1;

        check_value("writeM (row 9)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 9)", {1'b0, addressM}, 16'h2b67);
        check_value("pc (row 9)", {1'b0, pc}, 16'h4);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 10)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 10)", {1'b0, addressM}, 16'h3eb);
        check_value("pc (row 10)", {1'b0, pc}, 16'h5);

        instruction = 16'he308;
        clk = 0;
        #1;

        check_value("outM (row 11)", outM, 16'h2b67);
        check_value("writeM (row 11)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 11)", {1'b0, addressM}, 16'h3eb);
        check_value("pc (row 11)", {1'b0, pc}, 16'h5);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("outM (row 12)", outM, 16'h2b67);
        check_value("writeM (row 12)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 12)", {1'b0, addressM}, 16'h3eb);
        check_value("pc (row 12)", {1'b0, pc}, 16'h6);

        instruction = 16'h3ec;
        clk = 0;
        #1;

        check_value("writeM (row 13)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 13)", {1'b0, addressM}, 16'h3eb);
        check_value("pc (row 13)", {1'b0, pc}, 16'h6);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 14)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 14)", {1'b0, addressM}, 16'h3ec);
        check_value("pc (row 14)", {1'b0, pc}, 16'h7);

        instruction = 16'he398;
        clk = 0;
        #1;

        check_value("outM (row 15)", outM, 16'h2b66);
        check_value("writeM (row 15)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 15)", {1'b0, addressM}, 16'h3ec);
        check_value("pc (row 15)", {1'b0, pc}, 16'h7);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("outM (row 16)", outM, 16'h2b65);
        check_value("writeM (row 16)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 16)", {1'b0, addressM}, 16'h3ec);
        check_value("pc (row 16)", {1'b0, pc}, 16'h8);

        instruction = 16'h3e8;
        clk = 0;
        #1;

        check_value("writeM (row 17)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 17)", {1'b0, addressM}, 16'h3ec);
        check_value("pc (row 17)", {1'b0, pc}, 16'h8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 18)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 18)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 18)", {1'b0, pc}, 16'h9);

        instruction = 16'hf4f0;
        inM = 16'h2b67;
        clk = 0;
        #1;

        check_value("writeM (row 19)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 19)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 19)", {1'b0, pc}, 16'h9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 20)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 20)", {1'b0, addressM}, 16'h7fff);
        check_value("pc (row 20)", {1'b0, pc}, 16'ha);

        instruction = 16'he;
        clk = 0;
        #1;

        check_value("writeM (row 21)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 21)", {1'b0, addressM}, 16'h7fff);
        check_value("pc (row 21)", {1'b0, pc}, 16'ha);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 22)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 22)", {1'b0, addressM}, 16'he);
        check_value("pc (row 22)", {1'b0, pc}, 16'hb);

        instruction = 16'he304;
        clk = 0;
        #1;

        check_value("writeM (row 23)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 23)", {1'b0, addressM}, 16'he);
        check_value("pc (row 23)", {1'b0, pc}, 16'hb);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 24)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 24)", {1'b0, addressM}, 16'he);
        check_value("pc (row 24)", {1'b0, pc}, 16'he);

        instruction = 16'h3e7;
        clk = 0;
        #1;

        check_value("writeM (row 25)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 25)", {1'b0, addressM}, 16'he);
        check_value("pc (row 25)", {1'b0, pc}, 16'he);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 26)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 26)", {1'b0, addressM}, 16'h3e7);
        check_value("pc (row 26)", {1'b0, pc}, 16'hf);

        instruction = 16'hfde0;
        clk = 0;
        #1;

        check_value("writeM (row 27)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 27)", {1'b0, addressM}, 16'h3e7);
        check_value("pc (row 27)", {1'b0, pc}, 16'hf);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 28)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 28)", {1'b0, addressM}, 16'h2b68);
        check_value("pc (row 28)", {1'b0, pc}, 16'h10);

        instruction = 16'he328;
        clk = 0;
        #1;

        check_value("outM (row 29)", outM, 16'hffff);
        check_value("writeM (row 29)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 29)", {1'b0, addressM}, 16'h2b68);
        check_value("pc (row 29)", {1'b0, pc}, 16'h10);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("outM (row 30)", outM, 16'hffff);
        check_value("writeM (row 30)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 30)", {1'b0, addressM}, 16'h7fff);
        check_value("pc (row 30)", {1'b0, pc}, 16'h11);

        instruction = 16'h15;
        clk = 0;
        #1;

        check_value("writeM (row 31)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 31)", {1'b0, addressM}, 16'h7fff);
        check_value("pc (row 31)", {1'b0, pc}, 16'h11);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 32)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 32)", {1'b0, addressM}, 16'h15);
        check_value("pc (row 32)", {1'b0, pc}, 16'h12);

        instruction = 16'he7c2;
        clk = 0;
        #1;

        check_value("writeM (row 33)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 33)", {1'b0, addressM}, 16'h15);
        check_value("pc (row 33)", {1'b0, pc}, 16'h12);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 34)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 34)", {1'b0, addressM}, 16'h15);
        check_value("pc (row 34)", {1'b0, pc}, 16'h15);

        instruction = 16'h2;
        clk = 0;
        #1;

        check_value("writeM (row 35)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 35)", {1'b0, addressM}, 16'h15);
        check_value("pc (row 35)", {1'b0, pc}, 16'h15);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 36)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 36)", {1'b0, addressM}, 16'h2);
        check_value("pc (row 36)", {1'b0, pc}, 16'h16);

        instruction = 16'he0b8;
        clk = 0;
        #1;

        check_value("outM (row 37)", outM, 16'h1);
        check_value("writeM (row 37)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 37)", {1'b0, addressM}, 16'h2);
        check_value("pc (row 37)", {1'b0, pc}, 16'h16);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("outM (row 38)", outM, 16'h2);
        check_value("writeM (row 38)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 38)", {1'b0, addressM}, 16'h1);
        check_value("pc (row 38)", {1'b0, pc}, 16'h17);

        instruction = 16'hfdc8;
        clk = 0;
        #1;

        check_value("outM (row 39)", outM, 16'h2b68);
        check_value("writeM (row 39)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 39)", {1'b0, addressM}, 16'h1);
        check_value("pc (row 39)", {1'b0, pc}, 16'h17);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("outM (row 40)", outM, 16'h2b68);
        check_value("writeM (row 40)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 40)", {1'b0, addressM}, 16'h1);
        check_value("pc (row 40)", {1'b0, pc}, 16'h18);

        instruction = 16'hfca8;
        clk = 0;
        #1;

        check_value("outM (row 41)", outM, 16'h2b66);
        check_value("writeM (row 41)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 41)", {1'b0, addressM}, 16'h1);
        check_value("pc (row 41)", {1'b0, pc}, 16'h18);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("outM (row 42)", outM, 16'h2b66);
        check_value("writeM (row 42)", {15'b0, writeM}, 16'h1);
        check_value("addressM (row 42)", {1'b0, addressM}, 16'h2b66);
        check_value("pc (row 42)", {1'b0, pc}, 16'h19);

        instruction = 16'h3e8;
        clk = 0;
        #1;

        check_value("writeM (row 43)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 43)", {1'b0, addressM}, 16'h2b66);
        check_value("pc (row 43)", {1'b0, pc}, 16'h19);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 44)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 44)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 44)", {1'b0, pc}, 16'h1a);

        instruction = 16'hee90;
        clk = 0;
        #1;

        check_value("writeM (row 45)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 45)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 45)", {1'b0, pc}, 16'h1a);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 46)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 46)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 46)", {1'b0, pc}, 16'h1b);

        instruction = 16'he301;
        clk = 0;
        #1;

        check_value("writeM (row 47)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 47)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 47)", {1'b0, pc}, 16'h1b);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 48)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 48)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 48)", {1'b0, pc}, 16'h1c);

        instruction = 16'he302;
        clk = 0;
        #1;

        check_value("writeM (row 49)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 49)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 49)", {1'b0, pc}, 16'h1c);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 50)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 50)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 50)", {1'b0, pc}, 16'h1d);

        instruction = 16'he303;
        clk = 0;
        #1;

        check_value("writeM (row 51)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 51)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 51)", {1'b0, pc}, 16'h1d);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 52)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 52)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 52)", {1'b0, pc}, 16'h1e);

        instruction = 16'he304;
        clk = 0;
        #1;

        check_value("writeM (row 53)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 53)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 53)", {1'b0, pc}, 16'h1e);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 54)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 54)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 54)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he305;
        clk = 0;
        #1;

        check_value("writeM (row 55)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 55)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 55)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 56)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 56)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 56)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he306;
        clk = 0;
        #1;

        check_value("writeM (row 57)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 57)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 57)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 58)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 58)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 58)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he307;
        clk = 0;
        #1;

        check_value("writeM (row 59)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 59)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 59)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 60)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 60)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 60)", {1'b0, pc}, 16'h3e8);

        instruction = 16'hea90;
        clk = 0;
        #1;

        check_value("writeM (row 61)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 61)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 61)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 62)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 62)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 62)", {1'b0, pc}, 16'h3e9);

        instruction = 16'he301;
        clk = 0;
        #1;

        check_value("writeM (row 63)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 63)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 63)", {1'b0, pc}, 16'h3e9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 64)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 64)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 64)", {1'b0, pc}, 16'h3ea);

        instruction = 16'he302;
        clk = 0;
        #1;

        check_value("writeM (row 65)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 65)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 65)", {1'b0, pc}, 16'h3ea);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 66)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 66)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 66)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he303;
        clk = 0;
        #1;

        check_value("writeM (row 67)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 67)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 67)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 68)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 68)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 68)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he304;
        clk = 0;
        #1;

        check_value("writeM (row 69)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 69)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 69)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 70)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 70)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 70)", {1'b0, pc}, 16'h3e9);

        instruction = 16'he305;
        clk = 0;
        #1;

        check_value("writeM (row 71)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 71)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 71)", {1'b0, pc}, 16'h3e9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 72)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 72)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 72)", {1'b0, pc}, 16'h3ea);

        instruction = 16'he306;
        clk = 0;
        #1;

        check_value("writeM (row 73)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 73)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 73)", {1'b0, pc}, 16'h3ea);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 74)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 74)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 74)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he307;
        clk = 0;
        #1;

        check_value("writeM (row 75)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 75)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 75)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 76)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 76)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 76)", {1'b0, pc}, 16'h3e8);

        instruction = 16'hefd0;
        clk = 0;
        #1;

        check_value("writeM (row 77)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 77)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 77)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 78)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 78)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 78)", {1'b0, pc}, 16'h3e9);

        instruction = 16'he301;
        clk = 0;
        #1;

        check_value("writeM (row 79)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 79)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 79)", {1'b0, pc}, 16'h3e9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 80)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 80)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 80)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he302;
        clk = 0;
        #1;

        check_value("writeM (row 81)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 81)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 81)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 82)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 82)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 82)", {1'b0, pc}, 16'h3e9);

        instruction = 16'he303;
        clk = 0;
        #1;

        check_value("writeM (row 83)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 83)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 83)", {1'b0, pc}, 16'h3e9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 84)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 84)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 84)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he304;
        clk = 0;
        #1;

        check_value("writeM (row 85)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 85)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 85)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 86)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 86)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 86)", {1'b0, pc}, 16'h3e9);

        instruction = 16'he305;
        clk = 0;
        #1;

        check_value("writeM (row 87)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 87)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 87)", {1'b0, pc}, 16'h3e9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 88)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 88)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 88)", {1'b0, pc}, 16'h3e8);

        instruction = 16'he306;
        clk = 0;
        #1;

        check_value("writeM (row 89)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 89)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 89)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 90)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 90)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 90)", {1'b0, pc}, 16'h3e9);

        instruction = 16'he307;
        clk = 0;
        #1;

        check_value("writeM (row 91)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 91)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 91)", {1'b0, pc}, 16'h3e9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 92)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 92)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 92)", {1'b0, pc}, 16'h3e8);

        reset = 1'h1;
        clk = 0;
        #1;

        check_value("writeM (row 93)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 93)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 93)", {1'b0, pc}, 16'h3e8);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 94)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 94)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 94)", {1'b0, pc}, 16'h0);

        instruction = 16'h7fff;
        reset = 1'h0;
        clk = 0;
        #1;

        check_value("writeM (row 95)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 95)", {1'b0, addressM}, 16'h3e8);
        check_value("pc (row 95)", {1'b0, pc}, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("writeM (row 96)", {15'b0, writeM}, 16'h0);
        check_value("addressM (row 96)", {1'b0, addressM}, 16'h7fff);
        check_value("pc (row 96)", {1'b0, pc}, 16'h1);

        $display("PASS CPU_tb: %0d checks", checks);
        $finish;
    end
endmodule

module ComputerRect_tb;
    logic clk = '0;
    logic reset = '0;
    int checks = 0;

    Computer dut(
        .clk(clk),
        .reset(reset)
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
        $readmemb("projects/5/Rect.hack", dut.rom.words);
        dut.memory.ram.words[0] = 16'h4;

        check_value("ARegister[] (row 1)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 1)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 1)", {1'b0, dut.cpu.pc}, 16'h0);
        check_value("RAM16K[0] (row 1)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 1)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 1)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 2)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 2)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 2)", {1'b0, dut.cpu.pc}, 16'h1);
        check_value("RAM16K[0] (row 2)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 2)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 2)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 3)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 3)", dut.cpu.d_register.out, 16'h4);
        check_value("PC[] (row 3)", {1'b0, dut.cpu.pc}, 16'h2);
        check_value("RAM16K[0] (row 3)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 3)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 3)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 4)", dut.cpu.a_register.out, 16'h17);
        check_value("DRegister[] (row 4)", dut.cpu.d_register.out, 16'h4);
        check_value("PC[] (row 4)", {1'b0, dut.cpu.pc}, 16'h3);
        check_value("RAM16K[0] (row 4)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 4)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 4)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 5)", dut.cpu.a_register.out, 16'h17);
        check_value("DRegister[] (row 5)", dut.cpu.d_register.out, 16'h4);
        check_value("PC[] (row 5)", {1'b0, dut.cpu.pc}, 16'h4);
        check_value("RAM16K[0] (row 5)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 5)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 5)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 6)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 6)", dut.cpu.d_register.out, 16'h4);
        check_value("PC[] (row 6)", {1'b0, dut.cpu.pc}, 16'h5);
        check_value("RAM16K[0] (row 6)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 6)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 6)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 7)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 7)", dut.cpu.d_register.out, 16'h4);
        check_value("PC[] (row 7)", {1'b0, dut.cpu.pc}, 16'h6);
        check_value("RAM16K[0] (row 7)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 7)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 7)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 8)", dut.cpu.a_register.out, 16'h4000);
        check_value("DRegister[] (row 8)", dut.cpu.d_register.out, 16'h4);
        check_value("PC[] (row 8)", {1'b0, dut.cpu.pc}, 16'h7);
        check_value("RAM16K[0] (row 8)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 8)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 8)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 9)", dut.cpu.a_register.out, 16'h4000);
        check_value("DRegister[] (row 9)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 9)", {1'b0, dut.cpu.pc}, 16'h8);
        check_value("RAM16K[0] (row 9)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 9)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 9)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 10)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 10)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 10)", {1'b0, dut.cpu.pc}, 16'h9);
        check_value("RAM16K[0] (row 10)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 10)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 10)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 11)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 11)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 11)", {1'b0, dut.cpu.pc}, 16'ha);
        check_value("RAM16K[0] (row 11)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 11)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 11)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 12)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 12)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 12)", {1'b0, dut.cpu.pc}, 16'hb);
        check_value("RAM16K[0] (row 12)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 12)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 12)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 13)", dut.cpu.a_register.out, 16'h4000);
        check_value("DRegister[] (row 13)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 13)", {1'b0, dut.cpu.pc}, 16'hc);
        check_value("RAM16K[0] (row 13)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 13)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 13)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 14)", dut.cpu.a_register.out, 16'h4000);
        check_value("DRegister[] (row 14)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 14)", {1'b0, dut.cpu.pc}, 16'hd);
        check_value("RAM16K[0] (row 14)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 14)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 14)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 15)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 15)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 15)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 15)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 15)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 15)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 16)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 16)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 16)", {1'b0, dut.cpu.pc}, 16'hf);
        check_value("RAM16K[0] (row 16)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 16)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 16)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 17)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 17)", dut.cpu.d_register.out, 16'h4000);
        check_value("PC[] (row 17)", {1'b0, dut.cpu.pc}, 16'h10);
        check_value("RAM16K[0] (row 17)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 17)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 17)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 18)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 18)", dut.cpu.d_register.out, 16'h4020);
        check_value("PC[] (row 18)", {1'b0, dut.cpu.pc}, 16'h11);
        check_value("RAM16K[0] (row 18)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 18)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 18)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 19)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 19)", dut.cpu.d_register.out, 16'h4020);
        check_value("PC[] (row 19)", {1'b0, dut.cpu.pc}, 16'h12);
        check_value("RAM16K[0] (row 19)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 19)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 19)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 20)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 20)", dut.cpu.d_register.out, 16'h4020);
        check_value("PC[] (row 20)", {1'b0, dut.cpu.pc}, 16'h13);
        check_value("RAM16K[0] (row 20)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 20)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 20)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 21)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 21)", dut.cpu.d_register.out, 16'h4020);
        check_value("PC[] (row 21)", {1'b0, dut.cpu.pc}, 16'h14);
        check_value("RAM16K[0] (row 21)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 21)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 21)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 22)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 22)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 22)", {1'b0, dut.cpu.pc}, 16'h15);
        check_value("RAM16K[0] (row 22)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 22)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 22)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 23)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 23)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 23)", {1'b0, dut.cpu.pc}, 16'h16);
        check_value("RAM16K[0] (row 23)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 23)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 23)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 24)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 24)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 24)", {1'b0, dut.cpu.pc}, 16'ha);
        check_value("RAM16K[0] (row 24)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 24)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 24)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 25)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 25)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 25)", {1'b0, dut.cpu.pc}, 16'hb);
        check_value("RAM16K[0] (row 25)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 25)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 25)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 26)", dut.cpu.a_register.out, 16'h4020);
        check_value("DRegister[] (row 26)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 26)", {1'b0, dut.cpu.pc}, 16'hc);
        check_value("RAM16K[0] (row 26)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 26)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 26)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 27)", dut.cpu.a_register.out, 16'h4020);
        check_value("DRegister[] (row 27)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 27)", {1'b0, dut.cpu.pc}, 16'hd);
        check_value("RAM16K[0] (row 27)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 27)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 27)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 28)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 28)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 28)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 28)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 28)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 28)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 29)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 29)", dut.cpu.d_register.out, 16'h4020);
        check_value("PC[] (row 29)", {1'b0, dut.cpu.pc}, 16'hf);
        check_value("RAM16K[0] (row 29)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 29)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 29)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 30)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 30)", dut.cpu.d_register.out, 16'h4020);
        check_value("PC[] (row 30)", {1'b0, dut.cpu.pc}, 16'h10);
        check_value("RAM16K[0] (row 30)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 30)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 30)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 31)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 31)", dut.cpu.d_register.out, 16'h4040);
        check_value("PC[] (row 31)", {1'b0, dut.cpu.pc}, 16'h11);
        check_value("RAM16K[0] (row 31)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 31)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 31)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 32)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 32)", dut.cpu.d_register.out, 16'h4040);
        check_value("PC[] (row 32)", {1'b0, dut.cpu.pc}, 16'h12);
        check_value("RAM16K[0] (row 32)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 32)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 32)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 33)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 33)", dut.cpu.d_register.out, 16'h4040);
        check_value("PC[] (row 33)", {1'b0, dut.cpu.pc}, 16'h13);
        check_value("RAM16K[0] (row 33)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 33)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 33)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 34)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 34)", dut.cpu.d_register.out, 16'h4040);
        check_value("PC[] (row 34)", {1'b0, dut.cpu.pc}, 16'h14);
        check_value("RAM16K[0] (row 34)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 34)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 34)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 35)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 35)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 35)", {1'b0, dut.cpu.pc}, 16'h15);
        check_value("RAM16K[0] (row 35)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 35)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 35)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 36)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 36)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 36)", {1'b0, dut.cpu.pc}, 16'h16);
        check_value("RAM16K[0] (row 36)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 36)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 36)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 37)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 37)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 37)", {1'b0, dut.cpu.pc}, 16'ha);
        check_value("RAM16K[0] (row 37)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 37)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 37)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 38)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 38)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 38)", {1'b0, dut.cpu.pc}, 16'hb);
        check_value("RAM16K[0] (row 38)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 38)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 38)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 39)", dut.cpu.a_register.out, 16'h4040);
        check_value("DRegister[] (row 39)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 39)", {1'b0, dut.cpu.pc}, 16'hc);
        check_value("RAM16K[0] (row 39)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 39)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 39)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 40)", dut.cpu.a_register.out, 16'h4040);
        check_value("DRegister[] (row 40)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 40)", {1'b0, dut.cpu.pc}, 16'hd);
        check_value("RAM16K[0] (row 40)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 40)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 40)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 41)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 41)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 41)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 41)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 41)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 41)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 42)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 42)", dut.cpu.d_register.out, 16'h4040);
        check_value("PC[] (row 42)", {1'b0, dut.cpu.pc}, 16'hf);
        check_value("RAM16K[0] (row 42)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 42)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 42)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 43)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 43)", dut.cpu.d_register.out, 16'h4040);
        check_value("PC[] (row 43)", {1'b0, dut.cpu.pc}, 16'h10);
        check_value("RAM16K[0] (row 43)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 43)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 43)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 44)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 44)", dut.cpu.d_register.out, 16'h4060);
        check_value("PC[] (row 44)", {1'b0, dut.cpu.pc}, 16'h11);
        check_value("RAM16K[0] (row 44)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 44)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 44)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 45)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 45)", dut.cpu.d_register.out, 16'h4060);
        check_value("PC[] (row 45)", {1'b0, dut.cpu.pc}, 16'h12);
        check_value("RAM16K[0] (row 45)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 45)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 45)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 46)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 46)", dut.cpu.d_register.out, 16'h4060);
        check_value("PC[] (row 46)", {1'b0, dut.cpu.pc}, 16'h13);
        check_value("RAM16K[0] (row 46)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 46)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 46)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 47)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 47)", dut.cpu.d_register.out, 16'h4060);
        check_value("PC[] (row 47)", {1'b0, dut.cpu.pc}, 16'h14);
        check_value("RAM16K[0] (row 47)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 47)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 47)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 48)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 48)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 48)", {1'b0, dut.cpu.pc}, 16'h15);
        check_value("RAM16K[0] (row 48)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 48)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 48)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 49)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 49)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 49)", {1'b0, dut.cpu.pc}, 16'h16);
        check_value("RAM16K[0] (row 49)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 49)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 49)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 50)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 50)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 50)", {1'b0, dut.cpu.pc}, 16'ha);
        check_value("RAM16K[0] (row 50)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 50)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 50)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 51)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 51)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 51)", {1'b0, dut.cpu.pc}, 16'hb);
        check_value("RAM16K[0] (row 51)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 51)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 51)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 52)", dut.cpu.a_register.out, 16'h4060);
        check_value("DRegister[] (row 52)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 52)", {1'b0, dut.cpu.pc}, 16'hc);
        check_value("RAM16K[0] (row 52)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 52)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 52)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 53)", dut.cpu.a_register.out, 16'h4060);
        check_value("DRegister[] (row 53)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 53)", {1'b0, dut.cpu.pc}, 16'hd);
        check_value("RAM16K[0] (row 53)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 53)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 53)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 54)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 54)", dut.cpu.d_register.out, 16'h1);
        check_value("PC[] (row 54)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 54)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 54)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 54)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 55)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 55)", dut.cpu.d_register.out, 16'h4060);
        check_value("PC[] (row 55)", {1'b0, dut.cpu.pc}, 16'hf);
        check_value("RAM16K[0] (row 55)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 55)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 55)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 56)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 56)", dut.cpu.d_register.out, 16'h4060);
        check_value("PC[] (row 56)", {1'b0, dut.cpu.pc}, 16'h10);
        check_value("RAM16K[0] (row 56)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 56)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 56)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 57)", dut.cpu.a_register.out, 16'h20);
        check_value("DRegister[] (row 57)", dut.cpu.d_register.out, 16'h4080);
        check_value("PC[] (row 57)", {1'b0, dut.cpu.pc}, 16'h11);
        check_value("RAM16K[0] (row 57)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 57)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 57)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 58)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 58)", dut.cpu.d_register.out, 16'h4080);
        check_value("PC[] (row 58)", {1'b0, dut.cpu.pc}, 16'h12);
        check_value("RAM16K[0] (row 58)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 58)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 58)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 59)", dut.cpu.a_register.out, 16'h11);
        check_value("DRegister[] (row 59)", dut.cpu.d_register.out, 16'h4080);
        check_value("PC[] (row 59)", {1'b0, dut.cpu.pc}, 16'h13);
        check_value("RAM16K[0] (row 59)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 59)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 59)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 60)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 60)", dut.cpu.d_register.out, 16'h4080);
        check_value("PC[] (row 60)", {1'b0, dut.cpu.pc}, 16'h14);
        check_value("RAM16K[0] (row 60)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 60)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 60)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 61)", dut.cpu.a_register.out, 16'h10);
        check_value("DRegister[] (row 61)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 61)", {1'b0, dut.cpu.pc}, 16'h15);
        check_value("RAM16K[0] (row 61)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 61)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 61)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 62)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 62)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 62)", {1'b0, dut.cpu.pc}, 16'h16);
        check_value("RAM16K[0] (row 62)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 62)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 62)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 63)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 63)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 63)", {1'b0, dut.cpu.pc}, 16'h17);
        check_value("RAM16K[0] (row 63)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 63)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 63)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 64)", dut.cpu.a_register.out, 16'h17);
        check_value("DRegister[] (row 64)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 64)", {1'b0, dut.cpu.pc}, 16'h18);
        check_value("RAM16K[0] (row 64)", dut.memory.ram.words[0], 16'h4);
        check_value("RAM16K[1] (row 64)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 64)", dut.memory.ram.words[2], 16'h0);

        check_value("screen word 0", dut.memory.screen.words[0], 16'hffff);
        check_value("screen word 32", dut.memory.screen.words[32], 16'hffff);
        check_value("screen word 64", dut.memory.screen.words[64], 16'hffff);
        check_value("screen word 96", dut.memory.screen.words[96], 16'hffff);
        check_value("screen beyond rectangle", dut.memory.screen.words[128], 16'h0000);

        $display("PASS ComputerRect_tb: %0d checks", checks);
        $finish;
    end
endmodule

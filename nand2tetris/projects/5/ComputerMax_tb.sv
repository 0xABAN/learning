module ComputerMax_tb;
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
        $readmemb("projects/5/Max.hack", dut.rom.words);
        dut.memory.ram.words[0] = 16'h3;
        dut.memory.ram.words[1] = 16'h5;

        check_value("ARegister[] (row 1)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 1)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 1)", {1'b0, dut.cpu.pc}, 16'h0);
        check_value("RAM16K[0] (row 1)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 1)", dut.memory.ram.words[1], 16'h5);
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
        check_value("RAM16K[0] (row 2)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 2)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 2)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 3)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 3)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 3)", {1'b0, dut.cpu.pc}, 16'h2);
        check_value("RAM16K[0] (row 3)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 3)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 3)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 4)", dut.cpu.a_register.out, 16'h1);
        check_value("DRegister[] (row 4)", dut.cpu.d_register.out, 16'h3);
        check_value("PC[] (row 4)", {1'b0, dut.cpu.pc}, 16'h3);
        check_value("RAM16K[0] (row 4)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 4)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 4)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 5)", dut.cpu.a_register.out, 16'h1);
        check_value("DRegister[] (row 5)", dut.cpu.d_register.out, 16'hfffe);
        check_value("PC[] (row 5)", {1'b0, dut.cpu.pc}, 16'h4);
        check_value("RAM16K[0] (row 5)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 5)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 5)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 6)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 6)", dut.cpu.d_register.out, 16'hfffe);
        check_value("PC[] (row 6)", {1'b0, dut.cpu.pc}, 16'h5);
        check_value("RAM16K[0] (row 6)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 6)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 6)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 7)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 7)", dut.cpu.d_register.out, 16'hfffe);
        check_value("PC[] (row 7)", {1'b0, dut.cpu.pc}, 16'h6);
        check_value("RAM16K[0] (row 7)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 7)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 7)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 8)", dut.cpu.a_register.out, 16'h1);
        check_value("DRegister[] (row 8)", dut.cpu.d_register.out, 16'hfffe);
        check_value("PC[] (row 8)", {1'b0, dut.cpu.pc}, 16'h7);
        check_value("RAM16K[0] (row 8)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 8)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 8)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 9)", dut.cpu.a_register.out, 16'h1);
        check_value("DRegister[] (row 9)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 9)", {1'b0, dut.cpu.pc}, 16'h8);
        check_value("RAM16K[0] (row 9)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 9)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 9)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 10)", dut.cpu.a_register.out, 16'hc);
        check_value("DRegister[] (row 10)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 10)", {1'b0, dut.cpu.pc}, 16'h9);
        check_value("RAM16K[0] (row 10)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 10)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 10)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 11)", dut.cpu.a_register.out, 16'hc);
        check_value("DRegister[] (row 11)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 11)", {1'b0, dut.cpu.pc}, 16'hc);
        check_value("RAM16K[0] (row 11)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 11)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 11)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 12)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[] (row 12)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 12)", {1'b0, dut.cpu.pc}, 16'hd);
        check_value("RAM16K[0] (row 12)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 12)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 12)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 13)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[] (row 13)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 13)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 13)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 13)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 13)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 14)", dut.cpu.a_register.out, 16'he);
        check_value("DRegister[] (row 14)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 14)", {1'b0, dut.cpu.pc}, 16'hf);
        check_value("RAM16K[0] (row 14)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 14)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 14)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 15)", dut.cpu.a_register.out, 16'he);
        check_value("DRegister[] (row 15)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 15)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 15)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 15)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 15)", dut.memory.ram.words[2], 16'h5);

        reset = 1'h1;
        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 16)", dut.cpu.a_register.out, 16'he);
        check_value("DRegister[] (row 16)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 16)", {1'b0, dut.cpu.pc}, 16'h0);
        check_value("RAM16K[0] (row 16)", dut.memory.ram.words[0], 16'h3);
        check_value("RAM16K[1] (row 16)", dut.memory.ram.words[1], 16'h5);
        check_value("RAM16K[2] (row 16)", dut.memory.ram.words[2], 16'h5);

        reset = 1'h0;
        dut.memory.ram.words[0] = 16'h5ba0;
        dut.memory.ram.words[1] = 16'h3039;

        check_value("ARegister[] (row 17)", dut.cpu.a_register.out, 16'he);
        check_value("DRegister[] (row 17)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 17)", {1'b0, dut.cpu.pc}, 16'h0);
        check_value("RAM16K[0] (row 17)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 17)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 17)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 18)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 18)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 18)", {1'b0, dut.cpu.pc}, 16'h1);
        check_value("RAM16K[0] (row 18)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 18)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 18)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 19)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 19)", dut.cpu.d_register.out, 16'h5ba0);
        check_value("PC[] (row 19)", {1'b0, dut.cpu.pc}, 16'h2);
        check_value("RAM16K[0] (row 19)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 19)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 19)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 20)", dut.cpu.a_register.out, 16'h1);
        check_value("DRegister[] (row 20)", dut.cpu.d_register.out, 16'h5ba0);
        check_value("PC[] (row 20)", {1'b0, dut.cpu.pc}, 16'h3);
        check_value("RAM16K[0] (row 20)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 20)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 20)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 21)", dut.cpu.a_register.out, 16'h1);
        check_value("DRegister[] (row 21)", dut.cpu.d_register.out, 16'h2b67);
        check_value("PC[] (row 21)", {1'b0, dut.cpu.pc}, 16'h4);
        check_value("RAM16K[0] (row 21)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 21)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 21)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 22)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 22)", dut.cpu.d_register.out, 16'h2b67);
        check_value("PC[] (row 22)", {1'b0, dut.cpu.pc}, 16'h5);
        check_value("RAM16K[0] (row 22)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 22)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 22)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 23)", dut.cpu.a_register.out, 16'ha);
        check_value("DRegister[] (row 23)", dut.cpu.d_register.out, 16'h2b67);
        check_value("PC[] (row 23)", {1'b0, dut.cpu.pc}, 16'ha);
        check_value("RAM16K[0] (row 23)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 23)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 23)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 24)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 24)", dut.cpu.d_register.out, 16'h2b67);
        check_value("PC[] (row 24)", {1'b0, dut.cpu.pc}, 16'hb);
        check_value("RAM16K[0] (row 24)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 24)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 24)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 25)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[] (row 25)", dut.cpu.d_register.out, 16'h5ba0);
        check_value("PC[] (row 25)", {1'b0, dut.cpu.pc}, 16'hc);
        check_value("RAM16K[0] (row 25)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 25)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 25)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 26)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[] (row 26)", dut.cpu.d_register.out, 16'h5ba0);
        check_value("PC[] (row 26)", {1'b0, dut.cpu.pc}, 16'hd);
        check_value("RAM16K[0] (row 26)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 26)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 26)", dut.memory.ram.words[2], 16'h5);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[] (row 27)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[] (row 27)", dut.cpu.d_register.out, 16'h5ba0);
        check_value("PC[] (row 27)", {1'b0, dut.cpu.pc}, 16'he);
        check_value("RAM16K[0] (row 27)", dut.memory.ram.words[0], 16'h5ba0);
        check_value("RAM16K[1] (row 27)", dut.memory.ram.words[1], 16'h3039);
        check_value("RAM16K[2] (row 27)", dut.memory.ram.words[2], 16'h5ba0);

        $display("PASS ComputerMax_tb: %0d checks", checks);
        $finish;
    end
endmodule

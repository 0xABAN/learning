module ComputerAdd_tb;
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
        $readmemb("projects/5/Add.hack", dut.rom.words);

        check_value("ARegister[0] (row 1)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[0] (row 1)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 1)", {1'b0, dut.cpu.pc}, 16'h0);
        check_value("RAM16K[0] (row 1)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 1)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 1)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 2)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[0] (row 2)", dut.cpu.d_register.out, 16'h0);
        check_value("PC[] (row 2)", {1'b0, dut.cpu.pc}, 16'h1);
        check_value("RAM16K[0] (row 2)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 2)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 2)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 3)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[0] (row 3)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 3)", {1'b0, dut.cpu.pc}, 16'h2);
        check_value("RAM16K[0] (row 3)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 3)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 3)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 4)", dut.cpu.a_register.out, 16'h3);
        check_value("DRegister[0] (row 4)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 4)", {1'b0, dut.cpu.pc}, 16'h3);
        check_value("RAM16K[0] (row 4)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 4)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 4)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 5)", dut.cpu.a_register.out, 16'h3);
        check_value("DRegister[0] (row 5)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 5)", {1'b0, dut.cpu.pc}, 16'h4);
        check_value("RAM16K[0] (row 5)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 5)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 5)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 6)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[0] (row 6)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 6)", {1'b0, dut.cpu.pc}, 16'h5);
        check_value("RAM16K[0] (row 6)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 6)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 6)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 7)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[0] (row 7)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 7)", {1'b0, dut.cpu.pc}, 16'h6);
        check_value("RAM16K[0] (row 7)", dut.memory.ram.words[0], 16'h5);
        check_value("RAM16K[1] (row 7)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 7)", dut.memory.ram.words[2], 16'h0);

        reset = 1'h1;
        dut.memory.ram.words[0] = 16'h0;
        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 8)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[0] (row 8)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 8)", {1'b0, dut.cpu.pc}, 16'h0);
        check_value("RAM16K[0] (row 8)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 8)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 8)", dut.memory.ram.words[2], 16'h0);

        reset = 1'h0;
        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 9)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[0] (row 9)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 9)", {1'b0, dut.cpu.pc}, 16'h1);
        check_value("RAM16K[0] (row 9)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 9)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 9)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 10)", dut.cpu.a_register.out, 16'h2);
        check_value("DRegister[0] (row 10)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 10)", {1'b0, dut.cpu.pc}, 16'h2);
        check_value("RAM16K[0] (row 10)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 10)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 10)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 11)", dut.cpu.a_register.out, 16'h3);
        check_value("DRegister[0] (row 11)", dut.cpu.d_register.out, 16'h2);
        check_value("PC[] (row 11)", {1'b0, dut.cpu.pc}, 16'h3);
        check_value("RAM16K[0] (row 11)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 11)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 11)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 12)", dut.cpu.a_register.out, 16'h3);
        check_value("DRegister[0] (row 12)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 12)", {1'b0, dut.cpu.pc}, 16'h4);
        check_value("RAM16K[0] (row 12)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 12)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 12)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 13)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[0] (row 13)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 13)", {1'b0, dut.cpu.pc}, 16'h5);
        check_value("RAM16K[0] (row 13)", dut.memory.ram.words[0], 16'h0);
        check_value("RAM16K[1] (row 13)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 13)", dut.memory.ram.words[2], 16'h0);

        clk = 0;
        #1;
        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("ARegister[0] (row 14)", dut.cpu.a_register.out, 16'h0);
        check_value("DRegister[0] (row 14)", dut.cpu.d_register.out, 16'h5);
        check_value("PC[] (row 14)", {1'b0, dut.cpu.pc}, 16'h6);
        check_value("RAM16K[0] (row 14)", dut.memory.ram.words[0], 16'h5);
        check_value("RAM16K[1] (row 14)", dut.memory.ram.words[1], 16'h0);
        check_value("RAM16K[2] (row 14)", dut.memory.ram.words[2], 16'h0);

        $display("PASS ComputerAdd_tb: %0d checks", checks);
        $finish;
    end
endmodule

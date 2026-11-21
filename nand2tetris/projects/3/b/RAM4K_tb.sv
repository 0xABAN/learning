module RAM4K_tb;
    logic clk = '0;
    logic [15:0] in = '0;
    logic load = '0;
    logic [11:0] address = '0;
    logic [15:0] out;
    int checks = 0;

    RAM4K dut(
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
        in = 16'h0;
        load = 1'h0;
        address = 12'h0;
        clk = 0;
        #1;

        check_value("out (row 1)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 2)", out, 16'h0);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 3)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 4)", out, 16'h0);

        in = 16'h457;
        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 5)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 6)", out, 16'h0);

        load = 1'h1;
        address = 12'h457;
        clk = 0;
        #1;

        check_value("out (row 7)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 8)", out, 16'h457);

        load = 1'h0;
        address = 12'h0;
        clk = 0;
        #1;

        check_value("out (row 9)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 10)", out, 16'h0);

        in = 16'hdb9;
        address = 12'hdb9;
        clk = 0;
        #1;

        check_value("out (row 11)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 12)", out, 16'h0);

        load = 1'h1;
        clk = 0;
        #1;

        check_value("out (row 13)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 14)", out, 16'hdb9);

        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 15)", out, 16'hdb9);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 16)", out, 16'hdb9);

        address = 12'h457;
        #1;

        check_value("out (row 17)", out, 16'h457);

        in = 16'hfff;
        clk = 0;
        #1;

        check_value("out (row 18)", out, 16'h457);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 19)", out, 16'h457);

        load = 1'h1;
        address = 12'hfff;
        clk = 0;
        #1;

        check_value("out (row 20)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 21)", out, 16'hfff);

        load = 1'h0;
        clk = 0;
        #1;

        check_value("out (row 22)", out, 16'hfff);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 23)", out, 16'hfff);

        address = 12'hdb9;
        #1;

        check_value("out (row 24)", out, 16'hdb9);

        address = 12'hfff;
        #1;

        check_value("out (row 25)", out, 16'hfff);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 26)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 27)", out, 16'h0);

        address = 12'haa9;
        #1;

        check_value("out (row 28)", out, 16'h0);

        address = 12'haaa;
        #1;

        check_value("out (row 29)", out, 16'h0);

        address = 12'haab;
        #1;

        check_value("out (row 30)", out, 16'h0);

        address = 12'haac;
        #1;

        check_value("out (row 31)", out, 16'h0);

        address = 12'haad;
        #1;

        check_value("out (row 32)", out, 16'h0);

        address = 12'haae;
        #1;

        check_value("out (row 33)", out, 16'h0);

        address = 12'haaf;
        #1;

        check_value("out (row 34)", out, 16'h0);

        load = 1'h1;
        in = 16'h5555;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 35)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 36)", out, 16'h5555);

        address = 12'haa9;
        clk = 0;
        #1;

        check_value("out (row 37)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 38)", out, 16'h5555);

        address = 12'haaa;
        clk = 0;
        #1;

        check_value("out (row 39)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 40)", out, 16'h5555);

        address = 12'haab;
        clk = 0;
        #1;

        check_value("out (row 41)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 42)", out, 16'h5555);

        address = 12'haac;
        clk = 0;
        #1;

        check_value("out (row 43)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 44)", out, 16'h5555);

        address = 12'haad;
        clk = 0;
        #1;

        check_value("out (row 45)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 46)", out, 16'h5555);

        address = 12'haae;
        clk = 0;
        #1;

        check_value("out (row 47)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 48)", out, 16'h5555);

        address = 12'haaf;
        clk = 0;
        #1;

        check_value("out (row 49)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 50)", out, 16'h5555);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 51)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 52)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 53)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 54)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 55)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 56)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 57)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 58)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 59)", out, 16'h5555);

        load = 1'h1;
        address = 12'haa8;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 60)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 61)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 62)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 63)", out, 16'haaaa);

        address = 12'haa9;
        #1;

        check_value("out (row 64)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 65)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 66)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 67)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 68)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 69)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 70)", out, 16'h5555);

        load = 1'h1;
        address = 12'haa8;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 71)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 72)", out, 16'h5555);

        address = 12'haa9;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 73)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 74)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 75)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 76)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 77)", out, 16'haaaa);

        address = 12'haaa;
        #1;

        check_value("out (row 78)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 79)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 80)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 81)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 82)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 83)", out, 16'h5555);

        load = 1'h1;
        address = 12'haa9;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 84)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 85)", out, 16'h5555);

        address = 12'haaa;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 86)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 87)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 88)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 89)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 90)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 91)", out, 16'haaaa);

        address = 12'haab;
        #1;

        check_value("out (row 92)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 93)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 94)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 95)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 96)", out, 16'h5555);

        load = 1'h1;
        address = 12'haaa;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 97)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 98)", out, 16'h5555);

        address = 12'haab;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 99)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 100)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 101)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 102)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 103)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 104)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 105)", out, 16'haaaa);

        address = 12'haac;
        #1;

        check_value("out (row 106)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 107)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 108)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 109)", out, 16'h5555);

        load = 1'h1;
        address = 12'haab;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 110)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 111)", out, 16'h5555);

        address = 12'haac;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 112)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 113)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 114)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 115)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 116)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 117)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 118)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 119)", out, 16'haaaa);

        address = 12'haad;
        #1;

        check_value("out (row 120)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 121)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 122)", out, 16'h5555);

        load = 1'h1;
        address = 12'haac;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 123)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 124)", out, 16'h5555);

        address = 12'haad;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 125)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 126)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 127)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 128)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 129)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 130)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 131)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 132)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 133)", out, 16'haaaa);

        address = 12'haae;
        #1;

        check_value("out (row 134)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 135)", out, 16'h5555);

        load = 1'h1;
        address = 12'haad;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 136)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 137)", out, 16'h5555);

        address = 12'haae;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 138)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 139)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 140)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 141)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 142)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 143)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 144)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 145)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 146)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 147)", out, 16'haaaa);

        address = 12'haaf;
        #1;

        check_value("out (row 148)", out, 16'h5555);

        load = 1'h1;
        address = 12'haae;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 149)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 150)", out, 16'h5555);

        address = 12'haaf;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 151)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 152)", out, 16'haaaa);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 153)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 154)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 155)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 156)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 157)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 158)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 159)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 160)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 161)", out, 16'haaaa);

        load = 1'h1;
        address = 12'haaf;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 162)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 163)", out, 16'h5555);

        load = 1'h0;
        address = 12'haa8;
        clk = 0;
        #1;

        check_value("out (row 164)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 165)", out, 16'h5555);

        address = 12'haa9;
        #1;

        check_value("out (row 166)", out, 16'h5555);

        address = 12'haaa;
        #1;

        check_value("out (row 167)", out, 16'h5555);

        address = 12'haab;
        #1;

        check_value("out (row 168)", out, 16'h5555);

        address = 12'haac;
        #1;

        check_value("out (row 169)", out, 16'h5555);

        address = 12'haad;
        #1;

        check_value("out (row 170)", out, 16'h5555);

        address = 12'haae;
        #1;

        check_value("out (row 171)", out, 16'h5555);

        address = 12'haaf;
        #1;

        check_value("out (row 172)", out, 16'h5555);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 173)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 174)", out, 16'h0);

        address = 12'h355;
        #1;

        check_value("out (row 175)", out, 16'h0);

        address = 12'h555;
        #1;

        check_value("out (row 176)", out, 16'h0);

        address = 12'h755;
        #1;

        check_value("out (row 177)", out, 16'h0);

        address = 12'h955;
        #1;

        check_value("out (row 178)", out, 16'h0);

        address = 12'hb55;
        #1;

        check_value("out (row 179)", out, 16'h0);

        address = 12'hd55;
        #1;

        check_value("out (row 180)", out, 16'h0);

        address = 12'hf55;
        #1;

        check_value("out (row 181)", out, 16'h0);

        load = 1'h1;
        in = 16'h5555;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 182)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 183)", out, 16'h5555);

        address = 12'h355;
        clk = 0;
        #1;

        check_value("out (row 184)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 185)", out, 16'h5555);

        address = 12'h555;
        clk = 0;
        #1;

        check_value("out (row 186)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 187)", out, 16'h5555);

        address = 12'h755;
        clk = 0;
        #1;

        check_value("out (row 188)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 189)", out, 16'h5555);

        address = 12'h955;
        clk = 0;
        #1;

        check_value("out (row 190)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 191)", out, 16'h5555);

        address = 12'hb55;
        clk = 0;
        #1;

        check_value("out (row 192)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 193)", out, 16'h5555);

        address = 12'hd55;
        clk = 0;
        #1;

        check_value("out (row 194)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 195)", out, 16'h5555);

        address = 12'hf55;
        clk = 0;
        #1;

        check_value("out (row 196)", out, 16'h0);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 197)", out, 16'h5555);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 198)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 199)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 200)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 201)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 202)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 203)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 204)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 205)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 206)", out, 16'h5555);

        load = 1'h1;
        address = 12'h155;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 207)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 208)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 209)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 210)", out, 16'haaaa);

        address = 12'h355;
        #1;

        check_value("out (row 211)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 212)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 213)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 214)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 215)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 216)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 217)", out, 16'h5555);

        load = 1'h1;
        address = 12'h155;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 218)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 219)", out, 16'h5555);

        address = 12'h355;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 220)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 221)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 222)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 223)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 224)", out, 16'haaaa);

        address = 12'h555;
        #1;

        check_value("out (row 225)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 226)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 227)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 228)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 229)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 230)", out, 16'h5555);

        load = 1'h1;
        address = 12'h355;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 231)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 232)", out, 16'h5555);

        address = 12'h555;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 233)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 234)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 235)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 236)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 237)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 238)", out, 16'haaaa);

        address = 12'h755;
        #1;

        check_value("out (row 239)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 240)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 241)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 242)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 243)", out, 16'h5555);

        load = 1'h1;
        address = 12'h555;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 244)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 245)", out, 16'h5555);

        address = 12'h755;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 246)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 247)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 248)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 249)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 250)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 251)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 252)", out, 16'haaaa);

        address = 12'h955;
        #1;

        check_value("out (row 253)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 254)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 255)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 256)", out, 16'h5555);

        load = 1'h1;
        address = 12'h755;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 257)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 258)", out, 16'h5555);

        address = 12'h955;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 259)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 260)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 261)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 262)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 263)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 264)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 265)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 266)", out, 16'haaaa);

        address = 12'hb55;
        #1;

        check_value("out (row 267)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 268)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 269)", out, 16'h5555);

        load = 1'h1;
        address = 12'h955;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 270)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 271)", out, 16'h5555);

        address = 12'hb55;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 272)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 273)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 274)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 275)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 276)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 277)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 278)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 279)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 280)", out, 16'haaaa);

        address = 12'hd55;
        #1;

        check_value("out (row 281)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 282)", out, 16'h5555);

        load = 1'h1;
        address = 12'hb55;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 283)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 284)", out, 16'h5555);

        address = 12'hd55;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 285)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 286)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 287)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 288)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 289)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 290)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 291)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 292)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 293)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 294)", out, 16'haaaa);

        address = 12'hf55;
        #1;

        check_value("out (row 295)", out, 16'h5555);

        load = 1'h1;
        address = 12'hd55;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 296)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 297)", out, 16'h5555);

        address = 12'hf55;
        in = 16'haaaa;
        clk = 0;
        #1;

        check_value("out (row 298)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 299)", out, 16'haaaa);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 300)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 301)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 302)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 303)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 304)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 305)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 306)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 307)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 308)", out, 16'haaaa);

        load = 1'h1;
        address = 12'hf55;
        in = 16'h5555;
        clk = 0;
        #1;

        check_value("out (row 309)", out, 16'haaaa);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 310)", out, 16'h5555);

        load = 1'h0;
        address = 12'h155;
        clk = 0;
        #1;

        check_value("out (row 311)", out, 16'h5555);

        clk = 1;
        #1;
        clk = 0;
        #1;

        check_value("out (row 312)", out, 16'h5555);

        address = 12'h355;
        #1;

        check_value("out (row 313)", out, 16'h5555);

        address = 12'h555;
        #1;

        check_value("out (row 314)", out, 16'h5555);

        address = 12'h755;
        #1;

        check_value("out (row 315)", out, 16'h5555);

        address = 12'h955;
        #1;

        check_value("out (row 316)", out, 16'h5555);

        address = 12'hb55;
        #1;

        check_value("out (row 317)", out, 16'h5555);

        address = 12'hd55;
        #1;

        check_value("out (row 318)", out, 16'h5555);

        address = 12'hf55;
        #1;

        check_value("out (row 319)", out, 16'h5555);

        $display("PASS RAM4K_tb: %0d checks", checks);
        $finish;
    end
endmodule

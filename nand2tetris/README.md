# Nand2Tetris

The official Nand2Tetris 2.7 desktop suite is installed here, with an isolated
Eclipse Temurin 17 runtime for Apple Silicon in `.runtime/`.

Open the simulator:

```sh
cd ~/dev/learning/nand2tetris
./hardware-simulator
```

Edit the starter chips in `projects/1/`. In the simulator, select File → Load
Script and open the matching `.tst` file, then run it.

After implementing a chip, run its supplied test from the terminal:

```sh
./hardware-simulator projects/1/Not.tst
```

The HDL exercises are untouched and are not expected to pass before you implement
them. The remaining course projects are included in `projects/`.

The launcher selects the bundled Java runtime without changing shell profiles or
system Java. To run other supplied tools, explicitly set JAVA_HOME and PATH to
this folder's `.runtime/java` and `.runtime/java/bin` in your terminal session.

Sources: https://www.nand2tetris.org/software and https://adoptium.net/installation/archives

The course now recommends its online IDE; this desktop suite is legacy software.

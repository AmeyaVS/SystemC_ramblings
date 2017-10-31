# README

This Folder contains an example of an FIR filter design.

* Files:
  - `fir.h/cpp`: Source files for the SystemC FIR filter design.
  - `tb.h/cpp`: Source files for the SystemC fir module testbench.
  - `firsytemmain.cpp`: Source file for instantiating the fir and the testbench module and connecting them together for running the Simulation.
  - `golden/ref_output.dat`: Reference output for comparing the results with the simulation results.
  - `Makefile`: use make to build the project and execute the simulation.(**Will be deprecated**)
  - `CMakeLists.txt`: CMake based build system generator, this will support
    variety of platforms.

## Steps

**Note:** Assuming UNIX based systems.

1. Generate Build Scripts:
    ```sh
    cmake ..
    ```
2. Run `make` to build the example.
3. Run `make test` to run the simulation.
4. The simulation generates an output file `output.dat` which is compared with
the `golden/ref_output.dat` file after simulation ends.
4. If both files are identical then the simulation has completed successfully otherwise not.

Instead of generating the test vectors manually using code, one can actually
read a file of samples required for the FIR filter input, and pass it to the
FIR filter via the `tb.cpp` source file.

**Note:** For the variable input one needs corresponding output file in the
golden directory and necessary changes have to be made in the
[CMakeLists.txt](CMakeLists.txt) for the same.


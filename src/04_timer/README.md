# README

This folder contains the example of a 8-Bit Timer design.

**Note:** This project is currently incomplete kindly **do not** use this
project in it's current state.

* Files:
  - `timer.h/cpp`: Source files for the SystemC Timer module.
  - `timer_tb.h/cpp`: Source files for the SystemC Timer test-bench module.
  - `defines.h`: Common Header file setting up the Timer parameters.
  - `main_timer_check.cpp`: The Source file for the Timer module and the testbench instantiation.
  - `Makefile`: Used to build the project.(**Deprecated**)
  - [CMakeLists.txt](CMakeLists.txt): CMake Build System Generator support file for this
	  project.

## Steps

1. Configure using `CMake`:
    ```sh
    mkdir build
    cd build
    cmake ..
    ```
2. Build:
    ```sh
    make
    ```
3. Observe the output using the two implementation of the source method in the
[timer_tb.cpp](timer_tb.cpp) file.

**Warning:** while running the simulation for longer duration it can lead to exponentially growing vcd trace file.

# README

This folder contains the example of a 32-Bit RAM memory design.

**Note:** This project is currently incomplete kindly **do not** use this
project in it's current state.

* Files:
  - `memory.h/cpp`: Source files for the SystemC RAM module.
  - `main_mem_check.cpp`: Source file containing the Testbench for the module.
  - `Makefile`: Used to build and run the project.(**Deprecated**)
  - `data/gen_ram.c`: Source file used to create a utility for generating the ram)init file used to initialize the RAM module.
  - `data/Makefile`: Used to generate the gen_ram executable.(**Deprecated**)
  - `data/ram_init`: Sample ram initialization file.

### gen_ram Usage:

after running make in the data folder which would generate the `gen_ram` executable.

    ```sh
    ./gen_ram <Input a number>
    ```
**Note:** This will create a file ram_init containing <number of lines of 32-bit ints in hex form>.

**TO-DO:**
	Generate more test coverage cases for the memory module.

#include "driver.h"

void driver::prc_driver() {
  sc_dt::sc_uint<3> pattern;
  pattern = 0;
  while(1) {
    d_a = pattern[0];
    d_b = pattern[1];
    d_cin = pattern[2];
    wait(5, sc_core::SC_NS);
    pattern++;
  }
}


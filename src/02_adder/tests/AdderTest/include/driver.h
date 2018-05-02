#ifndef __DRIVER_H
#define __DRIVER_H

#include <systemc>

SC_MODULE(driver) {
  sc_core::sc_out<bool> d_a, d_b, d_cin;

  void prc_driver(void);

  SC_CTOR(driver):
    d_a("d_a"),
    d_b("d_b"),
    d_cin("d_cin")
  {
    SC_THREAD(prc_driver);
  }
};

#endif /* __DRIVER_H */


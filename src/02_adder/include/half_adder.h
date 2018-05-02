#ifndef __HALF_ADDER_H
#define __HALF_ADDER_H

#include <systemc>

SC_MODULE(half_adder) {
  sc_core::sc_in<bool> a, b;
  sc_core::sc_out<bool> sum, carry;

  void prc_half_adder(void);
  void tracing(sc_core::sc_trace_file*);

  SC_CTOR(half_adder):
    a("a"),
    b("b"),
    sum("sum"),
    carry("carry")
  {
    SC_METHOD(prc_half_adder);
    sensitive << a << b;
    dont_initialize();
  }
};

#endif /* __HALF_ADDER_H */

#ifndef __FULL_ADDER_H
#define __FULL_ADDER_H

#include <systemc>
#include "half_adder.h"

SC_MODULE(full_adder) {
  sc_core::sc_in<bool> a, b, ci;
  sc_core::sc_out<bool> sum, co;

  sc_core::sc_buffer<bool> s1, c1, c2;

  void prc_or(void);
  void tracing(sc_core::sc_trace_file *tf);

  half_adder *ha1, *ha2;

  SC_CTOR(full_adder):
    a("a"),
    b("b"),
    ci("ci"),
    sum("sum"),
    co("co"),
    s1("s1"),
    c1("c1"),
    c2("c2")
  {

    ha1 = new half_adder("ha1");
    ha1->a(a);
    ha1->b(b);
    ha1->sum(s1);
    ha1->carry(c1);

    ha2 = new half_adder("ha2");
    (*ha2)(s1, ci, sum, c2);

    SC_METHOD(prc_or);
    sensitive << c1 << c2;
    dont_initialize();
  }

  ~full_adder() {
    delete ha2;
    delete ha1;
  }
};

#endif /* __FULL_ADDER_H */

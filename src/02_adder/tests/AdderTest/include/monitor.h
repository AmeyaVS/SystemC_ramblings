#ifndef __MONITOR_H
#define __MONITOR_H

#include <systemc>

SC_MODULE(monitor) {
  sc_core::sc_in<bool> m_a, m_b, m_cin, m_sum, m_cout;

  void prc_monitor(void);

  SC_CTOR(monitor):
    m_a("m_a"),
    m_b("m_b"),
    m_cin("m_cin"),
    m_sum("m_sum"),
    m_cout("m_cout")
  {
    SC_METHOD(prc_monitor);
    sensitive << m_sum
              << m_cout;
#if 0
              << m_b
              << m_cin
              << m_sum
              << m_cout;
#endif
    dont_initialize();
  }
};

#endif /* __MONITOR_H */


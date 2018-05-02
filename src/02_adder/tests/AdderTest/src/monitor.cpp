#include "monitor.h"

void monitor::prc_monitor() {
  std::cout << "At time " << sc_core::sc_time_stamp() << " :: ";
  std::cout << "(a, b, cin): " << m_a << m_b << m_cin;
  std::cout << " (sum, carry_out): " << m_sum << m_cout << std::endl;
}


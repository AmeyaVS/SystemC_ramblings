#ifndef __HALF_ADDER_H
#define __HALF_ADDER_H

#include <systemc.h>

SC_MODULE(half_adder) {
	sc_in< bool > a, b;
	sc_out< bool > sum, carry;

	void prc_half_adder(void);
	void tracing(sc_trace_file*);

	SC_CTOR(half_adder) {
		SC_METHOD(prc_half_adder);
		sensitive << a << b;
	}
};

#endif /* __HALF_ADDER_H */

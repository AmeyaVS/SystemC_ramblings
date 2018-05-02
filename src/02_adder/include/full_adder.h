#ifndef __FULL_ADDER_H
#define __FULL_ADDER_H

#include "half_adder.h"

SC_MODULE(full_adder) {
	sc_in< bool > a, b, ci;
	sc_out< bool > sum, co;

	sc_signal< bool > s1, c1, c2;

	void prc_or(void);
	void tracing(sc_trace_file *tf);

	half_adder *ha1, *ha2;

	SC_CTOR(full_adder) {

		ha1 = new half_adder("ha1");
		ha1->a(a);
		ha1->b(b);
		ha1->sum(s1);
		ha1->carry(c1);

		ha2 = new half_adder("ha2");
		(*ha2)(s1, ci, sum, c2);

		SC_METHOD(prc_or);
		sensitive << c1 << c2;
	}

	~full_adder() {
		delete ha2;
		delete ha1;
	}
};

#endif /* __FULL_ADDER_H */

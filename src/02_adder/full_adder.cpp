#include "full_adder.h"

void full_adder::prc_or(void ) {
	// This is prefered
	co.write(c1.read() | c2.read());
	// over than the above one
	//co = c1 | c2;
}

void full_adder::tracing(sc_trace_file *tf) {
	const std::string str = this->name();
	sc_trace(tf, this->a, str+".a");
	sc_trace(tf, this->b, str+".b");
	sc_trace(tf, this->ci, str+".ci");
	sc_trace(tf, this->sum, str+".sum");
	sc_trace(tf, this->co, str+".co");

	// Trace the sub-modules also
	// comment these line to not to trace the sub-modules used.
	ha1->tracing(tf);
	ha2->tracing(tf);
}

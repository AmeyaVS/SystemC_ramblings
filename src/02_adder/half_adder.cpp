#include "half_adder.h"

void half_adder::prc_half_adder(void) {
	// This method of implementation is prefered
	sum.write( a.read() ^ b.read());
	carry.write( a.read() & b.read());
	// Over this method
	//sum = a ^ b;
	//carry = a & b;
}

void half_adder::tracing(sc_trace_file *tf) {
	const std::string str = this->name();
	sc_trace(tf, this->a, str+".a");
	sc_trace(tf, this->b, str+".b");
	sc_trace(tf, this->sum, str+".sum");
	sc_trace(tf, this->carry, str+".carry");
}

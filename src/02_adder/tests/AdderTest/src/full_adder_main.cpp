#include "monitor.h"
#include "driver.h"
#include "full_adder.h"

int sc_main(int argc, char* argv[]) {
	sc_signal< bool > t_a, t_b, t_cin, t_sum, t_cout;

	sc_trace_file *tf = sc_create_vcd_trace_file("FullAdder");

	full_adder fa1("fa1");
	// Deprecated
	//fa1 << t_a << t_b << t_cin << t_sum << t_cout;
	fa1.a(t_a);
	fa1.b(t_b);
	fa1.ci(t_cin);
	fa1.sum(t_sum);
	fa1.co(t_cout);

	fa1.tracing(tf);

	driver d1("d1");
	d1.d_a(t_a);
	d1.d_b(t_b);
	d1.d_cin(t_cin);

	monitor m1("m1");
	// Deprecated
	//m1 << t_a << t_b << t_cin << t_sum << t_cout;
	m1.m_a(t_a);
	m1.m_b(t_b);
	m1.m_cin(t_cin);
	m1.m_sum(t_sum);
	m1.m_cout(t_cout);

	sc_start(100, SC_NS);

	sc_close_vcd_trace_file(tf);
	// sc_int<1024 is invalid only supported value is 64 bit only need to test this
	//cout << sizeof(sc_int<1024>);

	return 0;

}


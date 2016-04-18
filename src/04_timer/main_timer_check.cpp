#include "timer.h"
#include "timer_tb.h"

SC_MODULE(SYSTEM) {
	timer *t;
	timer_tb *tb;

	sc_clock clk_sig;
	sc_signal < bool > rst_sig;

	sc_signal < bool > read_en_sig;
	sc_signal < bool > write_en_sig;

	sc_signal < sc_uint<ADDR_WIDTH> > addr_sig;
	sc_signal < sc_uint<DATA_WIDTH> > data_in_sig;

	sc_signal < bool > intr0_sig;
	sc_signal < bool > intr1_sig;

	sc_signal < sc_uint<DATA_WIDTH> > data_out_sig;

	sc_trace_file *wf;

	SC_CTOR(SYSTEM) : clk_sig("clk_sig", 10, SC_NS) {
		tb = new timer_tb("tb");
		tb->clk(clk_sig);
		tb->rst(rst_sig);
		tb->read_en(read_en_sig);
		tb->write_en(write_en_sig);
		tb->addr(addr_sig);
		tb->data_in(data_in_sig);
		tb->intr0(intr0_sig);
		tb->intr1(intr1_sig);
		tb->data_out(data_out_sig);
		
		char str_vcd_file_name[100];
		snprintf(str_vcd_file_name, 100, "%s", SC_TRACE_FILE);
		wf = sc_create_vcd_trace_file(str_vcd_file_name);

		t = new timer("t");
		//t->clk(clk_sig);		
		t->clk(clk_sig);
		t->rst(rst_sig);
		t->read_en(read_en_sig);
		t->write_en(write_en_sig);
		t->addr(addr_sig);
		t->data_in(data_in_sig);
		t->intr0(intr0_sig);
		t->intr1(intr1_sig);
		t->data_out(data_out_sig);

		t->tracing(wf);
	}

	~SYSTEM() {
		sc_close_vcd_trace_file(wf);
		delete t;
		delete tb;
	}
};	

int sc_main(int argc, char *argv[]) {

	SYSTEM *top = NULL;
	top = new SYSTEM("top");
	sc_start();

	delete top;
	return 0;
}

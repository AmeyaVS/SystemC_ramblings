#include "memory.h"

int sc_main(int argc, char* argv[]) {
	memory *mem = new memory("memory");
	sc_set_time_resolution(1, SC_PS);

	char str_vcd_file_name[100];
	snprintf(str_vcd_file_name, 100, "%s", SC_TRACE_FILE);
	sc_trace_file *wf = sc_create_vcd_trace_file(str_vcd_file_name);
	sc_trace(wf, (*mem).address, "address");
	sc_trace(wf, (*mem).data_in, "data_in");
	sc_trace(wf, (*mem).data_out, "data_out");
	sc_trace(wf, (*mem).enable, "enable");
	sc_trace(wf, (*mem).rw, "rw");

	sc_signal < bool >  enable, rw;
	sc_signal < sc_uint<BITWIDTH> > data_in;
	sc_signal < sc_uint<BITWIDTH> > data_out;
	sc_signal< sc_uint<ADDWIDTH> > address;

	(*mem).rw(rw);
	(*mem).data_in(data_in);
	(*mem).data_out(data_out);
	(*mem).address(address);
	(*mem).enable(enable);

	enable  = 0;
	data_in = 0;
	data_out= 0;
	address = 0;
	rw      = 0;
	sc_start(0, SC_PS);

	rw      = 1;
	address.write(0x10<<2);
	data_in.write(0x110011);
	enable  = 1;
	sc_start(5, SC_PS);

	enable  = 0;
	sc_start(5, SC_PS);

	address.write(0x12<<2);
	data_in.write(0x1100);
	enable  = 1;
	sc_start(5, SC_PS);

	address.write(0x8<<2);
	data_in.write(0x1010);
	sc_start(5, SC_PS);

	rw      = 0;
	address = 0x10<<2;
	sc_start(5, SC_PS);

	address = 0x1<<2;
	sc_start(5, SC_PS);

	address = 0x3<<2;
	sc_start(5, SC_PS);

	address = 0x50;
	sc_start(5, SC_PS);

	address = 0;
	sc_start(5, SC_PS);

	enable  = 0;
	sc_start(5, SC_PS);

	sc_start(5, SC_PS);

	(*mem).debugMemory();
	sc_close_vcd_trace_file(wf);

	delete mem;
	return(0);
}

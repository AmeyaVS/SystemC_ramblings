#ifndef __TIMER_TB_H
#define __TIMER_TB_H

#include <systemc.h>
#include "defines.h"

SC_MODULE(timer_tb) {
	sc_in < bool > clk;
	sc_out < bool > rst;
	sc_out < bool > read_en;
	sc_out < bool > write_en;
	sc_out < bool > enable;

	sc_out < sc_uint<ADDR_WIDTH> > addr;
	sc_out < sc_uint<DATA_WIDTH> > data_in;

	sc_in < bool > intr0;
	sc_in < bool > intr1;

	sc_in < sc_uint<DATA_WIDTH> > data_out;

	//const int base_addr;

	void source(void);
	void sink(void);

	SC_CTOR(timer_tb) {
	//timer_tb(sc_module_name name_, const int bAddr = 0) : sc_module(name_), base_addr(bAddr) {
		//SC_CTHREAD(source, clk.pos()||clk.neg());
		//SC_CTHREAD(sink, clk.pos()||clk.neg());
		SC_THREAD(source);
		sensitive << clk.pos() << clk.neg(); // << intr0 << intr1;
		//SC_THREAD(sink);
		//sensitive << intr0 << intr1;
	}

	//SC_HAS_PROCESS(timer_tb);
};

#endif /* __TIMER_TB_H */

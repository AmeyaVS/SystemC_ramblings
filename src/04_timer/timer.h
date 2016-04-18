#ifndef __TIMER_H
#define __TIMER_H

#include <systemc.h>

#define ADDR_WIDTH 8
#define DATA_WIDTH 8

SC_MODULE(timer) {
	/* Input Port Declaration */
	sc_in < bool > clk;
	sc_in < bool > rst;
	sc_in < bool > read_en;
	sc_in < bool > write_en;

	sc_in < sc_uint<ADDR_WIDTH> > addr;
	sc_in < sc_uint<DATA_WIDTH> > data_in;

	sc_out < bool > intr0;
	sc_out < bool > intr1;

	sc_out < sc_uint<DATA_WIDTH> > data_out;

	sc_uint<DATA_WIDTH> timer_cntrl;
	sc_uint<DATA_WIDTH> timer_val;
	sc_uint<DATA_WIDTH> timer_cmp;
	sc_uint<DATA_WIDTH> timer_intr_status;

	void prc_timer(void);

	SC_CTOR(timer) {
		SC_METHOD(prc_timer);
		sensitive << clk.pos() << clk.neg();
	}

};

#endif /* __TIMER_H */

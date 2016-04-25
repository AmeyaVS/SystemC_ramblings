#ifndef __TIMER_H
#define __TIMER_H

#include <systemc.h>
#include "defines.h"

SC_MODULE(timer) {
	/* Input Port Declaration */
	sc_in < bool > clk;
	sc_in < bool > rst;
	sc_in < bool > read_en;
	sc_in < bool > write_en;
	sc_in < bool > enable;

	sc_in < sc_uint<ADDR_WIDTH> > addr;
	sc_in < sc_uint<DATA_WIDTH> > data_in;

	sc_out < bool > intr0;
	sc_out < bool > intr1;

	sc_out < sc_uint<DATA_WIDTH> > data_out;

	sc_uint<DATA_WIDTH> timer_cntrl;
	sc_uint<DATA_WIDTH> timer_val;
	sc_uint<DATA_WIDTH> timer_cmp;
	sc_uint<DATA_WIDTH> timer_intr_status;

	//const int base_addr;

	void prc_timer(void);
#if 0
	void prc_intr(void) {
		intr0.write(timer_intr_status[TMR_INTR_CMP]);
		intr1.write(timer_intr_status[TMR_INTR_OV]);
	}
#endif
	void prc_bus_logic(void);

	SC_CTOR(timer) {
	//timer(sc_module_name name_, const int bAddr = 0) : base_addr(bAddr) {
		SC_METHOD(prc_timer);
		sensitive << clk.pos() << clk.neg() << rst.neg();
		//SC_METHOD(prc_intr);
		//sensitive << timer_intr_status;//<< timer_intr_status[TMR_INTR_CMP] << timer_intr_status[TMR_INTR_OV];
		SC_METHOD(prc_bus_logic);
		sensitive << clk.pos() << clk.neg() << rst.neg();
	}

	//SC_HAS_PROCESS(timer);

	void tracing(sc_trace_file *wf) {
		if(NULL != wf) {
			const std::string str = this->name();
			sc_trace(wf, this->clk, str + ".clk");
			sc_trace(wf, this->rst, str + ".rst");
			sc_trace(wf, this->enable, str + ".enable");
			sc_trace(wf, this->addr, str + ".addr");
			sc_trace(wf, this->data_in, str + ".data_in");
			sc_trace(wf, this->read_en, str + ".read_en");
			sc_trace(wf, this->write_en, str + ".write_en");
			sc_trace(wf, this->intr0, str + ".intr0");
			sc_trace(wf, this->intr1, str + ".intr1");
			sc_trace(wf, this->data_out, str + ".data_out");
			sc_trace(wf, this->timer_val, str + ".timer_val");
		}
	}

};

#endif /* __TIMER_H */

#include <systemc.h>
#include "fir.h"
#include "tb.h"

SC_MODULE(SYSTEM) {
	// Module declarations
	tb *tb0;
	fir *fir0;

	// Local signal declarations
	sc_signal< bool > rst_sig;
	sc_signal< sc_int<16> > inp_sig;

	sc_signal< bool > inp_sig_vld;
	sc_signal< bool > inp_sig_rdy;

	sc_signal< sc_int<16> > outp_sig;

	sc_signal< bool > outp_sig_vld;
	sc_signal< bool > outp_sig_rdy;

	sc_clock clk_sig;
	
	SC_CTOR(SYSTEM) :clk_sig("clk_sig", 10, SC_NS) {
		// Module instance signal connections
		tb0 = new tb("tb0");
		tb0->clk(clk_sig);
		tb0->rst(rst_sig);
		tb0->inp(inp_sig);
		tb0->outp(outp_sig);

		tb0->inp_vld(inp_sig_vld);
		tb0->inp_rdy(inp_sig_rdy);
		tb0->outp_vld(outp_sig_vld);
		tb0->outp_rdy(outp_sig_rdy);

		fir0 = new fir("fib0");
		fir0->clk(clk_sig);
		fir0->rst(rst_sig);
		fir0->inp(inp_sig);
		fir0->outp(outp_sig);

		fir0->inp_vld(inp_sig_vld);
		fir0->inp_rdy(inp_sig_rdy);
		fir0->outp_vld(outp_sig_vld);
		fir0->outp_rdy(outp_sig_rdy);
	}

	~SYSTEM() {
		// Destructor for removing simulations modules
		delete fir0;
		delete tb0;
	}
};

SYSTEM *top = NULL;

int sc_main(int argc, char *argv[]) {
	top = new SYSTEM("top");
	sc_start();

	delete top;
	return 0;
}

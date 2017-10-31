#include "fir.h"

//Coefficients for each FIR
const sc_int<8> coef[] = {18, 77, 107, 77, 18};

void fir::fir_main(void)
{
	//Reset Code
	//Rest internal variables
	//Reset outputs
	//wait();
	//
	//while(true) {
	//Read inputs
	//Algorithm code
	//Write Outputs
	//wait();
	//}
	
	sc_int<16> taps[5];

	// Initialize the handshake
	inp_rdy.write(0);
	outp_vld.write(0);
	outp.write(0);
	for(int i = 0; i < 4; ++i) {
		taps[i] = 0;
	}
	wait();

	while(true) {
		for(int i = 4; i>0; i--) {
			taps[i] = taps[i-1];
		}
		inp_rdy.write(1);
		// To check the guard condition added to the test bench
		//wait(1000000);
		do {
			wait();
		} while(! inp_vld.read());
		taps[0] = inp.read();
		inp_rdy.write(0);

		sc_int<16> val;
		for(int i = 0; i<5; ++i) {
			val += coef[i] * taps[i];
		}

		outp.write(val);
		outp_vld.write(1);
		do {
			wait();
		} while(!outp_rdy.read());
		outp_vld.write(0);
	}
}

void fir::tracing(sc_trace_file *tf) {
	const std::string str = this->name();
	sc_trace(tf, this->clk, str+".clk");
	sc_trace(tf, this->rst, str+".rst");

	sc_trace(tf, this->inp, str+".inp");
	sc_trace(tf, this->inp_vld, str+".inp_vld");
	sc_trace(tf, this->inp_rdy, str+".inp_rdy");

	sc_trace(tf, this->outp, str+".outp");
	sc_trace(tf, this->outp_vld, str+".outp_vld");
	sc_trace(tf, this->outp_rdy, str+".outp_rdy");
}

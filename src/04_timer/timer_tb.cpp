#include "timer_tb.h"

void timer_tb::source(void) {
	addr.write(0);
	read_en.write(0);
	write_en.write(0);
	data_in.write(0);
	rst.write(0);
	wait();
	rst.write(1);
	wait();

	// Generate signals here
	int i = 0;
	while(true) {
		wait();
		++i;
		if(i >200) {
			break;
		}
	}
	sc_stop(); // stopping the simulation.
}

void timer_tb::sink(void) {
	//if interrupt is detected notify source then clear it.
	wait();
	while(true) {
		wait();
	}
}

#include "timer_tb.h"

void timer_tb::source(void) {
	int temp_intr = 0;
	const int temp_cmp_data = 50;
	addr.write(0);
	read_en.write(0);
	write_en.write(0);
	enable.write(0);
	data_in.write(0);
	rst.write(0);
	wait();
	rst.write(1);
	wait();

	// Generate signals here
	
	//Write the compare value for the timer
	addr.write(0x8);
	read_en.write(0);
	write_en.write(1);
	data_in.write(50); //50 clock cycles
	enable.write(1);
	wait();

	addr.write(0x0);
	data_in.write(0x7); // Enable timer enable Overflow interrupt and compare interrupts
	wait();
	enable.write(0);

	int i = 0;
	while(true) {
		wait();
		++i;
		if(i >1500) {
			break;
		}
		
		if(1 == intr1.read()) {
			temp_intr |= (1<<TMR_INTR_OV);
		}

		if(1 == intr0.read()) {
			temp_intr |= (1<<TMR_INTR_CMP);
			// Read back the compare value register
			addr.write(0x8);
			read_en.write(1);
			write_en.write(0);
			enable.write(1);
			wait();
			int temp = data_out.read();
			// Modify the register
			temp += temp_cmp_data;
			// Write back the register
			addr.write(0x8);
			read_en.write(0);
			write_en.write(1);
			data_in.write(temp);
			wait();
			enable.write(0);
			wait();
		}
		// Clear the interrupts
		if(intr1.read() || intr0.read()) {
			addr.write(0xC);
			read_en.write(0);
			write_en.write(1);
			enable.write(1);
			data_in.write(temp_intr);
			wait();
			enable.write(0);
		}
		temp_intr = 0;

	}
	sc_stop(); // stopping the simulation.
}

#if 0
void timer_tb::sink(void) {
	//if interrupt is detected notify source then clear it.
	int temp_intr = 0;
	const int temp_cmp_data = 50;
	wait();
	while(true) {
		wait();
		if(1 == intr1.read()) {
			temp_intr |= (1<<TMR_INTR_OV);
		}

		if(1 == intr0.read()) {
			temp_intr |= (1<<TMR_INTR_CMP);
			// Read back the compare value register
			addr.write(0x8);
			read_en.write(1);
			write_en.write(0);
			enable.write(1);
			wait();
			int temp = data_out.read();
			// Modify the register
			temp += temp_cmp_data;
			// Write back the register
			addr.write(0x8);
			read_en.write(0);
			write_en.write(1);
			data_in.write(temp);
			wait();
			enable.write(0);
			wait();
		}
		// Clear the interrupts
		if(intr1.read() || intr0.read()) {
			addr.write(0xC);
			read_en.write(0);
			write_en.write(1);
			enable.write(1);
			data_in.write(temp_intr);
			wait();
			enable.write(0);
		}
		temp_intr = 0;
	}
}
#endif

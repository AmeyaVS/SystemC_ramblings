#include "timer_tb.h"

void timer_tb::source(void) {
	enableDebug(); // This will enable the logs on the console
	read_en.write(0);
	write_en.write(0);
	enable.write(1);
	rst.write(1);
	wait();
	rst.write(0);
	wait();
	rst.write(1);
	addr.write(0x8);
	read_en.write(0);
	write_en.write(1);
	data_in.write(100); // Writing some value in timer_cmp register
	wait();
	addr.write(0x0);
	read_en.write(0);
	write_en.write(1);
	data_in.write(0x7); // Enable the timer interrupts
	wait();
	enable.write(0);
	wait(18415, SC_NS);
	enable.write(1);
	wait();
	addr.write(0x4);
	read_en.write(1);
	write_en.write(0);
	wait();
	wait();
	cout << "@" << sc_time_stamp() << " Timer Val: " << data_out.read() << endl;
	wait(1520, SC_NS);
	cout << "@" << sc_time_stamp() << " Timer Val: " << data_out.read() << endl;
	// Stop the timer
	addr.write(0x0);
	write_en.write(1);
	read_en.write(0);
	data_in.write(0);
	wait();
	//wait();
	//cout << "@" << sc_time_stamp() << endl;
	wait(500, SC_NS);
	// Read the timer val register
	addr.write(0x4);
	read_en.write(1);
	write_en.write(0);
	wait();
	wait();
	cout << "@" << sc_time_stamp() << " Timer Val: " << data_out.read() << endl;
	wait(500, SC_NS);
	// Enable the timer again.
	addr.write(0x0);
	read_en.write(0x0);
	write_en.write(1);
	read_en.write(0);
	data_in.write(0x7);
	//cout << "@" << sc_time_stamp() << endl;
	// Read the timer_val register.
	wait(8980, SC_NS);
	addr.write(0x4);
	read_en.write(1);
	write_en.write(0);
	wait();
	wait();
	cout << "@" << sc_time_stamp() << " Timer Val: " << data_out.read() << endl;
	wait();
	addr.write(0x8);
	write_en.write(1);
	read_en.write(0);
	data_in.write(40);
	//cout << "@" << sc_time_stamp() << endl;
	wait(10000, SC_NS);
	disableDebug();
	//cout << "@" << sc_time_stamp() << endl;
	wait(960000, SC_NS);
	enableDebug();
	//cout << "@" << sc_time_stamp() << endl;
	wait(740, SC_NS);
	addr.write(0x4);
	read_en.write(1);
	write_en.write(0);
	wait();
	wait();
	cout << "@" << sc_time_stamp() << " Timer Val: " << data_out.read() << endl;
	wait(9250, SC_NS);
	disableDebug();
	cout << "@" << sc_time_stamp() << endl;
	wait(98990, SC_US);
	cout << "@" << sc_time_stamp() << endl;
	sc_stop();
}

#if 0
void timer_tb::source(void) {
	int temp_intr = 0;
	const int temp_cmp_data = 50;
	enableDebug();
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
			wait(); // Added one more wait statement since read below was not returning correct value.
			int temp = data_out.read();
			// Modify the register
			//cout << "Temp: " << temp << endl;
			temp += temp_cmp_data;
			//cout << "Timer cmp: " << temp << endl;
			wait();
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
#endif

void timer_tb::sink0(void) {
	//wait();
	while(true) {
		if(1 == this->debug) {
			if(1 == intr0.read()) {
				cout << "Interrupt asserted: Intr0 ( " << sc_time_stamp() << " )" << endl;
			}
		}
		wait();
	}
}

void timer_tb::sink1(void) {
	while(true) {
		if(1 == intr1.read()) {
			cout << "Interrupt asserted: Intr1 ( " << sc_time_stamp() << " )" << endl;
		}
		wait();
	}
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

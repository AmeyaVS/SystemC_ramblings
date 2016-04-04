#ifndef __DRIVER_H
#define __DRIVER_H

#include <systemc.h>

SC_MODULE(driver) {
	sc_out< bool > d_a, d_b, d_cin;

	void prc_driver();

	SC_CTOR(driver) {
		SC_THREAD(prc_driver);
	}
};

#endif /* __DRIVER_H */


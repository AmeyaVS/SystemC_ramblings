#include "timer.h"

void timer::prc_timer(void) {
	if(rst) {
		intr0.write(0);
		intr1.write(0);
		data_out.write(0);

		timer_cntrl = 0;
		timer_val = 0;
		timer_cmp = 0;
		timer_intr_status = 0;
	} else {
		timer_val = timer_val + 1;
	}
}

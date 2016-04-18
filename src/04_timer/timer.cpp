#include "timer.h"

void timer::prc_timer(void) {
	if(0 == rst) {
		intr0.write(0);
		intr1.write(0);
		//data_out.write(0);

		timer_cntrl = 0;
		timer_val = 0;
		timer_cmp = 0;
		timer_intr_status = 0;
	} else {
		if(1 == timer_cntrl[TMR_CNTRL_EN]) { // If timer is enabled
			if(1 == timer_cntrl[TMR_CNTRL_CMP]) {
				if( timer_val == timer_cmp) {
					timer_intr_status[TMR_INTR_CMP] = 1;
					intr0.write(1);
				}
			}
			if(1 == timer_cntrl[TMR_CNTRL_OV]) {
				if(timer_val == MAX) {
					timer_intr_status[TMR_INTR_OV] = 1;
					intr1.write(1);
				}
			}
			timer_val = timer_val + 1;
		}
	}
}

void timer::prc_bus_logic(void) {
	if(0 == rst) {
		data_out.write(0);
	} else {
		int tempAddr = addr.read();
		int tempdata = 0;
		tempAddr = tempAddr - base_addr;
		if(tempAddr >= 0 && tempAddr <= 0xC) {
			if(read_en == 1 && write_en == 0) {
				switch(tempAddr) {
					case 0:
						tempdata = timer_cntrl;
						break;
					case 4:
						tempdata = timer_val;
						break;
					case 8:
						tempdata = timer_cmp;
						break;
					case 0xC:
						tempdata = timer_intr_status;
						break;
				}
				data_out.write(tempdata);
			} else if(read_en == 0 && write_en == 1) {
				tempdata = data_in.read();
				switch(tempAddr) {
					case 0:
						timer_cntrl = tempdata;
						break;
					case 8:
						timer_cmp = tempdata;
						break;
					case 0xC:
						if(timer_intr_status[TMR_INTR_OV] && (tempdata & (1<<TMR_INTR_OV))) {
							tempdata = timer_intr_status ^ (1<<TMR_INTR_OV);
							timer_intr_status = tempdata;
							intr1.write(0);
						}
						if(timer_intr_status[TMR_INTR_CMP] && (tempdata & (1<<TMR_INTR_CMP))) {
							tempdata = timer_intr_status ^ (1<<TMR_INTR_CMP);
							timer_intr_status = tempdata;
							intr0.write(0);
						}
						break;
					default:
						break;
				}
				data_out.write(tempdata);
			} else {
				data_out.write(0);
			}
		} else {
			data_out.write(0);
		}
	}
}

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
				}
			}
			if(1 == timer_cntrl[TMR_CNTRL_OV]) {
				if(timer_val == MAX) {
					timer_intr_status[TMR_INTR_OV] = 1;
				}
			}
			timer_val = timer_val + 1;
			intr0.write(timer_intr_status[TMR_INTR_CMP]);
			intr1.write(timer_intr_status[TMR_INTR_OV]);
		}
	}
}

void timer::prc_bus_logic(void) {
	if(0 == rst) {
		data_out.write(0);
	} else {
		int tempAddr = addr.read();
		int tempData = 0;
		if(enable == 1) {
			if(read_en == 1 && write_en == 0) {
				switch(tempAddr) {
					case 0x0:
						tempData = timer_cntrl;
						break;
					case 0x4:
						tempData = timer_val;
						break;
					case 0x8:
						tempData = timer_cmp;
						break;
					case 0xC:
						tempData = timer_intr_status;
						break;
					default:
						tempData = 0;
				}
				data_out.write(tempData);
			} else if(read_en == 0 && write_en == 1) {
				tempData = data_in.read();
				switch(tempAddr) {
					case 0x0:
						timer_cntrl = tempData;
						break;
					case 0x8:
						timer_cmp = tempData;
						break;
					case 0xC:
						if(timer_intr_status[TMR_INTR_OV] && (tempData & (1<<TMR_INTR_OV))) {
							tempData = timer_intr_status ^ (1<<TMR_INTR_OV);
							timer_intr_status = tempData;
							//intr1.write(timer_intr_status[TMR_INTR_OV]);
						}
						if(timer_intr_status[TMR_INTR_CMP] && (tempData & (1<<TMR_INTR_CMP))) {
							tempData = timer_intr_status ^ (1<<TMR_INTR_CMP);
							timer_intr_status = tempData;
							//intr0.write(timer_intr_status[TMR_INTR_CMP]);
						}
						break;
					default:
						break;
				}
				data_out.write(tempData);
			}
		} else {
			data_out.write(0);
		}
#if 0
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
#endif
	}
}

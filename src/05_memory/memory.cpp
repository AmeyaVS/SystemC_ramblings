#include "memory.h"

void memory::prc_memory() {
	sc_lv<BITWIDTH> tempData(SC_LOGIC_Z);
	int tempAddr = 0;
	if(enable.read() == 1) {
		cout << sc_time_stamp();
		tempAddr = address.read().to_int();
		if(rw.read() == 1) {
			tempData = data.read().to_int();
			ramData[tempAddr] = tempData.to_int();
			cout << " Writing Data " << tempData << " at " <<  tempAddr << endl;
		} else {
			tempData = ramData[tempAddr];
			data.write(tempData);
			cout << " Reading Data " << tempData << " at " << tempAddr << endl;
		}
	} else {
		data.write(tempData);
	}
}

void memory::debugMemory() {
	FILE *fRam = fopen("data/memdump", "w");
	if(fRam != NULL) {
		for(int i = 0; i<MEMORYSIZE; ++i) {
			fprintf(fRam, "%08X\n", ramData[i]);
		}
		fclose(fRam);
	} else {
		cerr << "Unable to create dump file" << endl;
	}
}

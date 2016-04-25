#include "memory.h"

void memory::prc_memory(void) {
	int tempData = 0;
	int tempAddr = 0;
	if(enable.read() == 1) {
#if DEBUG
		cout << sc_time_stamp();
#endif
		tempAddr = address.read().to_int();
		tempAddr >>= 2; // Since lower 2 bits will be trucated as each memory location is 32 bits. Not byte addressable memory
		if(rw.read() == 1) {
			tempData = data_in.read().to_int();
			ramData[tempAddr] = tempData; //.to_int();
#if DEBUG
			cout << " Writing Data " << tempData << " at " <<  tempAddr << endl;
#endif
		} else {
			tempData = ramData[tempAddr];
			data_out.write(tempData);
#if DEBUG
			cout << " Reading Data " << tempData << " at " << tempAddr << endl;
#endif
		}
	} else {
		data_out.write(tempData);
	}
}

void memory::debugMemory(void) {
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

#ifndef __MEMORY_H
#define __MEMORY_H

#include <systemc.h>

#define DEBUG 0

#define BITWIDTH 32
/* Each memory location is 32 bit storage space so for:
 * 1MB = 1024KB = 1024*1024/4 Bytes*/
#define MEMORYSIZE 1024*256
/* ADDWIDTH should be around log2(MEMORYSIZE)
 */
#define ADDWIDTH 20

SC_MODULE(memory) {
	sc_out < sc_uint<BITWIDTH> > data_out;
	sc_in < sc_uint<BITWIDTH> > data_in;
	sc_in < sc_uint<ADDWIDTH> > address;
	sc_in < bool > rw;
	sc_in < bool > enable;

	// Using C++ integer so as to save storage space used by sc_signal class.
	int ramData[MEMORYSIZE];

	void prc_memory();
	void debugMemory();

	SC_CTOR(memory) {
		SC_METHOD(prc_memory);
		sensitive << enable << rw << address;

		FILE *fRam = fopen("data/ram_init", "r");
		if(fRam != NULL) {
			int mem_word = 0;
			int i = 0;
			for(i = 0; i<MEMORYSIZE && fscanf(fRam, "%x", &mem_word) != EOF; ++i) {
				//fscanf(fRam, "%x", &mem_word);
				ramData[i] = mem_word;
			}
			for(; i < MEMORYSIZE; ++i) {
				ramData[i] = 0;
			}
			fclose(fRam);
		} else {
			for(int i = 0; i<MEMORYSIZE; ++i) {
				ramData[i] = 0;
			}
		}
	}
};

#endif /* __MEMORY_H */

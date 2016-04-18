/**
 * This program will accept only one input how many patterns,
 * to generate the memeory data layout in the ram_init file.
 */

#include <stdio.h>

int main() {
	int i;
	int T=100;
	FILE *fo = fopen("ram_init", "w"); // Open file for writing.
	if(NULL != fo) {
		scanf("%d", &T);
		srand(time(NULL)); // This seeds the random number generator.
		for(i = 0; i < T; ++i) {
			fprintf(fo, "%08X\n", rand()); // generates the random number in the file.
		}
		fclose(fo);
	}
	return 0;
}

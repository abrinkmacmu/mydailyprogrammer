#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	// program expects 1 int and 1 string argument
	if(argc != 3){
		printf("ERROR: please input int");
		return 0;
	}
	int n = atoi(argv[1]);
	printf("input is %s and atoi gives %d\n",argv[1],n);
	int N = n/2;
	printf("opening %s \n",argv[2]);
	// allocate list array to hold prime references
	int* list = (int*)calloc(N, sizeof(int));
	
	int i, j, v;
		for (i = 1; i <= N; ++i) {
		    for (j = i; (v = i+j+2*i*j) <= N; ++j) {
		        list[v-1] = 1;
		    }
		}

	FILE * pFile;
	printf("Printing primes to %s \n",argv[2]);
	pFile = fopen(argv[2],"w");
		for (i = 1; i <= N; ++i) {
		    if (!list[i-1]) {
		        fprintf(pFile,"%d\n", 2*i+1);
		    }
		}

	fclose(pFile);
    free(list);





	return 0;
}

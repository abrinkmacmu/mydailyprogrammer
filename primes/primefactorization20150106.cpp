#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int redivide(int, int, int*);

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("ERROR: please input int");
		return 0;
	}
	int n = atoi(argv[1]);
	printf("Prime Factorization of: %d\n",n);
	

	int prime = 0;
	int counter;
	int * count = &counter;
	FILE * pFile;
	int remainder = n;
	pFile = fopen("myprimes.txt","r");
	printf("opening myprimes.txt\n\n");
	printf("   %d = ",n);
	while(prime<n){

		//read list of primes
		fscanf(pFile, "%d", &prime);
		counter = 0;
		remainder = redivide(prime,remainder,count);
		//printf("%d divides %d i=%d times, Remainder is %d\n ",prime,n,counter,remainder); // debug printing	
		if(counter > 0){		
			printf("(%d^%d) ",prime, counter);
		}
		if(remainder == 0){
			break;
		}
		
	}
	fclose(pFile);
	printf("\n\nClosing myprimes.txt\n");
	return 0;
}

int redivide(int prime, int rem, int* i){
	//printf("Remainder in recursion is %d\n",rem); // debug printing
	if(0 ==(rem % prime)){
		*i = *i+1;
		redivide(prime,rem/prime,i);
	}
	if(*i > 0){	
		return (rem/((*i) * prime));
	} else {
		return rem;
	}
}	


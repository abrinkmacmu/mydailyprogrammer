#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	// program expects 1 int argument
	if(argc != 3){
		printf("ERROR: please input int");
		return 0;
	}
	int n = atoi(argv[1]);
	printf("input is %s and atoi gives %d\n",argv[1],n);

	sscanf(argv[1],"%d",&n);
	printf("input is %s and sscanf gives %d\n",argv[1],n);

	char *dummy;
	n = strtol(argv[1],&dummy,0);
	printf("input is %s and strtol gives %d ptr is %c\n",argv[1],n,*dummy);

	char filename[] = {""};
	strcpy(filename, argv[2]);
	printf("input string is %s and strcpy gives %s\n", argv[2], filename);
	return 0;
}

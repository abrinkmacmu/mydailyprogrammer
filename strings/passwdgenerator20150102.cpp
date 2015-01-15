/* passwdgenerator20150102.cpp
prompts user for length of password and output random alpha-Numeric password
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
	
	// define variables
	int pwlen = 1;
	int code = -1;

	// prompt user for password length
	printf("\n***PASSWORD GENERATOR PROGRAM BEGINNING***\n\n");	
	printf("please enter length of password:\n");	
	code = scanf("%d", &pwlen);
	printf("input length is: %d\n", pwlen);
	if(code < 0 or pwlen < 1) {
		printf("Not a valid entry, try again");
		printf("\n***PASSWORD GENERATOR PROGRAM ENDING***\n\n");
		return 0;
	}
		
	// generate random ascii values and typecast to char
	int i = 0;
	int num = 0;
	int sect = 0;
	char password[pwlen+1];
	srand(time(NULL));	
	for(i = 0; i<pwlen;i++){	
		sect = rand()%3;
		if(sect == 0){
			// generate number
			num = rand()%10;
			password[i] = (48+num);
		}
		if(sect == 1){
			// generate lowercase alpha
			num = rand()%26;
			password[i] = (97+num);
		}
		if(sect == 2){
			// generate uppercase alpha
			num = rand()%26;
			password[i] = (65+num);
		}
		//printf("sect: %d   num: %c   i:%d\n",sect,password[i],i);//for debug
	}
	password[i] = '\0';
	printf("Generated Password:    %s\n",password);
	printf("\n***PASSWORD GENERATOR PROGRAM ENDING***\n\n");
	return 0;
}

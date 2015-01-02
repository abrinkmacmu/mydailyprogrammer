/* disemvoweler.cpp
prompts user for input string and strips vowels, displaying de-voweled string and removed vowels
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char *argv[]){
	
	// define variables
	int MAX_STRING = 256;
	char inputstring[MAX_STRING];
	char devoweldstring[MAX_STRING];
	char vowelstring[MAX_STRING];

	// prompt user for input string
	printf("\n***DISEMVOWELER PROGRAM BEGINNING***\n\n");
	printf("please enter input string:\n");	
	fgets(inputstring, MAX_STRING, stdin);
	printf("input string is: %s", inputstring);

	// loop over each char in input string
	int i = 0;
	int devowel = 0;
	int vowel = 0;
	char curchar;
	for(i=0; i<(int)strlen(inputstring); i++){
		curchar = inputstring[i];
		//printf("%c\n",curchar); // for debugging
		switch(curchar){
			case 'a':
				vowelstring[vowel] = curchar;
				vowel++;
				break;
			case 'e':
				vowelstring[vowel] = curchar;
				vowel++;
				break;
			case 'i':
				vowelstring[vowel] = curchar;
				vowel++;
				break;
			case 'o':
				vowelstring[vowel] = curchar;
				vowel++;
				break;
			case 'u':
				vowelstring[vowel] = curchar;
				vowel++;
				break;
			case ' ':
				// do nothing
				break;
			default:
			devoweldstring[devowel] = curchar;
				devowel++;
				break;	
		}
	}
	devoweldstring[devowel] = '\0';
	vowelstring[vowel] = '\0';
	
	printf("de-voweled string is: %s", devoweldstring);
	printf("vowels removed are: %s\n", vowelstring);

	printf("\n***DISEMVOWELER PROGRAM ENDING***\n\n");
	return 0;
}

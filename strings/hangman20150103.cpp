/* Hangman20150103.cpp
Plays hangman with you from a random word from http://www.joereynoldsaudio.com/wordlist.txt
*/

// Psuedocode
	// Read random string from webfile (strip punctuation)
	// Repeat the following:
		// Print menu with blanks and guesses
		// prompt user for guess
		// check guess against chosen word
		// evaluate Win/Loss condition

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void printgallows(int);

int main(int argc, char *argv[]){
	
	printf("\n***HANGMAN PROGRAM BEGINNING***\n\n");	

	// Get and condition guesswrd from webfile
	srand(time(NULL));
	char guesswrd[20];	
	FILE * pFile;
	pFile = fopen("wordlist.txt","r");
	int wrd = rand()%608324;
	//wrd = 51666; //"Banna"
	int i = 0;
	for(i = 0; i<wrd;i++){
		fscanf(pFile, "%s", guesswrd);		
	}

	printf("solution word is: %d %s\n", i,guesswrd);

	// Condition guessword to change caps to lowercase
	for(i=0;i<(int)strlen(guesswrd);i++){
		if( guesswrd[i] < 91 and guesswrd[i] > 40){
			guesswrd[i] = (char)((int)guesswrd[i] + 32);
		}
	}
	printf("Conditioned word is: %d %s\n", i,guesswrd);
	
	char guessedletters[26] = {'\0'};
	char missedletters[26] = {'\0'};
	char displaywrd[20];
	char inputstr[100];
	int guessnumber = 0;
	int missednumber = 0;
	char guesschar = '\0';

	while(true){
		
		// print menu with blanks and guesses
		for(i=0; i<(int)strlen(guesswrd);i++){
			if(NULL != strchr(guessedletters,guesswrd[i])){
				displaywrd[i] = guesswrd[i];
			}else if(guesswrd[i] == '\''){
				displaywrd[i] = '\'';
			}else{
				displaywrd[i] = '_';
			}
		}
		displaywrd[i] = '\0';
		
		printf("Guess this word:  %s\n",displaywrd);
		printf("Previous guesses: %s\n", missedletters);
		// evaluate win condition
		if(NULL == strchr(displaywrd, '_')){
			printf("Congrats! you Won!\n");
			printf("\n***HANGMAN PROGRAM ENDING***\n\n");
			return 0;
		}
		// prompt user for guess
		printf("%d / 6 Incorrect guesses\n\n", missednumber);
		printf("Please input guess:");
		scanf("%s",&inputstr);
		guesschar = inputstr[0];
		//fgets(&guesschar, 1, stdin);
		printf("echo %c\n", guesschar);
		guessedletters[guessnumber] = guesschar;
		guessnumber++;
		guessedletters[guessnumber] = '\0';
		
		// check latest guess
		
		if(NULL == strchr(guesswrd, (int)guesschar)){
			
			missedletters[missednumber] = guesschar;
			missednumber++;
			missedletters[missednumber] = '\0';
		}

		// print gallowss
		printgallows(missednumber);

		// check loss condidtion
		if(missednumber == 6){
			printf("You lost, stop sucking!\n");
			printf("\n***HANGMAN PROGRAM ENDING***\n\n");
			return 0;
		}
	//printf("\033[2J"); // Clear screen
	}
}

void printgallows(int miss){
	char *gallows[6] = {"","","","","",""};	
	switch(miss){
		case 0:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         ";
			gallows[3] = "|         ";
			gallows[4] = "|         ";
			gallows[5] = "|______________";
			break;
		case 1:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         O";
			gallows[3] = "|         ";
			gallows[4] = "|         ";
			gallows[5] = "|______________";
			break;
		case 2:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         O";
			gallows[3] = "|         |";
			gallows[4] = "|         ";
			gallows[5] = "|______________";
			break;
		case 3:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         O";
			gallows[3] = "|        /|";
			gallows[4] = "|         ";
			gallows[5] = "|______________";
			break;
		case 4:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         O";
			gallows[3] = "|        /|\\";
			gallows[4] = "|         ";
			gallows[5] = "|______________";
			break;
		case 5:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         O";
			gallows[3] = "|        /|\\";
			gallows[4] = "|        /";
			gallows[5] = "|______________";
			break;
		case 6:
			gallows[0] = "------------";
			gallows[1] = "|         | ";
			gallows[2] = "|         O";
			gallows[3] = "|        /|\\ ";
			gallows[4] = "|        / \\";
			gallows[5] = "|______________";
			break;

	}
	
	
	int i = 0;
	for(i = 0; i<7;i++){
		printf("%s\n", gallows[i]);
	}

}

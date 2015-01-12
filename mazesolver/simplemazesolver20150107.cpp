#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	// import maze size and maze array
	if(argc != 2){
		printf("need a maze file... exiting\n");
		return 0;
	}
	printf("inputted maze file: %s\n", argv[1]);
	FILE * pFile;
	pFile = fopen(argv[1], "r");
	int x,y;	
	fscanf(pFile, "%d %d", &x, &y);
	printf("maze size is %d by %d\n", x,y);

	char maze[x][y];
	int mazeind = 0;
	char dummy;
	int i,j;	
	for(i = 0; i<x;i++){
		for(j = 0; j<y+1; j++){
			dummy = fgetc(pFile);
			if(dummy != '\n'){
				maze[i][j] = dummy;
				mazeind++;
				printf("%c",maze[i][j]);
			}		
		}
		printf("\n");
	}
	//maze[mazeind] = '\0';
	int size = x*y;//(int)strlen(maze);
	int neighbors[x][y];
	int count;
	for(i = 0; i<x; i++){
		for(j = 0; j<y; j++){
			neighbors[i][j] = 0;
		}
	}
	for(i = 1; i<x-1; i++){
		for(j = 1; j<y-1; j++){
			count = 0;
			if(' ' == maze[i][j]){
				if('#' == maze[i][j+1] ){
					count++;
				}
				if('#' == maze[i][j-1] ){
					count++;
				}
				if('#' == maze[i-1][j] ){
					count++;
				}
				if('#' == maze[i+1][j] ){
					count++;
				}
				neighbors[i][j] = count;
			}	
		}		
	}
	
	for(i = 0; i<x; i++){
		for(j = 0; j<y; j++){
			printf("%d",neighbors[i][j]);
		}
		printf("\n");
	}




	fclose(pFile);
	printf("exiting\n");
	return 0;
}


#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<string>

using namespace std;

struct Mazestruct {
    char **maze;
    int x;
    int y;
	int starti;
	int startj;
	int score;
	int moves;
	
};
typedef struct Mazestruct Maze;
/**************  MAZE OPERATIONS  ****************************
1. read_maze
2. print_maze
3. destory_maze
*/

void read_maze(Maze * MAZE, char *filename){
	ifstream mfile;
	mfile.open(filename);
	if (0 == mfile.is_open()) { 
		cout<<"maze file invalid, try again"<<endl;
		return;
	}
	int x,y;
	mfile>> x >> y;
	MAZE->x = x;
	MAZE->y = y;
	MAZE->moves = 25;
	MAZE->score = 0;
	cout<< "inputs are "<< x << " " << y<<endl;
	MAZE->maze = (char**)malloc(x * sizeof(char*));
    for (int i = 0; i < x; i++) {
        MAZE->maze[i] = (char*)malloc(y*sizeof(char*));
    }
	string readline;
	getline(mfile,readline); // clears remainder of first line
	for(int i = 0; i<y;i++){
		getline(mfile,readline);
		for(int j = 0; j<x;j++){
			MAZE->maze[i][j] = readline[j];			
			if(readline[j] == '@'){
			MAZE->starti = i;	
			MAZE->startj = j;
			}		
		}		
	}
	mfile.close();
	return;
}

void print_maze(Maze *MAZE){
	cout<<"LEGEND"<<endl;
	cout<< "% - Walls"<<endl;
	cout<< "@ - You are here"<<endl;
	cout<< "$ - Treasure!"<<endl;
	cout<< "T - Torch"<<endl;
	cout<< "P - PIT O' DEATH"<<endl;    

	for (int i = 0; i < MAZE->x; i++) {
        for (int j = 0; j < MAZE->y; j++) {
            cout<<MAZE->maze[i][j];
        }
        cout<<endl;
    }

	cout<<"Moves remaining: "<<MAZE->moves<<"  Score:"<<MAZE->score<<endl;		
	cout<<"Use wasd to move, q to quit"<<endl;
	return;
}

void destroy_maze(Maze *MAZE){
    for (int i = 0; i < MAZE->x; i++) {
        free(MAZE->maze[i]);
    }
    free(MAZE->maze);
    free(MAZE);
}

/* ********************** VIDEO GAME CODE ***************/
int update_maze_moves_score_coords(Maze *MAZE,int i, int j){
	// cmd = -1:quit, 0:invalid entry, 1:valid entry, 2:barrier encountered, 3:killed	
	int cmd = 0;	
	switch(MAZE->maze[i][j]){
		case '%':
			cmd = 2;
			break;
		case '$':
			cmd = 1;
			MAZE->score = MAZE->score + 10;
			MAZE->maze[i][j] = '@';
			MAZE->starti = i;
			MAZE->startj = j;
			break;
		case 'T':
			cmd = 1;
			MAZE->maze[i][j] = '@';
			MAZE->starti = i;
			MAZE->startj = j;
			break;
		case 'P':
			cmd = 3;
			break;
		default:
			cmd = 1;
			MAZE->maze[i][j] = '@';
			MAZE->starti = i;
			MAZE->startj = j;
			break;
	}
			
	
	MAZE->moves = MAZE->moves - 1;
	return cmd;
}

int update_maze_from_user_input(Maze * MAZE){
	// cmd = -1:quit,0:invalid entry,1:valid entry,2:barrier encountered, 3:killed
	char input;
	cin>>input;
	int i = MAZE->starti;
	int j = MAZE->startj;
	int cmd = 0;
	switch(input){
		case 'w':		
			cmd = update_maze_moves_score_coords(MAZE,i-1,j);
			break;
		case 'a':
			cmd = update_maze_moves_score_coords(MAZE,i,j-1);
			break;
		case 's':
			cmd = update_maze_moves_score_coords(MAZE,i+1,j);
			break;
		case 'd':
			cmd = update_maze_moves_score_coords(MAZE,i,j+1);
			break;
		case 'q':
			cmd = (-1);
			break;		
		default:
			cmd = 0;
			break;
	}
	if(cmd==1 or cmd==3){
		MAZE->maze[i][j] = '.';
	}

	return cmd;
}


/* **********************  MAIN *************************/
int main(int argc, char *argv[]){		
	if (argc != 2){
		cout<<"please input a map file"<<endl;
		return 0;
	}

	Maze *mymaze = (Maze *)malloc(sizeof(Maze));	
	read_maze(mymaze,argv[1]);
	system("clear");
	print_maze(mymaze);

	// get user input, update character location, and print map
	int cmd = '\0';	// cmd = -1:quit,0:invalid entry,1:valid entry,2:barrier encountered, 3:killed
	while(cmd != (-1)){
		cmd = update_maze_from_user_input(mymaze);
		switch(cmd){
			case 0:
				cout<<"invalid entry"<<endl;
				break;
			case 1:
				system("clear");
				print_maze(mymaze);		
				break;
			case 2:
				cout<<"cannont move there!"<<endl;
				cout<<"Moves remaining: "<<mymaze->moves<<"  Score:"<<mymaze->score<<endl;		
				break;
			case 3:
				cout<<"you have been killed :c"<<endl;
				cmd = -1;
				break;
			
		}
		if(mymaze->moves == 0){
			cout<<"ran out of moves, try more cardio :P"<<endl;
			cmd = (-1);
		}
	}
	cout<< "FINAL SCORE: "<<mymaze->score<<endl;
	cout<<"Thanks for playing"<<endl;
    destroy_maze(mymaze);
	cout<<"**Exiting**"<<endl;
	return 0;
}	

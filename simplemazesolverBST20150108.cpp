/*
	Maze solver using modified binary search tree
	Maze indexing issue in create_maze function (work around in place)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodestruct{
	struct nodestruct * left;
	struct nodestruct * right;
	struct nodestruct * parent;
	int isend;
	int dist;
	int i;
	int j;
};
typedef struct nodestruct Node;
struct Mazestruct {
    char **maze;
    int x;
    int y;
	int starti;
	int startj;
	
};
typedef struct Mazestruct Maze;


void create_maze(Maze *MAZE, char * filename){
	
	// open file and get maze data	
	int x,y;
	FILE * pFile;
	pFile = fopen(filename, "r");
	fscanf(pFile, "%d %d", &x, &y);
	printf("\nmaze size is %d by %d\n", x,y);	
 	MAZE->x = x;
    MAZE->y = y;
	// initalize maze array
	MAZE->maze = (char**)malloc(x * sizeof(char*));
    for (int i = 0; i < x; i++) {
        MAZE->maze[i] = (char*)malloc(sizeof(char*));
    }

	// read file for maze characters
	char dummy;
	for(int i = 0; i<x;i++){
		for(int j = 0; j<y+1; j++){
			dummy = fgetc(pFile);
			if(dummy == '\n'){
				MAZE->maze[i][j] = '\0';
				
			} else if (j > 0){
				MAZE->maze[i][j-1] = dummy; // MAZE indexing issue
				//printf("%c",MAZE->maze[i][j]); // for debug
			}

			if(dummy == 'S'){
				// this is start node
				MAZE->starti = i;
				MAZE->startj = j-1;
			}	
		}
		//printf("\n"); // for debug
	}
	//printf("\n"); // for debug
	fclose(pFile);
}

void destroy_maze(Maze *MAZE){
    for (int i = 0; i < MAZE->x; i++) {
        free(MAZE->maze[i]);
    }
    free(MAZE->maze);
    free(MAZE);
}

void print_maze(Maze *MAZE){
    for (int i = 0; i < MAZE->x; i++) {
        for (int j = 0; j < MAZE->y; j++) {
            printf("%c", MAZE->maze[i][j]);
        }
        printf("\n");
    }
	printf("%c should be S\n",MAZE->maze[MAZE->starti][MAZE->startj]); // for debug
	//printf("%c should be E\n",MAZE->maze[13][13]); // for debug
	
}

void deltree(Node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

/*
struct node * left;
	struct node * right;
	int i;
	int j;
	int numwalls;
	int isdead;
*/
void print_node(Node * NODE){
	if(NULL == NODE){
		printf("Node is empty\n");
	} else{
	printf("i:%d j:%d isend:%d dist:%d\n",NODE->i,NODE->j,NODE->isend,NODE->dist);
	printf("left:%p right:%p parent:%p\n",NODE->left,NODE->right,NODE->parent);
	}
	return;
}
void insert_next_node(Node ** tree,Maze *MAZE, int i, int j, int isend,int dist,char lastmove, Node ** prevnode){
	// first check if input tree is NULL, if so... initalize	
	Node *temp = NULL;
	if(!(*tree)) {
	printf("initializing new node\n");
	temp = (Node *)malloc(sizeof(Node));
	temp->left = temp->right = NULL;
	temp->isend = isend;
	temp->dist = dist;
	temp->parent = (*prevnode);
	temp->i = i;
	temp->j = j;
	*tree = temp;
	}
	// increment dist and insert next open space
	
	//printf("in insert_next_node [%d,%d] dist:%d isend:%d\n",i,j,dist,isend);
	dist++;

	if(' ' == MAZE->maze[i][j+1] and 'l' != lastmove ){
		printf("moving right\n");
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j+1),0,dist,'r',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j+1),0,dist,'r',&(*tree));
   		 }
	}
	if(' ' == MAZE->maze[i][j-1] and 'r' != lastmove){
		printf("moving left\n");		
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j-1),0,dist,'l',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j-1),0,dist,'l',&(*tree));
   		 }
	}
	if(' ' == MAZE->maze[i-1][j] and 'u' != lastmove){
		printf("moving down\n");
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i-1),j,0,dist,'d',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i-1),j,0,dist,'d',&(*tree));
   		 }
	}
	if(' ' == MAZE->maze[i+1][j] and 'd' != lastmove){
		printf("moving up\n");		
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i+1),j,0,dist,'u',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i+1),j,0,dist,'u',&(*tree));
   		 }
	}
	// also check for end condition
	if('E' == MAZE->maze[i][j+1] and 'l' != lastmove ){
		printf("moving right\n");
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j+1),0,dist,'r',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j+1),0,dist,'r',&(*tree));
   		 }
	}
	if('E' == MAZE->maze[i][j-1] and 'r' != lastmove){
		printf("moving left\n");		
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j-1),1,dist,'l',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j-1),1,dist,'l',&(*tree));
   		 }
	}
	if('E' == MAZE->maze[i-1][j] and 'u' != lastmove){
		printf("moving down\n");
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i-1),j,1,dist,'d',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i-1),j,1,dist,'d',&(*tree));
   		 }
	}
	if('E' == MAZE->maze[i+1][j] and 'd' != lastmove){
		printf("moving up\n");		
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i+1),j,1,dist,'u',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i+1),j,1,dist,'u',&(*tree));
   		 }
	}
	print_node((*tree));
	return;
}


void search_ends(Node ** tree,Node **retnode){
	if(NULL == (*tree)){
		printf("returning\n");
        return;
		
    }

    if( 0 == (*tree)->isend){
        search_ends(&((*tree)->left),retnode);
		search_ends(&((*tree)->right),retnode);		
	}
	if( (*tree)->isend){
		printf("found End node\n");		
		(*retnode)= (*tree);
		print_node(*retnode);

		return;
	}
	//printf("returning NULL\n");
	//return NULL;
}

void mark_maze_solution(Node ** tree, Maze * MAZE){   
	if(NULL == (*tree)->parent){
		printf("debug 2\n");       
		 return;
    }
		printf("at [%d,%d] in markup\n",(*tree)->i,(*tree)->j);
		MAZE->maze[(*tree)->i][(*tree)->j] = '*';			
		mark_maze_solution(&(*tree)->parent,MAZE);
	
	return;
}


int main(int argc, char *argv[]){
	// import maze size and maze array
	if(argc != 2){
		printf("need a maze file... exiting\n");
		return 0;
	}
	printf("inputted maze file: %s\n", argv[1]);
	Maze *mymaze = (Maze *)malloc(sizeof(Maze));
	create_maze(mymaze,argv[1]);
	print_maze(mymaze);
	// initalize root
	Node *root = (Node *)malloc(sizeof(Node));
	root->left = root->right = NULL;
	root->parent = NULL;
	root->dist = 0;
	root->isend = 0;
	insert_next_node(&(root), mymaze,mymaze->starti,mymaze->startj,0,0,'a',NULL);
	Node *theend;

	search_ends(&(root),&(theend));
	print_node(theend);
	if(NULL == theend){
		printf("Couldn't find the end, no solution");
	}else{
		mark_maze_solution(&(theend->parent),mymaze);
		print_maze(mymaze);
	}

	printf("deleting BST...");
	deltree(root);
	printf("exiting\n");
	return 0;
}


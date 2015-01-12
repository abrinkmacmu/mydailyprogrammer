/*
	the maze file was not reading correctly for arbitrarily large map.
	Hoping C++ filestreaming will fix this issue
*/


#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<string>
using namespace std;

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
	cout<< "input nums are "<< x << " and " << y<<endl;
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
			if(readline[j] == 'S'){
			MAZE->starti = i;	
			MAZE->startj = j;
			}		
		}		
	}
	mfile.close();
	return;
}

void print_maze(Maze *MAZE){
    for (int i = 0; i < MAZE->x; i++) {
        for (int j = 0; j < MAZE->y; j++) {
            cout<<MAZE->maze[i][j];
        }
        cout<<endl;
    }
	return;
}

void destroy_maze(Maze *MAZE){
    for (int i = 0; i < MAZE->x; i++) {
        free(MAZE->maze[i]);
    }
    free(MAZE->maze);
    free(MAZE);
}
/*********************  LINKED LIST OPERATIONS ********************
1. print_node
2. insert_next_node
3. search_for_ends
4. mark_maze_solution
5. destroy_node

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
	dist++;
	if(' ' == MAZE->maze[i][j+1] and 'l' != lastmove ){
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j+1),0,dist,'r',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j+1),0,dist,'r',&(*tree));
   		 }
	}
	if(' ' == MAZE->maze[i][j-1] and 'r' != lastmove){
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j-1),0,dist,'l',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j-1),0,dist,'l',&(*tree));
   		 }
	}
	if(' ' == MAZE->maze[i-1][j] and 'u' != lastmove){
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i-1),j,0,dist,'d',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i-1),j,0,dist,'d',&(*tree));
   		 }
	}
	if(' ' == MAZE->maze[i+1][j] and 'd' != lastmove){		
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i+1),j,0,dist,'u',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i+1),j,0,dist,'u',&(*tree));
   		 }
	}
	// also check for end condition
	if('E' == MAZE->maze[i][j+1] and 'l' != lastmove ){
		cout<<"found an end"<<endl;
		print_node((*tree));
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j+1),1,dist,'r',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j+1),1,dist,'r',&(*tree));
   		 }
	}
	if('E' == MAZE->maze[i][j-1] and 'r' != lastmove){	
		cout<<"found an end"<<endl;
		print_node((*tree));
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,i,(j-1),1,dist,'l',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,i,(j-1),1,dist,'l',&(*tree));
   		 }
	}
	if('E' == MAZE->maze[i-1][j] and 'u' != lastmove){
		cout<<"found an end"<<endl;
		print_node((*tree));
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i-1),j,1,dist,'d',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i-1),j,1,dist,'d',&(*tree));
   		 }
	}
	if('E' == MAZE->maze[i+1][j] and 'd' != lastmove){		
		cout<<"found an end"<<endl;
		print_node((*tree));
		if(NULL == (*tree)->left) {
      		insert_next_node(&(*tree)->left, MAZE,(i+1),j,1,dist,'u',&(*tree));
  		 } else if(NULL == (*tree)->right){
     		insert_next_node(&(*tree)->right, MAZE,(i+1),j,1,dist,'u',&(*tree));
   		 }
	}
	return;
}

void search_ends(Node ** tree,Node **retnode){
	if(NULL == (*tree)){
        return;		
    }
	if( (*tree)->isend){
		printf("found End node\n");		
		(*retnode)= (*tree);
		print_node(*retnode);
		return;
	}else{
		search_ends(&((*tree)->left),retnode);
		search_ends(&((*tree)->right),retnode);
	}
}

void mark_maze_solution(Node ** tree, Maze * MAZE){   
	if(NULL == (*tree)->parent){       
		 return;
    }
	MAZE->maze[(*tree)->i][(*tree)->j] = '*';			
	mark_maze_solution(&(*tree)->parent,MAZE);	
	return;
}

void destroy_node(Node * tree){
    if (tree){
        destroy_node(tree->left);
        destroy_node(tree->right);
        free(tree);
    }
}

/* **********************  MAIN *************************/
int main(int argc, char *argv[]){
	cout<< "\n **Starting Maze solver program**\n"<<endl;
	if (argc != 2){
		cout<<"please input a maze file"<<endl;
	}
	cout<<"input maze file is: "<< argv[1]<<endl;

	Maze *mymaze = (Maze *)malloc(sizeof(Maze));	
	read_maze(mymaze,argv[1]);
	print_maze(mymaze);
	cout<< "Maze start found at "<< mymaze->starti<< " "<<mymaze->startj<<endl;
	// initalize root
	Node *root = (Node *)malloc(sizeof(Node));
	Node *theend = (Node *)malloc(sizeof(Node));
	root->left = root->right = NULL;
	root->parent =  NULL;
	root->dist = 0;
	root->isend = 0;
	root->i = mymaze->starti;
	root->j = mymaze->startj;
	print_node(root);
	cout<< "beginning insert_next_node"<<endl;
	insert_next_node(&(root), mymaze,mymaze->starti,mymaze->startj,0,0,'a',NULL);
	theend = NULL;
	cout<< "beginning search_ends"<<endl;
	search_ends(&(root),&(theend));
	if(NULL == theend){
		cout<<"could not find solution..."<<endl;
	}else{
		cout<< "found solution, Marking solution on Maze..."<<endl;
		mark_maze_solution(&(theend->parent),mymaze);
		print_maze(mymaze);
	}

    destroy_maze(mymaze);
	destroy_node(root);
	cout<<"**Exiting**"<<endl;
	return 0;
}	

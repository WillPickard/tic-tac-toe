#include "BoardState.h"
#include "TreeNode.h"
#include "t3Solver.h"

#include <stdio.h>
#include <array>
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>

class BoardState;
class TreeNode;
class t3Solver;

const unsigned char IS_VALID = 1;
const unsigned char UNKNOWN_CHAR = 2;
const unsigned char SURPLUS_O = 4;
const unsigned char SURPLUS_X = 8;
const unsigned char MORE_THAN_9 = 16;
const unsigned char LESS_THAN_9 = 32;



void menu();
unsigned char isValidStart(std::string);
using namespace std;
int main(int argc, char* argv[]){
	if(argc < 2){
		printf("You must provide a valid file to read from\n.Exiting with error..\n");
		exit(1);
	}
	
	string line;
	ifstream gameFile(argv[1]);
	if(gameFile.is_open()){
	  clock_t sTime, eTime, elapsed;
	  unsigned char iv;
	  while(getline(gameFile, line)){
	    printf("\n.........................begin...............................\n");
	    iv = isValidStart(line);
	    if(iv == IS_VALID){
	        BoardState * init = new BoardState(line);
	 	TreeNode * node = new TreeNode(init);
	 	t3Solver * solver = new t3Solver(node);
	 	sTime = clock();
	 	solver->build(solver->getRoot());
	 	eTime = clock();
	 	elapsed = eTime - sTime;
		cout << "Board Position: " << line << " Total nodes created: " << solver->getSize() << endl;
		printf("Start time: %f sec\n", ((float)sTime)/CLOCKS_PER_SEC);
		printf("End Time: %f sec\n", ((float)eTime)/CLOCKS_PER_SEC);
		printf("Elapsed Time %f sec\n", ((float)elapsed)/CLOCKS_PER_SEC);
		printf("Please press <ENTER> to continue. Upon doing so, this tree's preorder, postorder, levelorder, and terminalPath methods will be called\n");
		getchar();
		sTime = eTime = elapsed = 0;
		node  = solver->getRoot();
		cout << "Preorder for starting: " << line << endl;
		solver->preOrder(node);
		cout << "Postorder for starting: " << line << endl;
		solver->postOrder(node);
		cout << "Levelorder for starting: " << line << endl;
		solver->levelOrder(node);
		cout << "Terminal Path for starting: " << line << endl;
		solver->terminalPath(node);

	    }
	    else{
		cout << "starting position: " << line << endl;
		printf("invalid starting configuration given for the following reasons:\n");
	   	if(iv & UNKNOWN_CHAR) printf("invalid character given. valid characters are case insensitive x, o, and *\n");
	 	if(iv & SURPLUS_O) printf("too many os given. The total o count in the string must be equal to or one less than the x count\n");
		if(iv & SURPLUS_X) printf("too many xs given. The total x count must be equal to or 1 greater than the o count\n");
		if(iv & MORE_THAN_9) printf("more than 9 characters in the string. \n");
		if(iv & LESS_THAN_9) printf("less than 9 characters in the string. \n");
	    }
	    printf("..............................done...........................\n");	
	  }
	}
	return 0;
}

void menu(){
	printf("this is the menu.\nPress 1 for preOrder, 2 for post\n");
}
unsigned char isValidStart(string line){
	unsigned char isValid = IS_VALID;
	size_t length = line.length();
	int xCount = 0;
	int oCount = 0;
	int blankCount = 0;
	for(std::string::size_type i=0; i< length; i++){
	  switch(line[i]){
	    case 'x':
	    case 'X':
		xCount++; break;
	    case 'o':
	    case 'O':
	  	oCount++; break;
	    case '*':
		blankCount++; break;
	    default:
		isValid |= UNKNOWN_CHAR;
	  }; 
	}
	int totalSum = xCount + oCount + blankCount;
	if(xCount < oCount) isValid |= SURPLUS_O;
	if(xCount >= (oCount+2)) isValid |= SURPLUS_X;
	if(totalSum > 9) isValid |= MORE_THAN_9;
	if(totalSum < 9) isValid |= LESS_THAN_9;
	return isValid;
}

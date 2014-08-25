/*
 *
 *@file 
 *	t3Solver.cpp
 *
 *Implements methods in t3Solver.h
 */

#include "t3Solver.h"
#include "TreeNode.h"
#include "BoardState.h"
#include <math.h>
#include <vector>
#include <queue>
t3Solver::t3Solver():
	size(0),
	root(NULL)
	{};
t3Solver::t3Solver(TreeNode *r):
	size(1),
	root(r)
	{};
void t3Solver::setRoot(TreeNode *r){
  root = r;
}
void t3Solver::setSize(int s){
  size = s;
}

TreeNode * t3Solver::getRoot() const{
  return root;
}
int t3Solver::getSize() const{
  return size;
}

void t3Solver::insert(TreeNode *parentNode, TreeNode *childNode){
  parentNode -> addChild(childNode);
  childNode -> setParent(parentNode);
  size++;
}

void t3Solver::build(TreeNode *node){
	BoardState *board = node -> getData();
	short int xSum = board -> getXSum();
	short int oSum = board -> getOSum();	
	short int totalSum = xSum | oSum;
	short int remainingSum = MAX_SUM - totalSum;	
	short int turn = board -> getTurn();
	while(remainingSum != 0){
		short int lgResult = (short int) log2(remainingSum);
		short int powResult = pow(2,lgResult);
		remainingSum -= powResult;
		BoardState *clone = board ->clone();
		short int newSum;
		if(turn == O_TURN){
		  newSum = oSum | powResult;
		  clone -> setOSum(newSum);
		  clone -> setOCount(newSum);
		}
		else{
		  newSum = xSum | powResult;
		  clone -> setXSum(newSum);
		  clone -> setXCount(newSum);
		}
		TreeNode *newNode = new TreeNode(clone);
		insert(node, newNode);
		clone->checkOutcome();
		if(clone->getOutcome() == GAME_INPROGRESS){
			build(newNode);
		}
	}
	return;	
	
}

void t3Solver::levelOrder(TreeNode *node){
	  std::vector<TreeNode *> children;
	  std::queue<TreeNode *> queue;

	  int cs;
	  if(node -> getParent() == NULL){
		queue.push(node);
	  }
	  else{
	    TreeNode * parent = node -> getParent();
	    children = parent -> getChildren();
	    cs = children.size();
	    for(int i=cs; i>=0; i--){
		queue.push(children.at(i));
	    }
	  }
	  //at this point all of the siblings (if they exist) of the passed node will be in queue
	  //to start, pop the queue and assign that to a temp nodes
	  //from there, we enter a while loop
	  //this while loops purpose will be to 
	  //	a) print the last popped node
	  //	b) enqueue all of that nodes children
	  //	c) pop a node and loop
	  TreeNode * tempNode = queue.front();
	  while(!queue.empty()){
	  	tempNode -> getData() -> print();
		children = tempNode -> getChildren();
		cs = children.size() - 1;
		for(int i=cs; i>=0; i--){ 
			queue.push(children.at(i));
		}
		tempNode = queue.front();
	        queue.pop();
	  }
  return;
}
void t3Solver::postOrder(TreeNode *node){
	std::vector<TreeNode *> children = node->getChildren();
	int cs = children.size() -1;
	for(int i=cs; i>=0; i--){
	  postOrder(children.at(i));
	}
	const BoardState *board = node->getData();
	board->print();	
	return;
}
void t3Solver::preOrder(TreeNode *node){
	const BoardState *board = node->getData();
	board -> print();
	std::vector<TreeNode *> children = node->getChildren();
	int cs = children.size() -1;
	for(int i=cs; i>=0; i--){
	  preOrder(children.at(i));
	}
	return;
}
void t3Solver::terminalPath(TreeNode *node){
	std::vector<TreeNode *> children;
	int cs;

	node -> getData() -> print();
	int outcome = node -> getData() -> getOutcome();
	//printf("outcome: %d\n", outcome);
	if(outcome == GAME_WIN || outcome == GAME_DRAW){
		return;
	}
	children = node->getChildren();
	cs = children.size() - 1;
	
	terminalPath(children.at(cs)); 	
	return;
}

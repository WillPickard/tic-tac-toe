/*
 *
 *@file
 *  t3Solver.h
 *
 *This is the header file for the t3Solver class
 *This class manages tree nodes and solves the tic tac toe game
 *
 */

#ifndef T3SOLVER_H
#define T3SOLVER_H
#include "TreeNode.h"
#include "BoardState.h"

class t3Solver{
  private:
	TreeNode * root;
	int size;
  public:
	t3Solver();
	t3Solver(TreeNode *);

	void setRoot(TreeNode *);
	void setSize(int);

	TreeNode* getRoot() const;
	int getSize() const;
	
	void insert(TreeNode *, TreeNode *);
	
	void build(TreeNode *);
	void postOrder(TreeNode *);
	void preOrder(TreeNode *);
	void levelOrder(TreeNode *);
	void terminalPath(TreeNode *);
};
#endif

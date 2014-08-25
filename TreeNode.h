/******************
 *
 *@file
 *	 TreeNode.h
 *  
 * This file is the header file for a tree node
 * The tree node is managed by the t3Solver
 *
 * *****************/

#ifndef TREENODE_H
#define TREENODE_H
#include <vector>
#include "BoardState.h"
 
class TreeNode{
   private:
	TreeNode * parent;
	std::vector<TreeNode *> children;
	BoardState * data;
   public:
	TreeNode(){};
	TreeNode(BoardState *);
	
	void setParent(TreeNode *);
	void addChild(TreeNode *);
	void setData(BoardState *);

	TreeNode * getParent() const;
	std::vector<TreeNode *> getChildren() const;
	BoardState * getData() const;
};
#endif

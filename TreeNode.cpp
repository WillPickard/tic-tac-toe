/*
 *
 *#file
 *	TreeNode.cpp
 *
 *
 *This file implements TreeNode.h
 *
 */

#include "TreeNode.h"
#include <stdio.h>
#include<vector>

TreeNode::TreeNode(BoardState *d):
	data(d)
	{};

void TreeNode::setParent(TreeNode * n){
  parent = n;
}
void TreeNode::addChild(TreeNode *c){
  children.push_back(c);
}
void TreeNode::setData(BoardState *d){
  data = d;
}


TreeNode * TreeNode::getParent() const{
  return parent;
}
std::vector<TreeNode *> TreeNode::getChildren() const{
  return children;
}
BoardState * TreeNode::getData() const{
  return data;
}


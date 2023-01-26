#include "PrimaryTreeNode.h"
#include <iostream>

PrimaryTreeNode::PrimaryTreeNode(const string &category, const string &name, const int &data){
    this->category = category;
    avl = new AvlTree();
    llrbt = new LLRBT();
    avl->root = new AvlTreeNode(name, data);
    avl->left_child = new AvlTree();
    avl->right_child = new AvlTree();
    llrbt->root = new LLRBTNode(name, data);
    llrbt->left_child = new LLRBT();
    llrbt->right_child = new LLRBT();
}
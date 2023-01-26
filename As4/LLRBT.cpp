#include "LLRBT.h"
#include <iostream> 

LLRBT::LLRBT(){
    height = 0;
    red = false;
    root = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

void LLRBT::insert(const string& name, const int& price) {
    AvlTree* temp = find(name);
    if (temp->root != nullptr) {
        return;
    }
    temp->root = new LLRBTNode(name, price);
    temp->red = true;
    temp->left_child = new LLRBT(); 
    temp->right_child = new LLRBT();
}

void LLRBT::implement_insert(const string& name, const int& data) {
    insert(name, data);
    balance(this);
}


void LLRBT::implement_remove(const string& name) {
    remove(name);
    balance(this);
}


void LLRBT::balance(AvlTree* tree){
    if (tree->root == nullptr)return;
    balance(tree->left_child);
    balance(tree->right_child);
    if(tree->right_child->root == nullptr && tree->left_child->root == nullptr)return;
    AvlTree* temp;
    if(tree->right_child->red && !tree->left_child->red){
        if (tree->right_child->left_child->red) {
            temp = tree->right_child->left_child;
            tree->right_child->left_child = temp->right_child;
            temp->right_child = tree->right_child;
            tree->right_child = temp;
        }
		temp = new LLRBT();
		temp->left_child = tree->left_child;
		temp->right_child = tree->right_child->left_child;
		temp->root = tree->root;
		temp->red = tree->right_child->red;
		tree->left_child = temp;
		tree->root = tree->right_child->root;
		tree->right_child = tree->right_child->right_child;
	}
    else if(tree->left_child->red && !tree->right_child->red){
        if (tree->left_child->right_child->red) {
            temp = tree->left_child->right_child;
            tree->left_child->right_child = temp->left_child;
            temp->left_child = tree->left_child;
            tree->left_child = temp;
        }
        if (tree->left_child->left_child->red){
			temp = new LLRBT();
			temp->right_child = tree->right_child;
			temp->left_child = tree->left_child->right_child;
			temp->root = tree->root;
			temp->red = tree->left_child->red;
			tree->right_child = temp;
			tree->root = tree->left_child->root;
			tree->left_child = tree->left_child->left_child;

        }
    }
    if (tree->left_child->red && tree->right_child->red) {
        tree->red = !tree->red;
        tree->left_child->red = tree->right_child->red = false;
    }
}

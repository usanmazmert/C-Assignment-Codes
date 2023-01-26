#include "LLRBT.h"
#include <iostream>
#include <queue>

AvlTree::AvlTree(){
    red = false;
    level = 0;
    height = 0;
    balance_factor = 0;
    root = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

AvlTree* AvlTree::go_left(AvlTree* temp){
    while(temp->left_child->root != nullptr){
        temp = temp->left_child;
    }
    return temp;
}

AvlTree* AvlTree::find(const string &name){
    AvlTree* temp = this;
    while(temp->root != nullptr){
        if(name == temp->root->name){
            return temp;
        }
        if(name > temp->root->name){
            temp = temp->right_child;
        }
        else if(name < temp->root->name){
            temp = temp->left_child;
        }
    }
    return temp;
}
void AvlTree::insert(const string& name, const int& price){   
    AvlTree* temp = find(name);
    if (temp->root != nullptr) {
        return;
    }
    temp->root = new AvlTreeNode(name, price);
    temp->red = true;
    temp->height = 1;
    temp->left_child = new AvlTree();
    temp->right_child = new AvlTree();
}
void AvlTree::implement_insert(const string& name, const int& price) {
    insert(name, price);
    int height = 0;
    bool balanced = false;
    balance(this, height, balanced);
}

void AvlTree::remove(const string& name){
    AvlTree* temp = find(name);
    if(temp->root == nullptr)return;
    AvlTree* left_most_child;
    if (temp->right_child->root == nullptr) {
        temp->root = temp->left_child->root;
        if (temp->left_child->root == nullptr)
            return;
        temp->right_child = temp->left_child->right_child;
        temp->left_child = temp->left_child->left_child;
        return;
    }
	left_most_child = go_left(temp->right_child);
    temp->root = left_most_child->root;
    left_most_child->root = left_most_child->right_child->root;
    left_most_child->red = left_most_child->right_child->red;
    if (left_most_child->right_child->root != nullptr) {
		left_most_child->left_child = left_most_child->right_child->left_child;
		left_most_child->right_child = left_most_child->right_child->right_child;
    }
}
void AvlTree::implement_remove(const string& name) {
    remove(name);
    int height = 0;
    bool balanced = false;
    balance(this, height, balanced);
}

void AvlTree::balance(AvlTree* tree, int& height,  bool& balanced){
    if(tree->root == nullptr)return;
    int height_right = 0;
    int height_left = 0;
    balance(tree->left_child, height_left, balanced);
    balance(tree->right_child, height_right, balanced);
    height++;
    height = height_left >= height_right ? height + height_left : height + height_right;
    tree->height = height; 
    tree->balance_factor = tree->left_child->height - tree->right_child->height;
    if(balanced)return;
    if(tree->right_child->root == nullptr && tree->left_child->root == nullptr)return;
    AvlTree* temp;
    if(tree->balance_factor < -1){
        if(tree->right_child->balance_factor == -1){
            temp = new AvlTree();
            temp->left_child = tree->left_child;
            temp->root = tree->root;
            temp->right_child = tree->right_child->left_child;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            tree->left_child = temp;
            tree->root = tree->right_child->root;
            tree->right_child = tree->right_child->right_child;
            tree->height = tree->left_child->height >= tree->right_child->height ? tree->left_child->height+1 : tree->right_child->height + 1;
            tree->balance_factor = tree->left_child->height - tree->right_child->height;
            return;
        }
        if(tree->right_child->balance_factor == 1){
            temp = tree->right_child->left_child;
            tree->right_child->left_child = temp->right_child;
            temp->right_child = tree->right_child;
            tree->right_child = temp;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            temp->right_child->balance_factor = temp->right_child->left_child->height - temp->right_child->right_child->height;
            temp->right_child->height = temp->right_child->left_child->height >= temp->right_child->right_child->height ? temp->right_child->left_child->height+1 : temp->right_child->right_child->height + 1;


            temp = new AvlTree();
            temp->left_child = tree->left_child;
            temp->root = tree->root;
            temp->right_child = tree->right_child->left_child;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height > temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            tree->left_child = temp;
            tree->root = tree->right_child->root;
            tree->right_child = tree->right_child->right_child;
            tree->height = tree->left_child->height > tree->right_child->height ? tree->left_child->height+1 : tree->right_child->height + 1;
            tree->balance_factor = tree->left_child->height - tree->right_child->height;
            return;
        }
        if(tree->right_child->balance_factor == 0){
            temp = new AvlTree();
            temp->left_child = tree->left_child;
            temp->root = tree->root;
            temp->right_child = tree->right_child->left_child;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            tree->left_child = temp;
            tree->root = tree->right_child->root;
            tree->right_child = tree->right_child->right_child;
            tree->height = tree->left_child->height >= tree->right_child->height ? tree->left_child->height+1 : tree->right_child->height + 1;
            tree->balance_factor = tree->left_child->height - tree->right_child->height;
            return;
        }
        balanced = true;
    }
    if(tree->balance_factor > 1){
        if(tree->left_child->balance_factor == 1){
            temp = new AvlTree();
            temp->right_child = tree->right_child;
            temp->root = tree->root;
            temp->left_child = tree->left_child->right_child;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            tree->right_child = temp;
            tree->root = tree->left_child->root;
            tree->left_child = tree->left_child->left_child;
            tree->height = tree->left_child->height >= tree->right_child->height ? tree->left_child->height+1 : tree->right_child->height + 1;
            tree->balance_factor = tree->left_child->height - tree->right_child->height;
            return;
        }
        if(tree->left_child->balance_factor == -1){
            temp = tree->left_child->right_child;
            tree->left_child->right_child = temp->left_child;
            temp->left_child = tree->left_child;
            tree->left_child = temp;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            temp->left_child->balance_factor = temp->left_child->left_child->height - temp->left_child->right_child->height;
            temp->left_child->height = temp->left_child->left_child->height >= temp->left_child->right_child->height ? temp->left_child->left_child->height+1 : temp->left_child->right_child->height + 1;

            temp = new AvlTree();
            temp->right_child = tree->right_child;
            temp->root = tree->root;
            temp->left_child = tree->left_child->right_child;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            tree->right_child = temp;
            tree->root = tree->left_child->root;
            tree->left_child = tree->left_child->left_child;
            tree->height = tree->left_child->height >= tree->right_child->height ? tree->left_child->height+1 : tree->right_child->height + 1;
            tree->balance_factor = tree->left_child->height - tree->right_child->height;
            return;
        }
        if(tree->left_child->balance_factor == 0){
            temp = new AvlTree();
            temp->right_child = tree->right_child;
            temp->root = tree->root;
            temp->left_child = tree->left_child->right_child;
            temp->balance_factor = temp->left_child->height - temp->right_child->height;
            temp->height = temp->left_child->height >= temp->right_child->height ? temp->left_child->height+1 : temp->right_child->height + 1;

            tree->right_child = temp;
            tree->root = tree->left_child->root;
            tree->left_child = tree->left_child->left_child;
            tree->height = tree->left_child->height >= tree->right_child->height ? tree->left_child->height+1 : tree->right_child->height + 1;
            tree->balance_factor = tree->left_child->height - tree->right_child->height;
            return;
        }
        balanced = true;
    }
}

string AvlTree::print_all_items(){
    string output = "";
    std::queue<AvlTree*> item_queue;
    item_queue.push(this);
    AvlTree* temp;
    int count2 = 0;
    int count = 1;
    while(!item_queue.empty()){
        temp = item_queue.front();
        item_queue.pop();
        count--;
        if(temp->left_child->root != nullptr){
            count2++;
            item_queue.push(temp->left_child);
        }
        if(temp->right_child->root != nullptr){
            item_queue.push(temp->right_child);
            count2++;
        }
        output = output + '"' + temp->root->name + '"' + ":" + '"' + std::to_string(temp->root->price) + '"';
        if (item_queue.empty()) {
            continue;
        }
        if (count == 0) {
			output = output + "\n\t";
            count = count2;
            count2 = 0;
        }
        else{
            output = output + ",";
        }
    }
    return output;
}

string AvlTree::print_item(const string& name){
    int level = 1;
    string output = "";
    AvlTree* temp = find(name);
    if(temp->root == nullptr){
        return output;
    }
    output += '"' + temp->root->name  + '"' + ":" + '"' + std::to_string(temp->root->price) + '"';
    return output;
}
void AvlTree::update_data(const string& name, const int& price){
    AvlTree* temp = find(name);
    temp->root->price = price;
}
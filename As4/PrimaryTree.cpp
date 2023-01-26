#include "PrimaryTree.h"
#include <iostream>
#include <queue>

PrimaryTree::PrimaryTree(){
    root = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}

PrimaryTree* PrimaryTree::find_category(const string &category){
    PrimaryTree* temp = this;
    while(temp->root != nullptr){
        if(category == temp->root->category){
            return temp;
        }
        if(category > temp->root->category){
            temp = temp->right_child;
        }
        else if(category < temp->root->category){
            temp = temp->left_child;
        }
    }
    return temp;
}

void PrimaryTree::insert(const string &category, const string &name, const int &price){

    PrimaryTree* primary_tree = find_category(category);
    if(primary_tree->root == nullptr){
        primary_tree->root = new PrimaryTreeNode(category, name, price);
        primary_tree->left_child = new PrimaryTree();
        primary_tree->right_child = new PrimaryTree();
    }
    else{
        primary_tree->root->avl->implement_insert(name, price);
        primary_tree->root->llrbt->implement_insert(name, price);

    }
}
void PrimaryTree::remove(const string& category, const string& name){
    if(root == nullptr)return;
    PrimaryTree* primary_tree = find_category(category);
    if(primary_tree->root == nullptr)return;
    primary_tree->root->avl->implement_remove(name);
    primary_tree->root->llrbt->implement_remove(name);
}

string PrimaryTree::print_all_items(const bool& avl){
    string output = "command:printAllItems\n{";
    if (root == nullptr || root->llrbt->root == nullptr || root->avl->root == nullptr) {
        output += "}\n";
        return output;
    }
    output += '\n';
    std::queue<PrimaryTree*> item_queue;
    item_queue.push(this);
    PrimaryTree* temp;
    while(!item_queue.empty()){
        temp = item_queue.front(); 
        item_queue.pop();
        if (temp->root->llrbt->root == nullptr || temp->root->avl->root == nullptr) {
			output += '"' + temp->root->category + '"' + ':' + "{}\n";
            continue;
		}
        if(temp->left_child->root != nullptr){
            item_queue.push(temp->left_child);
        }
        if(temp->right_child->root != nullptr){
            item_queue.push(temp->right_child);
        }
        output += '"' + temp->root->category + '"' + ':' + '\n' + '\t';
        if(avl)
			output += temp->root->avl->print_all_items();
        else
			output += temp->root->llrbt->print_all_items();
        if(!item_queue.empty())
			output += "\n";
    }
	output += "\n}\n";
    return output;
}

string PrimaryTree::print_all_items_in_category(const string& category, const bool& avl){
    PrimaryTree* temp = find_category(category);
    string output = "command:printAllItemsInCategory\t"+ category + "\n";
    if (temp->root == nullptr || temp->root->llrbt->root == nullptr) {
        output += "{\n";
        output += '"' + category + '"' + ":" + "{}";
        output += "\n}\n";
        return output;
    }
    output += "{\n\"" + temp->root->category + '"' + ':' + '\n' + '\t';
    if(avl)
		output += temp->root->avl->print_all_items();
    else
		output += temp->root->llrbt->print_all_items();
    output += "\n}\n";
    return output;
}

string PrimaryTree::print_item(const string& category, const string& name, bool find, const bool& avl){
    PrimaryTree* temp = find_category(category);
    string output = "command:";
    if(find){
        output += "find\t"+ category + + "\t" + name + "\n{";
    }
    else {
        output += "printItem\t" + category + "\t" + name + "\n{";
    }
    string item_output;
    if (temp->root != nullptr) {
        if(avl)
			item_output = temp->root->avl->print_item(name);
        else
			item_output = temp->root->llrbt->print_item(name);
    }
    if(item_output == "" || temp->root== nullptr){
        output += "}\n";
        return output;
    }
    output += "\n\"" + temp->root->category + '"' + ':' + '\n' + '\t';
    output += item_output;
    output += "\n}\n";
    return output;
}

void PrimaryTree::update_data(const string& category, const string& name, const int& price){
    PrimaryTree* temp = find_category(category);
    temp->root->avl->update_data(name, price);
    temp->root->llrbt->update_data(name, price);
}
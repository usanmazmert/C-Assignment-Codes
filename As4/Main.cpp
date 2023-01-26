#include "PrimaryTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

typedef std::string string;
using std::vector;
using std::cout;
using std::endl;


int main(int argc, char** argv){
    PrimaryTree* primary_tree = new PrimaryTree();
    std::ifstream ifs;
    ifs.open(argv[1]);
    std::ofstream ofs1;
    std::ofstream ofs2;
    ofs1.open(argv[2]);
    ofs2.open(argv[3]);
    string line;
    string item;
    vector<string> inputs;
    while(getline(ifs, line)){
        std::stringstream ss(line);
        while(getline(ss, item, '\t')){
            inputs.push_back(item);
        }
        if(inputs.at(0) == "insert")
        {   
            primary_tree->insert(inputs.at(1), inputs.at(2), std::stoi(inputs.at(3)));
        }
        if(inputs.at(0) == "remove")
        {
            primary_tree->remove(inputs.at(1), inputs.at(2));
        }
        if(inputs.at(0) == "updateData")
        {
            primary_tree->update_data(inputs.at(1), inputs.at(2), std::stoi(inputs.at(3)));
        }
        if(inputs.at(0) == "printAllItems")
        {
            ofs1 << primary_tree->print_all_items(true);
            ofs2 << primary_tree->print_all_items(false);
        }
        if(inputs.at(0) == "printAllItemsInCategory")
        {
            ofs1 << primary_tree->print_all_items_in_category(inputs.at(1), true);
            ofs2 << primary_tree->print_all_items_in_category(inputs.at(1), false);
        }
        if(inputs.at(0) == "printItem")
        {
            ofs1 << primary_tree->print_item(inputs.at(1), inputs.at(2), false, true);
            ofs2 << primary_tree->print_item(inputs.at(1), inputs.at(2), false, false);
        }
        if(inputs.at(0) == "find")
        {
            ofs1 << primary_tree->print_item(inputs.at(1), inputs.at(2), true, true);
            ofs2 << primary_tree->print_item(inputs.at(1), inputs.at(2), true, false);
        }
        inputs.clear();
    }
    ifs.close();
    ofs1.close();
    ofs2.close();
    return 1;
}
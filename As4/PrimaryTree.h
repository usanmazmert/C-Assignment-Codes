#include "PrimaryTreeNode.h"
#include <string>
using std::string;
class PrimaryTree{
    public:
        PrimaryTreeNode* root;
        PrimaryTree* left_child;
        PrimaryTree* right_child;
        PrimaryTree();
        /*
            @param category_name
            @brief finds the category node in tree first tree.
        */
        PrimaryTree* find_category(const string&);
        /*
            @param category_name
            @param node_name
            @param price
            @brief finds the category node from first tree and adds node to secondary avl and llrbts
        */
        void insert(const string&, const string&, const int&);
        /*
            @param category_name
            @param node_name
            @brief finds the category node from first tree and removes node from secondary avl and llrbts
        */
        void remove(const string&, const string&);
        /*
            @param is_avl
            @brief prints all the items in all categories in the tree.
        */
        string print_all_items(const bool&);
        /*
            @param category_name
            @param is_avl
            @brief prints all the items in the specified category.
        */
        string print_all_items_in_category(const string&, const bool&);
        /*
            @param category_name
            @param node_name
            @param is_find
            @param is_avl
            @brief prints the specific item in the specific category. If find is true then implements find method in the pdf.
        */
        string print_item(const string&, const string&, bool find, const bool& avl);
        /*
            @param category_name
            @param node_name
            @param price
            @brief updated the price of specified item
        */
        void update_data(const string&, const string&, const int&);
};
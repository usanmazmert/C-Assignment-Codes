#include "AvlTreeNode.h"
class AvlTree{
    public:
        int level;
        bool red;
        int height;
        int balance_factor;
        AvlTreeNode* root;
        AvlTree* left_child;
        AvlTree* right_child;
        AvlTree();
        /*
            @param category_name
            @brief finds the category node in tree first tree.
        */
        AvlTree* find(const string&);
        /*
            @param node_name
            @param price
            @brief finds the proper place for the node and adds it.
        */
        virtual void insert(const string&, const int&);
        virtual void implement_insert(const string&, const int&);
        /*
            @param node_name
            @brief finds the node to be deleted and deletes it.
        */
        void remove(const string&);
        virtual void implement_remove(const string&);
        /*
            @param tree_pointer
            @param height
            @param balanced
            @brief after each process balances avl tree
        */
        virtual void balance(AvlTree*, int&, bool&);
        /*
            @param tree_pointer
            @brief finds the the least bigger value in the tree from the given node.
        */
        AvlTree* go_left(AvlTree*);
        /*
            @param node_name
            @brief prints all the items in the tree.
        */
        string print_all_items();
        /*
            @param node_name
            @brief prints all the items in all categories in the tree.
        */
        string print_item(const string&);
        void update_data(const string&, const int&);
};
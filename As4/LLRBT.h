#include "LLRBTNode.h"
class LLRBT : public AvlTree{
    public:
        LLRBT();
        virtual void insert(const string&, const int&);
        void implement_insert(const string&, const int&);
        void implement_remove(const string&);

        /*
            @param tree_pointer
            @brief balances the left leaned red black tree
        */
        void balance(AvlTree*);
};
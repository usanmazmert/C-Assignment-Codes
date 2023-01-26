#include "LLRBT.h"
#include <string>
using std::string;
class PrimaryTreeNode{
    public:
        string category;
        AvlTree* avl;
        LLRBT* llrbt;
        PrimaryTreeNode(const string&, const string&, const int&);
};
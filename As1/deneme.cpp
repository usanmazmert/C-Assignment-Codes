#include <iostream>


using namespace std;
class A{
    public:
        void f2(){cout<<"A::f2";}
};

class B: public A{
    public:
        virtual void f2(){cout << "B::f2";}
};


class C: public B{
    public:
         void f2(){cout << "C::f2";}
};

int main(){
    B b;
    A* ptr = &b;
    ptr->f2();
    return -1;
}
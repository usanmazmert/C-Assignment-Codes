#include "Barista.h"
class Cashier : public Employee {
    public:
        Queue* barista_queue;
        Barista* barista;
        Cashier(const int&);
        Cashier();
        ~Cashier();
        Employee* operator<(Employee*);
};
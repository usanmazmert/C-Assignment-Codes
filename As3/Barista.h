#include "Employee.h"
class Barista : public Employee{
    public:
        Barista(const int&);
        Barista();
        ~Barista();
        Employee* operator<(Employee*);
};
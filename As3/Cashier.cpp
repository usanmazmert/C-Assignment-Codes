#include "Cashier.h"

Cashier::Cashier(const int& id){
    busy_time = 0.0;
    order = nullptr;
    this->is_available = true;
    total_time = 0.0;
    this->id = id;
}

Cashier::~Cashier(){
    order = nullptr;
    barista = nullptr;
    barista_queue = nullptr;
}

Cashier::Cashier(){
    busy_time = 0.0;
    order = nullptr;
    is_available=true;
    total_time=0.0;
    id= 0;
}

Employee* Cashier::operator<(Employee* cashier){
    if(this->total_time <= cashier->total_time)
        return this;
    return cashier;
}

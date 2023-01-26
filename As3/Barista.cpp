#include "Barista.h"

Barista::Barista(const int& id){
    busy_time = 0.0;
    order = nullptr;
    is_available = true;
    total_time = 0.0;
    this->id = id;
}

Barista::~Barista(){
    order = nullptr;
}

Barista::Barista(){
    busy_time = 0.0;
    order = nullptr;
    is_available = true;
    total_time = 0.0;
    id = -1;
}

Employee* Barista::operator<(Employee* barista){
    if(this->total_time <= barista->total_time)
        return this;
    return barista;
}
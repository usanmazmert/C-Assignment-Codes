#include "Apartment.h"
#include <iostream>

Apartment::Apartment(const std::string &name, const int &maxBandWidth){
    this->name = name;
    this->maxBandWidth = maxBandWidth;
    totalBandWidth= 0;
    next = nullptr;
    head = nullptr;
}

Apartment::~Apartment(){
    if(head != nullptr){
        Flat* temp = head;
        Flat* temp2;
        while(temp->next != nullptr){
            temp2 = temp->next;
            delete temp2->prev;
            temp = temp2;
        }
        delete temp;
        this->head = nullptr;
    }
}
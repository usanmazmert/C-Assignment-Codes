#include "Customer.h"

Customer::Customer(const double arrival, const double order, const double brew, const double price){
    next = nullptr;
    arrival_time = arrival;
    order_time = order;
    brew_time = brew;
    waiting_time  = 0.0;
    order_price = price;
}

Customer::Customer(){}

Customer::~Customer(){
    next = nullptr;
}
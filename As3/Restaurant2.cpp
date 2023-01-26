#include "Restaurant2.h"
#include "cstdlib"
#include <algorithm>

using std::vector;

Restaurant2::Restaurant2(const int size_value, const int order_value, std::vector<Customer*>* customers){
    this->customers = customers;
    total_time = 0.0;
    int cashier_id = 0;
    order_size = order_value;
    size = size_value;
    cashier_queue = new Queue();
    this->cashiers = new std::vector<Cashier*>();
    int n = -1;
    Barista* barista;
    Cashier* cashier;
    Queue* barista_queue;
    for(int i = 0; i < size; i++){
        if(i/3 > n || i == 0){
            barista = new Barista();
            barista_queue = new Queue();
            n++;
        }
        cashier = new Cashier(cashier_id++);
        cashier->barista_queue = barista_queue;
        cashier->barista = barista;
        cashiers->push_back(cashier);
    }
}

Restaurant2::~Restaurant2(){
    customers = nullptr;
    cashiers = nullptr;
    delete cashier_queue;
}

bool Restaurant2::compare_employees(Employee* first, Employee* second){ 
    return first->total_time < second->total_time;
}

vector<Cashier*>* Restaurant2::copy_array(vector<Cashier*>* first,const int& size){
    vector<Cashier*>* arr = new vector<Cashier*>();
    for(int i = 0; i < size; i++){
        arr->push_back(first->at(i));
    }
    return arr;
}

vector<Barista*>* Restaurant2::copy_array(vector<Barista*>* first,const int& size){
    vector<Barista*>* arr = new vector<Barista*>();
    for(int i = 0; i < size; i++){
        arr->push_back(first->at(i));
    }
    return arr;
}

vector<Cashier*>* Restaurant2::sort_array(vector<Cashier*>* array, const int& size){
    vector<Cashier*>* new_employee_array;
    new_employee_array = copy_array(array, size);
    std::sort(new_employee_array->begin(), new_employee_array->end(), compare_employees);
    return new_employee_array;
}


vector<Barista*>* Restaurant2::sort_array(vector<Barista*>* array, const int& size){
    vector<Barista*>* new_employee_array;
    new_employee_array = copy_array(array, size);
    std::sort(new_employee_array->begin(), new_employee_array->end(), compare_employees);
    return new_employee_array;
}

void Restaurant2::find_available_cashiers(Customer* order, const double total_time){
    Cashier* cashier;
    vector<Cashier*>* new_cashier_arr = new vector<Cashier*>();
    int index = 0;
    for(int i = 0; i < size; i++){
        cashier = cashiers->at(i);
        if(cashier->total_time <= total_time && !cashier->is_available){
            cashier->is_available = true;
            new_cashier_arr->push_back(cashier);
            index++;
        }
    }
    if(index!=0){
        std::sort(new_cashier_arr->begin(), new_cashier_arr->end() , compare_employees);
        for(int i = 0; i < index; i++){
            cashier = new_cashier_arr->at(i);
            find_available_baristas(cashier, cashier->total_time);
            cashier->order = nullptr;
        }
    }
    if(cashier_queue->head != nullptr){
        bool found = false;
        vector<Cashier*>* sorted_cashiers = sort_array(cashiers, size);
        while(cashier_queue->head != nullptr){
            found = false;
            for(int i = 0; i < size; i++){
                cashier = sorted_cashiers->at(i);
                if(cashier->is_available){
                    found = true;
                    cashier->is_available = false;
                    cashier->order = cashier_queue->dequeue();
                    cashier->order->waiting_time += cashier->total_time - cashier->order->arrival_time + cashier->order->order_time;
                    cashier->total_time += cashier->order->order_time; 
                    cashier->busy_time += cashier->order->order_time;
                    break;
                }
            }
            if(!found){
                break;
            }
        }
        if(cashier_queue->head ==nullptr && order != nullptr){
            found = false;
            for(int i = 0; i < size; i++){
                cashier = cashiers->at(i);
                if(cashier->is_available){
                    found =true;
                    if(cashier->total_time <= order->arrival_time){
                        cashier->total_time = order->arrival_time + order->order_time;
                    }else{
                        cashier->total_time += order->order_time;
                    }
                    cashier->busy_time += order->order_time;
                    cashier->order = order;
                    cashier->is_available = false;
                    break;
                }
            }
            if(!found){
                cashier_queue->enqueue(order);
            }
        }else if(order != nullptr){
            cashier_queue->enqueue(order);
        }
    }else if(order != nullptr){
        bool found = false;
        for(int i = 0; i < size; i++){
            cashier = cashiers->at(i);
            if(cashier->is_available){
                found = true;
                cashier->order = order;
                cashier->is_available = false;
                if(cashier->total_time <= order->arrival_time){
                    cashier->total_time = order->arrival_time + order->order_time;
                }else{
                    cashier->total_time += order->order_time;
                }
                cashier->busy_time += order->order_time;
                break;
            }
        }
        if(!found){
            cashier_queue->enqueue(order);
        }

    }
    cashier_queue->set_max_length();
}

void Restaurant2::find_available_baristas(Cashier* cashier, const double total_time){
    Queue* barista_queue = cashier->barista_queue;
    Barista* barista = cashier->barista;
    if(total_time == -1){
        while(barista_queue->head != nullptr){
            barista->order = barista_queue->dequeue();
            barista->order->waiting_time += barista->total_time - barista->order->arrival_time - barista->order->waiting_time - barista->order->order_time;
            barista->total_time += barista->order->brew_time;
            barista->busy_time += barista->order->brew_time;
        }
        return;
    }
    if(!barista->is_available){
        if(barista->total_time <= total_time){
            if(barista_queue->head != nullptr){
                barista->order = barista_queue->dequeue();
                barista->order->waiting_time += barista->total_time - barista->order->arrival_time - barista->order->waiting_time - barista->order->order_time;
                barista->total_time += barista->order->brew_time;
                barista->busy_time += barista->order->brew_time;
                if(cashier->order != nullptr){
                    barista_queue->barista_enqueue(cashier->order);
                }
            }else if(cashier->order != nullptr){
                if(barista->total_time <= total_time){
                    barista->total_time = total_time + cashier->order->brew_time;
                }else{
                    barista->total_time += cashier->order->brew_time;
                }
                barista->busy_time += cashier->order->brew_time;
                barista->order = cashier->order;
            }
            else{
                barista->is_available = true;
                barista->order = nullptr;
            }
        }else if(cashier->order != nullptr){
            barista_queue->barista_enqueue(cashier->order);

        }
    }else if(cashier->order != nullptr){
        if(barista->total_time <= total_time){
            barista->total_time = total_time + cashier->order->brew_time;
        }else{
            barista->total_time += cashier->order->brew_time;
        }
        barista->busy_time += cashier->order->brew_time;
        barista->order = cashier->order;
        barista->is_available = false;
    }
    barista_queue->set_max_length();
}

void Restaurant2::implement_restaurant(){
    Customer* customer;
    for(int i = 0; i < order_size; i++){
        customer = customers->at(i);
        total_time = customer->arrival_time;
        find_available_cashiers(customer, total_time);
    }
    vector<Cashier*>* sorted_employees;
    bool changed = false;
    while(cashier_queue->head != nullptr){
        changed = false;
        sorted_employees = sort_array(cashiers, size);
        for(int i = 0; i < size; i++){
            if(total_time >= sorted_employees->at(i)->total_time)continue;
            changed = true;
            total_time = sorted_employees->at(i)->total_time;
            find_available_cashiers(nullptr, total_time);
        }
        if(!changed){
            break;
        }
    }
    sorted_employees = sort_array(cashiers, size);
    double barista_time = total_time;
    for(int i = 0; i < size; i++){
        if(total_time >= sorted_employees->at(i)->total_time)continue;
        barista_time = sorted_employees->at(i)->total_time;
        find_available_cashiers(nullptr, barista_time);
    } 
    Cashier* cashier;
    for(int i = 1; i < size; i *= 3){
        cashier = cashiers->at(i);
        find_available_baristas(cashier, -1);
        if(cashier->barista->total_time > total_time){
            total_time = cashier->barista->total_time;
        }
    }
}

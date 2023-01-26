#include "Restaurant.h"
#include <algorithm>

using std::vector;

Restaurant::Restaurant(){}

Restaurant::Restaurant(const int size_value, const int order_value, std::vector<Customer*>* customers){
    this->customers = customers;
    total_time = 0.0;
    int barista_id = 0;
    int cashier_id = 0;
    order_size = order_value;
    size = size_value;
    cashier_queue = new Queue();
    barista_queue = new Queue();
    this->baristas = new std::vector<Barista*>();
    for(int i = 0; i < size/3; i++){
        baristas->push_back(new Barista(barista_id++));
    }
    this->cashiers = new std::vector<Cashier*>();
    for(int i = 0; i < size; i++){
        cashiers->push_back(new Cashier(cashier_id++));
    }
}


Restaurant::~Restaurant(){
    customers = nullptr;
    cashiers = nullptr;
    baristas = nullptr;
    delete cashier_queue;
    delete barista_queue;
}

/*
    @brief compares two employess respect to their first get to idle time.
    @param employee1
    @param employee2
*/
bool compare_employees(Employee* first, Employee* second){ 
    return first->total_time < second->total_time;
}

/*
    @param vector_will_be_coppied
    @param vector_size
    @brief creates copy of the given vector
*/
vector<Cashier*>* copy_array(vector<Cashier*>* first,const int& size){
    vector<Cashier*>* arr = new vector<Cashier*>();
    for(int i = 0; i < size; i++){
        arr->push_back(first->at(i));
    }
    return arr;
}

/*
    @param vector_will_be_coppied
    @param vector_size
    @brief creates copy of the given vector
*/
vector<Barista*>* copy_array(vector<Barista*>* first,const int& size){
    vector<Barista*>* arr = new vector<Barista*>();
    for(int i = 0; i < size; i++){
        arr->push_back(first->at(i));
    }
    return arr;
}

/*
    @param vector_will_be_sorted
    @param vector_size
    @brief creates an sorted copy of the given vector
*/
vector<Cashier*>* sort_array(vector<Cashier*>* array, const int& size){
    vector<Cashier*>* new_employee_array;
    new_employee_array = copy_array(array, size);
    std::sort(new_employee_array->begin(), new_employee_array->end(), compare_employees);
    return new_employee_array;
}

/*
    @param vector_will_be_sorted
    @param vector_size
    @brief creates an sorted copy of the given vector
*/
vector<Barista*>* sort_array(vector<Barista*>* array, const int& size){
    vector<Barista*>* new_employee_array;
    new_employee_array = copy_array(array, size);
    std::sort(new_employee_array->begin(), new_employee_array->end(), compare_employees);
    return new_employee_array;
}

void Restaurant::find_available_cashiers(Customer* order, const double total_time){
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
            find_available_baristas(cashier->order, cashier->total_time);
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

void Restaurant::find_available_baristas(Customer* order, const double total_time){
    Barista* barista;
    for(int i = 0; i < size/3; i++){
        barista = baristas->at(i);
        if(barista->total_time <= total_time && !barista->is_available){
            barista->is_available = true;
            barista->order= nullptr;
        }
    }
    if(barista_queue->head != nullptr){
        bool found = false;
        vector<Barista*>* sorted_baristas = sort_array(baristas, size/3);
        while(barista_queue->head != nullptr){
            found = false;
            for(int i = 0; i < size/3; i++){
                barista = sorted_baristas->at(i);
                if(barista->is_available){
                    found = true;
                    barista->is_available = false;
                    barista->order = barista_queue->dequeue();
                    barista->order->waiting_time += barista->total_time - barista->order->arrival_time - barista->order->waiting_time - barista->order->order_time;
                    barista->total_time += barista->order->brew_time; 
                    barista->busy_time += barista->order->brew_time; 
                    break;
                }
            }
            if(!found){
                break;
            }
        }
        if(barista_queue->head == nullptr && order != nullptr){
            found= false;
            for(int i = 0; i < size/3; i++){
                barista = baristas->at(i);
                if(barista->is_available){
                    found = true;
                    if(barista->total_time <= total_time){
                        barista->total_time = total_time + order->brew_time;
                    }else{
                        barista->total_time += order->brew_time;
                    }
                    barista->busy_time += order->brew_time;
                    barista->order = order;
                    barista->is_available = false;
                    break;
                }
            }
            if(!found){
                barista_queue->barista_enqueue(order);
            }

        }else if(order != nullptr){
            barista_queue->barista_enqueue(order);
        }
    }else if(order != nullptr){
        bool found = false;
        for(int i = 0; i < size/3; i++){
            barista = baristas->at(i);
            if(barista->is_available){
                found = true;
                barista->order = order;
                barista->is_available = false;
                if(barista->total_time <= total_time){
                    barista->total_time = total_time + order->brew_time;
                }else{
                    barista->total_time += order->brew_time;
                }
                barista->busy_time += order->brew_time;
                break;
            }
        }
        if(!found){
            barista_queue->barista_enqueue(order);
        }
    }
    barista_queue->set_max_length();
}

void Restaurant::implement_restaurant(){
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
    for(int i = 0; i < size; i++){
            if(total_time >= sorted_employees->at(i)->total_time)continue;
            total_time = sorted_employees->at(i)->total_time;
            find_available_cashiers(nullptr, total_time);
        }
    vector<Barista*>* sorted_baristas;
    while(barista_queue->head != nullptr){
        changed = false;
        sorted_baristas = sort_array(baristas, size/3);
        for(int i = 0; i < size/3; i++){
            if(total_time >= sorted_baristas->at(i)->total_time)continue;
            changed = true;
            total_time = sorted_baristas->at(i)->total_time;
            find_available_baristas(nullptr, total_time);
        }
        if(!changed){
            break;
        }
    }
    sorted_baristas = sort_array(baristas, size/3);
    for(int i = 0; i < size/3; i++){
        if(total_time >= sorted_baristas->at(i)->total_time)continue;
        total_time = sorted_baristas->at(i)->total_time;
        find_available_baristas(nullptr, total_time);
    }

}

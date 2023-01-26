#include "Restaurant2.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

int main(int argc, char** argv){
    std::ifstream ifs;
    ifs.open(argv[1]);
    std::string input;
    int size, order_number;
    std::getline(ifs, input);
    size = std::stoi(input);
    std::getline(ifs, input);
    order_number = std::stoi(input);
    std::vector<Customer*>* customers = new std::vector<Customer*>();
    std::vector<Customer*>* customers2 = new std::vector<Customer*>();
    while(std::getline(ifs, input)){
        std::vector<double>* arr = new std::vector<double>();
        std::string item;
        std::stringstream ss (input);
        while(std::getline(ss, item, ' ')){
            arr->push_back(std::stod(item));
        }
        customers->push_back(new Customer(arr->at(0), arr->at(1), arr->at(2), arr->at(3)));
        customers2->push_back(new Customer(arr->at(0), arr->at(1), arr->at(2), arr->at(3)));
    }
    ifs.close();
    Restaurant* model1 = new Restaurant(size, order_number, customers);
    model1->implement_restaurant();

    std::ofstream ofs;
    ofs.open(argv[2]);
    ofs << model1->total_time << std::endl;
    ofs << model1->cashier_queue->max_length << std::endl;
    ofs << model1->barista_queue->max_length << std::endl;
    long double ratio = 0;
    for(int i = 0; i < size; i++){
        ratio = model1->cashiers->at(i)->busy_time/model1->total_time;
        ofs << std::fixed << std::setprecision(2) << ratio << std::endl;
    }
    for(int i = 0; i < size/3; i++){
        ratio = model1->baristas->at(i)->busy_time/model1->total_time;
        ofs << std::fixed << std::setprecision(2) << ratio << std::endl;
    }
    for(int i = 0; i < order_number; i++){
        ofs << std::fixed << std::setprecision(2) << customers->at(i)->waiting_time + customers->at(i)->order_time + customers->at(i)->brew_time << std::endl;
    }

    Restaurant2* model2 = new Restaurant2(size, order_number, customers2);
    model2->implement_restaurant();

    ofs << std::endl << model2->total_time << std::endl;
    ofs << model2->cashier_queue->max_length << std::endl;
    for(int i = 1; i < size; i *= 3){
        ofs << model2->cashiers->at(i)->barista_queue->max_length << std::endl;
    }
    for(int i = 0; i < size; i++){
        ratio = model2->cashiers->at(i)->busy_time/model2->total_time;
        ofs << std::fixed << std::setprecision(2) << ratio << std::endl;
    }
    for(int i = 1; i < size; i *= 3){
        ratio = model2->cashiers->at(i)->barista->busy_time/model2->total_time;
        ofs << std::fixed << std::setprecision(2) << ratio << std::endl;
    }
    for(int i = 0; i < order_number; i++){
        ofs << std::fixed << std::setprecision(2) << customers2->at(i)->waiting_time + customers2->at(i)->order_time + customers2->at(i)->brew_time << std::endl;
    }
    ofs.close();
    for(int i = 0; i < order_number;i++){
        delete customers->at(i);
        delete customers2->at(i);
    }
    customers->clear();
    customers2->clear();
    return 1;
}
#include "Restaurant.h"
#include <iostream>
#include <vector>
class Restaurant2{
    public:
        std::vector<Customer*>* customers;
        int size;      
        int order_size;
        double total_time;
        Queue* cashier_queue;
        std::vector<Cashier*>* cashiers;

        Restaurant2(const int, const int, std::vector<Customer*>*);
        ~Restaurant2();

        /*
            @brief compares two employess respect to their first get to idle time.
            @param employee1
            @param employee2
        */
        static bool compare_employees(Employee*, Employee*);

        /*
            @param vector_will_be_coppied
            @param vector_size
            @brief creates copy of the given vector
        */
        std::vector<Cashier*>* copy_array(std::vector<Cashier*>*, const int&);
        
        /*
            @param vector_will_be_coppied
            @param vector_size
            @brief creates copy of the given vector
        */
        std::vector<Barista*>* copy_array(std::vector<Barista*>*, const int&);

        /*
            @param vector_will_be_sorted
            @param vector_size
            @brief creates an sorted copy of the given vector
        */
        std::vector<Cashier*>* sort_array(std::vector<Cashier*>*, const int&);
        
        /*
            @param vector_will_be_sorted
            @param vector_size
            @brief creates an sorted copy of the given vector
        */
        std::vector<Barista*>* sort_array(std::vector<Barista*>*, const int&);
        /*
            @brief implements restaurant process from start to end by the help of other functions
        */
        void implement_restaurant();

        /*
            @param customer
            @param time_reference
            @brief adjusts cashier_queue, implements find_available_baristas, sends cashiers that has finished his/her work to idle and gets order
        */
        void find_available_cashiers(Customer*, const double);

        /*
            @param cashier
            @param time_reference
            @brief gets new order, sends baristas that has finished his/her work to idle and handles barista_queue
        */
        void find_available_baristas(Cashier*, const double);
};

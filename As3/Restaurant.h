#include "Cashier.h"
#include <vector>
class Restaurant{
    public:
        std::vector<Customer*>* customers;
        int size;      
        int order_size;
        double total_time;
        Queue* cashier_queue;
        Queue* barista_queue;
        std::vector<Barista*>* baristas;
        std::vector<Cashier*>* cashiers;

        Restaurant(const int, const int, std::vector<Customer*>*);
        Restaurant();
        ~Restaurant();
        
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
        void find_available_baristas(Customer*, const double);
};

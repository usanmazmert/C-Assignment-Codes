#include "Customer.h"
class Queue{
    public:
        Customer* head;
        Customer* rear;
        int max_length;
        Queue();
        ~Queue();
        void enqueue(Customer*);

        /*
            @brief adds order respect to its price. The expensive one at the end
        */
        void barista_enqueue(Customer*);
        
        /*
            @brief handles maximum length of the queue.
        */
        void set_max_length();
        Customer* dequeue();
};
#include "Queue.h"

Queue::Queue(){
    head= nullptr;
    rear = nullptr;
    max_length = 0;
};

Queue::~Queue(){
    head = nullptr;
    rear = nullptr;
}

void Queue::barista_enqueue(Customer* order){
    if(head == nullptr){
        head = order;
        rear = order;
        return;
    }
    if(order->order_price < head->order_price){
        order->next = head;
        head = order;
        return;
    }
    Customer* temp = head;
    while(temp->next != nullptr){
        if(order->order_price < temp->next->order_price){
            order->next = temp->next;
            temp->next = order;
            return;
        }
        temp = temp->next;
    }
    temp->next = order;
    rear = order;
}

void Queue::enqueue(Customer* new_node){
    if(head == nullptr){
        head = new_node;
        rear = new_node;
        return;
    }
    new_node->next = head;
    head = new_node;
}

Customer* Queue:: dequeue(){
    Customer* trash;
    if(head == nullptr)
        return nullptr;
    if(head == rear)
    {
        trash = head;
        head = nullptr;
        rear = nullptr;
        return trash;
    }
    Customer* temp = head;
    while(temp->next != rear){ 
        temp = temp->next; 
    }
    trash = rear;
    rear = temp;
    temp->next = nullptr;
    return trash;
}

void Queue::set_max_length(){
    if(head == nullptr)
        return;
    Customer * temp = head;
    int count = 0;
    while(temp != nullptr){
        temp = temp->next;
        count++;
    }
    if (count > max_length)max_length = count;
}
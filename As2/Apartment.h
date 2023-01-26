#include <string>
#include "Flat.h"

class Apartment{
    public:
        std::string name;
        int totalBandWidth;
        int maxBandWidth;
        Flat* head;
        Apartment* next;

        //If there doesn't exist any apartment previously then the next attribute will point itself
        Apartment(const std::string&, const int&);

        ~Apartment();
};
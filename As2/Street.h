#include <string>
#include "Apartment.h"
#define ITRCRC while(temp != nullptr && head != nullptr && temp->next->name != head->name)
#define ITRCRC2(temp1, temp2) while(temp1 != nullptr && temp2 != nullptr && temp1->next->name != temp2->name)
#define ITRDBL while(temp != nullptr && temp->next != nullptr)
class Street{
    public:
        Apartment* head;

        //If head is null next attribute will point to head itself.
        Street();

        ~Street();


        /* 
            @param apartment_name
            @param position
            @param max_bandwidth
            @details adds an apartment node to circular apartment linked list.
        */
        void addApartment(const std::string&, const std::string&,const int&);

        
        /*
            @param apartment
            @param flat_index
            @param initial_bandwidth
            @param flat_id
        */
        void addFlat(const std::string&, const int&, const int&, const int&);

        /*
            @param apartment
            @details removes the apartment from the list and deallocates it and its flats
        */
        void removeApartment(const std::string&);


        /*
            @param apartment_name
            @param flat_id
            @details converts empty flag to 1 and assign 0 to
            initial_bandwith
        */
        void makeFlatEmpty(const std::string&, const int&);

        /*
            @details sums all of the max_bandwith values of apartments
        */
        int findSumOfMaxBandWidth();


        /*
            @param first_apartment
            @param second_apartment
            @details adds the second apartment's flats to first one's
        */
        void mergeTwoApartments(const std::string&, const std::string&);

        /*
            @param apartmentName
            @param id
            @param input
        */
        void relocateFlatsToSameApartments(std::string &, const int &, std::string &);

        std::string listApartments();

};

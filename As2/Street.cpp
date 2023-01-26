#include "Street.h"
#include <iostream>



Street::Street(){
    head = nullptr;
}


//@brief deletes the street object and apartments
Street::~Street(){
    if(head == nullptr)return;
    Apartment* temp = head->next;
    Apartment* trash;
    ITRCRC{
        trash = temp;
        temp = temp->next;
        delete trash;
    }
    delete temp;
    delete head;
}

/*
    @brief Returns a pointer to the apartment whose name is given
*/
Apartment* findApartment(Apartment* head, std::string name){
    Apartment* temp = head;
    ITRCRC{
       if(temp->name == name)return temp; 
       temp = temp->next;
    }
    if(temp->name == name)return temp;
    return head;
};

/*
    @brief Converts string to string array for rellocate function
*/ 
int* splitList(const std::string &input,const char &delimeter){
    std::string str = "";
    int* arr = new int[input.length() - 2];
    int index = 0;
    for(int i = 0; i < input.length(); i++){
        if(input[i] == '[')continue;
        if(input[i] == delimeter || input[i] == ']'){
            arr[index] = std::stoi(str);
            str = "";
            index++;
            continue;
        }
        str += input[i];
    }
    arr[index] = -1;
    return arr;
}

/*
    @brief Checks whether the given value is in the given array
    if is then returns its position
*/
int arrayIncludes(int* arr, int number){
    for(int i = 0; i < sizeof(arr); i++){
        if(arr[i] == -1)return-1;
        if (number == arr[i]) return i+1;
    } 
    return -1;
}

//Common rellocation function
void relocateFunc(Flat* temp, Apartment* itrApt, Apartment* newApartment, int* flats, Flat* reference){
    int position = arrayIncludes(flats, temp->id);
    if(position == -1)return;
    itrApt->maxBandWidth -= temp->initialBandWidth;
    itrApt->totalBandWidth -= temp->initialBandWidth;
    newApartment->maxBandWidth += temp->initialBandWidth;
    newApartment->totalBandWidth += temp->initialBandWidth;
    if(temp->next == nullptr){
        temp->prev->next = nullptr;
        temp->prev = nullptr;
    }else if(temp->prev == nullptr){
        itrApt->head = temp->next;
        temp->next->prev = nullptr;
        temp->next = nullptr;
    }else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        temp->prev = temp->next = nullptr;
    }
    int referencePosition = arrayIncludes(flats, reference->id);
    if(referencePosition == -1 || referencePosition > position){
        while(referencePosition != -1 && referencePosition > position){
            if(reference->prev == nullptr)break;
            referencePosition = arrayIncludes(flats, reference->prev->id);
            if(referencePosition > position)
                reference = reference->prev;
        }
        if(reference->prev == nullptr){
            reference->prev = temp;
            temp->next = reference;
            newApartment->head = temp;
        }else{
            reference->prev->next = temp;
            temp->next = reference;
            temp->prev = reference->prev;
            reference->prev = temp;
        }
        reference = temp;
        return;
    }else if(referencePosition < position){
        while(referencePosition < position){
            referencePosition = arrayIncludes(flats, reference->next->id);
            if(referencePosition == -1){
                break;
            }
            if(referencePosition < position){
                reference = reference->next;
            }
        }
        temp->next = reference->next;
        temp->prev = reference;
        reference->next->prev = temp;
        reference->next = temp;
        reference = temp;
    }
}

void Street::addApartment(const std::string &name, const std::string &position,const int &maxBandWidth){
    Apartment* newApartment = new Apartment(name, maxBandWidth);
    Apartment* temp = head;
    if(head == nullptr){
        head= newApartment;
        newApartment->next = newApartment;
        return;
    }
    if(position == "head"){
        ITRCRC{
            temp = temp->next;
        }
        temp->next = newApartment;
        newApartment->next = head;
        head = newApartment;
        return;
    }
    int index = 0;
    for(int i = 0; i < position.length(); i++){
        if(position[i] == '_'){
            index = i+1;
        }
    }
    std::string input1 = position.substr(0, index-1);
    std::string input2 = position.substr(index, position.length() - (index));
    if(input1 == "before"){
        ITRCRC{
            if(temp->next->name == input2){
                newApartment->next = temp->next;
                temp->next = newApartment;
                break;
            }
            temp = temp->next;
        }
        if(temp->next->name == input2){
            newApartment->next = temp->next;
            temp->next = newApartment;
        }
        if(head->name == input2){
            head = newApartment;
        }
    }
    if(input1 == "after"){
        ITRCRC{
            if(temp->name == input2){
                newApartment->next = temp->next;
                temp->next = newApartment;
                break;
            }
            temp = temp->next;
        }
        if(temp->name == input2){
            newApartment->next = temp->next;
            temp->next = newApartment;
        }
    }
};

void Street::addFlat(const std::string& apartmentName, const int& index, const int& initialBandWidth, const int& id){
    Apartment* apt = findApartment(head, apartmentName); // no problem
    int bandWidth = initialBandWidth + apt->totalBandWidth >=
    apt->maxBandWidth ? apt->maxBandWidth - apt->totalBandWidth : initialBandWidth;
    apt->totalBandWidth += bandWidth;
    Flat* newFlat = new Flat(bandWidth, id);
    if(apt->head == nullptr){
        apt->head = newFlat;
        return;
    }
    Flat* temp = apt->head;
    if(index == 0){
        apt->head->prev = newFlat;
        newFlat->next = apt->head;
        apt->head = newFlat;
        return;
    }
    for(int i = 1; i < index; i++){
        temp = temp->next;
    }
    if(temp->next == nullptr){
        newFlat->prev = temp;
        temp->next = newFlat;
        return;
    }
    newFlat->next = temp->next;
    newFlat->next->prev = newFlat;
    temp->next = newFlat;
    newFlat->prev = temp;
};

void Street::removeApartment(const std::string &name){
    if(head == nullptr){
        return;
    }
    Apartment* lastApartment = head;
    ITRCRC2(lastApartment, head){
        lastApartment = lastApartment->next;
    }
    if(head->name == name){
        if(head->next->name == name){
            head->next = nullptr;
            delete head;
            head = nullptr;
            return;
        }
        lastApartment->next = head->next;
        head = head->next;
        delete head;
    }
    Apartment* temp = head;
    Apartment* trash;
    ITRCRC{
        if(temp->next->name == name){
            trash = temp->next;
            temp->next = trash->next; 
            delete trash;
            break;
        }
        temp = temp->next;
    }
};

void Street::makeFlatEmpty(const std::string &apartmentName, const int &id){
    if(head == nullptr)return;
    Apartment* apt = findApartment(head, apartmentName);
    Flat* temp = apt->head;
    while(temp->next != nullptr){
        if(temp->id == id){
            temp->isEmpty = 1;
            apt->totalBandWidth - temp->initialBandWidth;
            temp->initialBandWidth = 0;
            break;
        }
        temp = temp->next;
    }
    if(temp->id == id){
        temp->isEmpty = 1;
        apt->totalBandWidth - temp->initialBandWidth;
        temp->initialBandWidth = 0;
    }
};

int Street::findSumOfMaxBandWidth(){
    int total = 0;
    if(head == nullptr)return total;
    Apartment *temp = head;
    ITRCRC{
        total+= temp->maxBandWidth;
        temp = temp->next;
    }
    total += temp->maxBandWidth;
    return total;
}

void Street::mergeTwoApartments(const std::string &apartment1, const std::string &apartment2){
    Apartment* apt1 = findApartment(head, apartment1);
    Apartment* apt2 = findApartment(head, apartment2);
    Apartment* tempApt = head;
    Apartment* tempApt2 = tempApt;
    apt1->maxBandWidth += apt2->maxBandWidth;
    apt1->totalBandWidth += apt2->totalBandWidth;
    ITRCRC2(tempApt2, head){
        tempApt2 = tempApt2->next;
    }
    if(apt2->name == head->name){
        tempApt2->next = apt2->next;
        head = apt2->next;
    }else if(tempApt2->name == apt2->name){
        ITRCRC2(tempApt,tempApt2){
            tempApt = tempApt->next;
        }
        tempApt->next = head;
    }
    else{
        ITRCRC2(tempApt, head){
            if(tempApt->name == apt2->name){
                tempApt2->next = tempApt->next;
                break;
            }
            tempApt2 = tempApt;
            tempApt = tempApt->next;
        }
    }
    apt2->next = nullptr;
    if(apt1->head == nullptr){ 
        apt1->head = apt2->head;
        apt2->head = nullptr;
        delete apt2;
        return;
    }
    if(apt2->head == nullptr){ 
        delete apt2;
        return;
    }
    Flat* temp = apt1->head;
    ITRDBL{ 
        temp = temp->next;
    }
    temp->next = apt2->head;
    apt2->head->prev = temp;
    apt2->head = nullptr; 
    delete apt2;
}

void Street::relocateFlatsToSameApartments(std::string &apartmentName, const int &flatId, std::string &flatList){
    int* flats = splitList(flatList, ',');
    Apartment* newApartment = findApartment(head, apartmentName);
    Flat* temp = newApartment->head;
    ITRDBL{
        if(temp->id == flatId){
            break;
        }
        temp = temp->next;
    }
    Flat* reference = temp; // sorunsuz
    Apartment* itrApt = head;
    Flat* temp2;
    ITRCRC2(itrApt, head){
        if(itrApt->name == apartmentName){
            itrApt = itrApt->next;
            continue;
        }
        temp = itrApt->head;
        ITRDBL{
            temp2 = temp;
            relocateFunc(temp2, itrApt, newApartment, flats, reference);
            temp = temp->next;
        }
        temp2 = temp;
        relocateFunc(temp2, itrApt, newApartment, flats, reference);
        itrApt = itrApt->next;
    }
    if(itrApt->name != newApartment->name){
        temp = itrApt->head;
        ITRDBL{
            temp2 = temp;
            relocateFunc(temp, itrApt, newApartment, flats, reference);
            temp = temp->next;
        }
        temp2 = temp;
        relocateFunc(temp2, itrApt, newApartment, flats, reference);
        itrApt = itrApt->next;
    }
}

std::string Street::listApartments(){
    if(head == nullptr)return "";
    std::string output = "";
    Apartment* tempApt = head;
    Flat* temp;
    ITRCRC2(tempApt, head){
        temp = tempApt->head;
        output +=tempApt->name + "(" + std::to_string(tempApt->maxBandWidth) + ")";
        ITRDBL{
            output += '\t';
            output += "Flat" + std::to_string(temp->id) + '(' + std::to_string(temp->initialBandWidth) + ')';
            temp = temp->next;
        }
        if(temp != nullptr){
            output += '\t';
            output += "Flat" + std::to_string(temp->id) + '(' + std::to_string(temp->initialBandWidth) + ')';
            temp = temp->next;
        }
        output += '\n';
        tempApt = tempApt->next;
    }
    if(tempApt != nullptr){
        output +=tempApt->name + "(" + std::to_string(tempApt->maxBandWidth) + ")";
        temp = tempApt->head;
        ITRDBL{
            output += '\t';
            output += "Flat" + std::to_string(temp->id) + '(' + std::to_string(temp->initialBandWidth) + ')';
            temp = temp->next;
        }
        if(temp != nullptr){
            output += '\t';
            output += "Flat" + std::to_string(temp->id) + '(' + std::to_string(temp->initialBandWidth) + ')';
            temp = temp->next;
        }
        output += '\n';
    }
    output += '\n';
    return output;
}


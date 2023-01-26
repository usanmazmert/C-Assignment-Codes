#include "Street.h"
#include <fstream>
#include <string>
#include <iostream>


//splits inputs respect to tabs between them
std::string* split(std::string input){
    std::string* inputArr = new std::string[5];
    std::string str = "";
    int index = 0;
    for(int i = 0; i < input.length(); i++){
        if(input[i] == '\t'){
            inputArr[index] = str;
            index++;
            str = "";
            continue;
        }
        str += input[i];
    }
    inputArr[index] = str;
    return inputArr;
}


int main(int argc, char** argv){
    std::ofstream fileWrite;

    //openning output file
    fileWrite.open(argv[2]);
    Street* street = new Street();
    std::ifstream ifs;
    ifs.open(argv[1]);
    std::string input;


    //taking inputs line by line
    while(std::getline(ifs, input)){
        std::string* inputs = split(input);
        if(inputs[0] == "add_apartment"){
            street->addApartment(inputs[1], inputs[2], std::stoi(inputs[3]));
        }
        if(inputs[0] == "add_flat"){
            street->addFlat(inputs[1], std::stoi(inputs[2]), std::stoi(inputs[3]), std::stoi(inputs[4]));
        }
        if(inputs[0] == "remove_apartment"){
            street->removeApartment(inputs[1]);
        }
        if(inputs[0] == "make_flat_empty")
        {
            street->makeFlatEmpty(inputs[1], std::stoi(inputs[2]));
        }
        if(inputs[0] == "merge_two_apartments")
        {
            street->mergeTwoApartments(inputs[1], inputs[2]);
        }
        if(inputs[0] == "find_sum_of_max_bandwidths")
            fileWrite << "sum of bandwidth: " + std::to_string(street->findSumOfMaxBandWidth()) + "\n\n";
        if(inputs[0] == "relocate_flats_to_same_apartment")
        {
            street->relocateFlatsToSameApartments(inputs[1], std::stoi(inputs[2]), inputs[3]);
        }
        if(inputs[0] == "list_apartments")
        {
            fileWrite << street->listApartments();
        }
    }
    fileWrite.close();
    ifs.close();
    delete street;
    return 1;
}
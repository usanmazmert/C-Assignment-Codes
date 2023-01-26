#include "Flat.h"

Flat::Flat(const int &initialBandWidth,const int &id){
    this->initialBandWidth = initialBandWidth;
    this->id = id;
    next = nullptr;
    prev = nullptr;
    isEmpty=0;
}

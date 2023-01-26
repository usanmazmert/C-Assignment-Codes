temp2 = temp;
itrApt->maxBandWidth -= temp->initialBandWidth;
newApartment->maxBandWidth += temp->initialBandWidth;
if(temp->next == nullptr){
    temp->prev->next = nullptr;
}else{
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    temp = temp->next;
    int referencePosition = 0;
    if(rellocatedOne->prev != nullptr){
        referencePosition = arrayIncludes(flats, reference->prev->id);
    }
    if(referencePosition == -1){
        reference->prev->next = temp2;
        temp2->prev = reference->prev;
        temp2->next = reference;
        reference->prev = temp2;
        continue;
    }
    while(referencePosition > position && reference->prev != nullptr){
        reference = reference->prev;
        referencePosition = arrayIncludes(flats, reference->prev->id);
    }
    if(reference->prev == nullptr){
        reference->prev = temp2;
        temp2->next = reference;
        newApartment->head = temp2;
    }else{
        reference->prev->next = temp2;
        temp2->next = reference;
        temp2->prev = reference->prev;
        reference->prev = temp2;
    }
}
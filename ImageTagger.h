//
// Created by baha2 on 03-Dec-18.
//

#ifndef HW2_LIBRARY_IMAGETAGGER_H
#define HW2_LIBRARY_IMAGETAGGER_H

#include <iostream>     // std::cout
#include <new>          // std::bad_alloc
#include "Image.h"
#include "Tree.h"
#include "HashTable.h"



class ImageTagger {

    Hash hashTable;
    int pixels;

    ImageTagger(int pixels) : pixels(pixels) {}

    StatusType deleteImage (int imageId) {
        if(imageId<=0) return INVALID_INPUT;
        if(!hashTable.delete_element(imageId))
            return FAILURE;
        return SUCCESS;
    }


    StatusType addImage (int imageId) {
        if(imageId<=0) return INVALID_INPUT;
        if(hashTable.find_element(imageId))
            return FAILURE;

        Image image= Image(imageId,pixels);
       if(hashTable.add_element(image))
        return SUCCESS;
       else
           return ALLOCATION_ERROR;
    }





};


#endif //HW2_LIBRARY_IMAGETAGGER_H

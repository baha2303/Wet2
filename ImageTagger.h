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

public:

    Hash* hashTable;
    int pixels;
    ImageTagger(int pixels) : pixels(pixels) {
        hashTable=new Hash();
    }
    ~ImageTagger() {

            delete (hashTable);
        }

    StatusType addImage (int imageId) {
        if(imageId<=0) return INVALID_INPUT;
        if(hashTable->find_element(imageId)!= nullptr)
            return FAILURE;

        Image* image= new Image(imageId,pixels);
        if(hashTable->add_element(image))
            return SUCCESS;
        else
            return ALLOCATION_ERROR;
    }


    StatusType deleteImage (int imageId) {
        if(imageId<=0) return INVALID_INPUT;
        if(!hashTable->delete_element(imageId))
            return FAILURE;
        return SUCCESS;
    }


    StatusType SetLabelScore(int imageID, int pixel, int label, int score) {

        Image* image= hashTable->find_element(imageID);
        if(!image) return FAILURE;

        return (image->setLabelScore(pixel,label,score));

    }

    StatusType ResetLabelScore( int imageID, int pixel, int label) {
        Image* image= hashTable->find_element(imageID);
        if(!image) return FAILURE;
        return(image->resetLabelScore(pixel,label));
    }


    StatusType GetHighestScoredLabel( int imageID, int pixel, int *label){
        Image* image= hashTable->find_element(imageID);
        if(!image) return FAILURE;

        return (image->getHighestLabel(pixel,label));
    }

    StatusType MergeSuperPixels( int imageID, int pixel1, int pixel2) {


        Image* image= hashTable->find_element(imageID);
        if(!image) return FAILURE;
        return (image->mergeSets(pixel1,pixel2));

    }



};


#endif //HW2_LIBRARY_IMAGETAGGER_H

//
// Created by baha2 on 12/31/2018.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "List.h"
#include "Image.h"
#include "library1LL.h"
#include <math.h>
#define DELETED -1

class Hash {
    void **table;
public:

    int size;
    int elements;
    bool transferring;

    //constructor
    Hash():size(7),elements(0) {
        transferring= false;
        table= new void*[size];
        for(int i=0 ; i< size ; i++) {
            table[i]= Init_LL();
        }
    }

    ~Hash() {
        for (int i = 0; i < size; i++) {

                void *image = getHeadValueandDelete(table[i]);
                while (image != nullptr) {
                    Image *image_ = static_cast<Image *>(image);
                    delete (image_);
                    image = getHeadValueandDelete(table[i]);

                }
                Quit_LL(&table[i]);
        }
        delete[] (table);
    }
    //function for turning an imageId into an interger that fits the array
    int hash_function(int key) {
        double golden = (sqrt(5)-1)/2;

        double num;
        return   ((int)(floor(size*modf(golden*key,&num))))%size ;
    }


    bool add_element(Image* image) {


        int hashed = hash_function(image->imageId);
        void* node;
        if(Find(table[hashed],image->imageId,&node)==SUCCESS) {
            return false;
        }
        if(Add(table[hashed],image->imageId, (void*)image,&node)==SUCCESS){
            elements++;

            if(!transferring)
                resize();

            return true;
        }

        return false;
    }


    bool delete_element(int imageId) {

        int hashed=hash_function(imageId);
        void* node;
        if(Find(table[hashed],imageId,&node)!=SUCCESS) {
            return false;
        }
        Image* image = static_cast<Image*>(node);
        delete(image);
        if(Delete(table[hashed],imageId)==SUCCESS) {
            elements--;
            resize();
            return true;

        }
        return false;
    }


    Image* find_element(int imageId) {
        int hashed=hash_function(imageId);
        void* node;
        if(Find(table[hashed],imageId,&node)!=SUCCESS) {
            return nullptr;
        }
        Image* image= static_cast<Image*>(node);
        return image;
    }



    void resize() {
        if(elements>=size) {
            transfer(size*2);
        }
        if(elements<=size*0.25 && size>27) {
            transfer(size/2);
        }


    }

    void transfer(int new_size) {
        void** old_table=table;
        int old_size=size;
        table= new void*[new_size];
        size=new_size;
        elements=0;
        for (int i = 0; i < size ; ++i) {
            table[i]= Init_LL();
        }
        transferring=true;
        for (int i = 0; i < old_size ; ++i) {
            void* image=getHeadValueandDelete(old_table[i]);
            while(image != nullptr) {
                Image* image_= static_cast<Image*>(image);
                add_element(image_);
                image=getHeadValueandDelete(old_table[i]);
            }
        }
        for (int i = 0; i < old_size ; ++i) {
            Quit_LL(&old_table[i]);
        }

        delete [](old_table);
        transferring=false;
    }

    void** getHashArray(int* array_size) {
        *array_size=size;
        return table;
    }



};

#endif //WET2_HASHTABLE_H

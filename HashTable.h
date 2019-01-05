//
// Created by baha2 on 12/31/2018.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "Image.h"


#define DELETED -1

class Hash {
    Image **table;
public:

    int size=7;
    int elements=0;
    Image *deleted_image = new Image(1,1);  ///////////////////////////remember to free !!!!
    bool transferring= false;

    //constructor
    Hash() {
       table= new Image*[size];
       for(int i=0 ; i< size ; i++) {
           table[i]= nullptr;
       }
        deleted_image->imageId=DELETED;
    }

    //function for turning an imageId into an interger that fits the array
    int hash_function(int key, int i) {

        return (key%size + i*(1+key%(size-2)))%size;

    }


    bool add_element(Image& image) {
        int i = 0;
        bool done = false;
        while (!done) {
            int hashed = hash_function(image.imageId, i);
            if (table[hashed] == nullptr || table[hashed]->imageId == DELETED) {
                if(transferring== false) {
                    elements++;
                }
                done = true;
                table[hashed]=&image;
                resize();
                return true;

            }

            if(table[hashed]->imageId == image.imageId) {
                return false;
            }
            i++;
        }
        return true;

    }


bool delete_element(int imageId) {
    int i=0;
    int hashed=hash_function(imageId,i);
    while(table[hashed]!= nullptr ) {
        if(table[hashed]->imageId == imageId) {
            table[hashed]->destroy();
            table[hashed]=deleted_image;
            elements--;
            resize();
            return true;
        }
        i++;
        hashed=hash_function(imageId,i);

    }
    return false;
}

Image* find_element(int imageId) {
        int i=0;
    int hashed=hash_function(imageId,i);
    while(table[hashed] != nullptr ) {
        if(table[hashed]->imageId==imageId) {
            return table[hashed];
        }
        i++;
        hashed=hash_function(imageId,i);
    }

    return nullptr;
    }



    void resize() {
            if(elements==size) {
                transfer(size*2);
            }
            if(elements<=size/4 && size>7) {
                transfer(size/2);
        }


    }

    void transfer(int new_size) {
      Image** old_table=table;
      int old_size=size;
      table= new Image*[new_size];
      size=new_size;
        for (int i = 0; i < size ; ++i) {
            table[i]= nullptr;

        }
        for (int i = 0; i < old_size ; ++i) {
            if(old_table[i]!= nullptr && old_table[i]->imageId!=DELETED) {
                transferring= true;
                add_element(*old_table[i]);
                transferring= false;
            }
        }
       delete[](old_table);

    }

    Image** getHashArray(int* array_size) {
        *array_size=size;
        return table;
    }


    void print() {

        for (int i = 0; i < size ; ++i) {
            if(table[i]== nullptr) {
                std::cout << i << "--NULL___";
            }
            else {
                std::cout << i << "--" << table[i]->imageId << "___" ;
            }
        }
        std::cout << std::endl;
    }

};

#endif //WET2_HASHTABLE_H

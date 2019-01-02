#include <stdio.h>
#include <new>
#include "HashTable.h"
#include "Image.h"



int main () {
    Image *image1 = new Image(10);
    image1->key=1;

    Image *image2 = new Image(10);
    image2->key=2;

    Image *image3 = new Image(10);
    image3->key=3;

    Image *image4 = new Image(10);
    image4->key=4;

    Image *image5 = new Image(10);
    image5->key=5;

    Image *image6 = new Image(10);
    image6->key=6;

    Image *image7 = new Image(10);
    image7->key=7;

    Hash* HashTable= new Hash();

    HashTable->print();
   if(HashTable->add_element(*image1)==true) {
    std::cout << "Good" << std::endl;
   }

    HashTable->print();
    if(HashTable->add_element(*image2)==true) {
        std::cout << "Good" << std::endl;
    }
    HashTable->print();
    if(HashTable->add_element(*image3)==true) {
        std::cout << "Good" << std::endl;
    }
    HashTable->print();


    if(HashTable->add_element(*image4)==true) {
        std::cout << "Good" << std::endl;
    }
    HashTable->print();
    if(HashTable->add_element(*image5)==true) {
        std::cout << "Good" << std::endl;
    }
    HashTable->print();
    if(HashTable->add_element(*image6)==true) {
        std::cout << "Good" << std::endl;
    }
    HashTable->print();
    if(HashTable->add_element(*image7)==true) {
        std::cout << "Good" << std::endl;
    }
    HashTable->print();

    if(HashTable->find_element(*image1)== true) {
        std::cout << "found" << std::endl;
    }

    HashTable->print();

    if(HashTable->delete_element(*image1)== true) {
        std::cout << "deleted" << std::endl;
    }

    HashTable->print();
}
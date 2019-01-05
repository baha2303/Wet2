#include <stdio.h>
#include <new>
#include "HashTable.h"
#include "Image.h"
#include "library.h"


int main () {
    Image *image1 = new Image(10,10);
    image1->imageId=1;

    Image *image2 = new Image(10,10);
    image2->imageId=2;

    Image *image3 = new Image(10,10);
    image3->imageId=3;

    Image *image4 = new Image(10,10);
    image4->imageId=4;

    Image *image5 = new Image(10,10);
    image5->imageId=5;

    Image *image6 = new Image(10,10);
    image6->imageId=6;

    Image *image7 = new Image(10,10);
    image7->imageId=7;



}
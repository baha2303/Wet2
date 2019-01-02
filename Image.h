//
// Created by baha2 on 04-Dec-18.
//

#ifndef HW2_LIBRARY_IMAGE_H
#define HW2_LIBRARY_IMAGE_H

#include "TreeClass.h"
#include "Tree.h"
#include <iostream>
#include <new>
#include "Pixel.h"


class Image {
    Pixel** pixelArr;
    int pixels;
    static void setRouteParent(Pixel* pixel,Pixel* superPixel) {
        Pixel* currPixel;
        while (pixel->parent) {//this while changes the parent in the route from the pixel to the root of the up tree
            currPixel = pixel->parent;
            pixel->parent = superPixel;
            pixel = currPixel;
        }
    }
public:
    int imageId;
    explicit  Image(int id,int pixels):imageId(id),pixels(pixels) {
        pixelArr = new Pixel*[pixels];
        for(int i=0;i<pixels;i++) {
            pixelArr[i] = new Pixel();
        }
    }
    void destroy(){
        for(int i=0;i<pixels;i++){
            pixelArr[i]->destroy();
            delete pixelArr[i];
        }
        delete [] pixelArr;
    }
    void setLabelScore(int index,int label, int score){
        Pixel* pixel = pixelArr[index];
        Pixel* superPixel =pixel->getSuper();
        setRouteParent(pixel,superPixel);
        Add_Tree(superPixel->labelsTree,label,&score);//adding the label and score to the super pixel
    }
    StatusType resetLabelScore(int index,int label){
        Pixel* pixel = pixelArr[index];
        Pixel* superPixel =pixel->getSuper();
        setRouteParent(pixel,superPixel);
        int* score;
        if(Find_Tree(superPixel->labelsTree,label,(void**)&score)==FAILURE){
            return FAILURE;
        }
        else {
            *score = 0;
        }
    }
    void getHighestLabel(int index,int *label){
        Pixel* superPixel = pixelArr[index]->getSuper();

    }
    void mergeSets(int index1, int index2){
        Pixel* dest,*source;

        Pixel* pixel1=pixelArr[index1];
        Pixel* superPixel1 = pixel1->getSuper();
        setRouteParent(pixel1,superPixel1);

        Pixel* pixel2=pixelArr[index2];
        Pixel* superPixel2 = pixel2->getSuper();
        setRouteParent(pixel2,superPixel2);

        if(superPixel1->size >= superPixel2->size){
            dest=superPixel1;
            source=superPixel2;
        }
        else{
            dest=superPixel2;
            source=superPixel1;
        }
        source->parent=dest;
        dest->size+=source->size;
        mergeTrees(dest->labelsTree,dest->size,source->labelsTree,source->size);

    }




};

#endif //HW2_LIBRARY_IMAGE_H

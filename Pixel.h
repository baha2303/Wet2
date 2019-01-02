//
// Created by muhan on 12/31/2018.
//

#ifndef IMAGESPROGRAM_PIXEL_H
#define IMAGESPROGRAM_PIXEL_H

#include "TreeClass.h"
#include"Tree.h"
#include "ScoresValue.h"
class Pixel{
public:
   // int Id; not important if the ids are from 0 to pixels-1
    int size;
    Tree<int>* labelsTree;
    Pixel* parent;
    Pixel():size(1),parent(nullptr) {
        labelsTree = (Tree<int> *) Init_Tree();
    }
    Pixel* getSuper(){
        Pixel* pixel = this;
        while(pixel->parent){
            pixel=pixel->parent;
        }
        return pixel;
    }
    void destroy(){
        Quit_Tree((void**)&labelsTree);

    }
};
#endif //IMAGESPROGRAM_PIXEL_H

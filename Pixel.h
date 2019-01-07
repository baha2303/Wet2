//
// Created by muhan on 12/31/2018.
//

#ifndef IMAGESPROGRAM_PIXEL_H
#define IMAGESPROGRAM_PIXEL_H

#include "TreeClass.h"
#include"Tree.h"
class Pixel{
public:
    int treeSize;
    int maxScore;
    int maxLabel;
    int size;
    Tree<int>* labelsTree;
    Pixel* parent;
    Pixel():treeSize(0),maxScore(0),maxLabel(-1),size(1),parent(nullptr) {
        labelsTree = (Tree<int> *) Init_Tree();
    }

    ~Pixel() {
        if(labelsTree != nullptr )
        Quit_Tree((void**)&labelsTree);
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

    Tree<int>* getRoot () {
        return labelsTree->getLeft();
    }

};
#endif //IMAGESPROGRAM_PIXEL_H

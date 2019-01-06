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
#include <assert.h>

class Image {
    Pixel** pixelArr;
    int pixels;


public:
    int imageId;
    explicit  Image(int id,int pixels):imageId(id),pixels(pixels) {
        pixelArr = new Pixel*[pixels];
        for(int i=0;i<pixels;i++) {
            pixelArr[i] = new Pixel();//pixel
        }
    }

    void destroy(){
        for(int i=0;i<pixels;i++){
            pixelArr[i]->destroy();
            delete pixelArr[i];
        }
        delete [] pixelArr;
    }


    static void setRouteParent(Pixel* pixel,Pixel* superPixel) {
        Pixel* currPixel;
        while (pixel->parent) {//this while changes the parent in the route from the pixel to the root of the up tree
            currPixel = pixel->parent;
            pixel->parent = superPixel;
            pixel = currPixel;
        }
    }




////////////////////////////functions for merging to trees into one AVL tree !!
//receives the real root//receives index 0
    void treeToArray(Tree<int>* tree,Tree<int>* array[],int* index){
        assert(array);
        if(!tree){
            return ;
        }
        treeToArray(tree->getLeft(),array,index);
        array[(*index)++]=tree;
        treeToArray(tree->getRight(),array,index);
    }

    Tree<int>* arrayToTreeAux(Tree<int>* array[],int left,int right,Tree<int>* father){
        if(left==right){
            Tree<int>* subTree = array[left];
            subTree->setLeft(nullptr);
            subTree->setRight(nullptr);
            subTree->setFather(father);
            return subTree;
        }
        int mid=(left+right)/2;

        Tree<int>* root = array[mid];
        root->setFather(father);
        if(mid!=left) {
            root->setLeft(arrayToTreeAux(array, left, mid - 1, root));
        }
        else {
            root->setLeft(nullptr);
        }
        if(mid!=right) {
            root->setRight(arrayToTreeAux(array, mid + 1, right, root));
        }
        else {
            root->setRight(nullptr);
        }
        return root;
    }
    Tree<int>* arrayToTree(Tree<int> * array[],int size){


        Tree<int>* head=(Tree<int>*) Init_Tree();
        if(size>0) {
            head->setLeft(arrayToTreeAux(array, 0, size - 1, head));
        }
        return head;
    }
//dest should be sized m+n;
    int mergeArrays(Tree<int>* a[],int na,Tree<int> *b[],int nb,Tree<int>* dest[]){
        int mergedArraySize=na+nb;
        int ia=0,ib=0,ic;
        for (ic=0; ic<na+nb;) {
            if (ia<na && ib<nb) {
                if (a[ia]->getKey() < b[ib]->getKey()) {
                    dest[ic]=new Tree<int>(a[ia]->getKey(), nullptr, nullptr);
                    dest[ic]->score=a[ia]->score;
                    ia++;
                }
                else if(a[ia]->getKey() > b[ib]->getKey()){
                    dest[ic]=new Tree<int>(b[ib]->getKey(), nullptr, nullptr);
                    dest[ic]->score=b[ib]->score;
                    ib++;

                }

                    //////////////////////////////////////////////////////
                else{//reaching here means the two labels are equal
                    dest[ic]=new Tree<int>(a[ia]->getKey(), nullptr, nullptr);

                    dest[ic]->score=a[ia]->score+b[ib]->score;
                    ia++;
                    ib++;
                }
                //////////////////////////////////////////////////////
                ic++;
            }
            else if (ia == na) {
                for (; ib < nb ;ic++,ib++) {
                    dest[ic]=new Tree<int>(b[ib]->getKey(), nullptr, nullptr);
                    dest[ic]->score=b[ib]->score;
                }
            }
            else {
                for (; ia< na ;ic++,ia++) {
                    dest[ic]=new Tree<int>(a[ia]->getKey(), nullptr, nullptr);
                    dest[ic]->score=a[ia]->score;
                }
            }
        }

        return ic;
    }
//this function receives the real roots
    Tree<int>* mergeTrees(Tree<int>* tree1,int size1,Tree<int>* tree2,int size2,int* returnsize){
        Tree<int>** array1=new Tree<int>*[size1];
        Tree<int>** array2=new Tree<int>*[size2];
        Tree<int>** mergedArr=new Tree<int>*[size1+size2];
        int index=0;
        treeToArray(tree1,array1,&index);
        index=0;
        treeToArray(tree2,array2,&index);
        *returnsize=mergeArrays(array1,size1,array2,size2,mergedArr);
        Tree<int>* mergedTree = arrayToTree(mergedArr,*returnsize);
        updateAllMaxScores(mergedTree->getLeft());
        updateAllHeights(mergedTree);
        delete [] array1;
        delete [] array2;
        delete [] mergedArr;
        return mergedTree;
    }




    /////////////////////////////required methods for the exercise !!

    StatusType setLabelScore(int index,int label, int score){
        Pixel* pixel = pixelArr[index];
        Pixel* superPixel =pixel->getSuper();
        setRouteParent(pixel,superPixel);
        if(UpdateScore(superPixel->labelsTree,label,score,superPixel->getRoot())) {
            superPixel->maxLabel=UpdateMaxLabel(superPixel->getRoot());
            return SUCCESS;
        }
        void *node;
        if(Add_Tree(superPixel->labelsTree,label,nullptr,score,&node)!=SUCCESS) //adding the label and score to the super pixel
            return FAILURE;
        superPixel->treeSize++;
        updateTillRoot(node,superPixel->getRoot());
        superPixel->maxLabel=UpdateMaxLabel(superPixel->getRoot());
        return SUCCESS;
    }



    StatusType resetLabelScore(int index,int label){
        Pixel* pixel = pixelArr[index];
        Pixel* superPixel =pixel->getSuper();
        setRouteParent(pixel,superPixel);
        if(Delete_Tree(superPixel->labelsTree,label)!=SUCCESS) return FAILURE;
        superPixel->maxLabel=UpdateMaxLabel(superPixel->getRoot());
        superPixel->treeSize--;
        return SUCCESS;
    }



    StatusType getHighestLabel(int index,int *label){
        Pixel* superPixel = pixelArr[index]->getSuper();
        if(superPixel->treeSize==0) return FAILURE;
        *label=superPixel->maxLabel;
        return SUCCESS;
    }



    StatusType mergeSets(int index1, int index2){
        Pixel *dest,*source;

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
        if(source->treeSize==0 ) {
            Quit_Tree((void**)&(source->labelsTree));
            return SUCCESS;
        }
        if(dest->treeSize==0 ) {
            Quit_Tree((void**)&(dest->labelsTree));
            dest->labelsTree=source->labelsTree;
            dest->treeSize=source->treeSize;
            return SUCCESS;
        }
        Tree<int>* newTree=mergeTrees(dest->getRoot(),dest->treeSize,source->getRoot(),source->treeSize,&(dest->treeSize));
        dest->labelsTree=newTree;
        UpdateMaxLabel(dest->getRoot());
        Quit_Tree((void**)&(source->labelsTree));
        Quit_Tree((void**)&(dest->labelsTree));


    }





    void Quit() {
        for(int i=0 ; i<pixels ; i++) {
            pixelArr[i]->destroy();
            delete( pixelArr[i]);
        }
        delete[](pixelArr);
    }



    void updateAllMaxScores(Tree<int>* node){
        if(!node){
            return;
        }
        updateAllMaxScores(node->getLeft());
        updateAllMaxScores(node->getRight());
        updateMax(node);

    }

    void updateAllHeights(Tree<int>* node){
        if(!node){
            return;
        }
        updateAllHeights(node->getLeft());
        updateAllHeights(node->getRight());
        node->setHeight(max(node->getLeft()->getHeight(),node->getRight()->getHeight())+1);
    }

};










#endif //HW2_LIBRARY_IMAGE_H



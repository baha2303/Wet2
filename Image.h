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


    static void setRouteParent(Pixel* pixel,Pixel* superPixel) {
        Pixel* currPixel;
        while (pixel->parent) {//this while changes the parent in the route from the pixel to the root of the up tree
            currPixel = pixel->parent;
            pixel->parent = superPixel;
            pixel = currPixel;
        }
    }




/////////////////////////////functions for merging to trees into one AVL tree !!
    void treeToArray(Tree<int>* tree,int* array){
        assert(array);
        if(!tree){
            return;
        }
        treeToArray(tree->getLeft(),array);
        array[tree->index]=tree->getKey();
        tree->index++;
        treeToArray(tree->getRight(),array);
    }

    Tree<int>* arrayToTreeAux(int * array,int left,int right,Tree<int>* father){
        if(left==right){
            Tree<int>* subTree = new Tree<int>(array[left], , father);
        }
        int mid=(left+right)/2;
        Tree<int>* root = new Tree<int>(array[mid], , father);
        root->setLeft(arrayToTreeAux(array,left,mid,root));
        root->setLeft(arrayToTreeAux(array,mid+1,right,root));
    }
    Tree<int>* arrayToTree(int * array,int size){
        Tree<int>* tree=(Tree<int>*) Init_Tree();
        tree->setLeft(arrayToTreeAux(array,0,size-1,tree));
        return tree;
    }
//dest should be sized m+n;
    void mergeArrays(int *a,int na,int* b,int nb,int* dest){
        int ia=0,ib=0,ic;
        for (ic=0; ic<na+nb;) {
            if (ia<na && ib<nb) {
                if (a[ia] < b[ib]) {
                    dest[ic] = a[ia++];
                }
                else {
                    dest[ic] = b[ib++];

                }
                i++;
            }
            else if (ia == na) {
                for (; ic < na + nb;) {
                    dest[ic++] = b[ib++];
                }
            }
            else {
                for (; ic < na + nb;) {
                    dest[ic++] = a[ia++];
                }
            }
        }
    }

    Tree<int>* mergeTrees(Tree<int>* tree1,int size1,Tree<int>* tree2,int size2){
        int* array1=new int[size1];
        int* array2=new int[size2];
        int* mergedArr=new int[size1+size2];
        treeToArray(tree1,array1);
        treeToArray(tree2,array2);
        mergeArrays(array1,size1,array2,size2,mergedArr);
        Tree<int>* mergedTree = arrayToTree(mergedArr,size1+size2);
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
           /////////////////////need to update max label after correction was made!!
            return SUCCESS;
        }
        void *node;
        if(Add_Tree(superPixel->labelsTree,label,nullptr,score,&node)!=SUCCESS) //adding the label and score to the super pixel
            return FAILURE;
        superPixel->treeSize++;
        updateTillRoot(node,superPixel->getRoot());
/////////////////////need to update max label after correction was made!!
///////////////////////////////////////update maxLabel and maxScore for superPixel !!
        return SUCCESS;
    }



    StatusType resetLabelScore(int index,int label){
        Pixel* pixel = pixelArr[index];
        Pixel* superPixel =pixel->getSuper();
        setRouteParent(pixel,superPixel);
        if(Delete_Tree(superPixel->labelsTree,label)!=SUCCESS) return FAILURE;
////////////////////////////////////////neeeds Fix after deleting label from tree and need to
///////////////////////////////////////update maxLabel and maxScore for superPixel !!

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
        dest->getRoot()->index=0;
        source->getRoot()->index=0;
        Tree<int>* newTree=mergeTrees(dest->getRoot(),dest->size,source->getRoot(),source->size);
        Quit_Tree((void**)&source->labelsTree);
        Quit_Tree((void**)&dest->labelsTree);
        dest->labelsTree=newTree;
        updateAllMaxScores(dest->getRoot());
        //////////////////////////////////////////////////////////////not done need to fix max !!
        ///////// update Max label and max SCore
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

};



#endif //HW2_LIBRARY_IMAGE_H



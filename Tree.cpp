#include "TreeClass.h"
#include "Tree.h"
#include <cstdbool>
#include <cassert>
#include  <new>
#include <iostream>
using std::cout;

//static void AVL_Fix(int BF_father, int BF_son, Tree<int> *p, Tree<int> *v) {
static int AVL_Fix(int BF_father, Tree<int> *p) {
    assert(p->getKey()>=0 &&p->getKey()<=11110);
    int BF_leftSon;
    int BF_rightSon;
    if(p->getRight()){
        BF_rightSon=p->getRight()->getLeft()->getHeight()-p->getRight()->getRight()->getHeight();
    }
    if(p->getLeft()){
        BF_leftSon=p->getLeft()->getLeft()->getHeight()-p->getLeft()->getRight()->getHeight();
    }
    //LL Rotation
    if (BF_father == 2 && BF_leftSon >= 0 && (p->getLeft())) {
        Tree<int>* v =p->getLeft();
        p->setLeft(v->getRight());
        if(v->getRight()) {
            v->getRight()->setFather(p);
        }
        v->setRight(p);
        v->setFather(p->getFather());
        if (p->getFather()->getRight() == p) {
            p->getFather()->setRight(v);
        } else {
            p->getFather()->setLeft(v);
        }
        p->setFather(v);
        p->setHeight(max(p->getLeft()->getHeight(),p->getRight()->getHeight())+1);
        v->setHeight(max(v->getLeft()->getHeight(),v->getRight()->getHeight())+1);
        return v->getHeight();//returning the height of the tat tree
    }
//LR Rotation
    if (BF_father == 2 && BF_leftSon == -1 && (p->getLeft())) {
        Tree<int>* v =p->getLeft();
        Tree<int> *B = v->getRight();
        p->setLeft(B->getRight());
        if(B->getRight()){
            B->getRight()->setFather(p);
        }
        v->setRight(B->getLeft());
        if(B->getLeft()){
            B->getLeft()->setFather(v);
        }
        B->setRight(p);
        B->setLeft(v);
        v->setFather(B);
        B->setFather(p->getFather());
        if (p->getFather()->getRight() == p) {//connecting the father of c to b
            p->getFather()->setRight(B);
        } else {
            p->getFather()->setLeft(B);
        }
        p->setFather(B);
        p->setHeight(max(p->getLeft()->getHeight(),p->getRight()->getHeight())+1);
        v->setHeight(max(v->getLeft()->getHeight(),v->getRight()->getHeight())+1);
        B->setHeight(max(p->getHeight(),v->getHeight())+1);
        return B->getHeight();
    }
    //RR Rotation
    if (BF_father == -2 && BF_rightSon <= 0 && (p->getRight())) {
        Tree<int> *v = p->getRight();
        p->setRight(v->getLeft());
        if (v->getLeft()) {
            v->getLeft()->setFather(p);
        }
        v->setLeft(p);
        v->setFather(p->getFather());
        if (p->getFather()->getRight() == p) {
            p->getFather()->setRight(v);
        } else {
            p->getFather()->setLeft(v);
        }
        p->setFather(v);
        p->setHeight(max(p->getLeft()->getHeight(), p->getRight()->getHeight()) + 1);
        v->setHeight(max(v->getLeft()->getHeight(), v->getRight()->getHeight()) + 1);
        return v->getHeight();//returning the height of the tat tree
    }
    //RL Rotation
    if (BF_father == -2 && BF_rightSon == 1 && (p->getRight())) {
        Tree<int>* v =p->getRight();
        Tree<int> *B = v->getLeft();
        p->setRight(B->getLeft());
        if(B->getLeft()){
            B->getLeft()->setFather(p);
        }
        v->setLeft(B->getRight());
        if(B->getRight()){
            B->getRight()->setFather(v);
        }
        B->setRight(v);
        B->setLeft(p);
        v->setFather(B);
        B->setFather(p->getFather());
        if (p->getFather()->getRight() == p) {//connecting the father of c to b
            p->getFather()->setRight(B);
        } else {
            p->getFather()->setLeft(B);
        }
        p->setFather(B);
        p->setHeight(max(p->getLeft()->getHeight(),p->getRight()->getHeight())+1);
        v->setHeight(max(v->getLeft()->getHeight(),v->getRight()->getHeight())+1);
        B->setHeight(max(p->getHeight(),v->getHeight())+1);
        return B->getHeight();
    }
    return -1;
}

/*sortTree() receives the real root not the dummy, and the added vertice.
it iterates over the route from the added vertice to the root and looks for
vertices with a |BF|=2 and fixes them using AVL_Fix
*/
template <class  T>
static void sortTree(Tree<T> *root, Tree<T> *v) {
    assert(v && root);//to// make sure non of them is null
    if (v == root) {
        return;
    }
    Tree<T> *p = v->getFather();
    if ((p->getHeight()) >= (v->getHeight() + 1)) {
        return;
    }
    p->setHeight(v->getHeight() + 1);
    int BF_father = p->getLeft()->getHeight() - p->getRight()->getHeight();
    //int BF_son = v->getLeft()->getHeight() - v->getRight()->getHeight();
    if (BF_father >= 2 || BF_father <= -2) {
        AVL_Fix(BF_father ,p);
        return;
    }
    sortTree<T>(root,p);

}
template<class T>
static void sortTreeDel(Tree<T>* root, Tree<T>* v){
    assert(v&&root );//to make sure non of them is null
    if (v == root) {
        return;
    }
    Tree<T>* p=v->getFather();
    // Tree<T>* brother=nullptr;
    int oldHeight=v->getHeight();
    v->setHeight(max(v->getLeft()->getHeight(),v->getRight()->getHeight())+1);
    int newHeight=v->getHeight();
    int BF=v->getLeft()->getHeight()-v->getRight()->getHeight();
    //if(p->getRight()==v){
    //    brother=p->getLeft();
    // }
    //else{
    //   brother=p->getRight();
    //}
    //assert(brother);
    if(BF>=2||BF<=-2){
        //int BF_son=son->getLeft()->getHeight()-son->getRight()->getHeight();
        newHeight = AVL_Fix(BF,v);
        //assert(brother);
    }
    //cout << "*******************8888888888******************"<<std::endl;
    // my_test(root->getFather(),8251);
    // cout << "*******************8888888888******************"<<std::endl;
    if(oldHeight==newHeight){
        return;
    }
    sortTreeDel(root,p);
}


//it receives nodes which have no sons or only one son
//this function does delete node;
static void remove_node(Tree<int>* root, Tree<int>* node){
    Tree<int>* nodePa = node->getFather();//what if the node is the root what should we do????????????????????????????????????????????????
    bool leftSon = true;// the node we want to delete :leftSon = true if it is a left son : false if it is a right son
    // Tree<int>* brother = nodePa->getRight();
    if (nodePa->getRight() == node) {
        leftSon=false;//the node we want to delete is a right son
        //    brother = nodePa->getLeft();
    }
    if(node->getLeft()){
        //make the gradnpa point to the left son depending on leftSon
        if(leftSon){
            nodePa->setLeft(node->getLeft());
        }else{
            nodePa->setRight(node->getLeft());
        }
        node->getLeft()->setFather(nodePa);
    }
    else{//if he has only one right son or no sons
        //make the grandpa point to the right son
        if(leftSon){
            nodePa->setLeft(node->getRight());
        }else{
            nodePa->setRight(node->getRight());
        }
        if(node->getRight()){
            node->getRight()->setFather(nodePa);
        }
    }
    if(node!=root) {
        sortTreeDel<int>(root,nodePa);
    }
    //nodePa->setHeight(max(node->getHeight()-1,nodePa->getRight()->getHeight())+1);
    //int nodepahhegiht=nodePa->getHeight();
    delete node;
}
//helper function for delete
//we dont need the root as input bas lal manzar,it swaps a node we want to delete with the next one in order
static void swap_node(void *DS,Tree<int>* node){
    Tree<int>* nodePa = node->getFather();
    bool leftSon = true;
    if (nodePa->getRight() == node) {
        leftSon=false;
    }
    Tree<int>* rightSon = node->getRight();
    assert(rightSon);//because there should be a right and left sons to do swap
    Tree<int>* nextNode = rightSon;
    while(nextNode->getLeft()){
        nextNode=nextNode->getLeft();
    }
    Tree<int>* nextNodePa = nextNode->getFather();
    //reaching here means that the nextNode is the next node after node inorderly
    nextNode->setLeft(node->getLeft());
    assert(node->getLeft());//because there should be a right and left sons to do swap
    node->getLeft()->setFather(nextNode);
    node->setRight(nextNode->getRight());
    if(nextNode->getRight()){
        nextNode->getRight()->setFather(node);
    }
    nextNode->setRight(rightSon);
    rightSon->setFather(nextNode);
    node->setLeft(nullptr);
    node->setFather(nextNodePa);
    if(nextNode==rightSon){
        nextNode->setRight(node);
        node->setFather(nextNode);
    }
    if(nextNode!=rightSon){
        nextNodePa->setLeft(node);
    }
    nextNode->setFather(nodePa);
    if(leftSon){
        nodePa->setLeft(nextNode);
    }
    else{
        nodePa->setRight(nextNode);
    }
    nextNode->setHeight(node->getHeight());//changing height of the node I put in the place of the node that I want to delete
}

/*
this function is made for the find and delete function it gets receives the data structure and a key
it looks for the node in the tree the has the same key
return value :
*a pointer to the node.( if it found one )
*NULL. ( if it didn't find one )
NOTE: it can't be used for the function ((Add)) because it looks for an existing node
*/
static Tree<int>* Find_Helper(void *DS, int key){
    auto curr = static_cast<Tree<int> *>(DS);
    curr = curr->getLeft();
    int currKey;
    while (curr) {
        currKey = curr->getKey();
        if (key == currKey) {
            return curr;
        }
        if (key < currKey) {
            curr = curr->getLeft();
        } else {
            curr = curr->getRight();
        }
    }
    return nullptr;
}
static void QuitAux(Tree<int> *head) {
    if (head == nullptr) return;
    if (head->getLeft()) { QuitAux(head->getLeft()); }
    if (head->getRight()) { QuitAux(head->getRight()); }
    delete head;
}




void *Init_Tree() {
    try {
        Tree<int> *DS = new Tree<int>(12321, nullptr, nullptr);
        DS->setRight(nullptr);
        DS->size = 0;
        return (void*)DS;
    }
    catch (std::bad_alloc& ba) {
        return nullptr;
    }
}

StatusType Add_Tree(void *DS, int key, void *value, int score) {
    if (!DS ) {
        return INVALID_INPUT;
    }
    auto head = static_cast<Tree<int> *>(DS);//head is the dummy
    try {
        Tree<int> *newTree = new Tree<int>(key, value, nullptr);//making a new node.
        newTree->score=score;
        newTree->maxScore=score;
        if (head->size == 0) {//if the tree is empty
            newTree->setFather(head);
            head->setLeft(newTree);
            (head->size)++;

            return SUCCESS;
        }

        Tree<int> *curr = head->getLeft();//curr starts from the real root
        int currKey;

        while (curr) {
            currKey=curr->getKey();
            if (key < currKey && (curr->getLeft() == nullptr)) {
                newTree->setFather(curr);
                curr->setLeft(newTree);
                break;
            } else if (key > currKey && (curr->getRight() == nullptr)) {
                newTree->setFather(curr);
                curr->setRight(newTree);
                break;
            } else if (key < currKey) {
                curr = curr->getLeft();
            } else if (key > currKey) {
                curr = curr->getRight();
            }
        }


        (head->size)++;//root here is the dummy
        sortTree<int>(head->getLeft(), newTree);//sortTree: insert algorithm fix
    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType Find_Tree(void *DS, int key, void **value) {
    if (!value || !DS) {
        return INVALID_INPUT;
    }
    Tree<int>* node = Find_Helper( DS , key );
    if(!node){
        return FAILURE;//because the key wasn't found
    }
    else{
        *value = node->getValue();
        return SUCCESS;
    }
}
bool UpdateScore(void *DS, int key, int score) {
    if (!DS) {
        return false;
    }
    Tree<int>* node = Find_Helper( DS , key );
    if(!node){
        return false;//because the key wasn't found
    }
    else{
        node->score=score;
        node->maxScore=score;
        return SUCCESS;
    }
}



StatusType Delete_Tree(void *DS, int key){
    if(!DS){
        return INVALID_INPUT;
    }
/*	if(key==8251){
	    PrintTree(DS);
	    cout << "";
    }*/
    Tree<int>* node = Find_Helper( DS , key );
    if(!node){
        return FAILURE;//because the key wasn't found
    }
    DeleteByPointer_Tree(DS,node);
    //my_test(DS,key);
    return SUCCESS;
}

StatusType DeleteByPointer_Tree(void *DS, void* node_del){
    if(!DS||!node_del){
        return INVALID_INPUT;
    }
    auto node = static_cast<Tree<int> *>(node_del);
    if(node->getLeft() && node->getRight()){//if he has two sons
        swap_node(DS,node);
    }
    auto head = static_cast<Tree<int> *>(DS);
    remove_node(head->getLeft(),node);//this function deallocates the node and sorts the tree
    head->size--;
    return SUCCESS;
}

StatusType Size_Tree(void *DS, int *n) {
    if (!DS || !n) {
        return INVALID_INPUT;
    }
    auto head = static_cast<Tree<int> *>(DS);
    *n = head->size;
    return SUCCESS;
}

void Quit_Tree(void **DS) {
    auto head = static_cast<Tree<int> *>(*DS);
    QuitAux(head);
    *DS = nullptr;

}


void maxLabelFix(Tree<int> *head) {

        if (head == nullptr) return;
        if (head->getLeft()) { QuitAux(head->getLeft()); }
        if (head->getRight()) { QuitAux(head->getRight()); }
        head->
    }


}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
}
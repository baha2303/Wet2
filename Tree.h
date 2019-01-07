
#ifndef _234218_WET1_DICT
#define _234218_WET1_DICT

#ifdef __cplusplus
extern "C" {
#endif

/* Return Values
 * ----------------------------------- */

#include "library.h"

/* Required Interface for the Data Structure
 * -----------------------------------------*/

/* Description:   Initiates the data structure.
 * Input:         None.
 * Output:        DS - A pointer to the data structure.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void *Init_Tree();

/* Description:   Adds a new item to the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The key to add.
 *                value - A pointer to the value to add.
 				  node - A pointer to a place which will hold a pointer to the new node in the DS.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item is already in the DS.
 *                SUCCESS - Otherwise.
 */
//StatusType Add_Tree(void *DS, int key, void* value, void** node);
StatusType Add_Tree(void *DS, int key, void* value,int score,void **node);

/* Description:   Finds an item in the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to find.
 * Output:        value - a pointer to a variable which will contain the value of the element.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - If the item is found in the DS.
 */
StatusType Find_Tree(void *DS, int key, void** value);



/* Description:   Delete an item from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                key - The item to delete.
 * Output:        None.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - Otherwise.
 */




StatusType Delete_Tree(void *DS, int key);

/* Description:   Delete an item from the data structure.
 * Input:         DS - A pointer to the data structure.
 *                p - A pointer to the node to delete.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                FAILURE - If the item does not exist in the DS.
 *                SUCCESS - Otherwise.
 */
StatusType DeleteByPointer_Tree(void *DS, void* p);

/* Description:   Returns the current number of items in the data structure.
 * Input:         DS - A pointer to the data structure.
 * Output:        n - A pointer to a variable that should be updated to the number of items in the data structure.
 * Return Values: ALLOCATION_ERROR - In case of an allocation error.
 *                INVALID_INPUT - If DS==NULL.
 *                SUCCESS - Otherwise.
 */
StatusType Size_Tree(void *DS, int *n);

/* Description:   Quits and deletes the database.
 *                DS should be set to NULL.
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void Quit_Tree(void** DS);

//functions for merging two AVL Trees. in O(N) time .


/*
void* mergeTrees(void* tree1,int size1,void* tree2,int size2);

//merge sort
void mergeArrays(int *a,int na,int* b,int nb,int* dest);


//imlementing an AVL Tree from a sorted array , such that every element in the
// array is a key for the tree node . this algorithm starts with the root and recursively
// sets it's sons thus taking O(n) time.

void* arrayToTree(int * array,int size);



void* arrayToTreeAux(int * array,int left,int right,void* father);


//copying a tree to array
void treeToArray(void* tree,int* array);
*/



void updateTillRoot(void *node,void *root);

bool UpdateScore(void *DS, int key, int score,void* root);

void updateMax (void *node1);

int UpdateMaxLabel (void* root_);

int max_int(int a, int b);

#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET1_ */

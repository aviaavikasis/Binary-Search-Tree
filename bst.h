/*****************************************************   
 * Author : Avia Avikasis                            *
 * Reviewer: Eitan                                   *
 * 15/07/2022                                        *
 * Description : imlementation of binary search tree *
 *                                                   *
 *****************************************************/
 
#ifndef __ILRD_OL127_128_BST_H__
#define __ILRD_OL127_128_BST_H__

#include <stddef.h> /* size_t */


typedef struct node node_ty;
typedef struct bst bst_ty;
typedef struct node *bst_iterator_ty;

typedef int(*cmp_func)(const void *bst_data, const void *user_data, void *params);
typedef int(*action_func)(void *data, void *params);

/*
DESCRIPTION : create new binary search tree(bst).
PARAMETERS : compare function , for compare between two elements
in the tree , Based on their size , void pointer tp params for
the compare function.
RETURN : pointer to new bst in success , and NULL otherwise
COMPLEXITY : time - O(1) , space - O(1)  
*/
bst_ty *BstCreate(cmp_func cmp, void *params);

/*
DESCRIPTION : free exist bst.
PARAMETERS : pointer to bst
RETURN : void
COMPLEXITY : time - O(n) , space - O(1)    
*/
void BstDestroy(bst_ty *bst);

/*
DESCRIPTION : insert new element to bst.
PARAMETERS : pointer to bst , void pointer to data
RETURN : pointer to the new element
COMPLEXITY : time - O(log(n)) , space - O(1)  
*/
bst_iterator_ty BstInsert(bst_ty *bst, void *data);

/*
DESCRIPTION : remove element from bst.
PARAMETERS : pointer to element in bst
RETURN : pointer to the element that located above in tree
COMPLEXITY : time - O(log(n)) , space - O(1)  
*/
void *BstRemove(bst_iterator_ty position);

/*
DESCRIPTION : find element in bst.
PARAMETERS : pointer to bst and void pointer to the data to find
RETURN : pointer to the element that find , if it's find,
otherwise - undefined.
COMPLEXITY : time - O(log(n)) , space - O(1)  
*/
bst_iterator_ty BstFind(const bst_ty *bst, void *data);

/*
DESCRIPTION : find the min element in bst.
PARAMETERS : pointer to bst
RETURN : pointer to the min element , in case that the 
tree in empty - the function will return null.
COMPLEXITY : time - O(log(n)) = O(h) , space - O(1)  
*/
bst_iterator_ty BstBegin(const bst_ty *bst);

/*
DESCRIPTION : find the end of bst.
PARAMETERS : pointer to bst.
RETURN : pointer to the element that come after
the max element in the tree.
UNDEFINED : Using the returned value will cause
undefined behavior
COMPLEXITY : time - O(1) , space - O(1)  
*/
bst_iterator_ty BstEnd(const bst_ty *bst);

/*
DESCRIPTION : get pointer to elemnt in bst
and return the element that small from it.
PARAMETERS : iterator to element in bst.
RETURN : iterator to the element that come before
the get element.
UNDEFINED : send to function iterator to 
the begin of the tree.
COMPLEXITY : time - O(log(n)) , space - O(1)  
*/
bst_iterator_ty BstGetPrev(bst_iterator_ty iterator);

/*
DESCRIPTION : get pointer to elemnt in bst
and return the element that big from it.
PARAMETERS : iterator to element in bst.
RETURN : iterator to the element that come after
the get element.
UNDEFINED : send to function iterator to 
the max element of the tree (=before the end).
COMPLEXITY : time - O(log(n)) , space - O(1)  
*/
bst_iterator_ty BstGetNext(bst_iterator_ty iterator);

/*
DESCRIPTION : return pointer to data of elemnt in bst
PARAMETERS : iterator to element in bst.
COMPLEXITY : time - O(1) , space - O(1)  
*/
void *BstGetData(bst_iterator_ty iterator);

/*
DESCRIPTION : return the num of elements in bst
PARAMETERS : pointer to bst.
RETURN : the num elements(size_t). if the bst is
empty , the return will be 0.
COMPLEXITY : time - O(n) , space - O(1)  
*/	
size_t BstSize(const bst_ty *bst);

/*
DESCRIPTION : check if bst is empty
PARAMETERS : pointer to bst.
RETURN : 1 in true , 0 in false
COMPLEXITY : time - O(1) , space - O(1)  
*/	
int BstIsEmpty(const bst_ty *bst);

/*
DESCRIPTION : check if two iterator point to
same element
PARAMETERS : two iterators.
RETURN : 1 in true , 0 in false
COMPLEXITY : time - O(1) , space - O(1)  
*/	
int BstIterIsEqual(bst_iterator_ty iterator1, bst_iterator_ty iterator2);

/*
DESCRIPTION : active given operation function on
each element in bst , on given range.
PARAMETERS : iterator to start from it(from) , iterator
to end i it(to) , action function and params to action function.
RETURN : iterator to.
COMPLEXITY : time - O(n) , space - O(1)  
*/
int BstForEach(bst_iterator_ty from, bst_iterator_ty to, action_func action, void *params);

#endif /* __ILRD_OL127_128_BST_H__ */









#include <assert.h> /* assert */
#include <stdio.h>  /* printf */
#include "bst.h"

void BstCreateTest(void);
void BstInsertTest(void);
void BstRemoveTest(void);
void BstFindTest(void);
void BstBeginTest(void);
void BstEndTest(void);
void BstGetPrevTest(void);
void BstGetNextTest(void);
void BstSizeTest(void);
void BstForEachTest(void);

/* help function */
int CompareInts(const void *bst_data, const void *user_data, void *params);
int MultInts(void *data, void *params);



int main()
{
	BstCreateTest();
	BstInsertTest();
	BstRemoveTest();
	BstFindTest();
	BstBeginTest();
	BstEndTest();
	BstGetPrevTest();
	BstGetNextTest();
	BstSizeTest();
	/*BstForEachTest();*/
	printf("\n->->->->->-> success!! <-<-<-<-<-<-\n\n");	

	return 0;
}


void BstCreateTest(void)
{
	cmp_func cmp_function = &CompareInts;
	bst_ty *bst = BstCreate(cmp_function , NULL);
	BstDestroy(bst);
}

void BstInsertTest(void)
{
	int a = 3;
	int b = 4;
	cmp_func cmp_function = &CompareInts;
	bst_ty *bst = BstCreate(cmp_function , NULL);
	BstInsert(bst , &a);
	BstInsert(bst , &b);
	BstDestroy(bst);
}

void BstBeginTest(void)
{
	int i = 0;
	int arr[10] = {10,9,3,7,6,5,4,8,2,1};
	cmp_func cmp_function = &CompareInts;
	bst_ty *bst = BstCreate(cmp_function , NULL);
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
		
	assert(1 == *(int*)BstGetData(BstBegin(bst)));
	BstDestroy(bst);
	
}


void BstEndTest(void)
{
	int i = 0;
	int arr[10] = {10,9,3,7,6,5,4,8,2,1};
	cmp_func cmp_function = &CompareInts;
	bst_ty *bst = BstCreate(cmp_function , NULL);
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
		
	assert(10 == *(int*)BstGetData(BstGetPrev(BstEnd(bst))));
	BstDestroy(bst);

}


void BstGetNextTest(void)
{
	int i = 0;
	int arr[10] = {2,9,3,4,6,5,7,8,10,1};
	cmp_func cmp_function = &CompareInts;
	bst_iterator_ty iterator = NULL; 
	bst_ty *bst = BstCreate(cmp_function , NULL);
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
	
	iterator = BstBegin(bst);
	for(i = 1 ; i <= 10 ; ++i)
	{
		assert(i == *(int*)BstGetData(iterator));
		iterator = BstGetNext(iterator);	
	}
	
	BstDestroy(bst);

}

void BstGetPrevTest(void)
{

	int i = 0;
	int arr[10] = {10,9,3,7,6,5,4,8,2,1};
	cmp_func cmp_function = &CompareInts;
	bst_iterator_ty iterator = NULL; 
	bst_ty *bst = BstCreate(cmp_function , NULL);
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
		
	iterator = BstEnd(bst);
	iterator = BstGetPrev(iterator);
	assert(10 == *(int*)BstGetData(iterator));
	iterator = BstGetPrev(iterator);
	assert(9 == *(int*)BstGetData(iterator));
	BstDestroy(bst);

}

void BstSizeTest(void)
{

	int i = 0;
	int arr[10] = {10,9,3,7,6,5,4,8,2,1};
	cmp_func cmp_function = &CompareInts;
	bst_ty *bst = BstCreate(cmp_function , NULL);
	assert(0 == BstSize(bst));
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
	assert(10 == BstSize(bst));	
	
	BstDestroy(bst);

}


void BstForEachTest(void)
{
	
	int i = 0;
	int arr[10] = {10,9,3,7,6,5,4,8,2,1};
	cmp_func cmp_function = &CompareInts;
	action_func action_function = &MultInts;
	bst_iterator_ty from = NULL; 
	bst_iterator_ty to = NULL;
	bst_iterator_ty iterator = NULL;  
	
	bst_ty *bst = BstCreate(cmp_function , NULL);
	assert(0 == BstSize(bst));
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
	
	from = BstBegin(bst);
	to = BstEnd(bst);
	BstForEach(from , to , action_function , NULL);
	
	iterator = BstBegin(bst);
	
	for(i = 1 ; i <= 10 ; ++i)
	{
		assert(i * 2 == *(int*)BstGetData(iterator));
		iterator = BstGetNext(iterator);	
	}
	BstDestroy(bst);

}


void BstFindTest(void)
{

	int i = 0;
	int arr[10] = {10,9,3,7,6,5,4,8,2,1};
	cmp_func cmp_function = &CompareInts;
	int to_find = 3; 
	
	bst_ty *bst = BstCreate(cmp_function , NULL);
	assert(0 == BstSize(bst));
	for( ; i < 10 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
	
	assert(3 == *(int*)BstGetData(BstFind(bst , &to_find)));
	to_find = 10;
	assert(10 == *(int*)BstGetData(BstFind(bst , &to_find)));

	BstDestroy(bst);
}



void BstRemoveTest(void)
{

	int i = 0;
	int arr[20] = {10,9,14,7,6,16,4,8,12,1,11,2,13,3,15,5,17,18,19,20};
	cmp_func cmp_function = &CompareInts;
	bst_iterator_ty iterator = NULL; 
	int to_find = 11; 
	bst_ty *bst = BstCreate(cmp_function , NULL);
	
	for( ; i < 20 ; ++i)
	{
		BstInsert(bst , arr + i);
	}
	
	BstRemove(BstFind(bst , &to_find));
	iterator = BstBegin(bst);
	for(i = 0 ; i < 19 ; ++i)
	{
		assert(11 != *(int*)BstGetData(iterator));
		iterator = BstGetNext(iterator);	
	}
	
	BstDestroy(bst);
	
}


int CompareInts(const void *bst_data, const void *user_data, void *params)
{
	(void)params;
	assert(NULL != bst_data);
	assert(NULL != user_data);
	return (*(int*)bst_data - *(int*)user_data);
}


int MultInts(void *data, void *params)
{
	(void)params;
	assert(NULL != data);
	*(int*)data *= 2;
	return 0;
}












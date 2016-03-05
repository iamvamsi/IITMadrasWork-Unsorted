/*********************************************************************
*        TEAM :                                                       *
*        MADHAVI Y       CS09B025                                     *
*        VAMSI KRISHNA   CS09B006                                     *
*        UDAY CHOWHAN    CS09B034                                     *
*                                                                     *
*        ***IMPLEMANTATION OF A HEAP***                               *
*                                                                     *
**********************************************************************/
 



#ifndef HEAP_HEADER_H_
#define HEAP_HEADER_H_
#include<iostream>

using namespace std;
//HEADER FILE DESCRIBING THE DEFINITION OF CLASS HEAP
class heap
{
	int arr[20000];
	public:
	void reader(int *);
	int rchild(int);
	int lchild(int);
	int parent(int);
	int size();
	void swap(int, int);
	void min_heapify(int);
	void build_heap();
	void min_heap_insert(int);
	void heap_decrease_key(int,int);
	int heap_minimum();
	int extract_min();
	void copy(int*);
	void heap_sort();
	void heap_meld(heap);
	
};

#endif

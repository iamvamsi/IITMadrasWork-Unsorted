  /*********************************************************************
  *        TEAM :                                                       *
  *        MADHAVI Y       CS09B025                                     *
  *        VAMSI KRISHNA   CS09B006                                     *
  *        UDAY CHOWHAN    CS09B034                                     *
  *                                                                     *
  *        ***IMPLEMANTATION OF A LEFTIST HEAP***                       *
  *                                                                     *
  **********************************************************************/  


#include<iostream>
using namespace std;


//Node class
class lhnode
{
    public:
    int data;
    int s;
    lhnode *lchild,*rchild;
    lhnode()
    {
        data=0;
        s=0;
        lchild=NULL;
        rchild=NULL;
        
    }
    
};


//Leftist heap class
class left_heap
{
    lhnode *root;

    public :
    left_heap()
    {
        root=NULL;
    }
    left_heap(lhnode* A)
    {
        root=A;
    }
    lhnode* return_root()
    {
        return root;
    }
    void insert(int);
    int extract_min();
    void sort(int *);
};
    

        

        


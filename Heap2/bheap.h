
#include<iostream>

using namespace std;

class Node
{
public:
    int data,deg;
    Node *lsib,*rsib,*par,*child;
    Node(int x)
    {
        data=x;
        deg=0;
        rsib=NULL;
        lsib=NULL;
        par=NULL;
        child=NULL;

    }

};


class Nodeuni
{
        public:
        Node *curr,*prev,*next;
        Nodeuni()
        {
                curr=NULL;
                prev=NULL;
                next=NULL;
        }


};


class bheap
{
        Node *head;
public:
        bheap()
        {
                head=NULL;
        }
        bheap(Node* t)
        {
                head=t;
        }
        Node* return_head();
        void  assign(Node*);
        Node* heap_min();
        void insert(int );
        int extract_min();
        void dec_key(Node* ,int );
        void del(int  );
    
};

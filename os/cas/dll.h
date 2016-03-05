#include <iostream>
using namespace std;
#ifndef DLL_H
#define DLL_H
class node{
	int data;
	class node *prev ,*next;
	public:
		node();
		node(int a);
		void set_prev(node *Node);
		void set_next(node *Node);
		node *next_node();
		node *prev_node();
		int value();
		void print();
};
class dll{
	class node * Head , *Tail;
	public:
		dll();
		node *get_Head(){
			return Head;
		}
		node *get_Tail(){
			return Tail;
		}
		void set_Head(node *head){
			Head=head;
		}
		void set_Tail(node *tail){
			Tail=tail;
		}
		void insert_tail(node *Node);
		void print();
};


#endif

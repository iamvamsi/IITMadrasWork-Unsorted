#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include<iostream>
using namespace std;
class node{
	public:
		int data;
		node *next;
		node(){
			next=NULL;
		}
		void insert(int num){
			data=num;
			next=NULL;
		}
//		~ node(){
		
//		}	
	};
class list{
	node *head;	
	public:
		list(){
			head=NULL;
		};
		list(node *list_head){
			head=list_head;
		};
		int insert(int value){
			 node *temp=new node;
			 temp->insert(value);
			 temp->next=head;
			 head=temp;
			 return value;
		}
		int size(){
			int count=0;
			node *curr=head;
			while(curr!=NULL){
				count ++;
				curr=curr->next;	
			}		
			return count;
		}		
		node *tail(){
			node *curr=head;
			while(curr->next!=NULL){
				curr=curr->next;	
			}
			return curr;
		}	
		node *goto_n_pos(int n){
			int i;
			node *curr=head;
			for(i=1;i<n;i++)
				curr=curr->next;
			return curr;		
		}
	
		int insert_After(int number_to_insert, int number_in_list){
			if(number_in_list==1)
				return insert(number_to_insert);
			if(number_in_list>=(size()+1)){
				node *temp=new node;
				temp->insert(number_to_insert);
				tail()->next=temp;
				return number_to_insert;
			}
			
			node temp;
			temp.insert(number_to_insert);
			node *curr=goto_n_pos(number_in_list);
			temp.next=curr;
			curr=goto_n_pos(number_in_list-1);
			curr->next=&temp;
			return number_to_insert;
		}
		int delete_value(int value){
			node *curr;
			curr=head;
			if(curr==NULL){
				cout<<"The list is empty"<<endl;
				return 0;
			}
			if(curr->data==value){
				head=curr->next;
	//			delete curr;
//				~ curr();
				return 1;
			}
			while((curr->next!=NULL)&&(curr->next->data!=value)){
				curr=curr->next;
			}
			if((curr->next)==NULL){
				cout<<"The given element is not present in the list"<<endl;
			return 0;
			}
			node *temp;
			temp=curr->next->next;
//			delete (curr->next);
//			~ curr->next();
			curr->next=temp;
			return 1;
		}
		int search(int value){
			node *curr=head;
			while((curr!=NULL)&&(curr->data!=value))
				curr=curr->next;
			if(curr==NULL)
				return 0;
			else		
				return 1;
		}
		int is_empty(){
			if(head==NULL)
				return 1;
			else
				return 0;
		}	
				
		node *next_node(node *curr){
			if(curr==NULL)
				return NULL;
			else
				return curr->next;
									
		}
		void print_list(){
			node *curr=head;
			while(curr!=NULL){
				cout<<curr->data;
				curr=curr->next;
			}
		}
		int data_pos(int n){
			node *curr=head;
			int i=1;
			if(n>size())
				cout<<"The position is invalid"<<endl;
			else{			
			while(i<n){
				curr=curr->next;
				i++;
				}
				return curr->data;
			}		
		}
};
#endif

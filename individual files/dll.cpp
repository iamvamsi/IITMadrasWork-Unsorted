#include<iostream>

using namespace std;

class Node
{
public:
	int data;
	Node *next;
	Node *prev;
	Node()
	{
		next=NULL;
	}
	Node(int num)
	{
		data=num;
		next=NULL;
		prev=NULL;
	}
};
	




class List
{
	Node *head;
	Node *tail;
public:
	List()
	{
		head=NULL;
		tail=NULL;
	}
	//copy constructor
        List(Node *list_head,Node *list_tail)
        {
                        while(list_head->next!=NULL)
                        {
                                head->data=list_head->data;
                                head=head->next;
                                list_head=list_head->next;
			}
			while(list_tail->prev!=NULL)
			{
				tail->data=list_tail->data;
				tail=tail->prev;
				list_tail=list_tail->prev;
                        }
        }
	//------------------------------------------------------------	
	//FUNCTION THAT RETURNS THE HEAD OF THE CLASS

        Node* return_head()
        {
		Node* temp=new Node();
		temp=head;
                return temp;
        }
	
	//------------------------------------------------------------	
	//FUNCTION THAT RETURNS THE HEAD OF THE CLASS

        Node* return_tail()
        {
		Node* temp=new Node();
		temp=tail;
                return temp;
        }
	
	//-------------------------------------------------------------
	//FUNCTION TO INSERT AT THE START OF THE LIST

        void insert_start(int num)
        {

                        Node *temp=new Node();
			if(head==NULL&&tail==NULL)
			{
				temp->data=num;
                        	temp->next=NULL;
				temp->prev=NULL;
				head=temp;
				tail=temp;
			}
			else
			{
				temp->data=num;
				temp->next=head;
				temp->prev=NULL;
				head->prev=temp;
				head=temp;
			}
				
                        						
        }
	
	//-------------------------------------------------------------
	//FUNCTION TO INSERT AT THE LAST OF THE LIST

        void insert_last(int num)
        {

                        Node *temp=new Node();
			if(head==NULL&&tail==NULL)
			{
				temp->data=num;
                        	temp->next=NULL;
				temp->prev=NULL;
				head=temp;
				tail=temp;
			}
			else
			{
                        	temp->data=num;
				temp->prev=tail;
                        	temp->next=NULL;
				tail->next=temp;
				tail=temp;	
			}					
        }
	//-------------------------------------------------------------
	//FUNCTION THAT INSERTS AFTER A GIVEN NUMBER	

        int  insert_After(int number_to_insert,int number_in_list)
        {
                Node *temp=new Node();
		Node *temp1=new Node();
                temp=head;
                temp1->data=number_to_insert;
		if(search(number_in_list))
		{
			while(temp->data!=number_in_list)
			{
				temp=temp->next;
			}
		}
                else
		{
			while(temp->next!=NULL)
				temp=temp->next;
		}
		temp1->prev=temp;
		temp1->next=temp->next;
		temp->next->prev=temp1;
                temp->next=temp1;
		
                
		return 1;
                
	}
	//-------------------------------------------------------------
	//FUNCTION THAT INSERTS BEFORE A GIVEN NUMBER	

        int  insert_Before(int number_to_insert,int number_in_list)
        {
                Node *temp=new Node();
		Node *temp1=new Node();
                temp=head;
                temp1->data=number_to_insert;
		if(search(number_in_list))
		{
			while(temp->data!=number_in_list)
			{
				temp=temp->next;
			}
		}
                //else
		//{
		//	while(temp->next!=NULL)
		//		temp=temp->next;
		//}
		if(temp==head)
		{
			insert_start(number_to_insert);
		}
		else
		{
			temp1->prev=temp->prev;
			temp1->next=temp;
			temp->prev->next=temp1;
                	temp->prev=temp1;
		}
		
                
		return 1;
                
	}


        //-------------------------------------------------------------
	//FUNCTION THAT GIVES NUMBER OF ELEMENTS IN THE LIST
        
        int number()
        {
                Node* temp=new Node();
                temp=head;
                int i=0;
                while(temp!=NULL)
                {
                        temp=temp->next;
                        i++;
                }
		delete(temp);
                return i;
	}
	

	//-------------------------------------------------------------			
	//FUNCTION THAT SEARCHES FOR AN ELEMENT IN THE LIST			

 	bool search(int num)
        {
                Node *temp=new Node();
                temp=head;
                while(temp!=NULL)
		{
			if(temp->data==num)
				return true;
			temp=temp->next;
		}
		delete(temp);	
		return false;

        }

	//-------------------------------------------------------------
	//FUNCTION TO DELETE AN ELEMENT IN THE LIST


        void delet(int num)
        {
                Node *temp=new Node();
		Node *temp1=new Node();
                temp=head;
		
		if(search(num))
		{
			
			if(head->data==num)
			{
				head=head->next;
				head->prev=NULL;
			
			}
			else
			{	
                		while(temp->next->data!=num)
                		{
                        		temp=temp->next;
                		}
				if(temp=tail)
				{
					tail=temp->prev;
					tail->next=NULL;
				}
				else
				{					
					temp1=temp->next;
                        		temp->next=temp1->next;
					temp1->next->prev=temp;
				}
                       	
                	}
		}
		
		delete(temp1);
		

        }

	//-------------------------------------------------------------
	//FUNCTION THAT PRINTS THE ELEMENTS OF THE LIST IN ORDER

        void print_List()
        {
		Node *temp=new Node();
		temp=head;
                if(head==NULL)
                {
                        cout<<"the list is empty"<<endl;
                
                }
                else
                {
                        while(temp!=NULL)
                        {
                                cout<<temp->data;
                                temp=temp->next;
                        }
                }
		delete(temp);
        }

	//-------------------------------------------------------------
	//FUNCTION THAT RETURNS THE REVERSED LIST
                
	List reverse()
	{
		List r;
		Node *temp=new Node();
		temp=return_head();
		int i=0;
		while(temp!=NULL)
		{
			int num=temp->data;
			r.insert_start(num);
			temp=temp->next;
		}
		
		delete(temp);
		return r;
	}

	//-------------------------------------------------------------
	//FUNCTION THAT PRINTS THE ELEMENTS OF THE LIST IN REVERSE

        void print_Listr()
        {
		Node *temp=new Node();
		temp=tail;
                if(tail==NULL)
                {
                        cout<<"the list is empty"<<endl;
                
                }
                else
                {
                        while(temp!=NULL)
                        {
                                cout<<temp->data;
                                temp=temp->prev;
                        }
                }
		delete(temp);
        }
	
	//-------------------------------------------------------------
	//FUNCTION THAT EMPTIES THE LIST
	void free()
	{
		head=NULL;
		tail=NULL;
	}

};

/*
int main()
{
	Dlist l;
	l.insert_last(2);
	l.insert_last(3);
	l.insert_last(4);
	l.insert_last(5);
	l.insert_Before(9,2);
	//l.delet(5);
	l.print_List();
	cout<<"\n";
	l.print_Listr();
	cout<<"\n";
	cout<<l.number()<<endl;
	return 0;
}
*/	


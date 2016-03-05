#include<string>
#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<stdlib.h>
#include<cmath>
using namespace std;
class node{
	public:
		char data;
		node *next,*pre;
		node(){
			next=NULL;
			pre=NULL;
		}
		void insert(char num){
			data=num;
			next=NULL;
			pre=NULL;
		}
		
	};
class stack{
	node *head;
	node *tail;		
	public:
		stack(){
			head=NULL;
			tail=NULL;
			};
		/*node *top_of_stack(){
			if(head==NULL)
				return NULL;		
			node *curr=head;
			while((curr->next)!=NULL){
				curr=curr->next;
				}
			return curr;
			}	*/
		int is_empty(){
			if(head==NULL&&tail==NULL)
				return 1;	
			else 
				return 0;
			}
		int size(){
			node *curr=head;
			int count=0;
			while(curr!=NULL){
				count++;
				curr=curr->next;
				}
			return count;	
			}
		char data(int i){
			node *curr=head;
			for(int j=1;j<i;j++){
				curr=curr->next;
				}
			return curr->data;
			}					
		char data_tos(){
			if(tail==NULL)
				cout<<"stack underflow"<<endl;
			else
				return tail->data;
			}
			
			
		int push(char value){
			 node *temp=new node;
			 temp->insert(value);
			 if(head==NULL&&tail==NULL){
			 	head=temp;
			 	tail=temp;
			 	}
			 else{
			 	temp->pre=tail;
			 	tail->next=temp;
			 	tail=tail->next;
			 	}
			 	
			 return 1;
			 }
		char pop(){
			if(tail==NULL)
				cout<<"stack underflow"<<endl;
			else if(head==tail){
				head=NULL;
				char temp_dat=tail->data;
				delete tail;
				tail=NULL;
				return temp_dat;
				}	
			else{	
				node *temp=tail->pre;
				temp->next=NULL;
				char temp_data=tail->data;
				delete tail;
				tail=temp;
				return temp_data;
				}
			}
		/*int rearrange(){
			node *curr=head,*temp=new node;
			temp->data=' ';
			if(curr==NULL)
				return 1;
			while(curr->data!=' '){
				
		*/		
				
				
					
	};
		/* revers:  reverse string s in place */
	 void revers(char s[])
	 {
	     int i, j=0;
	     char c;
	     while(s[j]!='\0')
	     	 j++;
	     	 j=j-1;	
	     for (i = 0; i<j; i++, j--) {
	         c = s[i];
	         s[i] = s[j];
	         s[j] = c;
	     }
	 }
		/* itoa:  convert n to characters in s */
	 void itoa(int n, char s[])
	 {
	     int i, sign;
	 
	     if ((sign = n) < 0)  /* record sign */
	         n = -n;          /* make n positive */
	     i = 0;
	     do {       /* generate digits in reverse order */
	         s[i++] = n % 10 + '0';   /* get next digit */
	     } while ((n /= 10) > 0);     /* delete it */
	     if (sign < 0)
	         s[i++] = '-';
	     s[i] = '\0';
	     revers(s);
	 }
	 


	void   reverse(char *a,char *b){
		//char *rev=new char[100];
		int j=0,i=0;
		while(a[i]!='\0'){
			i++;
			}
		
		while(i>0){
			b[j]=a[i-1];
			j++;
			i--;
			}
		b[j]='\0';	
		
		}	
		
	void    operator_top(stack *post,char *b){
		char temp_data;
		char temp[100];
		int i=0;
		while((!post->is_empty())&&(temp_data=post->pop())==' ');
		//if(!post->is_empty())
			post->push(temp_data);
		while((!post->is_empty())&&(temp_data=post->pop())!=' '){
				temp[i]=temp_data;
				i++;
				}
		if(!post->is_empty())
			post->push(temp_data);		
		temp[i]='\0';
	        reverse(temp,b);
		}
	int eval(stack *post){
		int i=1,j;
		int in1,in2,result;
		stack *temp=new stack;
		char a,b[100];
		char 	op1[100],op2[100];
		while(post->data(i)!='$'){
			a=post->data(i);
			if(a!='+'&&a!='-'&&a!='*'&&a!='/'&&a!='^'){
				temp->push(a);
				i++;
				}
			else{	
			operator_top(temp,op2);
			in2=atoi(op2);
			operator_top(temp,op1);
			in1=atoi(op1);
			switch(a){
				case('+'):
						result=in1+in2;
						break;
				case('-'):
						result=in1-in2;
						break;
				case('*'):	
						result=in1*in2;
						break;
				case('/'):
						result=in1/in2;
						break;
				case('^'):
						result=pow(in1,in2);
						break;		
				}
			itoa(result,b);
			j=0;
			while(b[j]!='\0'){
				temp->push(b[j]);
				j++;
				}
			temp->push(' ');
			i++;
				
			}
		}
		operator_top(temp,op1);
		return (in1=atoi(op1));
	}
				
				
	int cmp(char op1,char op2){
		if(op2==40)
			return 1;
		if(op2==41&&op1==40)
			return 1;
	        if(op2==41)
			return 0;
		if(op1==40)
			return 1;	
		
		if(op2=='+')
			return 0;
		
		if(op2=='-')
			return 0;
		if(op2=='*'&&(op1=='+'||op1=='-'))
			return 1;
		if(op2=='*')
			return 0;
		if(op2=='/'&&(op1=='+'||op1=='-'))
			return 1;
		if(op2=='/')
			return 0;
		if(op2=='^'&&op1==' ')
			return 0;
		if(op2=='^')
			return 1;		
	}		
	
								
					
	int main(){
		int prec,i=0,j=0;
		char temp_char;
		string exp;
		ofstream outfile("outputFile.txt");
		ifstream infile("inputFile.txt");
		if(!infile){	
			cout<<"Error in opening the file check once"<<endl;
			return 0;
			}
		while(getline(infile,exp)){
			if(exp=="$")
				break;
			int len_exp=exp.size();
			exp[len_exp-1]='\0';
			stack *stack_temp=new stack,*stack_post=new stack;	
			for( i=0;i<len_exp-1;i++){
				if(exp[i]>47&&exp[i]<58)
					stack_post->push(exp[i]);
				else{
					if(stack_temp->is_empty())
						stack_temp->push(exp[i]);
					else{
						while((!stack_temp->is_empty())&&(prec=cmp(stack_temp->data_tos(),exp[i]))==0){
							
								stack_post->push(stack_temp->pop());
						}
						if((!stack_temp->is_empty())&&(stack_temp->data_tos()==40)&&(exp[i]==41))
							stack_temp->pop();
							
								
						if(exp[i]!=41)		
							stack_temp->push(exp[i]);
						
						}	
					}	
			}
			while((stack_temp->is_empty()==0))
					stack_post->push(stack_temp->pop());
			stack_post->push('$');			
			//stack_post->rearrange();		
			for(j=0;j<stack_post->size();j++){
				outfile<<stack_post->data(j+1);
				}
			//outfile<<" $"<<endl;				
			outfile<<eval(stack_post)<<"$"<<endl;
		}
		return 0;
	}	
			

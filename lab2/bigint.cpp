#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cmath>
#include"linkedlist.h"
using namespace std;

int min(int a ,int b){
	if(a<b)
	return a;	
	else 
	return b;
	}
int  reverse(list *a, list *b){
	int i=a->size();	
	for(;i!=0;i--)
		b->insert(a->data_pos(i));
	return 1;	
}
list * add_lists(list *list1,list * list2){
	
	int list1_size=list1->size(),list2_size=list2->size(),min_size=min(list1_size,list2_size),i=0,carry=0,temp;
	list *result=new list;
	for(i=0;i<min_size;i++){
		temp=list1->data_pos(i+1)+list2->data_pos(i+1)+carry;
		result->insert(temp%10);
		if(temp>9)
			carry=1;	
		else 
			carry=0;
		}
	if(list1_size==list2_size){
		if(carry==1)
			result->insert(carry);
		return result;
	}
	if(list1_size>list2_size){
		for(;i<list1_size;i++){
			temp=list1->data_pos(i+1)+carry;
			result->insert(temp%10);
			if(temp>9)
				carry=1;
			else 
				carry=0;
			}
			if(carry==1)
                        result->insert(carry);
                return result;
	}
	if(list2_size>list1_size){
                for(;i<list2_size;i++){
                        temp=list2->data_pos(i+1)+carry;
                        result->insert(temp%10);
                        if(temp>9)
                                carry=1;
                        else
                                carry=0;
                        }
                        if(carry==1)
                        result->insert(carry);
                return result;
        }


			
}	
list *mux_lists(list *list1,list *list2){
	int list1_size=list1->size(),list2_size=list2->size(),i=0,carry=0,temp,a,j=1;
	list *temp_list=new list,*result=new list,*temp_result=new list;
	for(i=0;i<list1_size;i++){
		a=list2->data_pos(1);
		temp=a*list1->data_pos(i+1)+carry;
		result->insert(temp%10);
		carry= temp/10;
	}
	if(carry!=0)
		result->insert(carry);
		
	for(j=1;j<list2_size;j++){
		
		for(i=0;i<list1_size;i++){
        	        a=list2->data_pos(j+1);
               		temp=a*list1->data_pos(i+1)+carry;
               		temp_list->insert_After(temp%10,i+1);
                	carry= temp/10;
	        }               
		if(carry!=0)
                	temp_list->insert_After(carry,i+1);
		reverse(result,temp_result);
		delete result;	
		result=add_lists(temp_result,temp_list);
		delete temp_result,temp_list;	
	}	
	return result;
}
list *factorial(int n){
	list *result=new list,*temp=new list,*temp_result=new list;
	if(n==0){
		result->insert(1);
	}
	int i=1;
	for(i=1;i<n+1;i++){
		while((i)/10!=0){
			temp->insert_After((i+1)%10,i+1);
			(i)=(i)/10;
		}
		reverse(result,temp_result);
		delete result;
		result=mux_lists(result,temp);
		delete temp,temp_result;
	}
	return result;
}
int main(){
	string op,op1,op2;
	int l1,l2,i=0,count=0;
	list *ls1=new list,*ls2=new list,*vamsi;
	ofstream outfile("output.txt");
	ifstream infile("input.txt");
	if(!infile){
		cout<<"There is an error in opening the file"<<endl;
		return 0;
	}
	while(getline(infile,op))
			{
		if(op=="+"||op=="*"){
			getline(infile,op1);
			getline(infile,op2);
			l1=op1.size();
			l2=op2.size();
			op1[l1-1]='\0';
			op2[l2-1]='\0';
			for(i=0;i<l1-1;i++)
				ls1->insert((int)op1[i]-48);
			for(i=0;i<l2-1;i++)
                                ls2->insert((int)op2[i]-48);
			if(op=="+"){	
				outfile<<(++count)<<"\n";
				vamsi=add_lists(ls1,ls2);
				int i=0,length=vamsi->size();
		 		for(i=0;i<length;i++)
					{
 					outfile<<vamsi->data_pos(i+1);
	         			}
				outfile<<"$";
				outfile<<endl;
				}
			if(op=="*"){
				outfile<<(++count)<<"\n";
				vamsi=mux_lists(ls1,ls2);
				
				int i=0,len=vamsi->size();
		 		for(i=0;i<len;i++)
					{
 					outfile<<vamsi->data_pos(i+1);
	         			}
				outfile<<"$";
				outfile<<endl;
				
				}
			}
			if(op=="-"){
				getline(infile,op1);
				outfile<<(++count)<<"\n"<<"-"<<op1;
				outfile<<endl;
			}
			if(op=="!"){
				getline(infile,op1);
				int opint=0;
				int leng=op1.size();
				for(i=leng-1;i<=0;i--){
					opint=opint+(op[i]-48)*pow(10,leng-i-1);
				}	
				outfile<<(++count)<<"\n";
				vamsi=factorial(opint);
				
				int lengths=vamsi->size();
		 		for(i=0;i<lengths;i++)
					{
 					outfile<<vamsi->data_pos(i+1);
	         			}	
				
				outfile<<"$";
				outfile<<endl;
			}
			if(op=="$")
				return 1;
		}
		infile.close();
}					
	
			

/*********************************************************************
*        TEAM :                                                       *
*        MADHAVI Y       CS09B025                                     *
*        VAMSI KRISHNA   CS09B006                                     *
*        UDAY CHOWHAN    CS09B034                                     *
*                                                                     *
*        ***IMPLEMANTATION OF A HEAP***                               *
*                                                                     *
**********************************************************************/  




#include"heap_header.h"
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<string>
#include<time.h>
using namespace std;
//................DEFINTITIONS OF FUNCTIONS WHICH TAKE IN THE CLASS HEAP

//FUNC. TO READ INTO HEAP FROM ARRAY
void heap::reader(int *h)
{
	int i;
	for(i=1;h[i]!='\0';i++)
	{
		arr[i]=h[i];
	}
}

//FUNC. TO FIND RIGHT CHILD OF A NODE
int heap::rchild(int i)
{
	return 2*i+1;
}
//FUNC. TO RETURN LEFT CHILD
int heap::lchild(int i)
{
	return 2*i;
}
//FUNC. TO RETURN PARENT OF A NODE
int heap::parent(int i)
{
	return i/2;
}

//FUNC. TO RETURN SIZE OF HEAP
int heap::size()
{
	int i=1;
	for(i=1;arr[i]!='\0';i++)
	{
	}
	return i-1;
}	

//FUNC. TO SWAP ELEMENTS IN TWO NODES
void heap::swap(int i,int j)
{
	int temp;
	temp=arr[i];
	arr[i]=arr[j];
	arr[j]=temp;
}
	
//FUNC. TO MIN_HEAPIFY A GIVEN NODE
void heap::min_heapify(int index)
{
	int r,l;
	r=rchild(index);
	l=lchild(index);
	if(l>size())
	{
	}
	else if(l==size())
	{
		if(arr[index]>arr[l])
			swap(index,l);
	}		
	else if(r<=size()&&l<=size())
	{
		if(arr[r]<arr[l])
		{
			if(arr[index]>arr[r])
			{
				swap(index,r);
				min_heapify(r);
			}
		}
		else
		{
			if(arr[index]>arr[l])
			{
				swap(index,l);	
				min_heapify(l);
			}
		}
		
	}
}

//FUNC. TO BUILD MAX. HEAP
void heap::build_heap()
{
	int i;
	
	for(i=size()/2;i>0;i--)
	{
		min_heapify(i);
	}
}
//FUNC. TO DECREASE THE KEY AT GIVEN NODE TO GIVEN VALUE
void heap::heap_decrease_key(int index,int num)
{
	int p;
	p=parent(index);
	if(arr[index]>num)
	{
		arr[index]=num;
		while((arr[index]<arr[p])&& p>=1)
		{
			swap(index,p);
			index=p;
			p=parent(index);	
			
		}
	}

			
}
//FUNC. TO INSERT A GIVEN NUM IN HEAP
void heap::min_heap_insert(int num)
{
	int len;	
	len=size();
	len=len+1;
	arr[len]=99999999;
	arr[len+1]='\0';
	heap_decrease_key(len,num);
}

//FUNC.  TO RETURN MIN ELEMENT IN HEAP
int heap::heap_minimum()
{
        return arr[1];
}


//FUNC. TO RETURN AND REMOVE MIN ELEMENT IN HEAP       
int heap::extract_min()
{
        int  res=heap_minimum();
        int last=size();
	
        swap(1,last);
        arr[last]='\0';
        min_heapify(1);
        return res;
}
//FUNC. TO PERFORM SORTING USING HEAP
void heap::heap_sort()
{
        int temp[20000],i=1;
	int len=size();
        while(i<=len)
        {
            temp[i]=extract_min();
		i++;
        }
        temp[i]='\0';
        reader(temp);
}
//FUNC. TO COPY ELEMNTS HEAP INTO AN ARRAY
void heap::copy(int *a)
{
        int i=1;
        while(arr[i]!='\0')
        {
            a[i]=arr[i];
	    i++;
        }
        a[i]='\0';
}    
//FUNC. TO MELD TWO HEAPS     
void heap::heap_meld(heap heap2)
{
        int a[20000];
	int i=1;
        heap2.copy(a);
        int pos=size()+1; 
        while(a[i]!='\0')
        {
            arr[pos]=a[i];
            pos++;
	    i++;
        }
        arr[pos]='\0';
        build_heap();
}    
            
//MAIN FUNCTION           

int main(int argc,char *argv[])
{
	int in_arr1[20000],k;
	int in_arr2[20000],temp[20000];
	heap heap1,heap2;
	ifstream in1(argv[2]);
	ifstream in2(argv[3]);
	ofstream out1("outputfile");
	ofstream out2("sortedfile");
	
	if(!in1&&!in2)
	{
		cout<<"error in opening the file"<<endl;
		return -1;
	}
	int i=1;
	string we;
	while(!in1.eof())                      //READING INPUT_1 INTO......................
	{
		getline(in1,we);
		istringstream x(we);
		x >> in_arr1[i];
		i++;
	}
	in_arr1[i]='\0';
	heap1.reader(in_arr1);                 //...........................HEAP1
	
	if (argv[1][0]=='2')                   // IF ARG IS 2.........
	{
		
		 i=1;
		while(!in2.eof())
		{
			getline(in2,we);       //READING INPUT_2 IN HEAP2
			istringstream x(we);
			x >> in_arr2[i];
			i++;
		}
		in_arr2[i]='\0';
		heap2.reader(in_arr2);
		clock_t start=clock();
		heap1.heap_meld(heap2);	       //DOING MELD OPERATION AND STORING RESULT IN HEAP1
		double time_meld=((double)clock()-start)*1000/(double)CLOCKS_PER_SEC;
		heap1.copy(temp);
		for(k=1;k<=heap1.size();k++)
		{
			out1<<temp[k]<<endl;   //PRINTING RESULT IN OUPUTFILE
		}
                out1<<endl;
                out1<<endl;
		out1<<"time for meld : "<<endl; //PRITING TIME TAKEN IN MilliSeconds  
		out1<<time_meld<<"ms"<<endl;
		clock_t start2=clock();
		heap1.heap_sort();              //DOING SORTING
		double time_sort=((double)clock()-start2)*1000/(double)CLOCKS_PER_SEC;
		heap1.copy(temp);
		for(k=1;k<=heap1.size();k++)
		{
			out2<<temp[k]<<endl;   //PRINTING IN SORTEDLIST FILE
 		}
                out2<<endl;
		out2<<"time for sort : "<<endl;
		out2<<time_sort<<"ms"<<endl;	
	}
	
	if(argv[1][0]=='1')                       //IF ARG IS 1.................
	{	
		string s;
		char sp[200];
		int num,i=1,j;
		getline(in2,s);
		clock_t start3=clock();
		while(!in2.eof()&&(s[0]=='+'||s[0]=='-'))     //READING LINE BY LINE AND DOING CORREPONDING OPRATION
		{
			
			if(s[0]=='+')
			{
				getline(in2,s);
				j=0;
				int len_s=s.size();
				while(j<len_s)
				{
					sp[j]=s[j];
					j++;
				}	
				sp[j]='\0';	
				num=atoi(sp);
				heap1.min_heap_insert(num);
				
			}
			else if(s[0]=='-')
			{
                                heap1.build_heap();
				heap1.extract_min();
			}
			out1<<i<<")"<<endl;
			i++;
			heap1.copy(temp);
			for(k=1;k<=heap1.size();k++)
			{
				out1<<temp[k]<<endl;
			}
                        //out1<<endl;
                        out1<<endl;
			getline(in2,s);
		}
		double time_all_ope=((double)clock()-start3)*1000/(double)CLOCKS_PER_SEC;
		out1<<"time for all operations : "<<endl;
		out1<<time_all_ope<<"ms"<<endl;
		clock_t start4=clock();
		heap1.heap_sort();                      //SORTING THE FINALLY OBTAINED HEAP
		double time2=((double)clock()-start4)*1000/(double)CLOCKS_PER_SEC;
		heap1.copy(temp);
		for(k=1;k<=heap1.size();k++)
		{
			out2<<temp[k]<<endl;
		}
                //out2<<endl;
		out2<<"time for sort : "<<endl;
		out2<<time2<<"ms"<<endl;	
	}
	return 1;
}      
        



	

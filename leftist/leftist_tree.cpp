/*********************************************************************
  *        TEAM :                                                       *
  *        MADHAVI Y       CS09B025                                     *
  *        VAMSI KRISHNA   CS09B006                                     *
  *        UDAY CHOWHAN    CS09B034                                     *
  *                                                                     *
  *        ***IMPLEMANTATION OF A LEFTIST HEAP***                       *
  *                                                                     *
  **********************************************************************/  


#include "leftist_heap.h"
#include<sstream>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<stdio.h>
#include<vector>
#include<sys/time.h>


using namespace std;



//swap function
void swap(lhnode **A,lhnode **B)
{
    lhnode **temp;
    temp=B;
    B=A;
    A=temp;
}



//meld function
//lchild--left child
//rchild--right child
//r1 and r2 are roots of heaps to be melded
lhnode*  meld(lhnode *r1,lhnode *r2)
{
    if(r2==NULL)
    {
        return r1;
    }
    else if(r1==NULL)
    {
        return r2;
    }
    else
    {
        if(r1->data>r2->data)
            swap(r1,r2);
        r1->rchild=meld(r1->rchild,r2);
        if(r1->lchild==NULL)
            swap((r1->lchild),(r1->rchild));
        else if(r1->rchild!=NULL)
        {
            if(r1->rchild->s>r1->lchild->s)
            {
                swap((r1->rchild),(r1->lchild));
            }
        }    
        if(r1->rchild==NULL)
            r1->s=0;
        else
            r1->s=(r1->rchild->s)+1;
        return r1;

    }


}


//function to insert
void left_heap::insert(int a)
{
    lhnode *temp=new lhnode();
    temp->data=a;
    root=meld(root,temp);
}


//function t extract
int left_heap::extract_min()
{
    int dat=root->data;
    root=meld(root->rchild,root->lchild);
    return dat;
}


//function to sort
void left_heap::sort(int *a)
{
    int i=0;
    while(root!=NULL)
    {
        a[i]=extract_min();
        i++;
    }
    a[i]='\0';

}

//function to print the elements in inorder
//rchild---right child
//lchild---left child
void inorder(lhnode *lr,ofstream &fout)
{   
    int i=1;
    if(lr->lchild!=NULL)
        inorder(lr->lchild,fout);
    fout<<lr->data<<endl;
    if(lr->rchild!=NULL)
        inorder(lr->rchild,fout);
}


/*
timetaken----tima taken to perform any function
heap1 , heap2 store the heaps and heap3 stores the melded heap

   */
int main(int argc,char *argv[])
{
	int in_arr1[200000],k;
	int in_arr2[200000],temp[200000];
	left_heap heap1,heap2;
	ifstream in1(argv[2]);
	ifstream in2(argv[3]);
	ofstream out1("outputfile");
	ofstream out2("sortedfile");
	vector <double> time_taken;
        double cumulative=0;
        struct timeval before,after;
        double timetaken;
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
	int j=1;
	for(j=1;in_arr1[j]!='\0';j++)
	{
		heap1.insert(in_arr1[j]);
	}
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
		for(j=1;in_arr2[j]!='\0';j++)
	        {
        	        heap2.insert(in_arr2[j]);
        	}
                gettimeofday(&before, NULL);
		left_heap heap3(meld(heap1.return_root(),heap2.return_root()));
                gettimeofday(&after, NULL);
                timetaken=(after.tv_sec-before.tv_sec+ 1e-6 * (after.tv_usec - before.tv_usec));
                

                k=0;
		for(k=0;temp[k]!='\0';k++)
		{
			out1<<temp[k]<<endl;   //PRINTING RESULT IN OUPUTFILE
		}
                inorder(heap3.return_root(),out1);
		out1<<endl;
                out1<<endl;
		out1<<"time for meld : "<<endl; //PRITING TIME TAKEN IN MilliSeconds  
		out1<<timetaken;
                out1<<"ms"<<endl;
                gettimeofday(&before, NULL);
		heap3.sort(temp);
                gettimeofday(&after, NULL);
                timetaken=(after.tv_sec-before.tv_sec + 1e-6 * (after.tv_usec - before.tv_usec));
                
		for(k=0;temp[k]!='\0';k++)
		{
			out2<<temp[k]<<endl;   //PRINTING IN SORTEDLIST FILE
 		}
                out2<<endl;
		out2<<"time for sort : "<<endl;
		out2<<timetaken<<"ms"<<endl;	
	}
	if(argv[1][0]=='1')                       //IF ARG IS 1.................
	{	
		string s;
		char sp[200];
		int num,i=1,j;
		getline(in2,s);
                gettimeofday(&before, NULL);

                int count=1;
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
				heap1.insert(num);
				
			}
			
			else if(s[0]=='-')
			{
				out1<<i<<")"<<endl;
				i++;
				out1<<heap1.extract_min()<<endl;
			}	
			out1<<endl;
			getline(in2,s);
                        out1<<count<<')'<<endl;
                        inorder(heap1.return_root(),out1);
                        count++;

		}
                gettimeofday(&after, NULL);
                timetaken=(after.tv_sec-before.tv_sec+ 1e-6 * (after.tv_usec - before.tv_usec));

		out1<<"time for all operations : "<<endl;
		out1<<timetaken<<"ms"<<endl;

                gettimeofday(&before, NULL);
                heap1.sort(temp);
                gettimeofday(&after, NULL);
                timetaken=(after.tv_sec-before.tv_sec+ 1e-6 * (after.tv_usec - before.tv_usec));
                   


                for(k=0;temp[k]!='\0';k++)
                {
                        out2<<temp[k]<<endl;   //PRINTING IN SORTEDLIST FILE
                }
                out2<<endl;
                out2<<"time for sort : "<<endl;
                out2<<timetaken<<"ms"<<endl;
	}
	return 1;
}

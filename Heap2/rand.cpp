/*********************************************************************
*        TEAM :                                                       *
*        MADHAVI Y       CS09B025                                     *
*        VAMSI KRISHNA   CS09B006                                     *
*        UDAY CHOWHAN    CS09B034                                     *
*                                                                     *
*        ***function which produces random numbers***                 *
*                                                                     *
**********************************************************************/
 



#include<iostream>
#include<fstream>
#include<sstream>
#include<stdlib.h>

using namespace std;
int main(int argc,char* argv[])
{
	
	int i,j,op,insert,extract;
	//cout<<"Enter the number of inputs in first file :"<<endl;
	//cin>>i;
	ofstream out1("i1");
	ofstream out2("i2");
        string s;
        s=argv[1];
        //cout<<s<<endl;
        int num;

        istringstream x(s);
        x >> num;

        //itoa(num,s,10);

	for(j=0;j<num;j++)
	{
		out1<<rand()%50000<<endl;
	}
        for(j=0;j<num;j++)
        {
                out2<<rand()%50000<<endl;
        }
        /*
	cout<<"If u want to do :"<<endl;
	cout<<"                  insertion and deletion operations press 1"<<endl;
	cout<<"                  meld operation press 2"<<endl;
	cin>>op;
	if(op==2)
	{
		cout<<"Enter the number of inputs in second file :"<<endl;
		cin>>i;
		for(j=0;j<i;j++)
		{
			out2<<rand()%50000<<endl;
		}
	}
	if(op==1)
	{
		cout<<"enter the number of insert operations"<<endl;
		cin>>insert;
		for(j=0;j<insert;j++)
		{
			out2<<"+"<<endl;
			out2<<rand()%50000<<endl;
		}
		cout<<"enter the number of extract_min operations"<<endl;
		cin>>extract;
		for(j=0;j<extract;j++)
		{
			out2<<"-"<<endl;
			
		}
	}	
	*/		
	return 1;
}	

//THE PROGRAM JUST CONVERTS ANY ROMAN NUMBER ENETERED INTO A NUMBER


#include<iostream>

using namespace std;

int num_eq(char ch)
{
	switch(ch)
	{
		case 'I':
			return 1;
			break;
		case 'V':
			return 5;
			break;
		case 'X':
			return 10;
			break;
		case 'L':
			return 50;
			break;
		case 'C':
			return 100;
			break;
		case 'D':
			return 500;
			break;
		case 'M':
			return 1000;
			break;
		default:
			return -1;
			break;
	}
}



int rom_to_num(char *str)
{
	int i=0;
	int num[100];
	int len=0;
	int sum=0;
	for(i=0;str[i]!='\0';i++)
	{
		num[i]=num_eq(str[i]);
		len++;
	}
	for(i=0;i<len-1;i++)
	{
		if(num[i]<num[i+1])
		{
			int j=0;
			for(j=i;j>=0||num[j]>num[i];j--)
			{
				num[j]=0-num[j];
			}
			
		}
	}
	for(i=0;i<len;i++)
	{
		sum=sum+num[i];
	}
	
	return sum;
}

int main()
{
	char ch[100];
	cout<<"enter the string:";
	cin>>ch;
	if(rom_to_num(ch)>0)
		cout<<"invalid number"<<endl;
	else
		cout<<rom_to_num(ch)<<endl;
}




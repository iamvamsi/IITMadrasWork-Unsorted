#include <iostream>
#include<string>
#include<cstring>
using namespace std;
void print(char *,int,int);
void swap(char *,int,int);
int main()
{
    string input;
    cout<<"enter the string"<<endl;
    cin>>input;
    size_t length;
    char *s;
    s=new char [input.length()+1];
    length=input.copy(s,input.length(),0);
    s[length]='\0';
    print(s,0,strlen(s));
}
void print(char *s,int begin,int end)
{
    int i;
    if(begin==end)
    	cout<<s<<endl;
    else{
    for(i=begin;i<end;i++){
    	swap(s,begin,i);
    	print(s,begin+1,end);
    	swap(s,begin,i);
    	}
    }   
}
void swap(char *a,int p,int q)
{
    char temp;
    temp=a[p];
    a[p]=a[q];
    a[q]=temp;
}









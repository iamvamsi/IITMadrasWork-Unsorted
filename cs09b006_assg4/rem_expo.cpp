#include<iostream>
using namespace std;
unsigned int rem(unsigned int,unsigned int, unsigned int ); 
int main()
{
  unsigned int a,b,m;
  cout<<"enter the base number "<<endl;
  cin>>a;
  cout<<"enter the power to which base to be raised"<<endl;
  cin>>b;
  cout<<"enter the divisor"<<endl;
  cin>>m;
  if(m==0){
     cout<<"the value of m is invalid"<<endl;
     return 0;
  }
  cout<<"the remainder that is obtained is  "<< rem(a,b,m)<<endl;

}
unsigned int rem(unsigned int a,unsigned int b,unsigned int m ) 

{
    if(a==0)
        return 0;
    if(a==1)
        return 1%m;
    if(b==1)
        return a%m;
    if(b%2==0)
        return rem((a*a)%m,b/2,m);
    else 
       return  ( a*rem( (a*a)%m ,(b-1)/2 ,m ) )%m;
}

#include<iostream>
using namespace std;
void hanoi(int ,int,int,int);
int main()
{
    int source=1 ,destination=3,num_disks,inter_stage=2;
    cout<<"enter the number of disks to be available for arranging"<<endl;
    cin>>num_disks;
    if(num_disks==0){
        cout<<"nothing is required to be done"<<endl;
        return 0;
    }
       hanoi(source,inter_stage,destination,num_disks);
   
}
void hanoi(int source,int inter_stage,int destination,int num_disks)
{
    if(num_disks==1)
    {
        cout<<"("<<source<<","<<destination<<")"<<endl;
        return;
    }
    else
    {
        hanoi(source,destination,inter_stage,num_disks-1);
        cout<<"("<<source<<","<<destination<<")"<<endl;
        if(num_disks-1==1){
           cout<<"("<<inter_stage<<","<<destination<<")"<<endl;
           return;
        }
        hanoi(inter_stage,source,destination,num_disks-1);
     }
        
}



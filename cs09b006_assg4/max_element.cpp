#include <iostream>
using namespace std;
int max_finder(int ,int *,int ,int );
int main()
{
    int size;
    cout<<"enter the size of the int array"<<endl;
    cin>>size;
    int *array;
    array=new int(size);
    for(int i=0;i<size;i++){
	    cout<<"enter the  "<<i+1<<"  element"<<endl;    
	    cin>>array[i];
    }
    if((array==NULL)||(size==0)){
        cout<<"the int array is empty"<<endl;
        return 0;
    }
    int max_element=array[0];
    cout<<"the max element is "<<max_finder(max_element,array,0,size)<<endl;
    return 0;
}
    int  max_finder(int max_element,int *array,int i,int size)
{
        if(i==size-1)
            return max(max_element,array[i]);
        else if(i<size-1){
            max_element=max(max_element,array[i]);
            return  max_finder(max_element,array,i+1,size);
        }
        else{
            cout<<"there is an error"<<endl;
	    return 0;
	} 
}
int max(int a,int b){
    if(b>a)
        return b;
    else 
        return a;
}

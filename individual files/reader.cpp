#include<iostream>
#include<cstring>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
class student_info{
  char input[4][50];
  public:
  void getinfo(string );
  char *give_id();
  void details();
};
void student_info::getinfo(string line)
{
  int i=0,j=0,k=0,m=0;
  while(line[i]!='\0'){
    j=i;
    while(line[i]!='|'){
      input[k][m]=line[i];
      i++;
      m++;
    }
    i++;
    k++;
  }
}      
  
void student_info::details()
{
  int i=0;
  for(i=0;i<4;i++){
    cout<<input[i];
  }
} 
char *student_info::give_id()
{
  return input[1];
}
int main()
{
  student_info info[150];
  int count=0;
  int i=0;
  ifstream mydata;
  mydata.open("batchlist.txt");
  vector<string> list;
  string myline;
  while(getline(mydata,myline))
    list.push_back(myline);
  count=list.size();
  string buffer;
  for(i=0;i<count;i++){
    
    info[i].getinfo(buffer);
  }
  cout<<"enter the id to be searched"<<endl;
  char id[10];
  cin>>id;
  int flag=-1;
  for(i=0;i<count;i++){
    if(strcmp(id,info[i].give_id())==0)
    flag=i;
  }
  if(flag==-1)
    cout<<"the id doesnot exist in the data base"<<endl;
  else
    info[flag].details();
  return 0;
}    

  

#include<iostream>
using namespace std;
class intlist {
  typedef struct{
    int a;
    data *next;
  }data;
  iterator head;
public:
  class iterator {
    data *node;
  public:
    iterator(){
      node=NULL;
    }
    iterator(const iterator &it){
      node=it.node;
    }
    iterator operator=(const iterator &){
      node=it.node;
      return *this;
    }
    
    iterator operator++(){
      node= node->next;
    }
    iterator operator++(int a){
      for(int i=0;i<a;i++){
	node=node->next;
      }
    }
    int &operator*(){
      return node->a;
    }      
    bool operator==(iterator &it)const{
      if(node==it)
	return true;
      else 
	return false;
    }
    bool operator!=(iterator &)const
      if(node==it)
	return false;
      else 
	return true;
    }
  };
  friend class iterator;
  intlist(){
   
  bool empty() const;
  unsigned int size() const;
  void push_back(int);
  void push_front(int);
  int pop_back();
  int pop_front();
  void clear();
  Iterator first() const;
  Iterator end() const;
  void insert(const Iterator &);
  void insert(const Iterator &);
  ~IntList();
};
bool intlist:: empty(iterator head) const{
  if(head==NULL)
    return true;
  else 
    return false;
}
unsigned int intlist::size() const{
  unsigned int i=0;
  iterator current;
  while(current!=NULL){
    i++;
    current++;
  }
  return i;
}
void intlist:: push_back(int p){
  iterator temp:
  data *temp_data=new data;
  temp_data->a=p;
  temp_data->next=head.node;
  temp.node =temp_data;
  head=temp;
}
void intlist:: push_front(int p){
  data *temp_data=new data;
  temp_data->a=p;
  temp_data->next=NULL;
  head++(size());
  head.node=temp_data;
}
int intlist:: pop_back(){
  data *temp;
  head.node=temp;
  head++;
  int p= temp.a;
  delete temp;
  return p;
}
int intlist:: pop_front(){
  head++(size()-1);
  data *temp=head.node;
  head.node =NULL;
  int p=temp->a;
  delete  temp;
  return p;
}
void  intlist::clear(){
  data *temp= head.node;
  head.node=NULL;
  delete [] temp;
}
iterator  intlist::first() const{
  return head;
}  
iterator  intlist::end() const{
  head++(size()-1);
  return head;
}
void intlist:: insert(const Iterator &location){
  
  data *temp_node=location.node;
  data *temp_data=new data;
  location.node=temp_data;
  temp_data->next=temp_node;
}
void  intlist::remove(Iterator &location){
  data *temp= location .node;
  location=location++;
  delete temp;
}


    

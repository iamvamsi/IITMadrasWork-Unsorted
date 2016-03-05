/**---------OS lab assignment4 ----------
***	    author: D.vamsi krishna,
***	    Roll No:cs09b006
***	    Date:21-09-2011
---------------------------------------*****/	    
#include "dll.h"
#include "dll.cpp"
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <pthread.h>
using namespace std;
#define NSEC_PER_SEC 1000000000
#define IT 20
int active_threads_count=0;
int MAX_THREADS;
pthread_mutex_t lock;
struct ARG{
		
		node *t1;
		node *t2;
		dll  *t3;
	};

node *mid_node(node *t1,node *t2){
	if(t1==NULL||t2==NULL)
		exit(1);		
	if(t1==t2)
		return t1;
	node *temp=t1, *temp2=t1;
	while(1){
		if(temp2->next_node()==t2)
			return temp->next_node();
		else if(temp2==t2)
			return temp;
		else{
	
			temp=temp->next_node();
			temp2=temp2->next_node()->next_node();
		}
	}	
}		
	
int merge(node *head , node *mid , node *tail,dll *dll_list){
	node *currL=head,*currR=mid,*temp_next,*temp_prev,*mod_head=head,*int_mid=mid->prev_node();
	int inserted=0;
	while(currL!=mid&&currR!=NULL&&currR->prev_node()!=tail){
		if(currL->value()<=currR->value()){
			currL=currL->next_node();
			inserted=1;	
		}
		else{
			if(inserted==0){
				mod_head=currR;
			}
			inserted=1;
			temp_next=currR->next_node();
			temp_prev=currR->prev_node();
			currR->set_prev(currL->prev_node());
			if(currL->prev_node()!=NULL)
				currL->prev_node()->set_next(currR);			
			currR->set_next(currL);
			currL->set_prev(currR);	
			if(temp_prev!=NULL)
				temp_prev->set_next(temp_next);
			if(temp_next!=NULL)			
				temp_next->set_prev(temp_prev);
			if(currR==tail){
				dll_list->set_Head(mod_head);
				dll_list->set_Tail(int_mid);
				return 0;
			}
			else if(currR==mid)
				mid=temp_next;
			
			currR=temp_next;
		}
		
	}
	dll_list->set_Head(mod_head);
	dll_list->set_Tail(tail);
	return 0;		

}
void  *mergesort(void *ARG_THREADS)
{
	struct ARG *my_data;
	my_data = (struct ARG *) ARG_THREADS;
	node *head=my_data->t1;
	node *tail=my_data->t2;
	dll *dll_list=my_data->t3;
        struct ARG A1,A2;
	node *mid=mid_node(head,tail);
	dll *dll_list1=new dll();
	dll *dll_list2=new dll();
	int is_thread=0;
	pthread_t th;
	A1.t1=head;
	A1.t2=mid->prev_node();
	A1.t3=dll_list1;
	A2.t1=mid;
	A2.t2=tail;
	A2.t3=dll_list2;
	if(head==tail)
	{
		dll_list->set_Head(head);
		dll_list->set_Tail(tail);
		return NULL;
	}
	else{
		pthread_mutex_lock(&lock);
		is_thread=0;
		mid->prev_node()->set_next(NULL);
		mid->set_prev(NULL);
		if(active_threads_count >= MAX_THREADS)
    		{
     		         pthread_mutex_unlock(&lock);
			 mergesort((void*)&A2);
  		}
		else{
			active_threads_count++;
			is_thread=1;
			pthread_mutex_unlock(&lock);
			pthread_attr_t attr;
   			pthread_attr_init( & attr );
  			pthread_attr_setdetachstate( & attr, PTHREAD_CREATE_JOINABLE );
			pthread_create(&th, &attr, mergesort,(void*)&A2);
		}
		mergesort((void *)&A1);
		if(is_thread==1){
			(pthread_join(th,NULL));
			pthread_mutex_lock(&lock);
      			active_threads_count--;
     			pthread_mutex_unlock(&lock);
				
		  }
		dll_list1->get_Tail()->set_next(dll_list2->get_Head());
		dll_list2->get_Head()->set_prev(dll_list1->get_Tail());
	        merge(dll_list1->get_Head(),dll_list2->get_Head(),dll_list2->get_Tail(),dll_list);
		return NULL;
				
	}
	
}
double diff(timespec t1,timespec t2)
{
  return ((t2.tv_sec-t1.tv_sec)*NSEC_PER_SEC + t2.tv_nsec-t1.tv_nsec);
}	
int main(){
	int dll_size,seed,max_threads;
	//cout<<"Enter the size of the doubly linked list"<<endl;
	cin>>dll_size;
	//cout<<"Enter the seed"<<endl;
	cin>>seed;
	//cout<<"Enter the maximum number of active threads"<<endl;
	cin>>MAX_THREADS;
	double time;
	struct ARG A;
	//for(int exp=0;exp<20;exp++){
	srand(seed);
	node *temp;
	dll *dll_list=new dll();
	for(int i=0;i<dll_size;i++){
		temp= new node (rand());
		dll_list->insert_tail(temp);
			
	}
	//dll_list->print();	
	dll *dll_listF=new dll();
	timespec start,end;
	A.t1=dll_list->get_Head();
	A.t2=dll_list->get_Tail();
	A.t3=dll_listF;
	clock_gettime(CLOCK_REALTIME,&start);
	mergesort((void *)&A);
	clock_gettime(CLOCK_REALTIME,&end);
	time=diff(start,end);
	//}
	cout<<dll_size<<"\t"<<MAX_THREADS<<"\t"<<time<<endl;
	//cout<<"The sorted list is"<<endl;
	//dll_listF->print();	
	
	return 0;
}


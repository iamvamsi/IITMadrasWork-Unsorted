//linked list implementation in C
#include<stdio.h>
#include<stdlib.h>
typedef struct lnode{
	int a;
	struct lnode *next;
	}list_given;
list_given *insert_head(list_given *head,int a){
	list_given *temp=malloc(1);
	temp->a=a;	
	temp->next=head;
	return temp;
}
list_given *delete_head(list_given *head){
	 	list_given *temp=head;
		free(head);
		return temp->next;
}
int search(list_given *head,int a){
	list_given *curr=head;
	int count_num=0;
	while(curr!=NULL){
		if(curr->a==a)
			count_num++;
		curr=curr->next;
		}
	if(count_num==0){
		printf("The element is not present in the list\n");
		return 0;	
	}
	else{
		printf("The element occurs %d times in the list\n",count_num);
		return 1;
	}
}			
int check_empty(list_given *head){
	if(head==NULL){
		printf("The list is empty\n");
		return 1;
	}	
	else{
		printf("The list is not empty\n");
		return 0;
	}
}
list_given *access(list_given *head,int a){
	list_given *curr=head;
	if(search(head,a)==0)
		return NULL;
	else{
		while(curr->a!=a){
			curr=curr->next;
		}		
	return curr;
	}				
}
list_given *access_nextnode(list_given *position){
	if(position==NULL){
		printf("YOU ARE AT THE END\n");
		return NULL;
	}
	list_given *temp=position->next;
	return temp;
} 
main(){
	list_given *head=NULL;
	head=insert_head(head,454);
	head=insert_head(head,99);
	search(head,5454);
	printf(" %d\n",access(head,454)->a);
	if(access_nextnode(head)==NULL);
	else
	printf("%d\n",access_nextnode(head)->a);
	head=delete_head(head);
	
	check_empty(head);

}

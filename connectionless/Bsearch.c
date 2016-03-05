#include <stdio.h>
typedef struct Node
{
    char roll_no[9];
    char name[50];
    struct Node *left;
    struct Node *right;

}node;

node* insert(node* curr_node , node * bst)
{
    if(bst == NULL)
    {
        return curr_node;
    }

    int compare = strcmp(curr_node->roll_no , bst->roll_no) ;  
    if(compare < 0 )
    {
        bst->left = insert(curr_node , bst->left);   
    }
    else if(compare > 0)
    {
        bst->right = insert(curr_node , bst->right);   
    }
    else
    {
        printf("\n*****%s*******\n",curr_node->roll_no);
        printf("\n*****%s*******\n",bst->roll_no);
        printf("Error : Same roll number repeated again \n");
        exit(0);
    }

    return bst;
    
}

char* get_name(node * bst , char* buf )
{
    if(bst == NULL)
    {
        return "Sorry no such roll number present" ;
    }
    else
    {   
        int compare = strcmp(buf , bst->roll_no) ;  
        if(compare == 0)
        {
            return bst->name;
        }
        else if(compare < 0)
        {
            return get_name(bst->left , buf );
			//return bst->name;
        }
		else if(compare==10)
		{
			return bst->name;
		}
        else
        {
            return get_name(bst->right , buf );
        }


    }
}

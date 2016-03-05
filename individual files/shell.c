///////////////////Author :
///////////////////D.vamsi krishna
///////////////////cs09b006
///////////////////DOS:17/aug/11
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
void my_prompt()
{
    printf("vamsi@shell:");
}    
void main()
{
	
	pid_t pid;
	size_t nbytes=100;
	int bytes_read,i,j,background=0,fd[2],pre_fd=STDIN_FILENO;
	char *my_string, *not_used , *token_notused;
	char *token[20][20],*pipe_token[20]; 
	my_string = (char *) malloc (nbytes + 1);
	
	while(1){
		i=0;
		j=0;
	        my_prompt();
		//READING INPUT USING GETLINE
  		bytes_read = getline (&my_string, &nbytes, stdin);
		if (bytes_read == -1)
    		{
      			puts ("ERROR!");
    		}
		my_string[strlen(my_string)-1]='\0';
		
		//SEPERATING USING PIPE AS DELIMITER
		do
		{
			if(i==0)		
				pipe_token[i]=strtok_r(my_string,"|",&not_used);
			else
				pipe_token[i]=strtok_r(NULL,"|",&not_used);
			i++;	
			
		}while(pipe_token[i-1]!=NULL);
		int temp_size=i-1;
		
		i=0;		
		//SEPERATING USING SPACE AS DELIMITER
		while(i<temp_size)
		{
			do
			{
				if(j==0)
					token[i][j]=strtok_r(pipe_token[i]," ",&token_notused);
				else
					token[i][j]=strtok_r(NULL," ",&token_notused);
				j++;
			}while(token[i][j-1]!=NULL);
			i++;
			j=0;
			
		}
		int num_pipes =i-1;
		
		//CHECKING FOR INSTRUCTIONS.
		//ENTER 
		if(token[0][0]==NULL)
		{
			continue;		
		}	
		//EXIT
		else if(!strcmp(token[0][0],"exit"))
			exit(1);
		else if(!strcmp(token[0][0],"cd"))
		{
			
			chdir(token[0][1]);
			continue;
		}	
		//OTHER INPUT INSTRS.		
		else
		{
			i=0;
			while(i<=num_pipes)
			{
				j=0;
				while(token[i][j]!=NULL)
				{
					if(!strcmp(token[i][j],"&"))
					{
						token[i][j]=NULL;
						background=1;
						break;
					}	
					else 
						j++;
				}
				if(pipe(fd)){
					printf("Error in creating a pipe");
					break;				
				}
				pid=fork();
				
				if(pid==-1)
				{
					fprintf(stderr,"fork failed\n");
					exit(1);
				}
				else if(pid == 0)
				{	
					
					if(num_pipes>0)
					{
						if(i<num_pipes){
								
							close(fd[0]);
							dup2(pre_fd, STDIN_FILENO);
		      					close(pre_fd);
							
    					       		dup2(fd[1], STDOUT_FILENO);
               						close(fd[1]);
							
                				}
						else if(i==num_pipes){
							dup2(pre_fd, STDIN_FILENO);
            						close(pre_fd);
							dup2(STDOUT_FILENO,STDOUT_FILENO);
							
						}						
					}
					
					execvp(token[i][0],token[i]);
							
					
				}
				else 
				{	if(i<num_pipes){
						pre_fd=fd[0];
						close(fd[1]);
					}
					if(background==1)
					{
						background=0;
					}	
					else if (background==0 || !strcmp(token[i][0],"clean"))
					{
						wait(NULL);
					}
				
				
				}
			i++;	
			}
		
		}
							
		
	}
}	





	








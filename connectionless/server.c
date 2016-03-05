/*
**D.vamsikrishna
**CS09B006
** listener.c -- a datagram sockets "server" demo
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include "Bsearch.c"
//#define MYPORT "4950"
// the port users will be connecting to
#define MAXDATASIZE_INPUT 9
#define MAXDATASIZE_OUTPUT 100
// get sockaddr, IPv4 or IPv6:
int unreliable_recvfrom(int sockfd, void *buf, size_t buf_len , int flags, struct sockaddr *their_addr, socklen_t *addr_len , double prob)
{

    int random = rand()%100;
    printf("%d\n",random);
    int numbytes = recvfrom( sockfd, buf, buf_len, flags, their_addr, addr_len );
    if(random < 100*prob )
    {
        char * buffer = (char*) buf;
        buffer[0] = '\0';
        return -2;
    }
    return numbytes;    
}

void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
int main(int argc , char** argv)
{
		node *bst=NULL;
		FILE *fp;
		int i,j;
		fp = fopen ("database" ,"r");
    	char temp_name[50];
    	node *temp_node = (node*) malloc(sizeof(node));
    	while (fscanf (fp, "%s", temp_node->roll_no) != EOF)
    	{
    	    fgets(temp_name , 50 , fp);
   	    	temp_node->name[0] = '\0';
            char* tmp = strtok(temp_name , " ,\t");
        	while(tmp!=NULL)
        	{
                strcat(temp_node->name , tmp);
        	    strcat(temp_node->name , " ");
        	    tmp = strtok(NULL , " ,\t");
        	 }

       	 	//printf("%s %s \n", temp_node->roll_no, temp_node->name);
       		for (i = 0; temp_node->roll_no[i] != '\0'; i++){
       	     	temp_node->roll_no[i] = (char)tolower(temp_node->roll_no[i]);
       	 	}
       	 	bst = insert(temp_node , bst);
       	 	temp_node = (node*) malloc(sizeof(node));
    	}
	    fclose(fp);
		int sockfd;
		struct addrinfo hints, *servinfo, *p;
		int rv;
		int numbytes;
		struct sockaddr_storage their_addr;
		char buf[MAXDATASIZE_INPUT],name[MAXDATASIZE_OUTPUT];
		socklen_t addr_len;
		char s[INET6_ADDRSTRLEN];
		if(argc!=3)
	    {
		        fprintf(stderr, "./server <port> probability_of_dropping\n");
		        exit(0);

	    }
		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_flags = AI_PASSIVE; // use my IP
		if ((rv = getaddrinfo(NULL, argv[1], &hints, &servinfo)) != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
			return 1;
		}
// loop through all the results and bind to the first we can
		for(p = servinfo; p != NULL; p = p->ai_next) {
			if ((sockfd = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol)) == -1) {
				perror("listener: socket");
				continue;
			}
			if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
				close(sockfd);
				perror("listener: bind");
				continue;
			}
			break;
		}
		if (p == NULL) {
			fprintf(stderr, "listener: failed to bind socket\n");
			return 2;
		}
		freeaddrinfo(servinfo);
	    while(1)
	    {
	        printf("server: waiting to recvfrom...\n");
	
	        addr_len = sizeof their_addr;
	        if ((numbytes = unreliable_recvfrom(sockfd, buf, MAXDATASIZE_INPUT , 0,            //recvfrom() with a probability of dropping
		        (struct sockaddr *)&their_addr, &addr_len,atof(argv[2]))) == -1) 
	        {
	            perror("server : recvfrom");
	            exit(0);
	        }
	        else if(numbytes == -2)
	        {
	            perror("\nserver : packet dropped"); 
		     if ((numbytes = sendto(sockfd, "dropped", MAXDATASIZE_OUTPUT, 0,
			(struct sockaddr *)&their_addr, addr_len)) == -1) 
		     {
			perror("server : sentto");
			exit(0);
		     }
	            continue;
	        }        
	        printf("server: got packet from %s\n", inet_ntop(their_addr.ss_family,       //get the ip address of sender
	        get_in_addr((struct sockaddr *)&their_addr), s, sizeof s));
	
	        printf("server: packet received is %d bytes long\n", numbytes);
	        buf[numbytes] = '\0';
	        printf("server: packet received contains \"%s\"\n", buf);
	
	        //printf(" desired roll number %s \n" , buf);
	        strcpy( name , get_name(bst , buf));

	        if ((numbytes = sendto(sockfd, name, MAXDATASIZE_OUTPUT, 0,
	        (struct sockaddr *)&their_addr, addr_len)) == -1) 
	        {
	            perror("server : sentto");
	            exit(0);
	        }

	        printf("server: packet sent is %d bytes long\n\n\n", numbytes);
	    }

	    close(sockfd);
		return 0;
}


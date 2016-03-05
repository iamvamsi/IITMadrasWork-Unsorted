/*
**D.vamsikrishna
**CS09B006
** talker.c -- a datagram "client" demo
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
#define MAXDATASIZE_INPUT 9
#define MAXSIZE 100
//#define SERVERPORT "4950"
// the port users will be connecting to
int main(int argc, char *argv[])
{
	int sockfd;
	char buf[MAXSIZE],input[MAXDATASIZE_INPUT];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	int numbytes;
	struct sockaddr servaddr;
	socklen_t len_sockaddr=sizeof (struct sockaddr);
	if (argc != 3) {
		fprintf(stderr,"usage: serverip/address serverport\n");
		exit(1);
	}
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	// loop through all the results and make a socket
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
		p->ai_protocol)) == -1) {
			perror("talker: socket");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "talker: failed to bind socket\n");
		return 2;
	}
	freeaddrinfo(servinfo);
	printf("Client:Enter to 'q' to stop searching\n\n");
	while(1){
	fputs("Client:Enter some roll number: \n", stdout);
	scanf("%s",input);
	input[MAXDATASIZE_INPUT]='\0';
	//printf("The input is %s\n",input);
	//if(input[0]=='\n')
	//continue ;
	if(strcmp(input,"q")==0)
	  break;
	if ((numbytes = sendto(sockfd, input, MAXDATASIZE_INPUT, 0,p->ai_addr, p->ai_addrlen)) == -1) {
		perror("talker: sendto");
		exit(1);
	}
	//printf("talker: sent %d bytes to %s\n", numbytes, argv[1]);
	recvfrom(sockfd,buf,MAXSIZE,0,(struct sockaddr *)&servaddr, &len_sockaddr);
	if(strcmp(buf,"dropped")==0)
	    printf("Client:The packet sent was dropped .So aborting and starting again\n");
	else 
	    printf("Client:%s\n",buf);
	}
	
	close(sockfd);
	return 0;
}
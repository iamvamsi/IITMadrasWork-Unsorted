/*
** client.c -- a stream socket client demo
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#define MAXDATASIZE_INPUT 100
//#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once
// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
int main(int argc, char *argv[])
{
	int sockfd, numbytes;
	char buf[MAXDATASIZE];
	struct addrinfo hints, *servinfo, *p;
	int rv;
	char s[INET6_ADDRSTRLEN];
	if (argc != 3) {
		fprintf(stderr,"usage: client hostname port_of_server_to_connect_to\n");
		exit(1);
	}
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
        // loop through all the results and connect to the first we can
	for(p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
		p->ai_protocol)) == -1) {
			perror("client: socket");
			continue;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}
	if (p == NULL) {
		fprintf(stderr, "client: failed to connect\n");
		return 2;
	}
	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
	s, sizeof s);
	printf("client: connecting to %s\n", s);
	freeaddrinfo(servinfo); // all done with this structure
	char input[MAXDATASIZE_INPUT];
	printf("Client:Enter to 'q' to stop searching\n\n");
	while(1){
	printf("Enter the path address of a file at the server: ");
	//fflush(stdout); 
	//fgets(input, sizeof input, stdin);
	scanf("%s",input);
	input[MAXDATASIZE_INPUT]='\0';
	//printf("%s\n",input);
	if(strcmp(input,"q")==0)
	  break;
	if (send(sockfd,input,MAXDATASIZE_INPUT, 0) == -1)
		perror("send");
	/*if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("client: received '%s'\n",buf);
	//if(strcmp(buf,"NoSuchFile")==0){
	//	exit(1);
	//}*/
	printf("client: received \n");	
	while(1){
			if ((numbytes = recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
				perror("recv");
				exit(1);
			}
			if(numbytes<=0){
				printf("\nFile Ends\n");
				exit(1);
				//break;
			}
			printf("%s",buf);	
		}
	}
	close(sockfd);
	return 0;
}


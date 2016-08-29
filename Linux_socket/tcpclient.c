#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	
	if(argc <= 2)
	{
		printf("please input server ip and port number\r\n");
		return -1;
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&server_address.sin_addr);
	server_address.sin_port = htons(port);

	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		printf("socket create failed \r\n");
		return -1;
	}

	if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address))<0)
	{
		printf("connect failed \r\n");
		return -1;
	}
	else
	{
		char data[64]="Where are you from ?";
		char buffer[64];
		int i,len;

		for(i=0;i<10;i++)
		{
			memset(buffer,0x00,sizeof(buffer));
			send(sockfd,data,strlen(data),0);
			len = recv(sockfd,buffer,sizeof(buffer),0);
			sleep(1);
			printf("index is %d len is %d : %s\r\n",i,len,buffer);
		}
	}
	close(sockfd);
	return 0;
	}

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char* argv[])
{
	
	if(argc <=2 )
	{
		printf("please input ipaddress and port number\r\n");
		return -1;
	}

	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock <0)
	{
		printf("create sock failed \r\n");
		return -1;
	}

	int ret = bind(sock,(struct sockaddr*)&address,sizeof(address));
	if(ret == -1)
	{
		printf("bind failed\r\n");
		return -1;
	}

	ret = listen(sock,5);
	if(ret == -1)
	{
		printf("listen failed \r\n");
		return -1;
	}

	struct sockaddr_in client;
	socklen_t client_addrlength = sizeof(client);
	int connfd = accept(sock,(struct sockaddr*)&client,&client_addrlength);
	if(connfd < 0)
	{
		printf("accept failed \r\n");

	}
	else
	{
		char data[64]="I am from jikexueyuan!";
		char buffer[64];
		int i,len;
		
		for(i=0;i<10;i++)
		{
			memset(buffer,0x00,sizeof(buffer));
			len = recv(connfd,buffer,sizeof(buffer),0);
			printf("index is %d len is %d: %s\r\n",i,len,buffer);
			sleep(1);
			send(connfd,data,strlen(data),0);
		}
		close(connfd);
	}
	close(sock);
	return 0;
}

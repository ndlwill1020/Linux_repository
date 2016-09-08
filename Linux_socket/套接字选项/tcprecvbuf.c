#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024
//一般用于服务器
int main(int argc,char* argv[])
{
	if(argc <= 2)
	{
		printf("please input ip address and port number!\r\n");
		return -1;
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&server_address.sin_addr);
	server_address.sin_port = htons(port);

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		printf("create socket failed !\r\n");
		return -1;
	}
	
	int recvbuf = atoi(argv[3]);
	int len = sizeof(recvbuf);

	setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&recvbuf,sizeof(recvbuf));

	getsockopt(sock,SOL_SOCKET,SO_RCVBUF,&recvbuf,(socklen_t*)&len);

	printf("the tcp receive buffer size after setting is %d\r\n",recvbuf);

	int ret = bind(sock,(struct sockaddr*)&server_address,sizeof(server_address));

	if(ret == -1)
	{
		printf("bind failed !\r\n");
		return -1;
	}

	ret = listen(sock,5);
	if(ret == -1)
	{
		printf("listen failed !\r\n");
		return -1;
	}

	struct sockaddr_in client;
	socklen_t client_len = sizeof(client);
	int connfd = accept(sock,(struct sockaddr*)&client,&client_len);

	if(connfd < 0)
	{
		printf("accept failed !\r\n");	
	}
	else
	{
		char buffer[BUFFER_SIZE];
		memset(buffer,0x00,sizeof(buffer));
		while(recv(connfd,buffer,BUFFER_SIZE,0) > 0) {}
		close(connfd);
	}
	close(sock);
	return 0;

}

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

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
	//设置套接字发送缓冲区大小
	int sendbuf = atoi(argv[3]);
	int len = sizeof(sendbuf);

	setsockopt(sock,SOL_SOCKET,SO_SNDBUF,&sendbuf,sizeof(sendbuf));
	//验证设置的大小是否正确
	getsockopt(sock,SOL_SOCKET,SO_SNDBUF,&sendbuf,(socklen_t*)&len);

	printf("tcp send buffer size after setting is %d\r\n",sendbuf);

	if(connect(sock,(struct sockaddr*)&server_address,sizeof(server_address)) != -1)
	{
		char buffer[BUFFER_SIZE];
		memset(buffer,'a',BUFFER_SIZE);
		send(sock,buffer,BUFFER_SIZE,0);
	}
	close(sock);
	return 0;
}

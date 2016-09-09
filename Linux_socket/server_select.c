#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
	if(argc <= 2)
	{
		printf("please input ip address and port num\r\n");
		exit(1);
	}
	const char* ip = argv[1];
	int port = atoi(argv[2]);

	int ret = 0;
	struct sockaddr_in address;
	bzero(&address,sizeof(address));
	address.sin_family = AF_INET;
	inet_pton(AF_INET,ip,&address.sin_addr);
	address.sin_port = htons(port);

	int listenfd = socket(AF_INET,SOCK_STREAM,0);
	assert(listenfd >= 0);

	ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);
	
	ret = listen(listenfd,5);
	assert(ret != -1);

	struct sockaddr_in client_address;
	socklen_t client_addresslen = sizeof(client_address);
	int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addresslen);
	if(connfd < 0)
	{
		printf("accept error\r\n");
		exit(1);

	}
	
	char buf[1024];
	fd_set read_fds;//普通数据放在可读集合中
	fd_set exceptions_fds;//带外数据放在异常集合中

	FD_ZERO(&read_fds);
	FD_ZERO(&exceptions_fds);

	while(1)
	{
		memset(buf,0x00,sizeof(buf));
		//把套接字放入两个集合  因为我们要关注这个套接字上面的可读事件和异常事件
		FD_SET(connfd,&read_fds);
		FD_SET(connfd,&exceptions_fds);
		ret = select(connfd+1,&read_fds,NULL,&exceptions_fds,NULL);

		if(ret < 0)
		{
			printf("select error\r\n");
			exit(1);
		}
		
		if(FD_ISSET(connfd,&read_fds))
		{
			ret = recv(connfd,buf,sizeof(buf)-1,0);//接收普通数据
			if(ret <= 0)//对端发生关闭或发送失败
			{
				break;	
			}
			printf("recv data form %d  and buf is %s\r\n",connfd,buf);
		}
		else if(FD_ISSET(connfd,&exceptions_fds))//接收带外数据
		{
			ret = recv(connfd,buf,sizeof(buf)-1,MSG_OOB);
			if(ret <=0 )
			{
				break;	
			}
			printf("recv oob data fomr %d and buf is %s\r\n",connfd,buf);
		}
	}
	close(connfd);
	close(listenfd);
	return 0;
}


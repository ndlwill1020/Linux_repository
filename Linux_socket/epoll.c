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
#include <sys/epoll.h>
#include <pthread.h>

#define MAX_SOCKET_NUMBERS 1024
#define BUF_SIZE 1024

int setnonblocking(int fd);
void addfd(int epollfd,int fd, int flag);
void lt(struct epoll_event* events,int number,int epollfd,int listenfd);
void et(struct epoll_event* events,int number,int epollfd,int listenfd);

//把监听套接字和连接套接字 托给epoll管理
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

	int listenfd = socket(AF_INET,SOCK_STREAM,0);//监听套接字
	assert(listenfd >= 0);

	ret = bind(listenfd,(struct sockaddr*)&address,sizeof(address));
	assert(ret != -1);

	ret = listen(listenfd,5);
	assert(ret != -1);

	struct epoll_event events[MAX_SOCKET_NUMBERS];
	int epollfd = epoll_create(5);
	assert( epollfd != -1);

	addfd(epollfd,listenfd,1);//把监听套接字托管给epoll

	while(1)
	{
		int ret = epoll_wait(epollfd,events,MAX_SOCKET_NUMBERS,-1);//-1表示一直阻塞，直到有就绪的描述符  events就绪事件的队列

		//ret就绪事件的个数
		if(ret < 0)
		{
			printf("epoll_wait error\r\n");
			exit(1);
		}

		lt(events,ret,epollfd,listenfd);
		// et(events,ret,epollfd,listenfd);
	}
	close(listenfd);
	return 0;

}
int setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
	return new_option;
}

//flag lt模式还是et模式
void addfd(int epollfd,int fd,int flag)
{
	struct epoll_event event;
	memset(&event,0x00,sizeof(event));
	event.data.fd = fd;
	event.events = EPOLLIN;
	if(flag )
	{
		event.events |= EPOLLET;//默认lt模式
	}
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&event);
	setnonblocking(fd);
}

void lt(struct epoll_event* events,int number ,int epollfd,int listenfd)
{
	char buf[BUF_SIZE];
	int i;	
	for(i=0;i<number;i++)
	{
		int sockfd = events[i].data.fd;
		if(sockfd == listenfd)
		{
			struct sockaddr_in client_address;
			socklen_t client_addresslen = sizeof(client_address);
			int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addresslen);
			if(connfd < 0)
			{
				printf("accept error\r\n");
				exit(1);
			}
			addfd(epollfd,connfd,0);
		}
		else if(events[i].events & EPOLLIN)//可读事件
		{
			printf("LT once\r\n");
			memset(buf,0x00,sizeof(buf));
			int ret = recv(sockfd,buf,sizeof(buf)-1,0);
			if(ret <=0)
			{
				printf("recv 0\r\n");
				close(sockfd);
				continue;
			}
			printf("recv data form %d buf is %s\r\n",sockfd,buf);
		}
		else
		{
			printf("somthing else happen\r\n");	
		}

	}
}

void et(struct epoll_event* events,int number,int epollfd,int listenfd)
{
	char buf[BUF_SIZE];
	int i;
	for(i=0;i<number;i++)
	{
		int sockfd = events[i].data.fd;
		if(sockfd == listenfd )//如果就绪的是监听套接字
		{
			struct sockaddr_in client_address;
			socklen_t client_addresslen = sizeof(client_address);
			int connfd = accept(listenfd,(struct sockaddr*)&client_address,&client_addresslen);
			addfd(epollfd,connfd,0);//把连接套接字托管给epoll
		}
		else if(events[i].events & EPOLLIN)
		{
			printf("ET once\r\n");
			while(1)//这里面必须把事件处理了
			{
				memset(buf,0x00,sizeof(buf));
				int ret = recv(sockfd,buf,sizeof(buf)-1,0);
				if(ret < 0)
				{
					//发生中断EAGAIN
					if((errno == EAGAIN ) || (errno == EWOULDBLOCK))
					{
						printf("read later\r\n");
						break;
					}
					close(sockfd);
					break;
				}
				else if(ret == 0)
				{
					close(sockfd);
				}
				else
				{
					printf("recv data from %d buf is %s\r\n",sockfd,buf);
				}
			}
		}
		else
		{
			printf("somthin else happen\r\n");	
		}
	}
}

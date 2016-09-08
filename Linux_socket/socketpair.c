#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
	int fd[2];
	int ret = socketpair(AF_UNIX,SOCK_STREAM,0,fd);//创建的fd对，在父子进程中都存在
	if(ret < 0)
	{
		perror("socketpair() error\r\n");
		exit(1);
	}
	//fork会产生两个返回值，对于父进程它的返回值大于0，子进程返回值等于0
	if(fork())//父进程操作
	{
		printf("parent process \r\n");
		int val = 0;
		close(fd[1]);
		while(1)
		{
			sleep(1);
			++val;
			printf("send val to child : %d\r\n",val);
			write(fd[0],&val,sizeof(val));
			read(fd[0],&val,sizeof(val));
			printf("read val from child : %d \r\n",val);
		}
	}
	else//子进程操作
	{
		printf("child process \r\n");
		int val;
		close(fd[0]);

		while(1)
		{
			read(fd[1],&val,sizeof(val));
			++val;
			write(fd[1],&val,sizeof(val));
		}
	}
}


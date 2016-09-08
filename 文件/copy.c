#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#define MAX (256) //每次读写的字节数（缓冲区大小）
int main(int argc,char **argv)
{
	//拷贝test.mp4 到 new.mp4中
	//打开文件，源  目的
	int fd_s = -1;//源文件  描述字
	int fd_d = -1;//目标文件 描述字
	int ret = -1;
	fd_s = open("copy.c",O_RDONLY);//流  r    打开源文件
	if (-1 == fd_s )
	{
		perror("open file");
		return -1;
	}

	fd_d = open("new.c",O_WRONLY|O_TRUNC|O_CREAT,0777);//流  w   打开目标文件
	if (-1 == fd_d )
	{
		perror("open");
		return -1;
	}

	//分配内存
	char *mem = NULL;
	mem = malloc(MAX);
	if ( NULL == mem )
	{
		perror("malloc");
		return -1;
	}
	memset(mem,'\0',MAX);
	//(读取－》写入)
	while(1)
	{
		
		ret = read(fd_s,mem,MAX);
		printf("read: %dbytes\n",ret);
		if( -1 == ret )
		{
			perror("read");
			return -1;
		}
		if( 0 == ret )
		{
			break;
		}
		ret = write(fd_d,mem,ret);
		if( -1 == ret )
		{
			perror("write");
			return -1;
		}
	}
	//释放内存
	free(mem);
	//关闭文件 
	close(fd_s);
	close(fd_d);
	return 0;
}	


//time ./a.out查看时间
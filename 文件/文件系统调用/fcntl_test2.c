#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
int main(int argc,char **argv)
{
	//重定位  标准输出  ————》文件
	//
	int ret = -1;
	int fd = -1;
#if 1
	fd = open("log",O_CREAT|O_TRUNC|O_RDWR);
	if ( -1 == fd )
	{
		perror("open");
		return -1;
	}
	close(1);
	ret = fcntl(fd,F_DUPFD,1);//标准输出 重定位到 文件
	//ret = dup2(fd,1);//标准输出 重定位到 文件
	if ( -1 == ret )
	{
		perror("dup");
		return -1;
	}
#endif

	printf("hellworld\n");

	close(fd);
	return 0;
}

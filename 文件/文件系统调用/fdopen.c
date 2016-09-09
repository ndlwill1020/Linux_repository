#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char **argv)
{
	int ret = -1;
	int fd = -1;
	//打开文件b.c
	fd = open("b.c",O_RDWR);//流  r+
	//ret = open("b.c",O_RDWR|O_TRUNC);//流  w+
	//ret = open("b.c",O_RDWR|O_APPEND);//流  a+
	if( -1 == fd )
	{
		perror("create");
		return -1;
	}
	FILE *fp;
	//文件描述字转化为流
	fp = fdopen(fd,"r+");

	if( NULL == fp )
	{
		perror("fdopen");
		return -1;
	}
	// 用流  写入数据
	ret = fwrite("hello",1,5,fp);
	if ( -1 == ret )
	{
		perror("fwrite");
		return -1;
	}
	fflush(fp);
	ret = write(fd," world",7);
	if ( -1 == ret )
	{
		perror("fwrite");
		return -1;
	}
	close(ret);
	return 0;
}	

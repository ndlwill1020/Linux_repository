#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv)
{
	//拷贝test.mp4 到 new.mp4中
	//打开文件，源  目的
	int fd_s = -1;//源文件  描述字
	int fd_d = -1;//目标文件 描述字
	int ret = -1;
	fd_s = open("test.mp4",O_RDONLY);//流  r    打开源文件
	if (-1 == fd_s )
	{
		perror("open");
		return -1;
	}

	fd_d = open("new.mp4",O_WRONLY|O_TRUNC|O_CREAT,0777);//流  w   打开目标文件
	if (-1 == fd_d )
	{
		perror("open");
		return -1;
	}
	//计算出源文件大小
	// 源文件定位到尾部， 计算出大小
	long file_size = -1;
	file_size = lseek(fd_s,0,SEEK_END);
	if( -1 == file_size )
	{
		perror("lseek");
		return -1;
	}
	// 源文件定位到头部
	ret = lseek(fd_s,0,SEEK_SET);
	if( -1 == ret )
	{
		perror("lseek");
		return -1;
	}

	//分配内存
	char *mem = NULL;
	mem = malloc(file_size);
	if ( NULL == mem )
	{
		perror("malloc");
		return -1;
	}
	memset(mem,'\0',file_size);
	//(读取－》写入)
	//while(1)
//	{
		ret = read(fd_s,mem,file_size);
		if( -1 == ret )
		{
			perror("read");
			return -1;
		}
		if( 0 == ret )
		{
//			break;
		}
		ret = write(fd_d,mem,ret);
		if( -1 == ret )
		{
			perror("write");
			return -1;
		}
//	}
	//释放内存
	free(mem);
	//关闭文件 
	close(fd_s);
	close(fd_d);
	return 0;
}	

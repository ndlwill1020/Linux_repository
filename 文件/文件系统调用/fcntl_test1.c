#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc,char **argv)
{
	int ret = -1;
	int fd = -1;
	fd = fcntl(1,F_DUPFD,0);//等价于下面，完成文件描述字的复制
//	fd = dup(1);//1 --- > 标准输出
	if ( -1 == fd )
	{
		perror("dup");
		return -1;
	}
	//写入fd － 》 1（标准输出）－》显示
	ret = write(fd,"hello",5);
	if ( -1 == ret )
	{
		perror("write");
		return -1;
	}
	close(fd);
	return 0;
}

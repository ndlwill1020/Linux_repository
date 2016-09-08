#include <stdio.h>
int main(int argc,char **argv)
{
	int ret = -1;
	int fd = -1;
	fd = dup(1);//1 --- > 标准输出   dup：复制1（标准输出）给fd
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

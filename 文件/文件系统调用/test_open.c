#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
int main(int argc,char **argv)
{
	int ret = -1;
	//文件存在打开（不清空文件）,不存在就创建打开
	//创建新文件b.c，权限读写执行都有,并且打开文件
	ret = open("b.c",O_RDWR|O_CREAT|O_EXCL,0777);
	if( -1 == ret )
	{
		if ( EEXIST == errno )//是否存在,存在不清空打开
		{
			ret = open("b.c",O_RDWR);
			if ( -1 == ret )
			{
				perror("open");
				return -1;
			}
		}
		return -1;
	}
	close(ret);
	return 0;
}	

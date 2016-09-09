#include <stdio.h>
int main(int argc,char **argv)
{
	//测试标准输入流 stdin(man stdin查看帮助文档) 对应的文件描述字
	int fd = -1;
	fd = fileno(stdin);
	if( -1 == fd )
	{
		perror("fileno");
		return -1;
	}

	printf("%d\n",fd);
	return 0;
}

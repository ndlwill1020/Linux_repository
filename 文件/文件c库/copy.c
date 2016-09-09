#include <stdio.h>
#include <stdlib.h>  //man free, man malloc
#include <string.h>
int main(int argc,char **argv)
{
	int ret = -1;
	//拷贝 源文件（source.c）到目标文件（dst.c)
	FILE *fp_s = NULL;//源文件流
	fp_s = fopen("source.c","r");//只读 r
	if ( NULL == fp_s )
	{
		perror("fopen source.c");
		return -1;
	}

	FILE *fp_d = NULL;//目标文件流
	fp_d = fopen("dst.c","w");//写w 
	if ( NULL == fp_d )
	{
		perror("fopen dst.c");
		return -1;
	}


	//准备内存
	char *buff = NULL;
	buff = malloc(20);//堆  20字节
	if( NULL == buff )
	{
		perror("malloc buff");
		return -1;
	
	}
	while(1)
	{
		memset(buff,'\0',20);//内存每次完成后清0
		//读 
		//从源文件的默认光标（文件位置处）读取一个长度信息，存放到用户内存里面
		ret = fread(buff,1,20,fp_s);
		if ( 20 > ret )
		{
			if ( feof(fp_s))//ferror
			{
				//文件尾

				ret = fwrite(buff,1,ret,fp_d);
				if ( 0 == ret )
				{
					//bug...
					perror("fwrite");
					return -1;
				}
				break;
			}else
			{
				//出错
				perror("fread");
				return -1;

			}
		}
		//写
		//
		ret = fwrite(buff,1,ret,fp_d);
		if ( 0 == ret )
		{
			//bug...
			perror("fwrite");
			return -1;
		}

		//test
		//fflush(fp_d);
		//while(1);//ctrl+c 程序异常退出
	}

	free(buff);
	buff = NULL;
	fclose(fp_s);
	fp_s = NULL;
	fclose(fp_d);
	fp_d = NULL;
}

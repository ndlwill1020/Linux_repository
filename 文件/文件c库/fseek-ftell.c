#include <stdio.h>
#include <stdlib.h>  //man free, man malloc
#include <string.h>
int main(int argc,char **argv)
{

	//一次性完成数据的传递
	//
	//计算出源文件的大小
	//
	//准备一个合适的内存，大小（源文件本身大小）
	//
	//一次性读取源文件
	//一次性写入源文件
	//
	//关闭

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
	//计算出源文件的大小
	ret = fseek(fp_s,0,SEEK_END);//定位到文件尾部
	if ( -1 == ret )
	{
		perror("fseek");
		return -1;
	}
	long file_size;
	file_size = ftell(fp_s);//计算出大小
	if ( -1 == file_size )
	{
		perror("ftell");
		return -1;
	}
	//文件位置－－－文件头
	ret = fseek(fp_s,0,SEEK_SET);
	if ( -1 == ret )
	{
		perror("fseek");
		return -1;
	}
	//准备一个合适的内存，大小（源文件本身大小）
	buff = malloc(file_size);//堆 
	if( NULL == buff )
	{
		perror("malloc buff");
		return -1;

	}
	memset(buff,'\0',file_size);//内存每次完成后清0
	//读 
	//从源文件的默认光标（文件位置处）读取一个长度信息，存放到用户内存里面
	ret = fread(buff,1,file_size,fp_s);
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

	free(buff);
	buff = NULL;
	fclose(fp_s);
	fp_s = NULL;
	fclose(fp_d);
	fp_d = NULL;
}

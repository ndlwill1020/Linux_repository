//
//  main.c
//  Domain2NetworkByteOrder
//
//  Created by macuser on 16/6/13.
//  Copyright © 2016年 ndl. All rights reserved.
//

#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
//cd 可执行文件路径    ./可执行文件 www.baidu.com
int main(int argc, const char * argv[]) {
    printf("test!!!\n");
    
    char **aliases;//别名s
    char **addrs;//地址s
    char str[64];
    struct hostent *hptr;
    
    if (argc < 2) {
        fprintf(stderr, "usage:domain <domain>\n");
        return -1;
    }
    
    if ((hptr = gethostbyname(argv[1])) == NULL) {//获得DNS信息
        fprintf(stderr, "gethostbyname call failed. %s\n",hstrerror(h_errno));
        return -1;
    }
    
    printf("正式名:%s\n",hptr->h_name);
    for (aliases = hptr->h_aliases; *aliases != NULL; aliases++) {
        printf("\t 别名:%s\n",*aliases);
    }
    
    if (hptr->h_addrtype != AF_INET) {
        fprintf(stderr, "地址类型:%d\n",hptr->h_addrtype);
        return -1;
    }
    
    
    for (addrs = hptr->h_addr_list; *addrs != NULL; addrs++) {
        printf("\t address:%s\n",inet_ntop(hptr->h_addrtype, *addrs, str, sizeof(str)));//将网络字节序转换成字符串 *addrs是个char *类型 就是最终输出的字符串
    }
    
    return 0;
}

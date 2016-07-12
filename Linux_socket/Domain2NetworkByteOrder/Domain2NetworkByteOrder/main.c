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
        
        printf("str:%s\n",str);
    }
    printf("===============我是分割线===============\n");
    char ip1[16] = {0};
    char ip2[16] = {0};
    inet_ntop(hptr->h_addrtype, (hptr->h_addr_list)[0], ip1, sizeof(ip1));
    inet_ntop(hptr->h_addrtype, (hptr->h_addr_list)[1], ip2, sizeof(ip2));
    printf("addr:%s\n",(hptr->h_addr_list)[0]);//乱码
    printf("ip1:%s ip2:%s\n",ip1,ip2);
    
    
    printf("===============我是分割线===============\n");
    unsigned char* p = (unsigned char *)(hptr->h_addr_list)[0];
    if( p != NULL )
    {
        char ip[16] = {0};
        sprintf(ip, "%u.%u.%u.%u", p[0], p[1], p[2], p[3]);
        printf("ip:%s\n",ip);
    }
    
    printf("===============我是分割线===============\n");
    struct addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    
    struct addrinfo* answer = NULL;
    getaddrinfo(argv[1], NULL, NULL, &answer);
    char hostname[1025] = "";
    
    getnameinfo(answer->ai_addr,answer->ai_addrlen,hostname,1025,NULL,0,0);
    char ipv6[128] = "";
    memcpy(ipv6,hostname,128);
    printf("hostname:%s\n",hostname);
    
    return 0;
}

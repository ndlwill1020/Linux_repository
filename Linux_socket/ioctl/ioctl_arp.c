#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <string.h>

int main(int argc,char* argv[])
{
	
	int s;
	struct arpreq arpreq;
	struct ifreq ifr;
	struct sockaddr_in* addr = (struct sockaddr_in*)&arpreq.arp_pa;

	unsigned char* hw;
	int err = -1;
	if(argc<2)
	{
		printf("please input ip address !\r\n");
		return 0;
	}
	
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s<0)
	{
		printf("create socket failed !\r\n");
		return 0;
	}
	addr->sin_family = AF_INET;
	inet_pton(AF_INET,argv[1],&addr->sin_addr);
	if(addr->sin_addr.s_addr == INADDR_NONE)
	{
		printf("ip address error!\r\n");
		return -1;
	}

	strcpy(arpreq.arp_dev,"eth0");
	err = ioctl(s,SIOCGARP,&arpreq);
	if(err == -1)
	{
		printf("ioctl failed !\r\n");
		
	}
	else
	{
		hw = (unsigned char*)&arpreq.arp_ha.sa_data;
		printf("%s:  ",argv[1]);
		printf("%02x:%02x:%02x:%02x:%02x:%02x\r\n",hw[0],hw[1],hw[2],hw[3],hw[4],hw[5]);
	}
	close(s);
	return 0;
}

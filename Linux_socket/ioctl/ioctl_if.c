#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if_arp.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>

int main()
{
	int s;
	int err = -1;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s < 0)
	{
		printf("socket create faield !\r\n");
		return -1;
	}

	struct ifreq ifr;
	strcpy(ifr.ifr_name,"eth0");
	err = ioctl(s,SIOCGIFFLAGS,&ifr);
	if(err == -1)
	{
		printf("ioctl failed 0 \r\n");
		return -1;
	}
	else
	{
		printf("SICGIFFLAGS:%d\r\n",ifr.ifr_flags);	
	}

	/*   获取 MTU    */
	err = ioctl(s,SIOCGIFMTU,&ifr);
	if(err == -1)
	{
		printf("ioctl failed 1 !\r\n");
		return -1;
	}
	else
	{
		printf("SIOCGIFMTU:%d\r\n",ifr.ifr_mtu);	
	}

	/*获取 MAC ADDRESS*/
	err = ioctl(s,SIOCGIFHWADDR,&ifr);
	if(err == -1)
	{
		printf("ioctl failed 2! \r\n");
		return -1;
	}
	else
	{
		unsigned char* hw = ifr.ifr_hwaddr.sa_data;
		printf("SIOCGIFADDR:%02x:%02x:%02x:%02x:%02x:%02x\r\n",hw[0],hw[1],hw[2],hw[3],hw[4],hw[5]);
	}

	close(s);
	return  0;
}

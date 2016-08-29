#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT_SERVER 8888

int main(int argc,char* argv[])
{
	int s;
	struct sockaddr_in addr_server,addr_client;
	const char* ip = "192.168.80.130";

	bzero(&addr_server,sizeof(addr_server));
	inet_pton(AF_INET,ip,&addr_server.sin_addr);
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(PORT_SERVER);
	
	s = socket(AF_INET,SOCK_DGRAM,0);
	printf("s is %d \r\n",s);
	char data[64]="Where are you from ?";
	char buffer[64];
	int i;
	int len = sizeof(addr_server);

	for(i=0;i<10;i++)
	{
		memset(buffer,0x00,sizeof(buffer));
		int ret = sendto(s,data,strlen(data),0,(struct sockaddr*)&addr_server,len);
		recvfrom(s,buffer,sizeof(buffer),0,(struct sockaddr*)&addr_client,&len);
		printf("index is %d : %s \r\n",i,buffer);
		sleep(1);
	}
	close(s);
	return 0;
}

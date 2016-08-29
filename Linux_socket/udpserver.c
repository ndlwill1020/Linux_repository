#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PORT_SERVER 8888

int main(int argc,char* argv[])
{
	int s;
	struct sockaddr_in addr_server,addr_client;
	const char* ip = "192.168.80.130";

	s = socket(AF_INET,SOCK_DGRAM,0);
	memset(&addr_server,0x00,sizeof(addr_server));

	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(PORT_SERVER);

	bind(s,(struct sockaddr*)&addr_server,sizeof(addr_server));

	char data[64]="I am from jikexueyuan!";
	char buffer[64];
	int i;
	int len = sizeof(addr_server);

	for(i=0;i<10;i++)
	{
		memset(buffer,0x00,sizeof(buffer));
		recvfrom(s,buffer,sizeof(buffer),0,(struct sockaddr*)&addr_client,&len);
		printf("index is %d : %s \r\n",i,buffer);
		sendto(s,data,strlen(data),0,(struct sockaddr*)&addr_client,len);
		sleep(1);
	}
	close(s);
	return 0;
}

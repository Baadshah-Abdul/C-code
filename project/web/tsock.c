/*TCP client*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define IP "98.137.11.164" /*www.yahoo.com*/
#define PORT 80 /*http*/



int main()
{
	int s;//file descriptor
	struct sockaddr_in sock;//socket address struct
	char buf[512];//buffer for data
	char *data;//HTTP HEAD request

	data = "HEAD / HTTP/1.0\r\n\r\n";
	
	//initialize socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if( s < 0)
	{
		printf("socket() error\n");
		return -1;
	}

	//coverts from string to binary
	sock.sin_addr.s_addr = inet_addr(IP);
	//convert port number to network byte order
	sock.sin_port = htons(PORT);
	//set addr family to ipv4
	sock.sin_family = AF_INET;
	
	/*connect to server*/
	if (connect(s, (struct sockaddr *)&sock, sizeof(struct sockaddr_in)) != 0)
	{
		printf("connect() error\n");
		close(s);
		
		return -1;
	}
	
	write(s, data, strlen(data));
	memset(buf, 0, 512);

	read(s, buf, 511);
	close(s);
	printf("\n%s\n", buf);
		
	return 0;
}



/*TCP server*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8183 


int main()
{
	int s, c;//file descriptor
	socklen_t addrlen;//represent length of socket addr struct
	struct sockaddr_in srv, cli;//socket address information
	char buf[512];
	char *data;
	int n;
	//we put zero in all the variables
	addrlen = 0;
	memset(&srv, 0, sizeof(srv));
	memset(&cli, 0, sizeof(cli));
	
	//initialize socket
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		printf("socket()\n");
		return -1;
	}
	
	//fill struct sockaddr_in 
	srv.sin_family = AF_INET;//address family
	srv.sin_addr.s_addr = 0;//ipv4 addr - 32 bit
	//htons - (Host TO Network Short)used to convert 16 bit uint from host byte order to network byte order
	srv.sin_port = htons(PORT);//port number - 16 bit

	//assign local addr to socket
	if (bind(s, (struct sockaddr *)&srv, sizeof(srv)))
	{
		perror("bind()\n");
		close(s);

		return -1;
	}

	//makes socket ready to accept incomming connections
	if (listen(s, 5))
	{
		perror("listen()\n");
		close(s);

		return -1;
	}
	printf("Listening on 0.0.0.0:%d\n", PORT);
	
	//accepts incoming connecton on a listening scoket(TCP server)
	c = accept(s, (struct sockaddr *)&srv, &addrlen);
	if ( c < 0)
	{
		perror("accept()\n");
		close(c);

		return -1;
	}

	printf("Client connected\n");
	n =	read(c, buf, 511);
	data = "http v1.0\n";
	write(c, data, strlen(data));
	write(1, buf, n);

	close(c);
	close(s);

	return 0;
}










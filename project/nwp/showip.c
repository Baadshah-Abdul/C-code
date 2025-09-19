//shows IP addresses fro given on command line


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[])
{
	struct addrinfo hints, *res, *p;
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc !=2)
	{
		fprintf(stderr, "usage: input a hostname along with showip\n\reg: ./showip www.brave.com\n");
		return 1;
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; //either ipv4 or ipv6
	hints.ai_socktype = SOCK_STREAM; //TCP stream sockets

	//get ready to connect
	if((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0)
	{
		//if connection fails
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2; 
	}

	printf("IP address for %s:\n\n", argv[1]);
	//ai_next points to the next ip address
	//a host could have been assigned
	//a website can have and ipv4 and ipv6 address
	for(p = res; p != NULL; p = p->ai_next)
	{
		void *addr;
		char *ipver;
		struct sockaddr_in *ipv4;
		struct sockaddr_in6 *ipv6;

		//get the pointer t the address itself,
		//different fields in IPv4 & IPv6
		if (p->ai_family == AF_INET)//IPv4
		{
			ipv4 = (struct sockaddr_in *)p->ai_addr; //typecast to struct sockaddr* to struct sockaddr_in (ipv4) pointer
			addr = &(ipv4->sin_addr);
			ipver = "IPv4";
		}
		else
		{
			ipv6 = (struct sockaddr_in6 *)p->ai_addr; //typecast to struct sockaddr* to struct sockaddr_in6 (ipv6) pointer
			addr = &(ipv6->sin6_addr);
			ipver = "IPv6";
		}

		//convert the IP to a string and print it
		inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
		printf(" %s: %s\n", ipver, ipstr);
	}

	int s;
	s= socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("%d -> integer returned by the socket()\n", s);

	freeaddrinfo(res); //free the linked list
	return 0;
}



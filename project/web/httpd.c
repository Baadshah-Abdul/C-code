#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define LISTENADDR "127.0.0.1" ///local host 
#define PORT 

//structure
struct sHttpRequest
{
	char method[8];
	char url[128];
};
typedef struct sHttpRequest http_req;
//global
char *error;

/*return 0 on error or returns a scoket fd*/
int srv_init(int portno)
{
	int s;
	struct sockaddr_in srv;
	
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0)
	{
		error = "socket() errpr";
		return 0;
	}

	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(LISTENADDR);
	srv.sin_port = htons(portno);

	if (bind(s, (struct sockaddr *)&srv, sizeof(srv)))
	{
		close(s);
		error = "bind() error";
		return 0;
	}
	
	if(listen(s, 5))
	{
		close(s);
		error = "listen() error";
		return 0;
	}

	return s;
}

//return 0 on error, or returns the new client on socket fd*/
int cli_accept(int s)
{
	int c;
	socklen_t addrlen;
	struct sockaddr_in cli;
	
	addrlen = 0;
	memset(&cli, 0 , sizeof(cli));
	c = accept(s, (struct sockaddr *)&cli, &addrlen);
	if(c < 0)
	{
		error = "accept() error";
		return 0;
	}
	return c;
}

//returns 0 on erroe or returns a http_req structure*/
http_req *parse_http(char *str)
{
	http_req *req;
	char *p;

	req = malloc(sizeof(http_req));
	memset(req, 0 , sizeof(http_req));
	
	for(p=str; *p && *p != ' '; p++);
	if(*p == ' ')
		*p = 0;
	else
	{

		printf("DEBUG\n");
		error = "parse_http() NOSPACE error";
		free(req);
		return 0;
	}

	strncpy(req->method, str, 7);

	for(str = ++p; *p && *p != ' '; p++);
	if(*p == ' ')
		*p = 0;
	else
	{
		error = "parse_http() 2NDSPACE error";
		free(req);
		return 0;
	}

	strncpy(req->url, str, 127);
	return req;
}

/*return 0 on error or return the data*/
char *cli_read(int c)
{
	static char buf[512];

	memset(buf, 0, 512);
	if(read(c, buf, 511) < 0)
	{
		error = "read error";
		return 0;
	}
	else
		return buf;
}


void http_response(int c, char *contenttype, char *data)
{
	char buf[512];
	int n;

	n = strlen(data);
	memset(buf, 0, 512);
	snprintf(buf, 511,
	"Content-Type: %s\r\n"
	"Content-Length: %d\r\n"
	"\r\n%s\r\n", 
	contenttype, n, data);

	n = strlen(buf);
	write(c, buf, n);
	return;
}

void http_headers(int c, int code)
{
	int n;
	char buf[512];

	memset(buf, 0, 512);
	snprintf(buf, 511, 
	"HTTP/1.0 %d OK\r\n"
	"Server: http.c\r\n"
	"Cache-Control: no-store, no-cache, max-age=0, private\n"
	"Content-Language: en\r\n"
	"Expires: -1\n"
	"X-Frame-Options: SAMEORIGIN\n",
	code);

	n = strlen(buf);
	write(c, buf, n);

	return;
}

void cli_conn(int s, int c)
{
	http_req *req;
	char *p;
	char *res;

	p = cli_read(c);
	if (!p)
	{
		fprintf(stderr, "%s\n", error);
		close(c);
		return;
	}

	req = parse_http(p);
	if (!req)
	{
		fprintf(stderr, "%s\n", error);
		close(c);

		return;
	}

	if (!strcmp(req->method, "GET") && !strcmp(req->url, "/app/webpage"))
	{
		res = "<html>Hello World</html>";
		http_headers(c, 200);	//200 = file found*/
		http_response(c, "text/html", res);
	}
	else
	{
		res = "File not found";
		http_headers(c, 404);	//404 = file not found*/
		http_response(c, "text/plain", res);
	}

	
	free(req);
	close(c);
	return;

}


int main(int argc, char *argv[])
{
	int s, c;
	char *port;
 
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <listening port>\n", argv[0]);
		return -1;
	}
	else
		port = argv[1];


	s = srv_init(atoi(port));
	if(!s)
	{
		fprintf(stderr, "%s\n", error);
		return -1;
	}
	
	printf("listening on %s:%s\n", LISTENADDR, port);
	while(1)
	{
		c = cli_accept(s);
		if(!c)
		{
			fprintf(stderr, "%s\n", error);
			continue;
		}
		printf("Incoming connection\n");
		if(!fork())
			cli_conn(s, c);
	}
	return -1;
}



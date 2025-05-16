/*trl - timed read line*/

/*---select() allows program to moitor file descriptors for readliness for  I/O opreations---*/

/*-----------------------------------------------------
1) The program starts by printing "What is your name?"

2) It then calls trl(3) which:

Initializes a file descriptor set (rfds) for monitoring

Sets up a 3-second timeout (tv.tv_sec = 3)

Uses select() to wait for input on stdin (file descriptor 0)

//Two possible outcomes://

1) Input received within 3 seconds:

select() returns >0 indicating input is ready

read() gets up to 511 bytes from stdin

Input is null-terminated and returned

Main program prints "Hello [name]"

2) Timeout after 3 seconds:

select() returns 0

trl() returns NULL

Main program prints "Too slow"

*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

/*timed read line*/
char *trl(int timeout)
{
	static char buf[512];
	fd_set rfds;
	struct timeval tv;
	int ret;

	FD_ZERO(&rfds);
	FD_SET(0,&rfds);

	tv.tv_sec = timeout;
	tv.tv_usec = 0;
	
	ret = select(1, &rfds, 0, 0, &tv);
	if(ret && FD_ISSET(0, &rfds))
	{
		memset(buf, 0, 512);/*memset() used to fill a block of memory with aparticular value*/
		ret = read(0, buf, 511);
		if(ret < 1)
			return 0;
		ret--;
		buf[ret] = 0;
		return buf;
	}
	else
		return 0;
}

int main()
{
	char *name;
	printf("What is your name?\n");
	name = trl(3);
	if(name)
		printf("Hello %s\n", name);
	else
		printf("\nToo slow\n");
	return 0;
}



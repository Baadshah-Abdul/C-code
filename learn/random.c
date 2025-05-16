/*pseudo random functions*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int our_random_function(int max)
{
	int x;
	x = rand() % max + 1;//x = b/w 0 and max +1
	return x;
}

int main()
{
	int random;
	srand( getpid() );//use this to get small number
	random = our_random_function(5);
	printf("%d\n", random);
	random = our_random_function(100);
	printf("%d\n", random);

	return 0;
}


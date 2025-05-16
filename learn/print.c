#include <stdio.h>
#include <unistd.h>

int main()
{
	write(1, "Assalamualaikum\n", 17);
	/*
	0 - stdin (keyboard)
	1 - stdout (screen)
	2 - stderr (screen)
	*/


	return 0;
}

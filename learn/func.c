/*functions*/

#include <stdio.h>

void func()
{
	func2();
}

void func2()
{
	printf("Assalamualaikum from func2\n");
}

int main()
{
	func();
	return 0;
}

/*pointers*/

#include <stdio.h>
#include <string.h>

int main()
{
	char str[32];
	char *p;
	strncpy(str, "Danish is Chikna",31);
	p = str;
	printf("%s\n", p);
	p = p + 1;

	printf("%s\n", p);

	printf("%c\n", *p);
	return 0;
}

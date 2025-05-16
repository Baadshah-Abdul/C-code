/*Structures*/

#include <stdio.h>
#include<string.h>

struct person
{
	char *firstname;
	char lastname[32];
	int age;
};
/*struct person
{
	char title[8];
	char lastname[32];
	int age;
};
*/

int main()
{
	struct person p1;
	p1.firstname="Abdul";
	strncpy(p1.lastname, "Haque", 31);
	p1.age = 22;

	printf("%s %s is %d yrs old\n",
		p1.firstname,
		p1.lastname,
		p1.age);
	
	return 0;
}



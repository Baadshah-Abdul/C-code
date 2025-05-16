/*Have written on extra memory and corupted it due to <= */
#include <stdio.h>
#include <stdlib.h>

void iterateItems()
{
	int arrlength = 10;
	int *intArray = malloc(sizeof(int) * arrlength);
	for(int i = 0; i <= arrlength; i++)
	{
		intArray[i] = 5;
	}
}

int main()
{
	iterateItems();

	return 0;
}




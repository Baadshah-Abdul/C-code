/*function pointer*/
#include <stdio.h>

#define F fflush(stdout)
/*
fflush(stdout) is a standard C library function that forces any buffered output to be written to the standard output (stdout).

Buffering can sometimes delay the display of printed messagesi.

Using F; is a shorthand way to call fflush(stdout);.
*/

#define ADD 1
#define SUB 2
#define DIV 3
#define MULTI 4
void add(int *target, int a, int b)
{
	*target = a + b;
	return;
}
void sub(int *target, int a, int b)
{
	*target = a - b;
	return;
}
void div(int *target, int a, int b)
{
	*target = a / b;
	return;
}
void multi(int *target, int a, int b)
{
	*target = a * b;
	return;
}

void display()
{
	printf("Press 1 for add, 2 for sub, 3 for div, 4 for multi and anything else to quit\n");
}


int main()
{
	int x, y, op, result;
	void (*fp)(int*, int, int);/*function pointer*/
	
	display();
	
	scanf("%d", &op);

	switch (op)
	{
		case ADD:
		fp = add;
		break;
		case SUB:
		fp = sub;
		break;
		case DIV:
		fp = div;
		break;
		case MULTI:
		fp = multi;
		break;
		default:
		printf("quit\n");
		return 0;
	}
	printf("Number 1: "); F;
	scanf("%d", &x);
	printf("Number 2: "); F;
	scanf("%d", &y);
	
	(fp)(&result, x, y);
	
	printf("\nResult: %d\n", result);

	return 0;
}


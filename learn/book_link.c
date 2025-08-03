/*Linked list*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*Linked List Structure*/
struct s_book
{
	char title[64];
	int pages;
	struct s_book *next;
};
typedef struct s_book Book;

Book *first;

void add_book(char *title, int pages)
{
	Book *p, *new;
	if(!first)
	{
		p = malloc(sizeof(Book));
		//used to fill block of memory with specific value
		memset(p, 0, sizeof(Book));
		strncpy(p->title, title, 63);
		p->pages = pages;
		p->next = 0;
		first = p;
		return;
	}
	

	for(p = first; p->next; p = p->next);
	
	new = malloc(sizeof(Book));
	//used to fill block of memory with specific value 
	memset(new, 0, sizeof(Book));
	strncpy(new->title, title, 63);
	new->pages= pages;
	new->next = 0;

	p->next = new;
	return;
}

void list_books(char *search_str)
{
	Book *p;

	for(p = first; p; p=p->next)
	{
		if(!search_str || !strcmp(search_str, p->title))
			printf("Pages: %d\tTitle: %s\n", p->pages, p->title);
	}
	return;
}

int rm_books(char *search_str)
{
	Book *p, *ph;

	for(p = first; p; ph=p, p=p->next)
	{
		if(!search_str || !strcmp(search_str, p->title))
		{
			if(first == p)
			{
				first = p->next;
			}
			else
			{
				ph->next = (p->next)?p->next:0;
			}
			free(p);
			return 1;
		}
	}
	return 0;
}


	

int main()
{
	int ret;

	first = 0;

	add_book("linux", 3500);
	add_book("Dice Man", 350);
    add_book("Driver" , 590);
	add_book("Tintin", 356);
	add_book("Book", 100);
		

	list_books(0);
		
    ret = rm_books("linx");
	printf("%d\n", ret);

	list_books(0);


	return 0;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct man_link{
	char name[32];
	struct man_link *next;
};
typedef struct man_link man;

man *first;

void add_name(char *name)
{
	man *p, *new;
	if(!first)
	{
		p = malloc(sizeof(man));
		memset(p, 0, sizeof(man));
		strncpy(p->name, name, 31);
		p->next = 0;
		first = p;
		return;
	}

	for(p = first; p->next; p = p->next){}

	new = malloc(sizeof(man));
	memset(new, 0, sizeof(man));
	strncpy(new->name, name, 31);
	new->next = 0;

	p->next = new;
	return;
}

int rm_name(char *search_str)
{
	man *p, *phead;
	for(p = first; p; phead = p, p = p->next)
	{
		if(!search_str || !strcmp(search_str, p->name))
		{
			if(phead == p)
			{
				first = p->next;
			}
			else
			{
				phead->next = (p->next)?p->next:0;
			}
			free(p);
			return 0;
		}
	}
	return -1;
}

void list_name(char *search_str)
{
	man *p;

	for(p = first; p; p = p->next)
	{
		if(!search_str || !strcmp(search_str, p->name))
			printf("Names: %s\n", p->name);
	}
	return;
}


int main()
{
	int ret;

	first = 0;

	add_name("Abdul");
	add_name("Haque");
	add_name("Mohammad");
	add_name("Ainul");
	add_name("Haque");
	
	list_name(0);

	ret = rm_name("Haque");
	printf("%d\n", ret);

	list_name(0);

	return 0;
}



/*Linked List*/

#include <stdio.h>
#include <stdlib.h>


struct Node
{
	int data;
	struct Node *next;
};

void linklst_traverse(struct Node *ptr)
{
	while(ptr!=NULL)
	{
		printf("%d\n", ptr->data);
		ptr = ptr->next;
	}
}

struct Node *delAtFirst(struct Node *head)
{
	struct Node *ptr = head;
	head = head->next;
	free(ptr);
	return head;
}

struct Node *insertAtFirst(struct Node *head, int data)
{
	struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
	ptr->next = head;
	ptr->data = data;
	return ptr;
}

struct Node *delAtIndex(struct Node *head, int index)
{
	struct Node *ptr;
	struct Node *p = head;
	int i = 0;
	while(i != index-1)
	{
		p = p->next;
		i++;
	}
	ptr = p->next;
	p->next = ptr->next;
	free(ptr);
	return head;
}
	
struct Node *insertAtIndex(struct Node *head, int data, int index)
{
	struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
	struct Node *p = head;
	int i = 0;
	while(i != index-1)
	{
		p = p->next;
		i++;
	}
	ptr->data = data;
	ptr->next = p->next;
	p->next = ptr;

	return head;
}

struct Node *delAtEnd(struct Node *head)
{
	struct Node *p = head;

	while(p->next->next != NULL)
	{ 
		p = p->next;
	}
	free(p->next);
	p->next = NULL;

	return head;
}

struct Node *insertAtEnd(struct Node *head, int data)
{
	struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
	ptr->data = data;
	struct Node *p = head;
	
	while(p->next != NULL)
	{
		p = p->next;
	}
	
	p->next = ptr;
	ptr->next = NULL;
	return head;
}

struct Node *delAtValue(struct Node *head, int data)
{
	struct Node *ptr = head;
	struct Node *p;
	while(ptr->data != data)
	{
		ptr = ptr->next;
	}
	p = ptr->next;
	ptr->next = p->next;
	free(p);
	
	return head;
}

struct Node *insertAfterNode(struct Node *head, struct Node *prevNode, int data)
{
	struct Node *ptr = (struct Node *)malloc(sizeof(struct Node));
	ptr->data = data;

	ptr->next = prevNode->next;
	prevNode->next = ptr;

	return head;
}

int main()
{
	struct Node *head, *fourth;
	struct Node *second;
	struct Node *third;
	int data;

	//allocate memory for nodes in Heap
	head = (struct Node *) malloc(sizeof(struct Node));
	second = (struct Node *) malloc(sizeof(struct Node));
	third = (struct Node *) malloc(sizeof(struct Node));
	fourth = (struct Node *) malloc(sizeof(struct Node));
	//link the nodes
	head->data = 1;
	head->next = second;
	
	second->data = 2;
	second->next = third;
	
	third->data = 3;
	third->next = fourth;

	fourth->data = 4;
	fourth->next = NULL;

	//link list traversal
	printf("Befrore Insertion\n");
	linklst_traverse(head);
	printf("\n");
	//head = insertAtFirst(head, 0);
	//head = insertAtIndex(head, 123, 3);
	//head = insertAtEnd(head, 111);
	//head = insertAfterNode(head, second, 12);
	//head = delAtFirst(head);
	//head = delAtIndex(head, 2);
	//head = delAtEnd(head);
	head = delAtValue(head, 2);
	printf("After deletion at first\n");
	linklst_traverse(head);
	printf("\n");
	

	return 0;

}


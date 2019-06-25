#include<stdio.h>
#include<stdlib.h>
struct node {
	int num;
	struct node* next;
};
struct node* createNode(int num) {
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->num = num;
	newNode->next = NULL;
	return newNode;
}

struct node* createList(int num) {
	struct node* head = createNode(num % 10);
	num /= 10;
	while (num) {
		struct node* newNode = createNode(num % 10);
		newNode->next = head;
		head = newNode;
		num /= 10;
	}
	return head;
}
struct node* detect_loop(struct node* head) {
	struct node *meetpoint = NULL,*slow,*fast;
	slow = head;
	fast = head;
	while (slow->next != fast->next->next && slow->next!=NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	if (slow->next == fast->next->next)
		meetpoint = slow->next;
	return meetpoint;
}
struct node* detect_startingOfLoop(struct node *head,struct node* meetpoint)
{
	struct node* temp, * startpoint;
	temp = head;
	while (temp->next != meetpoint->next)
	{
		temp = temp->next;
		meetpoint = meetpoint->next;
	}
	startpoint = temp->next;
	return startpoint;
}
void main()
{
	struct node* head = createList(123456789);
	struct node* meet = detect_loop(head);
	if (meet == NULL)
		printf("No loop");
	else
	{
		struct node* start = detect_startingOfLoop(meet, head);
		printf("%d", start->num);
	}
	return 0;

}
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
struct node* reverse(struct node* head)
{
	struct node* reverse_head;
	if (head == NULL || head->next == NULL)
		return head;
	reverse_head = reverse(head->next);
	head->next->next = head;
	head->next = NULL;
	return reverse_head;
}
int main()
{
	struct node* head = createList(123456);
	head = reverse(head);
	struct node* temp = head;
	while (temp->next != NULL)
	{
		printf("%d->", temp->num);
		temp = temp->next;
	}
	printf("%d", temp->num);
	return 0;
}
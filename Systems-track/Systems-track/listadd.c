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
struct node* reverse(struct node* head) {
	if (head == NULL)
		return NULL;
	if (head->next == NULL)
		return head;
	struct node* temp, * prev = NULL, * next = NULL;
	temp = head;
	while (temp != NULL)
	{
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	head = prev;
	return head;
}
struct node* findSum(struct node* head)
{
	int carry = 0;
	head = reverse(head);
	struct node* temp = head;
	while (temp->next != NULL)
	{
		temp->num = temp->num + carry;
		if (temp->num > 9)
		{
			int n = temp->num;
			temp->num = temp->num % 10;
			carry = n / 10;
		}
		temp = temp->num;
	}
	temp->num = temp->num + carry;
	if (temp->num > 9)
	{
		temp->next = createNode(temp->num/10);
		temp->num = temp->num % 10;
	}
	head = reverse(head);
	return head;
} 
struct node* addlists(struct node* head1, struct node* head2)
{
	struct node* temp1, * temp2, * temp, * point1, * point2;
	int len1 = 1, len2 = 1;
	temp1 = head1; temp2 = head2;
	while (temp1->next != NULL) {
		temp1 = temp1->next;
		len1++;
	}
	while (temp2->next != NULL)
	{
		temp2 = temp2->next;
		len2++;
	}
	temp1 = head1; temp2 = head2;
	struct node* head;
	if (len1 > len2)
	{
		struct node* new = createNode(head1->num);
		head = new;
		head->next = NULL;
		temp = head;
		temp1 = temp1->next;
		for (int i = 1; i < len1 - len2; i++)
		{
			temp->next = createNode(temp1->num);
			temp1 = temp1->next;
			temp = temp->next;
		}
		point1 = temp1;
		point2 = head2;
	}
	else if (len2 > len1)
	{
		struct node* new = createNode(head2->num);
		head = new;
		head->next = NULL;
		temp = head;
		temp2 = temp2->next;
		for (int i = 1; i < len1 - len2; i++)
		{
			temp->next = createNode(temp2->num);
			temp2 = temp2->next;
			temp = temp->next;
		}
		point1 = temp2;
		point2 = head1;
	}
	else
	{
		point1 = head1;
		point2 = head2;
	}
	while (point1->next != NULL)
	{
		temp->next = createNode(point1->num + point2->num);
		temp = temp->next;
		point1 = point1->next;
		point2 = point2->next;
	}
	head = findSum(head);
	return head;
}
void main()
{
	struct node* head1 = createList(93279);
	struct node* head2 = createList(284);
	struct node *head = addlists(head1, head2); 
	struct node* temp;
	temp = head;
	while (temp->next != NULL)
	{
		printf("%d", temp->num);
		temp = temp->next;
	}
	return 0;
} 
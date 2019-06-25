#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node* next;
	struct node* prev;
};


struct node* create_node(int data) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

struct node* create_list(struct node* head, struct node* new_node) {
	if (head == NULL) {
		head = new_node;
		return head;
	}
	struct node* temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = new_node;
	new_node->prev = temp;
	return head;
}

int length_ll(struct node* start, struct node* end) {
	int length = 0;
	while (start != end) {
		length++;
		start = start->next;
	}
	return length;
}

struct node* middle_node(struct node* start) {
	struct node* pfast = start, * pslow = start;
	while (pfast->next != NULL && pfast->next->next != NULL) {
		pfast = pfast->next->next;
		pslow = pslow->next;
	}
	struct node* temp = pslow->next;
	pslow->next = NULL;
	return temp;
}

/*void merge_dll(struct node *start, struct node *middle, struct node *end,struct node *head){
	struct node *temp1 = start, *temp2 = middle->next;
	struct node *ptr1 = temp1->prev, *ptr2 = temp2->prev, *ptr3 = temp2->next;
	while (temp1 != middle->next && temp2 != end->next){
		if (temp1->data > temp2->data){
			if (temp1 == head){
				head = temp2;
				temp2->prev->next = ptr3;
				temp2->prev = NULL;
				temp2->next = temp1;
				temp1->prev = head;
				temp1->next->prev = temp1;
			}
			else{
				temp1->next = temp2->next;
				temp2->next = ptr3;
				ptr3->prev = temp2;
				temp2->prev = ptr1;
				temp1->prev = ptr2;
			}
			temp1 = temp2->next;
			temp2 = ptr3;
		}
		else{
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
	}
}*/

struct node* merge_dll(struct node* head1, struct node* head2) {
	if (!head1) {
		return head2;
	}
	if (!head2) {
		return head1;
	}
	if (head1->data < head2->data) {
		head1->next = merge_dll(head1->next, head2);
		head1->next->prev = head1;
		head1->prev = NULL;
		return head1;
	}
	head2->next = merge_dll(head1, head2->next);
	head2->next->prev = head2;
	head2->prev = NULL;
	return head2;

}

struct node* mergesort_dll(struct node* head) {
	if (!head || !head->next)
		return head;
	struct node* mid_node = middle_node(head);
	head = mergesort_dll(head);
	mid_node = mergesort_dll(mid_node);
	return merge_dll(head, mid_node);
}

/*int main(){
	int arr[] = { 5, 4, 3, 1, 7, 6 };
	struct node *new_node = NULL, *head = NULL;
	for (int index = 0; index < 6; index++){
		new_node = create_node(arr[index]);
		head = create_list(head, new_node);
	}
	struct node *last_node = head;
	while (last_node->next != NULL){
		last_node = last_node->next;
	}
	head=mergesort_dll(head);
	struct node *temp = head;
	while (temp != NULL){
		printf("%d ", temp->data);
		temp = temp->next;
	}
	getchar();
}*/
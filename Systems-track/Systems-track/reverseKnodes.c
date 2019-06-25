#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};

struct node *create_node(int data){
	struct node *new_node = (struct node *)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

struct node *create_list(struct node *head, struct node *new_node){
	if (head == NULL){
		head = new_node;
		return head;
	}
	struct node *temp = head;
	while (temp->next != NULL){
		temp = temp->next;
	}
	temp->next = new_node;
	return head;
}

struct node *reverseNodes(struct node *begin, struct node *end, struct node *head){
	struct node *prev = head;
	if (begin == head){
		head = end;
	}
	else{
		while (prev->next != begin){
			prev = prev->next;
		}
		prev->next = end;
	}
	struct node *ptr1 = end, *temp = begin, *ptr2 = end->next;
	while (temp->next->next != temp){
		while (temp->next != ptr1){
			temp = temp->next;
		}
		ptr1->next = temp;
		ptr1 = temp;
		temp = begin;
	}
	begin->next = ptr2;
	return head;
}

struct node *reverseKNodes(int K, struct node *head,int nodes){
	if (head == NULL){
		return NULL;
	}
	if (nodes < K){
		return head;
	}
	struct node *temp1 = head, *temp2 = head,*ptr=head;
	int count = 1;
	while (temp1->next != NULL){
		count = 1;
		temp2 = temp1->next;
		while (temp2->next != NULL && count<K-1){
			count++;
			temp2 = temp2->next;
		
		}
		if (count != K-1){
			return head;
		}
		ptr = temp2->next;
		head = reverseNodes(temp1, temp2, head);
		temp1 = ptr;
	}
	return head;
}

int main(){
	int nodes, K, data;
	struct node *head = NULL,*new_node;
	printf("Enter number of nodes:");
	scanf("%d", &nodes);
	fflush(stdin);
	printf("Enter nodes in the list:");
	for (int i = 0; i < nodes; i++){
		scanf("%d", &data);
		new_node = create_node(data);
		head = create_list(head, new_node);
	}
	fflush(stdin);
	printf("Enter the value of K:");
	scanf("%d", &K);
	struct node *result_head = reverseKNodes(K, head, nodes);
	struct node *temp = result_head;
	fflush(stdin);
	while (temp!= NULL){
		printf("%d ", temp->data);
		temp = temp->next;
	}
	getchar();
	return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define SIZE 26

struct ListNode {
	char *word;
	struct ListNode *next;
};

struct TrieNode {
	struct TrieNode *children[SIZE];
	bool word_end;
	struct ListNode *words;
};

//typedef struct ListNode ListNode;
//typedef struct TrieNode Node;

int strlen_(const char *str) {
	int len = 0;
	for (; str[len] != '\0' && str[len] != '\n'; len++);
	return  len;
}

void str_lower(char *str) {
	int index = 0;
	while (str[index] != '\n' && str[index]) {
		if (str[index] >= 'A' && str[index] <= 'Z')
			str[index] = (str[index] - 'A') + 'a';
		index++;
	}
}

void sort(char *string) {
	char temp;

	int i, j;
	int n = strlen_(string);

	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (string[i] > string[j]) {
				temp = string[i];
				string[i] = string[j];
				string[j] = temp;
			}
		}
	}
}

struct TrieNode *get_new_node() {
	struct TrieNode *new_node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

	new_node->word_end = false;
	new_node->words = NULL;
	for (int i = 0; i < SIZE; i++)
		new_node->children[i] = NULL;

	return new_node;
}

struct ListNode *get_new_word(char *str) {
	struct ListNode *new_node = (struct ListNode *)malloc(sizeof(struct ListNode));

	new_node->word = (char *)malloc(sizeof(char) * 50);
	int index = 0;
	while (*str != '\n' && *str) {
		new_node->word[index++] = *str++;
	}
	new_node->word[index] = '\0';

	new_node->next = NULL;
	return new_node;
}

void insert_word(struct TrieNode *root, char *str, char *actual) {
	struct TrieNode *ptr = root;
	int len = strlen_(str);

	for (int i = 0; i < len; i++) {
		int index = str[i] - 'a';

		if (!ptr->children[index])
			ptr->children[index] = get_new_node();

		ptr = ptr->children[index];
	}

	ptr->word_end = true;

	struct ListNode *new_word = get_new_word(actual);
	if (ptr->words == NULL) {
		ptr->words = new_word;
	}
	else {
		struct ListNode *temp = ptr->words;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_word;
	}
}

struct ListNode *get_anagrams(struct TrieNode *root, char *str) {
	struct TrieNode *ptr = root;
	int index;

	for (int i = 0; str[i]; i++) {
		index = (int)(str[i] - 'a');
		if (!ptr->children[index])
			return NULL;

		ptr = ptr->children[index];
	}

	return ptr->word_end ? ptr->words : NULL;
}

void print_trie(struct TrieNode *root, char *buffer, int index) {
	struct TrieNode *ptr = root;

	if (ptr->word_end) {
		for (int i = 0; i < index; i++)
			printf("%c", buffer[i]);
		printf(" End words: ");

		struct ListNode *head = ptr->words;
		while (head != NULL) {
			printf("%s ", head->word);
			head = head->next;
		}
		printf("\n");
	}
	else {
		for (int i = 0; i < SIZE; i++) {
			if (ptr->children[i]) {
				buffer[index] = (char)(i + 'a');
				print_trie(ptr->children[i], buffer, index + 1);
			}
		}
	}
}


int main() {
	struct TrieNode *dict_root = get_new_node();

	FILE *input = fopen("words.txt", "r");

	char line[256], actual_word[256];

	while (fgets(line, 256, input)) {

		str_lower(line);
		int index = 0;
		while (line[index] != '\n' && line[index]) {
			actual_word[index] = line[index];
			index++;
		}

		actual_word[index] = '\0';

		sort(line);
		insert_word(dict_root, line, actual_word);
	}

	char word[50];
	scanf("%s", word);

	sort(word);

	struct ListNode *anagrams = get_anagrams(dict_root, word);

	if (anagrams == NULL)
		printf("NOT Found\n");
	else {
		while (anagrams != NULL) {
			printf("%s ", anagrams->word);
			anagrams = anagrams->next;
		}
	}
	return 0;
}
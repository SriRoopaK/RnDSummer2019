#include<stdio.h>
#include<stdlib.h>
int word_check(char s[100][100], char word[100], int row, int column, int position, int direction, int* count, int m, int n)
{
	if (word[position] == '\0') {
		*count = *count + 1;
		return 1;
	}
	if (row == -1 || row == m || column == -1 || column == n)
		return 0;
	if (s[row][column] == word[position])
	{
		if (direction == 0)
		{
			if (s[row + 1][column + 1] == word[position + 1])
				word_check(s, word, row + 1, column + 1, position + 1, 1, count, m, n);
			if (s[row - 1][column - 1] == word[position + 1])
				word_check(s, word, row - 1, column - 1, position + 1, 2, count, m, n);
			if (s[row - 1][column + 1] == word[position + 1])
				word_check(s, word, row - 1, column + 1, position + 1, 3, count, m, n);
			if (s[row + 1][column - 1] == word[position + 1])
				word_check(s, word, row + 1, column - 1, position + 1, 4, count, m, n);
			if (s[row][column + 1] == word[position + 1])
				word_check(s, word, row, column + 1, position + 1, 5, count, m, n);
			if (s[row][column - 1] == word[position + 1])
				word_check(s, word, row, column - 1, position + 1, 6, count, m, n);
			if (s[row + 1][column] == word[position + 1])
				word_check(s, word, row + 1, column, position + 1, 7, count, m, n);
			if (s[row - 1][column] == word[position + 1])
				word_check(s, word, row - 1, column, position + 1, 8, count, m, n);
		}
		if (direction == 1) {
			word_check(s, word, row + 1, column + 1, position + 1, direction, count, m, n);
		}
		if (direction == 2) {
			word_check(s, word, row - 1, column - 1, position + 1, direction, count, m, n);
		}
		if (direction == 3) {
			word_check(s, word, row + 1, column - 1, position + 1, direction, count, m, n);
		}
		if (direction == 4) {
			word_check(s, word, row - 1, column + 1, position + 1, direction, count, m, n);
		}
		if (direction == 5) {
			word_check(s, word, row, column + 1, position + 1, direction, count, m, n);
		}
		if (direction == 6) {
			word_check(s, word, row, column - 1, position + 1, direction, count, m, n);
		}
		if (direction == 7) {
			word_check(s, word, row + 1, column, position + 1, direction, count, m, n);
		}
		if (direction == 8) {
			word_check(s, word, row - 1, column, position + 1, direction, count, m, n);
		}
	}
}
int main()
{
	char s[100][100] = { {'h','i','e','f','g'},{'d','i','c','h','h'},{'b','a','g','i','h'} };
	char word[100] = { 'h','i','g','\0' };
	int* count = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int ans = word_check(s, word, i, j, 0, 0, &count, 3, 5);
		}
	}
	printf("%d", count);
	return 0;

}
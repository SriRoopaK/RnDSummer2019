#include<stdio.h>

void printnum(int n, int s[100], int index)
{
	if (n == index)
	{
		int flag = 0;
		for (int i = 0; i < n; i++) {
			if (flag == 0 && s[i] == 0)
				continue;
			if (s[i] != 0)
				flag = 1;
			printf("%d", s[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i <= 9; i++)
	{
		s[index] = i;
		printnum(n, s, index + 1);
	}
}
int main()
{
	int a[100];
	printnum(2, a, 0);
	return 0;
}
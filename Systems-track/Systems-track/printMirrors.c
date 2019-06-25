#include<stdio.h>

void printnum(int n, int s[100], int index, char str[11])
{
	if (n == index)
	{
		int flag = 0;
		for (int i = 0; i < n; i++) {
			if (flag == 0 && s[i] == '0')
				continue;
			if (s[i] != '0')
				flag = 1;
			printf("%c", s[i]);
		}
		printf("\n");
		return;
	}
	for (int i = 0; i <= 9; i++)
	{
		s[index] = str[i];
		printnum(n, s, index + 1, str);
	}
}
int main()
{
	int a[100];
	char str[11] = "012Eh59L86\0";
	printnum(2, a, 0, str);
	return 0;
}
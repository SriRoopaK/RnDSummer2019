#include<stdio.h>
#include<stdlib.h>
int* sort0s1sCount(int* array,int len)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (array[i] == 0)
			count++;
	}
	for (int i = 0; i < count; i++)
	{
		array[i] = 0;
	}
	for (int i = count; i < len; i++)
		array[i] = 1;
	return array;
}
int* sort0s1sSum(int* array, int len)
{
	int sum = 0;
	for (int i = 0; i < len; i++)
		sum = sum + array[i];
	for (int i = 0; i < len - sum; i++)
		array[i] = 0;
	for (int i = len - sum; i < sum; i++)
		array[i] = 1;
	return array;
}
int* sort0s1sSwap(int* array, int len)
{
	int find1 = 0, find0 = len;
	while (find1 == find0-1)
	{
		while (array[find1] != 1)
			find1++;
		while (array[find0] != 0)
			find0--;
		if (find1 < find0)
		{
			array[find1] = 0;
			array[find0] = 1;
		}
	}
	return array;
}
/*void print(int* array, int len)
{
	for (int i = 0; i < len; i++)
		printf("%d ", array[i]);
	printf("\n");
} */
void main()
{
	int len,*ans;
	printf("Enter array length: ");
	scanf("%d", &len);
	int* array = (int*)malloc(sizeof(int) * len);
	printf("Enter array: ");
	for (int i = 0; i < len; i++)
		scanf("%d", &array[i]);
	fflush(stdin);
	/*ans = sort0s1sCount(array, len);
	print(array, len);
	ans = sort0s1sSum(array, len);
	print(array, len);
	ans = sort0s1sSwap(array, len); */
	print(array, len);
	return 0;

} 
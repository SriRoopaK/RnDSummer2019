#include<stdio.h>
#include<stdlib.h>
int* threecolor(int* array, int len)
{
	int count0 = 0, count1 = 0;
	for (int i = 0; i < len; i++)
	{
		if (array[i] == 0)
			count0++;
		else if (array[i] == 1)
			count1++;
	}

	for (int i = 0; i < count0; i++)
		array[i] = 0;
	for (int i = count0; i < count0+count1; i++)
		array[i] = 1;
	for (int i = count0+count1; i < len; i++)
		array[i] = 2;
	return array;
}
/*void print(int* array, int len)
{
	for (int i = 0; i < len; i++)
		printf("%d ", array[i]);
	printf("\n");
}
void main()
{
	int len, * ans;
	printf("Enter array length: ");
	scanf("%d", &len);
	int* array = (int*)malloc(sizeof(int) * len);
	printf("Enter array: ");
	for (int i = 0; i < len; i++)
		scanf("%d", &array[i]);
	fflush(stdin);
	ans = threecolor(array, len);
	print(array, len);
} */
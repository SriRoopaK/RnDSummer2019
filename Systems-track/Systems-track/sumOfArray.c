#include <stdio.h>
#include <stdlib.h>
long int sumOfArray(int *array,int len)
{
	if (len<0)
		return array[0];
	return array[len - 1] + sumOfArray(array, len - 1);
}
int main()
{
	int len;
	scanf("%d", &len);
	int* array = (int*)malloc(sizeof(int) * len);
	for (int i = 0; i < len; i++)
		scanf("%d", &array[i]);
	long int sum = sumOfArray(array, len);
	printf("%d", sum);
	return 0;

} 
/*#include<stdio.h>
#include<stdlib.h>
int read_from_file(FILE* fp)
{
	int num;
	fscanf(fp, "%d", &num);
	return num;
}
char* to_string(int num)
{
	char* str = (char*)malloc(sizeof(char) * 7);
	char* ans = (char*)malloc(sizeof(char) * 7);
	int index = 0;
	while (num > 0)
	{
		str[index++] = (num % 10) + '0';
		num = num / 10;
	}
	str[index] = '\0';
	int i = index;
	for (int j = 0; j < index; j++)
	{
		ans[j] = str[--i];
	}
	ans[index] = '\0';
	return ans;
}
void write_to_file(FILE* fp, int data)
{
	fprintf(fp, "%d", data);
}
int* fill_buffer(FILE* fp)
{
	int* buffer = (int*)malloc(sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
	{
		buffer[i] = read_from_file(fp);
	}
	return buffer;
}
void sort_files(char** fileNames)
{
	FILE* dest = fopen("final_dest.txt", "w");
	FILE* fp[4];
	int* arr = (int*)malloc(sizeof(int) * 4);
	for (int i = 0; i < 4; i++)
	{
		fp[i] = fopen(fileNames[i], "r");
	}
	int min = 10000000, flag = -1;
	for (int i = 0; i < 4; i++)
	{
		fscanf(fp[i], "%d", &arr[i]);
	}
	for (int i = 0; i < 20; i++)
	{
		min = 10000000;
		int j;
		for (j = 0; j < 4; j++) {
			if (arr[j] < min && arr[j]!=-1)
			{
				min = arr[j];
				flag = j;
			}
		}
		fprintf(dest, "%d\n", min);
		printf("%d\n", min);
		if (fscanf(fp[flag], "%d", &arr[flag]) == -1)
			arr[flag] = -1;
	}

	for (int i = 0; i < 4; i++)
	{
		fclose(fp[i]);
	}
	fclose(dest);
}
int* sort(int* buffer)
{
	
	int temp;
	for (int i = 0; i < 5; i++)
	{
		for (int j = i+1; j < 5; j++)
		{
			if (buffer[j] < buffer[i])
			{
				temp = buffer[i];
				buffer[i] = buffer[j];
				buffer[j] = temp;
			}
		}
	}
	return buffer;

}
void operate(FILE* fp)
{
	FILE* fp_dest[4];
	char** fileNames = (char*)malloc(sizeof(char) * 4);
	for (int i = 0; i < 4; i++)
	{
		char* file = (char*)malloc(sizeof(char) * 10);
		fileNames[i] = file;
	}
	int len = 5;
	for (int i = 0; i < 4; i++)
	{
		int* buffer = (int*)malloc(sizeof(int) * 5);
		buffer = fill_buffer(fp);
		buffer = sort(buffer);
		fileNames[i] = to_string(i + 1);
		fp_dest[i] = fopen(fileNames[i], "w");
		for (int j = 0; j < 5; j++)
		{
			fprintf(fp_dest[i], "%d\n", buffer[j]);
		}
		fclose(fp_dest[i]);
	}
	sort_files(fileNames);
}
int main() {
	char* fileName = (char*)malloc(sizeof(char) * 100);
	printf("Enter file name: ");
	scanf("%s",fileName);
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Invalid input");
		return;
	}
	operate(fp);
	return 0;
}  */
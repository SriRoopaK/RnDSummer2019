#include <stdio.h>
#include <stdlib.h>
void set_bit(char* buffer, int bit, int val)
{
	int byte = bit / 8;
	char mask = 1 << (bit % 8);
	if (val)
	{
		buffer[byte] |= mask;
	}
	else {
		buffer[byte] &= -mask;
	}
}
int get_bit(char* buffer, int bit)
{
	int byte = bit / 8;
	char mask = 1 << (bit % 8);
	int ans = buffer[byte] & mask ? 1 : 0;
	return ans;
}
void sort_file(char* buffer, char* inp_file_name, long lower_bound, long upper_bound)
{
	FILE* inp_file;
	char* number = (char*)malloc(sizeof(char) * 10);

	for (int count = 0; count < 10; count++) {
		fopen_s(&inp_file, inp_file_name, "r");
		if (number == NULL)
			number = (char*)malloc(sizeof(char) * 10);
		while (number != NULL) {
			long index;
			sscanf(number, "%ld", &index);
			index -= count * 1000000;
			if (index > lower_bound && index < upper_bound)
				set_bit(buffer, index, 1);
			number = fgets(number, 9, inp_file);
		}
		for (long i = 0; i < 1000000; i++)
			if (get_bit(buffer, i))
				printf("%ld\n", i + (count * 1000000));
		for (long i = 0; i < 1000000; i++)
			set_bit(buffer, i, 0);
		fclose(inp_file);
	}

}
int main()
{
	char* array = (char*)malloc(128000 * sizeof(char));
	for (long i = 0; i < 1000000; i++)
		set_bit(array, i, 0);
	sort_file(array, "num_inp.txt", 0, 999999);
	gecthar();
	return 0;
}
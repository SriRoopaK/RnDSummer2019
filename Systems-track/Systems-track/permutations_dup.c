#include <stdio.h>
#include <stdlib.h>

int* remove_element(int* Arr, int size, int element) {
	int* sub_array = (int*)malloc(sizeof(int) * size - 1);
	int pos = 0;
	for (int index = 0; index < size; index++) {
		if (index == element) {
			continue;
		}
		sub_array[pos++] = Arr[index];
	}
	return sub_array;
}

void permute(int* Arr, int current_state, int size, int* result) {
	if (size == 0) {
		for (int index = 0; index < current_state; index++) {
			printf("%d ", result[index]);
		}
		printf("\n");
	}
	else {
		for (int index = 0; index < size; index++) {
			int index1 = 0;
			for (index1 = 0; index1 < index; index1++) {
				if (Arr[index1] == Arr[index]) {
					break;
				}
			}
			if (index1 != index) {
				continue;
			}
			int current_element = Arr[index];
			result[current_state] = current_element;
			int* sub_Arr = remove_element(Arr, size, index);
			permute(sub_Arr, current_state + 1, size - 1, result);
		}
	}
}
void permutations(int* Arr, int size) {
	int* result = (int*)malloc(sizeof(int) * size);
	permute(Arr, 0, size, result);
}

int main() {
	int Arr[] = { 1, 7, 5, 5 };
	permutations(Arr, 4);
	getchar();
}
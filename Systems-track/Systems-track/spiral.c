#include <stdio.h>
#include <stdlib.h>

int *spiral_array(int **matrix, int m, int n){
	int min_col = 0, min_row = 0, max_col = n-1, max_row = m-1, index = 0;
	int *arr = (int *)malloc(sizeof(int)*m*n);
	while (min_col != max_col && min_row != max_row){
		for (int col = min_col; col <= max_col; col++){
			arr[index++] = matrix[min_row][col];
		}
		for (int row = min_row + 1; row <= max_row; row++){
			arr[index++] = matrix[row][max_col];
		}
		for (int col = max_col - 1; col >= min_col; col--){
			arr[index++] = matrix[max_row][col];
		}
		for (int row = max_row - 1; row > min_row; row--){
			arr[index++] = matrix[row][min_col];
		}
		max_row -= 1;
		max_col -= 1;
		min_row += 1;
		min_col += 1;
	}
	if (m == n){
		arr[index] = matrix[min_row][min_col];
	}
	return arr;
}
/*int main(){
	int m, n;
	printf("Enter number of rows:");
	scanf("%d", &m);
	fflush(stdin);
	printf("Enter number of columns:");
	scanf("%d", &n);
	fflush(stdin);
	int **matrix = (int **)malloc(sizeof(int *)*m);
	for (int i = 0; i < m; i++){
		matrix[i] = (int *)malloc(sizeof(int)*n);
	}
	printf("Elements of matrix:\n");
	for (int row = 0; row < m; row++){
		for (int col = 0; col < n; col++){
			scanf("%d", &matrix[row][col]);
		}
	}
	fflush(stdin);
	int *result = spiral_array(matrix, m, n);
	for (int index = 0; index < m*n; index++){
		printf("%d ", result[index]);
	}
	getchar();
	return 0;
}*/
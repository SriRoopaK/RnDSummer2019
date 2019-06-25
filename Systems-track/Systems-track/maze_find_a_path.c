#include <stdio.h>
#include <stdlib.h>

int **read_matrix(int row, int col){
	int **matrix = (int **)malloc(row*(sizeof(int *)));
	for (int index = 0; index < row; index++)
		matrix[index] = (int *)malloc(col*(sizeof(int)));

	printf("maze: \n");
	for (int row_index = 0; row_index < row; row_index++)
		for (int col_index = 0; col_index < col; col_index++)
			scanf_s("%d", &matrix[row_index][col_index]);

	return matrix;
}

int solve_maze(int **maze, int row_index, int col_index, int max_row, int max_col){
	if (maze[row_index][col_index] == 1)
		return 0;
	if (maze[row_index][col_index] == 2)
		return 1;

	maze[row_index][col_index] = 3; // visited

	if (col_index < max_col && maze[row_index][col_index + 1] != 3)
		if (solve_maze(maze, row_index, col_index + 1, max_row, max_col)){
			maze[row_index][col_index] = -1;
			return 1;
		}

	if (row_index < max_row && maze[row_index + 1][col_index] != 3)
		if (solve_maze(maze, row_index + 1, col_index, max_row, max_col)){
			maze[row_index][col_index] = -1;
			return 1;
		}

	if (col_index > 0 && maze[row_index][col_index - 1] != 3)
		if (solve_maze(maze, row_index, col_index - 1, max_row, max_col)){
			maze[row_index][col_index] = -1;
			return 1;
		}

	if (row_index > 0 && maze[row_index - 1][col_index] != 3)
		if (solve_maze(maze, row_index - 1, col_index, max_row, max_col)){
			maze[row_index][col_index] = -1;
			return 1;
		}

	return 0;

}

void print_path(int **maze, int row_index, int col_index, int max_row, int max_col){
	for (int row = row_index; row < max_row; row++)
	{
		for (int col = col_index; col < max_col; col++)
		{
			printf("%d ", maze[row][col]);
		}
		printf("\n");
	}
}



int main(){
	int row, col;
	printf("order of maze: ");
	scanf_s("%d %d", &row, &col);

	int **maze = read_matrix(row, col);
	int path_exist = solve_maze(maze, 0, 0, row - 1, col - 1);

	if (path_exist){
		printf("\npath exists\n");
		print_path(maze, 0, 0, row - 1, col - 1);
	}
	else
		printf("no path");

	getchar();
	return 0;
} 
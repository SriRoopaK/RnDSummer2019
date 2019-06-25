// #include <stdio.h>
//#include <stdlib.h>
//
//int **read_matrix(int row, int col){
//	int **matrix = (int **)malloc(row*(sizeof(int *)));
//	for (int index = 0; index < row; index++)
//		matrix[index] = (int *)malloc(col*(sizeof(int)));
//
//	printf("maze: \n");
//	for (int row_index = 0; row_index < row; row_index++)
//		for (int col_index = 0; col_index < col; col_index++)
//			scanf_s("%d", &matrix[row_index][col_index]);
//
//	return matrix;
//}
//void update_adjacents(int **maze,int **visited, int row_index, int col_index, int max_row, int max_col){
//
//	if (col_index < max_col && visited[row_index][col_index + 1] != 1){
//		if (maze[row_index][col_index + 1] == 0)
//			maze[row_index][col_index + 1] = maze[row_index][col_index] + 1;
//		else if (maze[row_index][col_index + 1] > maze[row_index][col_index] + 1)
//			maze[row_index][col_index + 1] = maze[row_index][col_index] + 1;
//	}
//	if (row_index < max_row && visited[row_index + 1][col_index] != 1)
//	{
//		if (maze[row_index + 1][col_index] == 0)
//			maze[row_index + 1][col_index] = maze[row_index][col_index] + 1;
//		else if (maze[row_index + 1][col_index] > maze[row_index][col_index] + 1)
//			maze[row_index + 1][col_index] = maze[row_index][col_index] + 1;
//	}	
//	if (col_index > 0 && visited[row_index][col_index - 1] != 1)
//	{
//		if (maze[row_index][col_index - 1] == 0)
//			maze[row_index][col_index - 1] = maze[row_index][col_index] + 1;
//		else if (maze[row_index][col_index - 1] > maze[row_index][col_index] + 1)
//			maze[row_index][col_index - 1] = maze[row_index][col_index] + 1;
//	}
//	if (row_index > 0 && visited[row_index - 1][col_index] != 1)
//	{
//		if (maze[row_index - 1][col_index] == 0)
//			maze[row_index - 1][col_index] = maze[row_index][col_index] + 1;
//		else if (maze[row_index - 1][col_index] > maze[row_index][col_index] + 1)
//			maze[row_index - 1][col_index] = maze[row_index][col_index] + 1;
//	}
//}
//
//void solve_maze(int **visited, int **maze, int row_index, int col_index, int max_row, int max_col){
//	if (row_index == 0 && col_index == 0)
//		return;
//	else{
//
//		update_adjacents(maze, visited, row_index, col_index, max_row, max_col);
//		visited[row_index][col_index] = 1;
//
//		if (col_index < max_col && visited[row_index][col_index + 1] != 1 && maze[row_index][col_index + 1] != -1)
//			solve_maze(visited, maze, row_index, col_index + 1, max_row, max_col);
//		if (row_index < max_row && visited[row_index + 1][col_index] != 1 && maze[row_index + 1][col_index] != -1)
//			solve_maze(visited, maze, row_index + 1, col_index, max_row, max_col);
//		if (col_index > 0 && visited[row_index][col_index - 1] != -1 && maze[row_index][col_index - 1] != -1)
//			solve_maze(visited, maze, row_index, col_index - 1, max_row, max_col);
//		if (row_index>0 && visited[row_index - 1][col_index] != -1 && maze[row_index - 1][col_index] != -1)
//			solve_maze(visited, maze, row_index - 1, col_index, max_row, max_col);
//	}
//}
//
//
//void print_path(int** maze, int row_index, int col_index, int max_row, int max_col) {
//	if (maze[row_index][col_index] == 0)
//		printf("(%d, %d) -> end\n", row_index, col_index);
//	int value = maze[row_index][col_index] - 1;
//	printf("(%d, %d)->", row_index, col_index);
//	if (col_index < max_col && maze[row_index][col_index + 1] == value)
//		print_path(maze, row_index, col_index + 1, max_row, max_col);
//	else if (row_index < max_row && maze[row_index + 1][col_index] == value)
//		print_path(maze, row_index + 1, col_index, max_row, max_col);
//	else if (col_index > 0 && maze[row_index][col_index - 1] == value)
//		print_path(maze, row_index, col_index - 1, max_row, max_col);
//	else if (row_index > 0 && maze[row_index - 1][col_index] == value)
//		print_path(maze, row_index - 1, col_index, max_row, max_col);
//
//}
//
//int **create_matrix(int rows, int cols){
//	int **matrix = (int **)malloc(rows*(sizeof(int *)));
//	for (int index = 0; index < rows; index++)
//		matrix[index] = (int *)malloc(cols*(sizeof(int)));
//
//	printf("maze: \n");
//	for (int row_index = 0; row_index < rows; row_index++)
//		for (int col_index = 0; col_index < cols; col_index++)
//			matrix[row_index][col_index] = 0;
//
//	return matrix;
//}
//
//int main(){
//	int row, col;
//	printf("order of maze: ");
//	scanf_s("%d %d", &row, &col);
//
//	int **maze = read_matrix(row, col);
//	int **visited = create_matrix(row, col);
//
//	int dest_row, dest_col;
//	printf("destination: ");
//	scanf_s("%d %d", &dest_row, &dest_col);
//	if (dest_row == 0 && dest_col == 0)
//		printf("(0,0) -> end");
//	else {
//		solve_maze(visited, maze, dest_row, dest_col, row - 1, col - 1);
//		print_array(maze, row, col);
//		printf("path:\n");
//		print_path(maze, 0, 0, row - 1, col - 1);
//	}
//	char c=getchar();
//	return 0;
//} 
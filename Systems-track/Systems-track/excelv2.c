//#include <stdio.h>
//#include <stdlib.h>
//#include<string.h>
//struct cell
//{
//	int data;
//	char* formula;
//};
//int get_num(char* str)
//{
//	int len = 0;
//	int num = 0;
//	for (; str[len] != '\0'; len++);
//	for (int i = 0; i < len; i++)
//	{
//		num = (num * 10) + (str[i] - '0');
//	}
//	return num;
//}
//int evaluate(char* str, struct cell** sheet)
//{
//	int len = 0, flag = 0;
//	int o1, o2;
//	for (; str[len] != '\0'; len++);
//	char* op1 = (char*)malloc(sizeof(char) * len);
//	char* op2 = (char*)malloc(sizeof(char) * len);
//	char operator;
//	int i = 0, index = 0;
//	while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
//		op1[index++] = str[i++];
//	op1[index] = '\0';
//	if (str[i] == '\0')
//	{
//		flag = 1;
//		op2 = 0;
//		goto noO2;
//	}
//	operator=str[i++];
//	index = 0;
//	while (i < len)
//		op2[index++] = str[i++];
//	op2[index] = '\0';
//	if ((op1[0] >= '0' && op1[0] <= '9') && (op2[0] >= '0' && op2[0] <= '9')) {
//		o1 = get_num(op1);
//		o2 = get_num(op2);
//	}
//	else if ((op1[0] >= '0' && op1[0] <= '9') && !(op2[0] >= '0' && op2[0] <= '9')) {
//		o1 = get_num(op1);
//		o2 = execute_get(op2, sheet);
//	}
//	else if (!(op1[0] >= '0' && op1[0] <= '9') && (op2[0] >= '0' && op2[0] <= '9'))
//	{
//		o1 = execute_get(op1, sheet);
//		o2 = get_num(op2);
//	}
//	else {
//		o2 = execute_get(op2, sheet);
//	noO2:o1 = execute_get(op1, sheet);
//	}
//	if (flag == 1)
//		return o1;
//	if (operator=='+')
//		return o1 + o2;
//	else if (operator=='-')
//		return o1 - o2;
//	else if (operator == '*')
//		return o1 * o2;
//	else if (operator=='/')
//		return o1 / o2;
//	return 0;
//}
//char* execute_import(char args[100], struct node** sheet)
//{
//	FILE* fp;
//	int arg_len = 0;
//	//printf("%s", args);
//	for (arg_len = 0; args[arg_len] != '\0'; arg_len++);
//	if (args[arg_len - 3] != 'c') {
//		args[arg_len++] = 'c';
//		args[arg_len++] = 's';
//		args[arg_len++] = 'v';
//		args[arg_len] = '\0';
//	}
//	fp = fopen(args, "r");
//	char buffer[15];
//	if (fp == NULL)
//		printf("File doesn't exist");
//	else
//	{
//		while (fgets(buffer, 10, fp))
//		{
//			printf("%s", buffer);
//		}
//	}
//	fclose(fp);
//	//printf("%s", args);
//	return args;
//}
//void execute_export(char args[100], struct cell** sheet)
//{
//	int arg_len = 0;
//	for (arg_len = 0; args[arg_len] != '\0'; arg_len++);
//	if (args[arg_len - 3] != 'c') {
//		args[arg_len++] = 'c';
//		args[arg_len++] = 's';
//		args[arg_len++] = 'v';
//		args[arg_len] = '\0';
//	}
//	FILE* fp;
//	int index = 0;
//	fp = fopen(args, "w");
//	for (int i = 0; i < 10; i++)
//	{
//		for (int j = 0; j < 10; j++)
//		{
//			if (sheet[i][j].formula == NULL)
//				fprintf(fp, "%d", sheet[i][j].data);
//			else
//				fprintf(fp, "%s", sheet[i][j].formula);
//			fprintf(fp, "%c", ',');
//		}
//		fprintf(fp, "%c", '\n');
//	}
//	fclose(fp);
//}
//void execute_print(struct cell** sheet)
//{
//	for (int i = 0; i < 10; i++)
//	{
//		printf("||");
//		for (int j = 0; j < 10; j++)
//		{
//			if (sheet[i][j].formula == NULL) {
//				printf(" %d ||", sheet[i][j].data);
//			}
//			else {
//				int d = evaluate(sheet[i][j].formula, sheet);
//				sheet[i][j].data = d;
//				printf(" %d ||", d);
//			}
//		}
//		printf("\n");
//	}
//}
//int execute_get(char args[100], struct cell** sheet)
//{
//	int row, col;
//	row = (args[1] - '0') - 1;
//	col = args[0] - 'A';
//	return sheet[row][col].data;
//}
//void execute_set(char args[100], struct cell** sheet)
//{
//	int row, col;
//	row = (args[1] - '0') - 1;
//	col = args[0] - 'A';
//	int num_len = 0, num = 0;
//	for (num_len = 3; args[num_len] != '\0'; num_len++);
//	char* sub_args = (char*)malloc(sizeof(char) * 100);
//	if (args[3] >= 'A' && args[3] <= 'Z')
//	{
//		int index = 0;
//		for (int j = 3; j < num_len; j++) {
//			sub_args[index++] = args[j];
//		}
//		sub_args[index] = '\0';
//		sheet[row][col].formula = sub_args;
//		//printf("%s", sheet[row][col].formula);
//		return;
//	}
//	else {
//		for (int j = 3; j < num_len; j++)
//		{
//			if (args[j] == '+' || args[j] == '-' || args[j] == '*' || args[j] == '\\')
//			{
//				int index = 0;
//				for (int i = 3; i < num_len; i++)
//				{
//					sub_args[index++] = args[i];
//				}
//				sub_args[index] = '\0';
//				sheet[row][col].formula = sub_args;
//				return;
//			}
//		}
//	}
//	for (int i = 3; i < num_len; i++)
//	{
//		num = (num * 10) + (args[i] - '0');
//	}
//	sheet[row][col].data = num;
//}
//void execute_command(char command_name[10], char args[100], struct cell** sheet)
//{
//	int a;
//	//char* file = (char*)malloc(sizeof(char) * 100);
//	if (strcmp(command_name, "GET") == 0) {
//		a = execute_get(args, sheet);
//	}
//	else if (strcmp(command_name, "SET") == 0) {
//		execute_set(args, sheet);
//	}
//	else if (strcmp(command_name, "PRINT") == 0) {
//		execute_print(sheet);
//	}
//	else if (strcmp(command_name, "IMPORT") == 0) {
//		execute_import(args, sheet);
//	}
//	else if (strcmp(command_name, "EXPORT") == 0) {
//		execute_export(args, sheet);
//	}
//	/*else if (strcmp(command_name, "SAVE") == 0) {
//
//		execute_export(file, sheet);
//		return file;
//	} */
//	else
//		printf("Command invalid");
//}
//void find_args(char command[100], char command_name[10], int command_len, struct cell** sheet)
//{
//	int len = 0;
//	for (len = 0; command[len] != '\0'; len++);
//	char args[100];
//	//char* file = (char*)malloc(sizeof(char) * 100);
//	int arg_index = 0;
//	for (int i = command_len; i < len; i++)
//	{
//		if (command[i] == ' ')
//			continue;
//		args[arg_index++] = command[i];
//	}
//	args[arg_index] = '\0';
//	execute_command(command_name, args, sheet);
//}
//void read_commands(char command[100], struct node** sheet)
//{
//	char commands[6][100] = { "GET","SET","PRINT","IMPORT","EXPORT","SAVE" };
//	char* command_name = (char*)malloc(sizeof(char) * 7);
//	int flag = -1, len;
//	//char* file = (char*)malloc(sizeof(char) * 100);
//	for (int i = 0; i < 6; i++)
//	{
//		int index = 0;
//		for (len = 0; commands[i][len] != '\0'; len++);
//		//printf("%c", commands[i][len]);
//		for (index = 0; index < len; index++)
//		{
//			command_name[index] = command[index];
//		}
//		command_name[index] = '\0';
//		if (strcmp(command_name, commands[i]) == 0)
//		{
//			flag = i;
//			break;
//		}
//	}
//	if (flag == -1) {
//		printf("invalid command");
//	}
//	else
//	{
//		find_args(command, command_name, len, sheet);
//	}
//}
//int main()
//{
//	struct cell** sheet = (struct cell**)malloc(sizeof(struct cell) * 10);
//	char command[100];
//	for (int i = 0; i < 10; i++)
//	{
//		struct cell* row = (struct cell*)malloc(sizeof(struct cell) * 10);
//		for (int j = 0; j < 10; j++)
//		{
//			row[j].data = 0;
//			row[j].formula = NULL;
//		}
//		sheet[i] = row;
//	}
//	printf(">");
//	while (1)
//	{
//		gets(command);
//		if (strcmp(command, "exit") == 0)
//			break;
//		else
//		    read_commands(command, sheet);
//		printf(">");
//	}
//	return 0;
//}
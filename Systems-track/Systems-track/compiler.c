#include "structures.h"
#include <stdlib.h>
#include <string.h>
void push(int val)
{
	stack[++top] = val;
}
int pop()
{
	return stack[top--];
}
int string_len(char *string){
	int len = 0;
	for (len = 0; string[len] != '\0'; len++);
	return len;
}

int string_compare(char *string1, char *string2){
	int index = 0;
	if (string_len(string1) != string_len(string2))
		return 0;
	for (index = 0; string1[index] != '\0'; index++){
		if (string1[index] != string2[index]){
			break;
		}
	}
	if (string1[index] == '\0')
		return 1;
	return 0;
}

struct data *update_symbol_table(char *line, struct data *data){
	char *token = (char *)malloc(sizeof(char) * 100);
	char *mnemonic = (char *)malloc(sizeof(char) * 6);
	int index = 0;
	while (*line){

		if (*line == ' '){
			break;
		}
		token[index++] = *line++;
	}
	*line++;
	token[index] = '\0';
	strcpy(mnemonic, token);
	index = 0;
	int size = 1;
	while (*line != '\n'){
		if (*line == '[' || *line == '='){
			break;
		}
		token[index++] = *line++;
	}
	token[index] = '\0';
	if (*line == '[' || *line == '='){
		*line++;
		if (*line == ' '){
			*line++;
		}
		size = *line - '0';
	}
	data->snum = data->snum + 1;
	int len = string_len(token);
	if (token[len - 1] == ' ')
		token[len - 1] = '\0';
	strcpy(data->symbol_table[data->snum].variable, token);
	data->symbol_table[data->snum].address = data->symbol_table[data->snum - 1].size + data->symbol_table[data->snum - 1].address;
	if (string_compare(mnemonic, "CONST") == 1){
		data->symbol_table[data->snum].size = 0;
		data->memory[data->symbol_table[data->snum].address] = size;
		return data;
	}
	data->symbol_table[data->snum].size = size;
	return data;
}


int get_opcode(char *token){
	if (string_compare("MOV", token) == 1){
		return 0;
	}
	if (string_compare("ADD", token) == 1){
		return 3;
	}
	if (string_compare("SUB", token) == 1){
		return 4;
	}
	if (string_compare("MUL", token) == 1){
		return 5;
	}
	if (string_compare("JUMP", token) == 1){
		return 6;
	}
	if (string_compare("IF", token) == 1){
		return 7;
	}
	if (string_compare("EQ", token) == 1){
		return 8;
	}
	if (string_compare("LT", token) == 1){
		return 9;
	}
	if (string_compare("GT", token) == 1){
		return 10;
	}
	if (string_compare("LTEQ", token) == 1){
		return 11;
	}
	if (string_compare("GTEQ", token) == 1){
		return 12;
	}
	if (string_compare("READ", token) == 1){
		return 14;
	}
	if (string_compare("PRINT", token) == 1){
		return 13;
	}
	return 15;
}

int get_address(char *token, struct data *data){
	for (int index = 0; index < 7; index++){
		if (string_compare(token, data->register_array[index]) == 1){
			return index;
		}
	}
	int size = 0;
	for (int index = 1; index <= data->snum; index++){
		int index1 = -1;
		for (int i = 0; token[i] != '\0'; i++)
		{
			if (token[i] == '['){
				index1 = i;
				break;
			}
		}
		if (index1 != -1){
			for (int i = index1 + 1; token[i] != '\0'; i++)
			{
				if (token[i] == ']')
					break;
				size = (size * 10) + (token[i] - '0');
			}
			token[index1] = '\0';
		}
		if (string_compare(token, data->symbol_table[index].variable) == 1){
			return  data->symbol_table[index].address + size;
		}
	}
	for (int index = 0; index < data->bnum; index++){
		if (string_compare(token, data->block_table[index].block_name) == 1){
			return data->block_table[index].block_address;
		}
	}
	int opcode = get_opcode(token);
	if (opcode != 15)
		return opcode;
	return -1;
}

struct data *update_data(char *line, struct data *data){
	char *token = (char *)malloc(sizeof(char) * 100);
	int index = 0;
	token = strtok(line, " \n");
	int opcode = get_opcode(token);
	int arg_ind = 0;
	if (opcode == 15){
		token = strtok(line, ":");
		if (string_compare(token, "ELSE") == 1){
			data->instr[data->inum].instr_num = data->inum;
			data->instr[data->inum].opcode = 6;
			data->instr[data->inum].arg[0] = -1;
			push(data->instr[data->inum].instr_num);
			data->inum++;
			return data;
		}
		else if (string_compare(token, "ENDIF") == 1){
			int in = data->inum;
			while (top != -1){
				int val = pop();
				for (int i = 0; i < 4; i++){
					if (data->instr[val].arg[i] == -1){
						data->instr[val].arg[i] = in;
						break;
					}
				}
				in = val + 1;
			}
			return data;
		}
		data->block_table[data->bnum].block_address = data->inum + 1;
		strcpy(data->block_table[data->bnum].block_name, token);
		data->bnum++;
		return data;
	}
	if (opcode == 0)
	{
		token = strtok(NULL, ",\n");
		int len = string_len(token);
		if (token[len - 1] == 'X')
			opcode = 2;
		else
			opcode = 1;
		int address = get_address(token, data);
		data->instr[data->inum].arg[arg_ind++] = address;
	}
	data->instr[data->inum].instr_num = data->instr[data->inum - 1].instr_num + 1;
	data->instr[data->inum].opcode = opcode;
	while (1){
		token = strtok(NULL, ", \n");
		if (token == NULL){
			break;
		}
		int address = get_address(token, data);
		data->instr[data->inum].arg[arg_ind++] = address;
	}
	if (opcode == 7){
		push(data->instr[data->inum].instr_num);
	}
	data->inum++;
	return data;
}


struct data* line_parsing(FILE *file, struct data *data){
	if (file == NULL){
		printf("File doesn't exist\n");
		return;
	}
	int length = 0;
	char *line = (char *)malloc(sizeof(char) * 60);
	char *token = (char *)malloc(sizeof(char) * 6);
	int index = 0;
	while (fgets(line, 60, file) != NULL){
		if (string_compare(line, "START:\n") == 1){
			break;
		}
		data = update_symbol_table(line, data);
	}
	while (fgets(line, 60, file) != NULL){
		/*if (string_compare(line, "END\n") == 1){
			return data;
		}*/
		data = update_data(line, data);
	}
	return data;
}

int get_number_of_operands(int opcode){
	if (opcode == 6 || opcode == 13 || opcode == 14){
		return 1;
	}
	if (opcode == 1 || opcode == 2){
		return 2;
	}
	if (opcode == 3 || opcode == 4 || opcode == 5){
		return 3;
	}
	if (opcode == 7){
		return 4;
	}
}

void write_data_to_file(char *filename, struct data *data){
	FILE *output = fopen(filename, "w");
	if (output == NULL){
		printf("Can't write to file\n");
		return;
	}
	for (int index = 1; index < data->inum; index++){
		int num_of_operands = get_number_of_operands(data->instr[index].opcode);
		fprintf(output, "%d ", data->instr[index].instr_num);
		fprintf(output, "%d ", data->instr[index].opcode);
		if (data->instr[index].opcode == 7){
			fprintf(output, "%d %d %d %d", data->instr[index].arg[0], data->instr[index].arg[2], data->instr[index].arg[1], data->instr[index].arg[3]);
		}
		else{
			for (int arg_index = 0; arg_index < num_of_operands; arg_index++){
				fprintf(output, "%d ", data->instr[index].arg[arg_index]);
			}
		}
		fputs("\n", output);
	}
	fclose(output);
}

struct data *init()
{
	struct data *data = (struct data *)malloc(sizeof(struct data));
	data->bnum = 0;
	data->snum = 0;
	data->inum = 1;
	data->symbol_table[0].size = 0;
	data->symbol_table[0].address = 0;
	data->block_table[0].block_address = 0;
	data->instr[0].instr_num = 0;
	data->register_array[0] = "AX";
	data->register_array[1] = "BX";
	data->register_array[2] = "CX";
	data->register_array[3] = "DX";
	data->register_array[4] = "EX";
	data->register_array[5] = "FX";
	data->register_array[6] = "GX";
	return data;
}

int main(){
	FILE *file = fopen("sum.txt", "r");
	if (file == NULL){
		printf("Can't open file\n");
	}
	struct data *data = init();
	data=line_parsing(file, data);
	write_data_to_file("sum_opcode.txt",data);
	fclose(file);
	return 0;
}
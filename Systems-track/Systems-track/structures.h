#include <stdio.h>

#ifndef _structures_h
#define _structures_h
int stack[100];
int top = -1;
void push(int);
int pop();

struct symbol_table{
	char variable[5];
	int address;
	int size;
};

struct instruction_table{
	int instr_num;
	int opcode;
	int arg[4];
};

struct block_table{
	char block_name[5];
	int block_address;
};

struct data{
	struct symbol_table symbol_table[100];
	struct block_table block_table[100];
	struct instruction_table instr[100];
	char *register_array[7];
	int memory[100];
	int snum;
	int bnum;
	int inum;
};
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 10 
#define META_SIZE 240
struct metadata {
	char fileName[16];
	unsigned int offset;
	unsigned int length;
};
void write_metadata(struct metadata md, int position)
{
	FILE* disk = fopen("hardDisk.hdd", "rb+");
	if (disk == NULL)
		return;
	if (fseek(disk, position * 24, SEEK_SET) == -1)
		return;
	if (fwrite(&md, sizeof(struct metadata), 1, disk) == -1)
		return;
	fclose(disk);
}
int find_md_position(struct metadata md[SIZE])
{
	int index = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (md[i].length == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}
int find_file_location(char* source, struct metadata md[SIZE])
{
	int index = 0;
	for (int i = 0; i < SIZE; i++)
	{
		if (strcmp(md[i].fileName, source) == 0)
		{
			index = i; break;
		}
	}
	return index;
}
int find_file_index(struct metadata md[SIZE])
{
	int i;
	for (i = 0; i < SIZE; i++)
	{
		if (strcmp(md[i].fileName, "NULL") == 0)
			break;
	}
	return i;
}
void execute_ls(struct metadata md[SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		if (strcmp(md[i].fileName, "NULL") == 0)
			break;
		printf("%s\n", md[i].fileName);
	}
}
void execute_format(struct metadata md[SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		strcpy(md[i].fileName, "NULL");
		md[i].offset = 0;
		md[i].length = 0;
	}
	FILE* fp = fopen("hardDisk.hdd", "rb+");
	int i=fseek(fp, 0, SEEK_SET);
	if (fp == NULL)
		return;
	/*for (int i = 0; i < SIZE; i++)
	{
		fwrite(&md[i], sizeof(struct metadata), SIZE, fp);
	} */
	fwrite(&md, sizeof(struct metadata), SIZE, fp);
	fclose(fp);
}
void execute_remove(char* command, struct metadata md[SIZE])
{
	int len = 0;
	for (; command[len] != '\0'; len++);
	char* source = (char*)malloc(sizeof(char) * len);
	int i = 0, file_index = 0, last_index = 0, index = 0;
	while (command[i] != ' ')
		i++;
	i++;
	while (i < len)
		source[index++] = command[i++];
	source[index] = '\0';
	file_index = find_file_location(source, md);
	last_index = find_file_index(md);
	last_index--;
	strcpy(md[file_index].fileName, md[last_index].fileName);
	md[file_index].offset = md[last_index].offset;
	md[file_index].length = md[last_index].length;
	strcpy(md[last_index].fileName, "NULL");
	md[last_index].offset = 0;
	md[last_index].length = 0;
	FILE* disk = fopen("hardDisk.hdd", "ab+");
	if (disk == NULL)
		return;
	if (fseek(disk, 0, SEEK_CUR) == -1)
		return;
	for (int i = 0; i < SIZE; i++)
	{
		write_metadata(md[i], i);
	}
	fclose(disk);
}
void execute_copy_from_disk(char* command, struct metadata md[SIZE])
{
	int len = 0;
	for (; command[len] != '\0'; len++);
	FILE* disk = fopen("hardDisk.hdd", "rb+");
	if (disk == NULL)
		return;
	char* source = (char*)malloc(sizeof(char) * len);
	char* dest = (char*)malloc(sizeof(char) * len);
	int i = 0, flag = 0, src_index = 0, dest_index = 0;
	for (i = 0; i < len; i++)
	{
		if (command[i] == ' ') {
			break;
		}
	}
	if (i < len)
	{
		i++;
		while (command[i] != ' ')
			source[src_index++] = command[i++];
		source[src_index] = '\0';
		dest_index = 0;
		while (i < len)
			dest[dest_index++] = command[i++];
		dest[dest_index] = '\0';
	}
	int index = find_file_location(source, md);
	if (fseek(disk, md[index].offset, SEEK_SET) == -1)
		return; 
	FILE* dst = fopen(dest, "w");
	if (dst == NULL)
		return;
	for (int i = 0; i < md[index].length; i++)
	{
		char c = fgetc(disk);
		fwrite(&c, sizeof(char), 1, dst);
	} 
	fclose(disk);
	fclose(dst);
}
void execute_copy_to_disk(char* command, struct metadata md[SIZE]) {
	int len = 0;
	for (; command[len] != '\0'; len++);
	char* source = (char*)malloc(sizeof(char) * len);
	char* dest = (char*)malloc(sizeof(char) * len);
	int i = 0, flag = 0, src_index = 0, dest_index = 0;
	for (i = 0; i < len; i++)
	{
		if (command[i] == ' ') {
			break;
		}
	}
	if (i < len)
	{
		i++;
		while (command[i] != ' ')
			source[src_index++] = command[i++];
		source[src_index] = '\0';
		i++;
		dest_index = 0;
		while (i < len)
			dest[dest_index++] = command[i++];
		dest[dest_index] = '\0';
	}
	int index = 0;
	index = find_file_index(md);
	FILE* fp_src = fopen(source, "r");
	if (fp_src == NULL)
		return;
	FILE* disk = fopen("hardDisk.hdd", "rb+");
	if (disk == NULL)
		return;
	strcpy(md[index].fileName, dest);
	if (index == 0)
		md[index].offset = META_SIZE;
	else
		md[index].offset = md[index - 1].offset + md[index - 1].length;
	char val;
	fseek(disk, md[index].offset, SEEK_SET);
	while (fread(&val, sizeof(char), 1, fp_src)>0) {
		fwrite(&val, sizeof(char), 1, disk);
	}
	if (fseek(fp_src, 0, SEEK_END) == -1)
		return;
	unsigned int size = ftell(fp_src);
	md[index].length = size;
	fclose(disk);
	write_metadata(md[index], index); 
}
void parse_command(char* command, int num, struct metadata* md)
{
	if (num == 1)
		execute_ls(md);
	else if (num == 2)
		execute_copy_to_disk(command, md);
	else if (num == 3)
		execute_copy_from_disk(command, md);
	else if (num == 4)
		execute_remove(command, md);
	else if (num == 5)
		execute_format(md);
	else
		printf("Invalid\n");
}
int find_command(char* command)
{
	int len = 0;
	for (; command[len] != '\0'; len++);
	char* cmd = (char*)malloc(sizeof(char) * len);
	int i;
	for (i = 0; i < len; i++)
	{
		if (command[i] == ' ')
			break;
		cmd[i] = command[i];
	}
	cmd[i] = '\0';
	if (strcmp(cmd, "LS") == 0)
		return 1;
	else if (strcmp(cmd, "COPY_TO_DISK") == 0)
		return 2;
	else if (strcmp(cmd, "COPY_FROM_DISK") == 0)
		return 3;
	else if (strcmp(cmd, "REMOVE") == 0)
		return 4;
	else if (strcmp(cmd, "FORMAT") == 0)
		return 5;
	else return 0;
}
void if_disk_recorded(struct metadata md[SIZE])
{
	FILE* fp = fopen("hardDisk.hdd", "rb+");
	char ch;
	ch = fgetc(fp);
	if (ch==NULL) {
		execute_format(md);
		return;
	}
	fseek(fp, 0, SEEK_SET);
	for (int i = 0; i < SIZE; i++)
	{
		fread(&md[i], sizeof(struct metadata), 1, fp);
	}
}
int main()
{
	char* command = (char*)malloc(sizeof(char) * 100);
	struct metadata md[SIZE];
	if_disk_recorded(md);
	while (1)
	{
		printf(">");
		gets(command);
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		int cmd_num = find_command(command);
		if (cmd_num == -1) {
			printf("Invalid command");
			return;
		}
		parse_command(command, cmd_num, md);
	}
	return 0;
}
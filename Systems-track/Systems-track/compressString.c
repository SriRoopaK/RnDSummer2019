#include <stdio.h>
#include <stdlib.h>


int strLen(char string[]){
	int len = 0;
	for (len = 0; string[len] != '\0'; len++);
	return len;
}

int reverse_count(int count){
	int reverseCount = 0;
	while (count > 0){
		reverseCount = reverseCount*10 + (count % 10);
		count = count / 10;
	}
	return reverseCount;
}


void compressed_string(char input_string[]){
	int charPos = 0, count =1, charPos1 = 0, charPos2 = 0;
	int length = strLen(input_string);
	for (charPos = 0; charPos < length - 1; charPos++){
		count = 1;
		for (charPos1 = charPos + 1; charPos1 < length && input_string[charPos1] == input_string[charPos]; charPos1++){
			count++;
		}
		charPos1 = charPos + 1;
		if (count > 1){
			charPos2 = charPos + count;
			count = reverse_count(count);
			while (count > 0){
				input_string[charPos1++] = '0' + (count % 10);
				count = count / 10;
			}
			charPos = charPos1-1;
			for (charPos2 = charPos2; charPos2 < length; charPos2++){
				input_string[charPos1++] = input_string[charPos2];
			}
			input_string[charPos1] = '\0';
			length = strLen(input_string);
		}
	}
}

/*int main(){
	char *input_string = (char *)malloc(sizeof(char) * 1020);
	printf("Enter the string:");
	scanf("%s", input_string);
	fflush(stdin);
	compressed_string(input_string);
	printf("Compressed_string:%s", input_string);
	getchar();
} */
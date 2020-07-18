#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define SIZE 27 // max size of array (-n -e \\x--\\x--\\x--\\x-- + '\0')
#define START_INDEX 6 // skip -n -e in string

// convert string to hex value
uint32_t stoh(char str[]);
// remove all non hex value('\', 'x', etc..)
void clear_str(char str[]);

int main(int argc, char* argv[])

{
	// array for argv[1]
	char str1[SIZE];
	// array for argv[2]
	char str2[SIZE];
	
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	// open bin file 
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	
	// read bin file
	fread(str1, sizeof(char), SIZE, fp1);
	fread(str2, sizeof(char), SIZE, fp2);
	
	// remove all non hex value('\', 'x', etc..) for plus operation
	clear_str(str1);
	clear_str(str2);

	// variable for converted value
	uint32_t hex1 = 0;
	uint32_t hex2 = 0;
	
	// convert string to hex value
	hex1 = stoh(str1);
	hex2 = stoh(str2);

	// plus operation by converted two argv
	uint32_t result = hex1 + hex2;
	
	// print result(decimal, hexadecimal)
	printf("%d(%#x) + %d(%#x) = %d(%#x)\n", hex1, hex1, hex2, hex2, result, result);
	
	fclose(fp2);
	fclose(fp1);
	
	return 0;
}

uint32_t stoh(char str[])
{
	int i;
	uint32_t hex = 0;
	
	for(i=0; str[i] != '\0'; i++)
	{
		// character number - '0' => number
		// in hexadecimal, positional number + 1 => *16 
		if(str[i] >= '0' && str[i] <= '9') 
		{	
			hex = hex * 16 + str[i] - '0'; 
		}
		// 깃허브에 한글 테스트
		else if(str[i] >= 'A' && str[i] <= 'F') 
		{	
			
			hex = hex * 16 + str[i] - 'A' + 10; 
		}
		
		else if(str[i] >= 'a' && str[i] <= 'f') 
		{
			hex = hex * 16 + str[i] - 'a' + 10; 
		}
		else
		{
			fprintf(stderr, "input is wrong"); 
			exit(1);	
		}
	}
	return hex;
}

void clear_str(char str[])
{
	int i,j;
	char temp[SIZE] = {0,};
	
	// only read '0'~'9' and 'a'~'f' and 'A'~'F'
	for(i=START_INDEX, j = 0; str[i] != '\0'; i++)
	{
		if((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F'))
		{
			temp[j++] = str[i];
		}
	}
	// add NULL in last index
	temp[j] = '\0';
	
	// copy temp's memory to original string
	memcpy(str, temp, SIZE+1);
}

		

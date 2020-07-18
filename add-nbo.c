#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#define SIZE 27
#define START_INDEX 6 

uint32_t stoh(char str[])
{
	int i;
	uint32_t hex = 0;
	for(i=0; str[i] != '\0'; i++)
	{
		if(str[i] >= '0' && str[i] <= '9') 
		{	
			hex = hex * 16 + str[i] - '0'; 
		}
	
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
			fprintf(stderr, "잘못된 값이 입력되었습니다."); 
			exit(1);	
		}
	}
	return hex;
}

void clear_str(char str[])
{
	int i,j;
	char temp[SIZE] = {0,};
	for(i=START_INDEX, j = 0; str[i] != '\0'; i++)
	{
		if((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F'))
		{
			temp[j++] = str[i];
		}
	}
	temp[j] = '\0';
	memcpy(str, temp, SIZE+1);
}

int main(int argc, char* argv[])

{
	char str1[SIZE];
	char str2[SIZE];
	
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	
	fread(str1, sizeof(char), SIZE, fp1);
	fread(str2, sizeof(char), SIZE, fp2);
	
	clear_str(str1);
	clear_str(str2);

	int hex1 = 0;
	int hex2 = 0;
	
	hex1 = stoh(str1);
	hex2 = stoh(str2);

	int result = hex1 + hex2;
	
	printf("%d(%#x) + %d(%#x) = %d(%#x)\n", hex1, hex1, hex2, hex2, result, result);
	
	fclose(fp2);
	fclose(fp1);
	
	return 0;
}
		

// 잘못된 파일 코드 저장용입니다.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>

int main(int argc, char* argv[])

{
	uint32_t buffer1;
	uint32_t buffer2;
	
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	// open bin file 
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	
	// read bin file
	fread(&buffer1, sizeof(char), sizeof(uint32_t), fp1);
	fread(&buffer2, sizeof(char), sizeof(uint32_t), fp2);
	
	printf("Before ntohl\n%s : %x\n%s : %x\n", argv[1], buffer1, argv[2], buffer2);
	
	uint32_t n1 = ntohl(buffer1);
	uint32_t n2 = ntohl(buffer2);
	uint32_t result = n1 + n2;
	
	printf("\nAfter ntohl\n");
	printf("%d(%x) + %d(%x) = %d(%x)\n", n1, n1, n2, n2, result, result);

	fclose(fp2);
	fclose(fp1);

	return 0;
}

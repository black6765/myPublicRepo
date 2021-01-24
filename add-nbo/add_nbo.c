#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <netinet/in.h>
#include "add_nbo.h"


void add_nbo(FILE *fp1, FILE *fp2)
{
	uint32_t buffer1;
	uint32_t buffer2;
	// read bin file
	fread(&buffer1, sizeof(uint32_t), 1, fp1);
	fread(&buffer2, sizeof(uint32_t), 1, fp2);
	
	// Convert Network Byte Order to Host Byte Order for add operation
	uint32_t n1 = ntohl(buffer1);
	uint32_t n2 = ntohl(buffer2);
	uint32_t result = n1 + n2;
	
	printf("After Convert Network Byte Order to Host Byte Order\n");
	printf("%d(%#x) + %d(%#x) = %d(%#x)\n", n1, n1, n2, n2, result, result);
}


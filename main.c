#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "add_nbo.h"

int main(int argc, char* argv[])

{
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	// open bin file 
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	
	add_nbo(fp1, fp2);

	fclose(fp2);
	fclose(fp1);

	return 0;
}

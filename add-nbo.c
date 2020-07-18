#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "add-nbo.h"

int main(int argc, char* argv[])

{
	// argv[1]을 위한 배열입니다. 
	char str1[SIZE];
	// argv[2]를 위한 배열입니다. 
	char str2[SIZE];
	
	FILE *fp1 = NULL;
	FILE *fp2 = NULL;
	
	// echo -n -e 명령어로 생성된 바이너리 파일을 엽니다. 
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	
	// 바이너리 파일을 읽어 str1, str2에 각각 저장합니다. 
	fread(str1, sizeof(char), SIZE, fp1);
	fread(str2, sizeof(char), SIZE, fp2);
	
	// 16진수의 연산을 위해서 문자열을 16진수 숫자로 변환하기 전에, 0~9 / a~f / A~F만 남깁니다. 
	clear_str(str1);
	clear_str(str2);
	
	// 문자열을 16진수 숫자로 바꿔주는 함수 stoh를 이용하여 hex1, hex2에 16진수 숫자를 저장합니다. 
	uint32_t hex1 = stoh(str1);
	uint32_t hex2 = stoh(str2);

	// 과제의 조건인 두 16진수의 합 연산을 실행하여 result 변수에 저장합니다. 
	uint32_t result = hex1 + hex2;
	
	// 결과 값을 10진수와 16진수로 출력합니다. 
	printf("%d(%#x) + %d(%#x) = %d(%#x)\n", hex1, hex1, hex2, hex2, result, result);
	
	fclose(fp2);
	fclose(fp1);
	
	return 0;
}

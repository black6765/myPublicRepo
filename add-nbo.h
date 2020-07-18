#pragma once

#define SIZE 27 // 배열의 최대 크기 입니다. 마지막에 널 문자를 고려하였습니다. (-n -e \\x--\\x--\\x--\\x-- + '\0')
#define START_INDEX 6 // 16진수로 계산하기 위해, 바이너리 파일을 불러올 때 남게 되는 "-n -e " 인덱스를 건너 뛰기 위한 숫자입니다. 

// 바이너리 파일을 읽어서 나온 문자열을 16진수로 변환합니다. 
uint32_t stoh(char str[]);
// 16진수 값이 아닌 값들을 문자열에서 제거합니다.('\', 'x', etc..)
void clear_str(char str[]);

uint32_t stoh(char str[])
{
	int i;
	uint32_t hex = 0;
	
	for(i=0; str[i] != '\0'; i++)
	{
		// 문자로 된 숫자에서 '0'을 빼면 숫자가 되는 것을 이용합니다. 
		// 또한, 앞의 자리부터 연산하므로 각 연산시마다 전 값에 *16을 하여 16진수에 대한 자릿수를 맞춰줍니다. 
		if(str[i] >= '0' && str[i] <= '9') 
		{	
			hex = hex * 16 + str[i] - '0'; 
		}
		// 대문자 A~F가 포함되었을 때, 16진수에서 A = 10이므로, 이에 맞게 변환해줍니다.
		// 또한, 앞의 자리부터 연산하므로 각 연산시마다 전 값에 *16을 하여 16진수에 대한 자릿수를 맞춰줍니다.  
		else if(str[i] >= 'A' && str[i] <= 'F') 
		{	
			
			hex = hex * 16 + str[i] - 'A' + 10; 
		}
		// 소문자 a~f가 포함되었을 때, 16진수에서 A = 10이므로 이에 맞게 변환해줍니다. 
		// 또한, 앞의 자리부터 연산하므로 각 연산시마다 전 값에 *16을 하여 16진수에 대한 자릿수를 맞춰줍니다. 
		else if(str[i] >= 'a' && str[i] <= 'f') 
		{
			hex = hex * 16 + str[i] - 'a' + 10; 
		}
		// 이 외의 경우는 잘못된 값이 포함된 것이므로 오류 메시지를 출력하고 프로그램을 종료합니다. 
		else
		{
			fprintf(stderr, "input is wrong"); 
			exit(1);	
		}
	}
	// 계산된 16진수 값을 리턴합니다. 
	return hex;
}

void clear_str(char str[])
{
	int i,j;
	char temp[SIZE] = {0,};
	
	// 문자 '0'~'9', 'a'~'f', 'A'~'F'만 읽어들여 temp에 저장합니다. 
	for(i=START_INDEX, j = 0; str[i] != '\0'; i++)
	{
		if((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f') || (str[i] >= 'A' && str[i] <= 'F'))
		{
			temp[j++] = str[i];
		}
	}
	// temp의 문자열이 끝나는 위치에 NULL 문자를 추가합니다. 
	temp[j] = '\0';
	
	// 문자 '0'~'9', 'a'~'f', 'A'~'F'만으로 구성된 temp를 원본 문자열에 복사합니다. 
	memcpy(str, temp, SIZE);
}

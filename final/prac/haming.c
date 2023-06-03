#include <stdio.h>
/*
	 해밍코드에서    =>  배열에서   
	 p1{3,5,7,9,11}  => {2,4,6,8,10}
	 p2{3,6,7,10,11} => {2,5,6,9,10}
	 p3{5,6,7,12}    => {4,5,6,11}   
	 p4{9,10,11,12}  => {8,9,10,11}
 */

unsigned short binary_output(char word){
	char haming[12] = {0, };	//해밍코드를 담을 배열
	char bin[8] = {0, };			//입력받은 문자의 이진 배열
	//p1~4까지 짝수 패러티비트
	int i, p1 = 0, p2 = 0, p3 = 0, p4 = 0, j = 7;
	unsigned short output = 0;	//결과 값 보낼 것

	//입력 받은 문자의 이진을 하나씩 때서 배열에 저장
	for(i = 0; i < 8; i++)
		bin[i] = word>>(7-i) & 1;
	//잘 들어 갔는지 확인하는 함수	
	
	for(i = 0; i < 8; i++)
		printf("%d ", bin[i]);
	printf("\n");
	
	//패러티 비트에 해당하는 1의 갯수를 카운트
	p1 = bin[7] + bin[6] + bin[4] + bin[3] + bin[1];
	p2 = bin[7] + bin[5] + bin[4] + bin[2] + bin[1];
	p3 = bin[6] + bin[5] + bin[4] + bin[0];
	p4 = bin[3] + bin[2] + bin[1] + bin[0];
	//카운트 된 수 확인
	//printf("p1:%d p2:%d p3:%d p4:%d\n", p1, p2, p3, p4);

	//haming배열에 해밍코드 완성된거 넣는 거
	//짝수 패러티 비트로 해밍코드를 사용함
	for(i = 0; i < 12; i++){
		//11=p1, 10=p2, 8=p3, 4=p4
		if(i == 11){
			if((p1 % 2)==0)	haming[i] = 0;
			else	haming[i] = 1;
		}
		else if(i == 10){
			if((p2 % 2)==0)	haming[i] = 0;
			else	haming[i] = 1;
		}
		else if(i == 8){
			if((p3 % 2)==0)	haming[i] = 0;
			else	haming[i] = 1;
		}
		else if(i == 4){
			if((p4 % 2)==0)	haming[i] = 0;
			else	haming[i] = 1;
		}
		else{
			haming[i] = word>>j & 1;		//j=7
			j--;
		}
	}
	//	배열에 잘 들어갔는지 확인하는 함수
	/*
	for(i = 0; i < 12; i++)
		printf("%d ", haming[i]);
	printf("\n");
	*/	
	//output이라는 short형에 값을 저장	
	output += (haming[0]) * 2048;
	output += (haming[1]) * 1024;
	output += (haming[2]) * 512;
	output += (haming[3]) * 256;
	output += (haming[4]) * 128;
	output += (haming[5]) * 64;
	output += (haming[6]) * 32;
	output += (haming[7]) * 16;
	output += (haming[8]) * 8;
	output += (haming[9]) * 4;
	output += (haming[10]) * 2;
	output += (haming[11]) * 1;

	//printf("output : %d\n", output);

	return output;
}
// 2의 제곱수 구하는 함수
int pow2(int value){
	int result = 1;
	for(int i = 0; i < value; i++)
		result *=2;
	return result;
}

unsigned short output_origin(unsigned short result){
	//11=p1, 10=p2, 8=p3, 4=p4
	char haming[12];
	char bin[8] = {0, };
	int j=11, i, k=0,  p[4]={0, }, syn=0, check=0;
	unsigned short output = 0;
	//비트값을 배열에 넣는 함수
	for(i = 0; i < 12; i++)
		haming[i] = result>>(11-i) & 1;
	//	배열에 잘 들어 갔는지 확인
	for(i = 0; i < 12; i++)
		printf("%d ", haming[i]);
	printf("\n");
	
	p[0] = haming[1] + haming[3] + haming[5] + haming[7] + haming[9] + haming[11];
	p[1] = haming[1] + haming[2] + haming[5] + haming[6] + haming[9] + haming[10];
	p[2] = haming[0] + haming[5] + haming[6] + haming[7] + haming[8];
	p[3] = haming[0] + haming[1] + haming[2] + haming[3] + haming[4];
	printf("p1: %d p2: %d p3: %d p4: %d\n",p[0], p[1], p[2], p[3]);
	//오류가 있는 지 검사
	for(i = 0; i < 4; i++){
		if(p[i]%2 == 1)	check += 1 * pow2(3-i);
		else if(p[i]%2 == 0) check += 0 * pow2(3-i);
	}	
	printf("check : %d\n", check);
	if(check != 0){
		if(haming[check] == 0) haming[check] = 1;
		else if(haming[check] == 1) haming[check] = 0;
	}
	printf("check befor\n");
	for(i = 0; i < 12; i++)
		printf("%d ", haming[i]);
	printf("\n");
	for(i = 0; i <12; i++){
		if(i==11||i==10||i==8||i==4)
			continue;
		else{
			bin[k] = haming[i];
			k++;
		}
	}
	printf("----------result------------\n");
	for(i = 0; i < 8; i++)
		printf("%d ", bin[i]);
	printf("\n");

	output += (bin[0]) * 128;
	output += (bin[1]) * 64;
	output += (bin[2]) * 32;
	output += (bin[3]) * 16;
	output += (bin[4]) * 8;
	output += (bin[5]) * 4;
	output += (bin[6]) * 2;
	output += (bin[7]) * 1;

	return output;
}	

int main(int argc, char* argv[]){
	char word;
	unsigned short result = 0;
	printf("문자를 입력하세요: ");
	scanf("%c", &word);
	result =  binary_output(word);
	//printf("result : %d\n", result);

	unsigned short result_word = output_origin(result);
	printf("result_word: %c\n", result_word);

	return 0;
}

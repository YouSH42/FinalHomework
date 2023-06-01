#include <stdio.h>

//해밍코드에서    =>  배열에서    \
	p1{3,5,7,9,11}  => {2,4,6,8,10} \
	p2{3,6,7,10,11} => {2,5,6,9,10} \
	p3{5,6,7,12}    => {4,5,6,11}   \
	p4{9,10,11,12}  => {8,9,10,11}

	void binary_output(char word){
		char haming[12] = {0, };
		char bin[8] = {0, };
		int i, p1 = 0, p2 = 0, p3 = 0, p4 = 0, j = 7;
		unsigned short output = 0;

		for(i = 0; i < 8; i++){
			bin[i] = word>>(7-i) & 1;
		}
		for(i = 0; i < 8; i++)
			printf("%d ", bin[i]);
		printf("\n");

		p1 = bin[7] + bin[6] + bin[4] + bin[3] + bin[1];
		p2 = bin[7] + bin[5] + bin[4] + bin[2] + bin[1];
		p3 = bin[6] + bin[5] + bin[4] + bin[0];
		p4 = bin[3] + bin[2] + bin[1] + bin[0];

		printf("p1:%d p2:%d p3:%d p4:%d\n", p1, p2, p3, p4);

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

		for(i = 0; i < 12; i++)
			printf("%d ", haming[i]);
		printf("\n");

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

		printf("output : %d\n", output);
	}


int main(int argc, char* argv[]){
	//바이트 문자열을 실제 2진수로 바꿀 수 있는지 토이 실험
	//char arr[8] = {0,0,0,0,0,1,0,1};	//5
	//unsigned short output = 0;
	char word;
	printf("문자를 입력하세요: ");
	scanf("%c", &word);
	binary_output(word);
	return 0;
}

/*
	 sum += (arr[0]) * 128;
	 sum += (arr[1]) * 64;
	 sum += (arr[2]) * 32;
	 sum += (arr[3]) * 16;
	 sum += (arr[4]) * 8;
	 sum += (arr[5]) * 4;
	 sum += (arr[6]) * 2;
	 sum += (arr[7]) * 1;

	 printf("sum : %d\n", sum);

 */

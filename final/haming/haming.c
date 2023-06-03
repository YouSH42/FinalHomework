#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//문자 하나와 배열을 가져와서 배열에 해밍코드화된 값을 저장
void mk_haming(char ch, char haming[]) {
	short bin[8];
	int j = 0, i;

	for(i = 7; i >= 0; i--) 
		bin[7-i] = (ch >> i) & 1;

	haming[11] = (bin[7] + bin[6] + bin[4] + bin[3] + bin[1]) % 2;
	haming[10] = (bin[7] + bin[5] + bin[4] + bin[2] + bin[1]) % 2;
	haming[8] = (bin[6] + bin[5] + bin[4] + bin[0]) % 2;
	haming[4] = (bin[3] + bin[2] + bin[1] + bin[0]) % 2;

	for(i = 0; i < 12; i++){
		if (i == 4||i == 8||i == 10||i == 11)
			continue;
		else haming[i] = bin[j++];
	}
}
//해밍코드를 가져와서 16*12배열에 저장
void mk_arr_1612(char test[], char storage[][12]){
	char haming[12];
	for(int i = 0; i < 16; i++){
		mk_haming(test[i], haming); 
		for(int k = 0; k < 12; k++)
			storage[i][k] = haming[k];		
	}
}
// 16*12 배열에 저장한 값 확인용
void print_haming(char storage[][12]){
	for(int i = 0; i < 16; i++){
		printf("%d 번째\n", i);
		for(int k = 0; k < 12; k++)
			printf("%d ", storage[i][k]);
		printf("\n");
	}
}

int main() {
	char test[16] = {'A','B','C','D','E','F','G','H','I','J','K','L',\
		'M','N','O','P'};
	char storage[16][12];
	mk_arr_1612(test, storage);
	//print_haming(storage);

	return 0;
}

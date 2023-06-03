#include <stdio.h>

int pow2(int value){
	int result = 1;
	for(int i = 0; i < value; i++)
		result *=2;
	return result;
}

int main(void){
	for(int i = 0; i < 10; i++)
		printf("%d ", pow2(i));

	return 0;
}

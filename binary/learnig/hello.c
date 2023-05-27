#include <stdio.h>

int main(void){
	FILE *fp = NULL;
	fp = fopen("temp.txt","rb");
	int arr[10] = {0,1,2,3,4,5,6,7,8,9};
	int value;

	//fwrite(arr, sizeof(int), 10, fp);
	fseek(fp, -4, SEEK_END);

	long position = ftell(fp);
	printf("현재 위치: %ld\n", position);
	fread(&value, sizeof(int), 1, fp);
	printf("값 : %d\n", value);

	fclose(fp);

	return 0;
}

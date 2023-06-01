#include <stdio.h>

int main(void){
	FILE *fp = fopen("temp.txt","wb");
	int arr = 10;
	//int value;

	fwrite(&arr, sizeof(int), 1, fp);
	//fseek(fp, -4, SEEK_END);

	//long position = ftell(fp);
	//printf("현재 위치: %ld\n", position);
	//fread(&value, sizeof(int), 1, fp);
	//printf("값 : %d\n", value);

	fclose(fp);

	return 0;
}

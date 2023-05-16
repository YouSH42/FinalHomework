#include <stdio.h>
#include <stdlib.h>

int main(void){
	FILE *fp;

	fp = fopen("sales.txt","a");
	fprintf(fp, "2020 sales\n");
	
	fclose(fp);
	return 0;
}

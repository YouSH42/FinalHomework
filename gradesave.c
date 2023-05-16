#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *fp;
	int number;
	char name[30];
	int score;
	char ch;

	fp = fopen("score.txt","a");
	if(fp == NULL){
		printf("성적 파일을 열 수 없습니다\n");
		exit(0);
	}

	while(1){
		printf("학번: ");
		scanf("%d", &number);

		printf("이름 : ");
		scanf("%s", name);

		printf("성적 : ");
		scanf("%f", &score);

		fprintf(fp,"%d %s %d\n", number, name, score);

		printf("데이터 추가를 계속?(y/n) :");
		ch = getchar();
		if(ch == 'n')
			break;
	}
	
	fclose(fp);

	return 0;
}

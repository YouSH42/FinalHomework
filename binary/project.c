#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256
#define MAX_AGE 128
#define MAX_HP 65536
#define ALLIANCE 256

int show_select(){
	int input;
	printf("1. 신규 플레이어 정보 기록\n");
	printf("2. 기록된 모든 플레이어 정보 확인\n");
	printf("3. 플레이어 삭제\n");
	printf("4. 종료\n");
	printf("입력하세요>");
	scanf("%d%*c", &input);

	return input;
}

void player_info_record(){
	int i, age, hp, all_cnt = 0;
	double x, y;
	char ch = 'Y', pl_ID[MAX_SIZE], alliance[ALLIANCE][MAX_SIZE],\
					 	fl_name[MAX_SIZE];
	FILE *fp = NULL;

	if((fp = fopen("user.txt", "wb")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	

	printf("ID 를 입력하세요:");
	scanf("%s%*c", pl_ID);
	printf("나이를 입력하세요:");
	scanf("%d", &age);
	printf("HP 를 입력하세요:");
	scanf("%d", &hp);
	printf("X 좌표를 입력하세요:");
	scanf("%lf", &x);
	printf("Y 좌표를 입력하세요:");
	scanf("%lf", &y);
	while(ch == 'Y'){
		printf("동맹 ID 를 입력하세요:");
		scanf("%s%*c", alliance[all_cnt]);
		all_cnt++;
		printf("동맹을 계속 추가할까요?:");
		ch = getchar();
		scanf("%*c");		//\n의 값을 무시하는 함수
	}
	fwrite(pl_ID, sizeof(char[MAX_SIZE]), 1, fp);
	fwrite(&age, sizeof(int), 1, fp);
	fwrite(&hp, sizeof(int), 1, fp);
	fwrite(&x, sizeof(double), 1, fp);
	fwrite(&y, sizeof(double), 1, fp);
	fwrite(&all_cnt, sizeof(int), 1, fp);
	for(i = 0; i < all_cnt; i++)
		fwrite(alliance[i], sizeof(char[MAX_SIZE]), 1, fp);
	printf("완료되었습니다.\n");
	fclose(fp);
}

	//printf("id : %s age : %d hp: %d x:%.3f y:%.3f all_cnt : %d\n",\
	pl_ID, age, hp, x, y, all_cnt);	

void player_info_check(){
	int i, age, hp, all_cnt;
	double x, y;
	char pl_ID[MAX_SIZE], alliance[ALLIANCE][MAX_SIZE];
	FILE *fp = NULL;

	if((fp = fopen("user.txt", "rb")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	
	
	fread(pl_ID, sizeof(char[MAX_SIZE]), 1, fp);
	fread(&age, sizeof(int), 1, fp);
	fread(&hp, sizeof(int), 1, fp);
	fread(&x, sizeof(double), 1, fp);
	fread(&y, sizeof(double), 1, fp);
	fread(&all_cnt, sizeof(int), 1, fp);
	for(i = 0; i < all_cnt; i++)
		fread(alliance[i], sizeof(char[MAX_SIZE]), 1, fp);
	printf("ID: %s / 나이:%d / hp:%d / 좌표:%.3f, %.3f\n",\
	pl_ID, age, hp, x, y);	
	printf("등록된 동맹 수: %d명\n",all_cnt);
	for(i = 0; i < all_cnt-1; i++)
		printf("%s / ", alliance[i]);
	printf("%s\n", alliance[i]);
	printf("완료되었습니다.\n");

	fclose(fp);
}

void player_delete(){
	printf("delete\n");
}

void start_program(int input){
	while(1){
		switch(input){
			case 1:
				player_info_record();
				break;
			case 2:
				player_info_check();
				break;
			case 3:
				player_delete();
				break;
			case 4:
				printf("종료되었습니다\n");
				return ;
			default:
				printf("잘못된 입력입니다\n");
		}
		input = show_select();
	}
}

int main(int argc, char* argv[]){
	int input = 0;

	input = show_select();
	start_program(input);

	return 0;
}

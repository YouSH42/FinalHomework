#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_SIZE 256
#define MAX_AGE 128
#define MAX_HP 65536
#define ALLIANCE 256

int is_text_file(const char *filename) {
	const char *extension = strrchr(filename, '.');
	if (extension != NULL && strcmp(extension, ".txt") == 0) {
		return 1; // 텍스트 파일인 경우
	}
	return 0; // 텍스트 파일이 아닌 경우
}

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
						fl_name[MAX_SIZE], tmp[MAX_SIZE];
	FILE *fp = NULL;

	printf("ID 를 입력하세요:");
	scanf("%s%*c", pl_ID);
	strcpy(tmp, pl_ID);
	strcat(tmp, ".txt");
	if((fp = fopen(tmp, "ab")) == NULL){
		fprintf(stderr, "원본 파일을 열 수 없습니다.\n");
		exit(1);
	}
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
	fwrite(pl_ID, sizeof(char), MAX_SIZE, fp);
	fwrite(&age, sizeof(int), 1, fp);
	fwrite(&hp, sizeof(int), 1, fp);
	fwrite(&x, sizeof(double), 1, fp);
	fwrite(&y, sizeof(double), 1, fp);
	fwrite(&all_cnt, sizeof(int), 1, fp);
	for(i = 0; i < all_cnt; i++)
		fwrite(alliance[i], sizeof(char), MAX_SIZE, fp);
	printf("완료되었습니다.\n");
	fclose(fp);
}

int find_user_cnt(){
	const char *folder_path = "./"; // 폴더 경로를 지정합니다
	DIR *dir;
	struct dirent *entry;
	int user_cnt = 0;

	dir = opendir(folder_path);
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return 1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 처리합니다
			if (is_text_file(entry->d_name)) {
				user_cnt++;
			}
		}
	}
	closedir(dir);
	return user_cnt;
}

void player_info_check(){
	const char *folder_path = "./"; // 폴더 경로를 지정합니다
	DIR *dir;
	struct dirent *entry;
	int age, hp, all_cnt, user_cnt, i, k = 1;
	double x, y;
	char pl_ID[MAX_SIZE], tmp[MAX_SIZE], alliance[ALLIANCE][MAX_SIZE];
	FILE *fp = NULL;

	user_cnt = find_user_cnt();
	printf("총 %d명의 플레이어가 기록되어 있습니다.\n", user_cnt);

	dir = opendir(folder_path);
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return ;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 처리합니다
			if (is_text_file(entry->d_name)) {
				if((fp = fopen(entry->d_name, "rb")) == NULL){
					fprintf(stderr,"파일을 열 수 없습니다.\n");
					exit(1);
				}	
				fread(pl_ID, sizeof(char), MAX_SIZE, fp);
				fread(&age, sizeof(int), 1, fp);
				fread(&hp, sizeof(int), 1, fp);
				fread(&x, sizeof(double), 1, fp);
				fread(&y, sizeof(double), 1, fp);
				fread(&all_cnt, sizeof(int), 1, fp);
				for(i = 0; i < all_cnt; i++)
					fread(alliance[i], sizeof(char), MAX_SIZE, fp);
				printf("[플레이어%d]\n", k++);
				printf("ID: %s / 나이:%d / hp:%d / 좌표:%.3f, %.3f\n",\
						pl_ID, age, hp, x, y);	
				printf("등록된 동맹 수: %d명\n",all_cnt);
				for(i = 0; i < all_cnt - 1; i++)
					printf("%s / ", alliance[i]);
				printf("%s\n\n", alliance[i]);
				fclose(fp);
			}
		}
	}
	printf("완료되었습니다.\n");
	closedir(dir);
}

void player_delete(){
	char name[MAX_SIZE], tmp[MAX_SIZE];

	printf("삭제할 ID를 입력하세요: ");
	scanf("%s%*c", name);
	strcpy(tmp, name);
	strcat(tmp,".txt");
	const char *folder_path = "./"; // 폴더 경로를 지정합니다
	const char *search_name = tmp; // 검색할 파일 이름을 지정합니다
	DIR *dir;
	struct dirent *entry;

	dir = opendir(folder_path);
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return;
	}
	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 검색합니다
			if (strcmp(entry->d_name, search_name) == 0) {
				printf("%s 삭제완료.\n", name);
				remove(search_name);
				break;
			}
		}
	}
	closedir(dir);
	if (entry == NULL) {
		printf("해당 데이터는 존재하지 않습니다.\n");
	}
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

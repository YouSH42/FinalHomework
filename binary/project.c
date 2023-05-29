#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_SIZE 256
#define MAX_AGE 128
#define MAX_HP 65536
#define ALLIANCE 256

int is_text_file(const char *filename) {		//txt파일인지 아닌지 확인하는 함수
	const char *extension = strrchr(filename, '.');
	if (extension != NULL && strcmp(extension, ".txt") == 0) {
		return 1; // 텍스트 파일인 경우
	}
	return 0; // 텍스트 파일이 아닌 경우
}

int show_select(){	//선택창 및 선택한 값 리턴 함수
	int input;
	printf("1. 신규 플레이어 정보 기록\n");
	printf("2. 기록된 모든 플레이어 정보 확인\n");
	printf("3. 플레이어 삭제\n");
	printf("4. 종료\n");
	printf("입력하세요>");
	scanf("%d%*c", &input);

	return input;
}

void player_info_record(){	//플레이어 정보 입력 받는 함수
	int i, age, hp, all_cnt = 0;		//플레이어 정보 
	double x, y;										//플레이어 정보
	char ch = 'Y', pl_ID[MAX_SIZE], alliance[ALLIANCE][MAX_SIZE],\
						fl_name[MAX_SIZE], tmp[MAX_SIZE];		//플레이어 정보
	FILE *fp = NULL;
	//플레이어 정보 입력 받는 코드
	printf("ID 를 입력하세요:");
	scanf("%s%*c", pl_ID);
	strcpy(tmp, pl_ID);			//임시파일에 아이디를 입력 받음
	strcat(tmp, ".txt");		//.txt를 붙여서 텍스트 파일 이름으로 변경
	if((fp = fopen(tmp, "wb")) == NULL){	// 아이디로 파일 생성
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
	while(ch == 'Y'){		// Y가 들어오면 계속 입력 받음
		printf("동맹 ID 를 입력하세요:");
		scanf("%s%*c", alliance[all_cnt]);
		all_cnt++;
		printf("동맹을 계속 추가할까요?:");
		ch = getchar();
		scanf("%*c");		//\n의 값을 무시하는 함수
	}
	// 파일에 바이너리 형식으로 입력
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

int find_user_cnt(){		//플레이어가 몇명이 있는지 확인 후 그 숫자만큼 리턴
	const char *folder_path = "./"; // 폴더 경로를 지정
	DIR *dir;
	struct dirent *entry;
	int user_cnt = 0;		//플레이어 수

	dir = opendir(folder_path);
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return 1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 처리
			if (is_text_file(entry->d_name)) {
				user_cnt++;	//txt 파일 일 경우 플레이어 파일로 간주 후 증가시킴
			}
		}
	}
	closedir(dir);
	return user_cnt;
}
//플레이어 정보를 출력하는 함수
void player_info_check(){
	const char *folder_path = "./"; // 폴더 경로 지정
	DIR *dir;
	struct dirent *entry;
	int age, hp, all_cnt, user_cnt, i, k = 1;		//플레이어 정보를 입력 받을 변수
	double x, y;		//플레이어 정보를 입력 받을 변수
	char pl_ID[MAX_SIZE], tmp[MAX_SIZE], alliance[ALLIANCE][MAX_SIZE];
	//플레이어 정보를 입력 받을 변수
	FILE *fp = NULL;

	user_cnt = find_user_cnt();	//플레이어 수를 확인
	printf("총 %d명의 플레이어가 기록되어 있습니다.\n", user_cnt);
	dir = opendir(folder_path);		//디렉토리 오픈
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return ;
	}
	while ((entry = readdir(dir)) != NULL) {	//모든 파일 검사
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 처리합니다
			if (is_text_file(entry->d_name)) {
				if((fp = fopen(entry->d_name, "rb")) == NULL){
					fprintf(stderr,"파일을 열 수 없습니다.\n");
					exit(1);
				}		//바이너리 정보를 읽어와서 변수에 저장
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
// 플레이어 제거
void player_delete(){
	char name[MAX_SIZE], tmp[MAX_SIZE];

	printf("삭제할 ID를 입력하세요: ");	//삭제할 id 입력 받음
	scanf("%s%*c", name);
	strcpy(tmp, name);		//임시 파일에 id 복사
	strcat(tmp,".txt");	//임시 파일에 txt를 붙여서 검사할 수 있게 만듬
	const char *folder_path = "./"; // 폴더 경로 지정
	const char *search_name = tmp; // 검색할 파일 이름 지정
	DIR *dir;
	struct dirent *entry;

	dir = opendir(folder_path);
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return;
	}
	while ((entry = readdir(dir)) != NULL) {	//파일 전부 다 검사
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 검색합니다
			if (strcmp(entry->d_name, search_name) == 0) {	//해당하는 파일 검사
				printf("%s 삭제완료.\n", name);
				remove(search_name);	// 해당하는 파일 삭제
				break;
			}
		}
	}
	closedir(dir);
	if (entry == NULL) {		//만약 삭제한 파일이 없다면
		printf("해당 데이터는 존재하지 않습니다.\n");
	}
}
// 사용자의 설정 명령을 받아서 해당하는 함수로 보내주는 함수
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

#include <stdio.h>
#include <stdlib.h>

int user_menu(){
	int input = 0;

	printf("1. 신규회원 저장\n");
	printf("2. 회원정보 수정\n");
	printf("3. 회원 삭제\n");
	printf("4. 모든 회원 리스트\n");
	printf("5. 종료\n");

	scanf("%d", &input);
	return input;
}

void add_user_info(){
	FILE *fp;
	int age;
	char name[255];
	char eail[255];
	
	fp = fopen("user.txt","a");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}

}

void user_request(int input){
	while(1){
		switch (input){
			case 1:
				add_user_info();
				break;
			case 2:
			case 3:
			case 4:
			case 5:
				return;
			default:
				printf("잘못된 입력입니다\n");
		}
	}
}

int main(int argc, char *argv[]){
	int input = 0;
	input = user_menu();

	user_request(input);

	return 0;
}

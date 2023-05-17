#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

int user_menu(){
	int input;

	printf("1. 신규회원 저장\n");
	printf("2. 회원정보 수정\n");
	printf("3. 회원 삭제\n");
	printf("4. 모든 회원 리스트\n");
	printf("5. 종료\n");
	printf("입력하세요>");

	scanf("%d%*c", &input);
	return input;
}

void add_user_info(){
	FILE *fp;
	int age;
	char name[MAX_SIZE];
	char email[MAX_SIZE];
	char ch;

	fp = fopen("user.txt","a");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}
	while(1){	
		printf("이름 : ");
		fgets(name, MAX_SIZE, stdin);
		name[strlen(name)-1] = '\0';
		printf("나이 : ");
		scanf("%d", &age);	
		printf("이메일 : ");
		scanf("%s%*c", email);	

		fprintf(fp,"%s / %d / %s\n", name, age, email);

		printf("계속 입력 할까요?(Y/N)");
		ch = getchar();
		scanf("%*c");
		if(ch == 'N')
			break;
	}
	fclose(fp);
}

void mod_user_info(){
	printf("mod\n");
}

void del_user_info(){ // 미구현
	char search[MAX_SIZE];
	FILE *in_fp, *out_fp;
	char buffer[MAX_SIZE];

	printf("제거할 회원 : "); 	//함수가 끝나도 한번 더 실행됨
															//확인 필요
	scanf(" %[^\n]s", search);

	if((in_fp = fopen("user.txt", "r")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	

	if((out_fp = fopen("inser.txt", "w")) == NULL){
		fprintf(stderr,"복사 파일을 열 수 없습니다.\n");
		exit(1);
	}
	//제대로 작동하지 않음 다시 확인해 볼 필요 있음
	while(fgets(buffer, MAX_SIZE, in_fp) != NULL){
		if(strstr(buffer, search) != NULL)
			fputs(buffer, out_fp);
	}	

	//삭제한 임시 파일의 값을 원본 파일에 복사하는코드
	fclose(in_fp);
	fclose(out_fp);
}

void print_user_info(){
	FILE *fp;
	char c;

	fp = fopen("user.txt","r");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}

	while((c = fgetc(fp)) != EOF)
		printf("%c", c);

	fclose(fp);
}

void user_request(int input){
	while(1){
		switch (input){
			case 1:
				add_user_info();
				break;
			case 2:
				mod_user_info();
				break;
			case 3:
				del_user_info();
				break;
			case 4:
				print_user_info();
				break;
			case 5:
				printf("종료합니다\n");
				return;
			default:
				printf("잘못된 입력입니다\n");
		}
		input = user_menu();
	}
}

int main(int argc, char *argv[]){
	int input = 0;
	input = user_menu();

	user_request(input);

	return 0;
}

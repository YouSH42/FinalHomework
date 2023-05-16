#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	char name[255];
	char email[255];
	char ch;

	fp = fopen("user.txt","a");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}
	while(1){	
		printf("이름 : ");
		fgets(name, 255, stdin);
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

void del_user_info(){
	FILE *fp1, *fp2;

	if((fp1 = fopen("user.txt", "r")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	

	if((fp2 = fopen("inser.txt", "w")) == NULL){
		fprintf(stderr,"복사 파일을 열 수 없습니다.\n");
		exit(1);
	}
	char c;
	while((c = fgetc(fp1)) != EOF)
		fputc(c,fp2);
	
	fclose(fp1);
	fclose(fp2);
	printf("...complete\n");
}

void print_user_info(){
	FILE *fp;
	char c;

	fp = fopen("user.txt","r");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}

	while ((c = fgetc(fp)) != EOF)
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

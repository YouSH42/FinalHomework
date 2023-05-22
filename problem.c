#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

void file_copy(){
	FILE *ori_fp, *copy_fp;

	if((ori_fp = fopen("user.txt", "w")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	

	if((copy_fp = fopen("tmp.txt", "r")) == NULL){
		fprintf(stderr,"복사 파일을 열 수 없습니다.\n");
		exit(1);
	}

	int c;
	while((c = fgetc(copy_fp)) != EOF)
		fputc(c, ori_fp);

	fclose(ori_fp);
	fclose(copy_fp);
}

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

int is_email_fake(char email[]){
	int len = strlen(email);
	int is_index_At = -1;
	int after_dot = -1;

	for(int i = 0; i < len; i++){
		if(email[i] == '@'){
			is_index_At = i;
			break;
		}
	}
	if(is_index_At == 0 || is_index_At == -1)
		return 1;

	for(int i = is_index_At + 1; i < len; i++){
		if(email[i] == '.'){
			after_dot = i;
			break;	
		}	
	}
	if(after_dot == is_index_At + 1)
		return 1;

	if(after_dot == len - 1)
		return 1;

	return 0;
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
		int jud = is_email_fake(email);
		if(jud){
			printf("잘못된 이메일 형식입니다\n");
			break;
		}

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
	FILE *in_fp, *out_fp;
	int age, count = 0;
	char search[MAX_SIZE], buffer[MAX_SIZE];
	char name[MAX_SIZE], email[MAX_SIZE];
	char *tmp;

	printf("수정할 사람의 이름을 입력해주세요 : "); 
	fgets(search, MAX_SIZE, stdin);
	search[strlen(search)-1] = '\0';

	if((in_fp = fopen("user.txt", "r")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	

	if((out_fp = fopen("tmp.txt", "w")) == NULL){
		fprintf(stderr,"임시 파일을 열 수 없습니다.\n");
		exit(1);
	}

	while(fgets(buffer, MAX_SIZE, in_fp) != NULL){
		if(strstr(buffer, search) != NULL){
			printf("사용자 %s 을 수정합니다.\n", search);

			printf("이름 : ");
			fgets(name, MAX_SIZE, stdin);
			name[strlen(name)-1] = '\0';
			printf("나이 : ");
			scanf("%d", &age);	
			printf("이메일 : ");
			scanf("%s%*c", email);	
			int jud = is_email_fake(email);
			if(jud){
				printf("잘못된 이메일 형식입니다\n");
				return ;
			}
			fprintf(out_fp,"%s / %d / %s\n", name, age, email);
			count++;
		}
		else
			fputs(buffer, out_fp);
	}	
	if(count == 0)
		printf("사용자 %s 은 없습니다.\n", search);
	else
		printf("수정 완료 되었습니다\n");

	fclose(in_fp);
	fclose(out_fp);

	file_copy();
}

void del_user_info(){ 
	char search[MAX_SIZE];
	FILE *in_fp, *out_fp;
	char buffer[MAX_SIZE];

	printf("제거할 회원 : "); 
	
	scanf(" %[^\n]s", search);

	if((in_fp = fopen("user.txt", "r")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	

	if((out_fp = fopen("tmp.txt", "w")) == NULL){
		fprintf(stderr,"임시  파일을 열 수 없습니다.\n");
		exit(1);
	}

	while(fgets(buffer, MAX_SIZE, in_fp) != NULL){
		if(strstr(buffer, search) == NULL)
			fputs(buffer, out_fp);
	}	

	fclose(in_fp);
	fclose(out_fp);

	file_copy();
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

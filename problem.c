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

int is_false(int age, char email[]){
	int len = strlen(email);
	int i = 0, at_cnt = 0, dot_cnt = 0 , dot = -1, index_At = -1;

	if(age > 200)
		return 2;

	for(i = 0; i < len; i++){
		if(email[i] == '@'){
			index_At = i;
			at_cnt++;
		}
		else if(email[i] == '.'){
			dot = i;
			dot_cnt++;
		}
	}
	if(dot == -1 || index_At == -1 || dot < index_At || index_At == 0)
		return 1;
	else if(index_At + 1 == dot || dot + 1 == len)
		return 1;
	else if(at_cnt >= 2 || dot_cnt >= 2)
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
		int jud = is_false(age, email);
		if(jud == 1){
			printf("잘못된 이메일 형식입니다\n");
			break ;
		}
		else if(jud == 2){
			printf("나이가 너무 많습니다\n");
			break ;	
		}

		fprintf(fp,"%s/%d/%s\n", name, age, email);

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
			int jud = is_false(age, email);
			if(jud == 1){
				printf("잘못된 이메일 형식입니다\n");
				return ;  // continue
			}
			else if(jud == 2){
				printf("나이가 너무 많습니다\n");
				return ;  //continue
			}
			fprintf(out_fp,"%s/%d/%s\n", name, age, email);
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

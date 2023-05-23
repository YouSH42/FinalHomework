#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 255

//임시 파일을 원본 파일에 복사하는 함수
void file_copy(){
	FILE *ori_fp, *copy_fp;
	int c;

	if((ori_fp = fopen("user.txt", "w")) == NULL){
		fprintf(stderr,"원본 파일을 열 수 없습니다.\n");
		exit(1);
	}	
	if((copy_fp = fopen("tmp.txt", "r")) == NULL){
		fprintf(stderr,"복사 파일을 열 수 없습니다.\n");
		exit(1);
	}

	while((c = fgetc(copy_fp)) != EOF)
		fputc(c, ori_fp);

	fclose(ori_fp);
	fclose(copy_fp);
}

//사용자에게 보여주는 설정창 함수
int user_menu(){
	int input;

	printf("1. 신규회원 저장\n");
	printf("2. 회원정보 수정\n");
	printf("3. 회원 삭제\n");
	printf("4. 모든 회원 리스트\n");
	printf("5. 종료\n");
	printf("입력하세요>");
	scanf("%d%*c", &input);

	return input;	//사용자의 입력을 반환한다.
}

//이메일 예외 처리 함수
int is_false(int age, char email[]){
	int len = strlen(email);	//이메일 길이 저장
	int i = 0, at_cnt = 0, dot_cnt = 0 , dot = -1, index_At = -1;
	// index_At는 @ 위치정보, dot은 .의 위치정보
	// at_cnt는 @의 갯수 확인, dot_cnt는 .의 갯수 확인
	if(age > 200)
		return 2;		//나이가 200이 넘으면 2를 리턴
	//이메일 문자열을 검사하는 반복문
	for(i = 0; i < len; i++){
		if(email[i] == '@'){
			index_At = i;		// @가 나오면 변수에 위치값 저장
			at_cnt++;				// @의 개수를 카운트
		}
		else if(email[i] == '.'){
			dot = i;				// .이 나오면 변수에 위치값 저장
			dot_cnt++;			// .의 개수를 카운트
		}
	}
	// dot과 index_At가 -1일 경우 @와 .이 나오지 않았다는 것
	// index_At가 dot보다 값이 클 경우 @이가 . 뒤에 나왔다는 것
	// index_At가 0이라는 것은 @가 이메일의 맨 처음에 나왔다는 것
	// index_At + 1 과 dot이 같다는 것은 @이 뒤에 바로 .이 나왔다는 것
	// dot + 1이 len이라는 것은 .뒤에 나오는 문자없이 끝났다는 것
	if(dot == -1 || index_At == -1 || dot < index_At || index_At == 0)
		return 1;
	else if(index_At + 1 == dot || dot + 1 == len)
		return 1;
	else if(at_cnt >= 2 || dot_cnt >= 2)
		return 1;

	return 0;		//모든 조건을 통과하면 0 
}

// 회원 정보를 입력 받는 함수
void add_user_info(){
	FILE *fp;
	int age, jud;
	char ch, name[MAX_SIZE], email[MAX_SIZE];

	fp = fopen("user.txt","a");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}

	while(1){	
		printf("이름 : ");
		fgets(name, MAX_SIZE, stdin);	//입력값이\n이 들어오기전까지 받는다
		name[strlen(name)-1] = '\0';	//name의 마지막 값이 \n이므로 지워준다
		printf("나이 : ");
		scanf("%d", &age);	
		printf("이메일 : ");
		scanf("%s%*c", email);		//%*c는 맨뒤에 \n를 무시해주는 코드이다
		jud = is_false(age, email); //이메일과 나이를 검사
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
		ch = getchar();	//Y,N의 값을 입력 받는다
		scanf("%*c");		//\n의 값을 무시하는 함수
		if(ch == 'N')	//N의 값이 들어올 경우 반복문을 멈춘다
			break;
	}
	fclose(fp);
}
// 회원 정보를 수정하는 함수
void mod_user_info(){
	FILE *in_fp, *out_fp;
	int age, jud, count = 0;
	char search[MAX_SIZE], buffer[MAX_SIZE];
	char name[MAX_SIZE], email[MAX_SIZE];
	char *tmp;

	printf("수정할 사람의 이름을 입력해주세요 : "); 
	fgets(search, MAX_SIZE, stdin);
	search[strlen(search)-1] = '\0';	//문자열 끝의 \n 제거
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
			jud = is_false(age, email);
			// jud에1이나 2가 들어올 경우 잘못된 입력이므로 원본 데이터를 그대로 입력한다
			if(jud == 1){		
				fputs(buffer, out_fp);
				continue;
			}
			else if(jud == 2){
				fputs(buffer, out_fp);
				continue;
			}
			fprintf(out_fp,"%s/%d/%s\n", name, age, email);
			count++;		//수정되었을 경우 count를 올린다
		}
		else
			fputs(buffer, out_fp);
	}	
	//	무슨 작업이 일어났는지 알려준다
	if(jud == 1)
		printf("잘못된 이메일 형식입니다\n");
	else if(jud == 2)
		printf("나이가 너무 많습니다\n");
	else if(count == 0)
		printf("사용자 %s 은 없습니다.\n", search);
	else if(count > 0)
		printf("수정 완료 되었습니다\n");

	fclose(in_fp);
	fclose(out_fp);

	file_copy();		//임시파일에 저장한 정보를 원본 파일에 복사한다
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
	// 한문장식  buffer에 넣어서 가져와서 일치하는 문자가 없다면 임시파일에 입력
	// 만약 일치하는 문자가 있다면 임시파일에 입력하지 않는다
	while(fgets(buffer, MAX_SIZE, in_fp) != NULL){
		if(strstr(buffer, search) == NULL)
			fputs(buffer, out_fp);
	}	
	fclose(in_fp);
	fclose(out_fp);

	file_copy();		//임시 파일에 저장한 정보를 원본파일에 복사한다.
}
// 데이터베이스에 저장된 회원의 리스트를 출력하는 함수
void print_user_info(){
	FILE *fp;
	char c;

	fp = fopen("user.txt","r");
	if(fp == NULL){
		printf("파일을 열 수 없습니다\n");
		exit(1);
	}
	while((c = fgetc(fp)) != EOF)		//한글자씩 가져와서 출력한다
		printf("%c", c);
	fclose(fp);
}
// 유저의 응답을 입력받아 원하는 명령으로 보내주는 함수
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

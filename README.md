# 컴공창 기말 프로젝트

## C언어 파일처리 함수
- fopen
- fclose
- fprintf
- fscanf

### fopen
- 파일에 접근할 수 있도록 도와주는 함수  

형식
```
#include <stdio.h>

FILE *fopen(const char *filename, const char *mode)
```
예시
```
#include <stdio.h>

FILE *fp = fopen("test.txt","w");
```
함수의 첫번째 파라미터에는 자신이 접근하고 싶은 파일의 이름을 기입  
함수의 두번째 파라미터에는 파일을 어떠한 형식으로 열 것인지에 대해 기입  
 --- -
##### 파일을 여는 형식
- w  
w는 write의 약자로 쓰는 기능만 가지고 있는 형식  
기존에 존재하는 파일을 w기능으로 열 경우 기존의 내용을 덮어씌움  
- r  
r는 read의 약자로 읽는 기능만 가지고 있는 형식  
- a  
a는 append의 약자로 기존의 파일에 이어서 쓸 수 있는 형식  
만약 열려고 하는 파일이 없다면 새로 만들어서 쓸 수 있음  
 --- -
### fclose
- 열어놓았던 파일을 닫는 함수  

형식  
```
#include <stdio.h>

int fclose(FILE *stream);
```
예시  
```
#include <stdio.h>

fclose(fp);
```
fopen으로 열어서 저장해두었던 FILE 포인터를 파라미터로 가져옴  
함수가 정상적으로 실행되었을 경우 0을 리턴  
정상적으로 실행되지 않았을 경우 EOF을 리턴(EOF는 end of file의 약어로 상수로는 -1를 지칭)  

### fprintf
- 파일에 형식화된 데이터를 출력하는 함수

형식
```
#include <stdio.h>

int fprintf(FILE *stream, const char *format-string, argument-list);
```
예시
```
#include <stdio.h>
 
int main(void){
   int number = 100;
   FILE *fp = fopen("test.txt", "w");  	//텍스트 파일을 쓰기 모드로 엽니다
   fprintf(fp,"helloworld\n");		//helloworld라는 문자열을 파일에 출력합니다
   fprintf(fp,"%d\n", number);		//number라는 변수의 값을 파일에 출력합니다
   
   fclose (stream);
   
   return 0;
}
```
기존의 printf 함수에서 앞에 FILE포인터를 추가하여 사용  

### fscanf
- 파일에 있는 형식화된 테이터를 읽어오는 함수  

형식
```
#include <stdio.h>

int fscanf(FILE *stream, const char *format, ...);
```
예시
```
#include <stdio.h>

int main() {
    FILE* fp = fopen("test.txt", "r"); // 텍스트 파일을 읽기 모드로 엽니다

    int number;
    char word[100];

    fscanf(fp, "%s", word); // 파일로부터 정수를 읽어와 number 변수에 저장합니다
    fscanf(fp, "%d", &number); // 파일로부터 실수를 읽어와 value 변수에 저장합니다

    printf("정수: %d\n", number);
    printf("실수: %f\n", value);

    fclose(fp);

    return 0;
}
```
scanf와 사용법이 유사하고 파일 포인터를 받는 파라미터가 하나 더 있다는 것이 차이점
## 바이너리 과제를 해결하면서 사용한 함수/외부디렉토리/변수🚧공사중🚧🚫접근근지🚫
- fwrite
- fread
- fseek
- opendir
- closedir
- dirent.h
- DIR *dir
- struct dirent *entry
- DT-REG

#include <stdio.h>
#include <dirent.h>
#include <string.h>

int is_text_file(const char *filename) {
	const char *extension = strrchr(filename, '.');
	if (extension != NULL && strcmp(extension, ".txt") == 0) {
		return 1; // 텍스트 파일인 경우
	}
	return 0; // 텍스트 파일이 아닌 경우
}

char* find_file_name(){
	const char *folder_path = "./"; // 폴더 경로를 지정합니다
	DIR *dir;
	struct dirent *entry;

	dir = opendir(folder_path);
	if (dir == NULL) {
		printf("폴더 열기 실패\n");
		return NULL;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 일반 파일인 경우만 처리합니다
			if (is_text_file(entry->d_name)) {
				//내용을 여기에 다 넣어
				entry->d_name;		//이 이름이 텍스트 파일 이름
			}
		}
	}

	closedir(dir);

}

int main() {
	char tmp[100];
	for(int i = 0; i < 5; i++){
		strcpy(tmp, find_file_name());
		printf(" 파일 이름:%s\n", tmp);
	}

	return 0;
}


// config-encryption.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "string.h"

static const char usage_message[] =
" USAGE:\n"
"    config-encryption [src_file] [out_file] [pass] \n"
" Examples:\n"
"    > config-encryption src.conf out.dat password\n"
"\n"
;

void crpypt(char file_path[], char crpypt_path[], char fp_password[]) {
	FILE *source, *crpypt_test, *crpypt_fp;
	errno_t err;

	err = fopen_s(&source, file_path, "r");
	if (err == 0){
		printf("源文件成功打开\n");
	}
	else{
		printf("源文件打开失败\n");
		return;
	}

	err = fopen_s(&crpypt_test, crpypt_path, "r");
	if (err == 0){
		if (crpypt_test != NULL)fclose(crpypt_test);
		err = fopen_s(&crpypt_fp, crpypt_path, "w");
		if (err == 0) {
			printf("加密文件成功打开\n");
		}
	}
	else{
		if (crpypt_test != NULL)fclose(crpypt_test);
		err = fopen_s(&crpypt_fp, crpypt_path, "a");
		if (err == 0) {
			printf("加密文件成功创建\n");
		}
		else {
			printf("未知错误\n");
			printf(usage_message);
			return;
		}
	}

	int sign, i = 0, pw_len = strlen(fp_password);
	while ((sign = fgetc(source)) != EOF) {
		fputwc(sign ^ fp_password[i % pw_len], crpypt_fp);
		i++;
	}

	fclose(crpypt_fp);
	fclose(source);
	printf("加密完成");
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf(usage_message);
		return 4;
	}
	char *source_path = argv[1];
	char *crpypt_path = argv[2];
	char *password = argv[3];
	crpypt(source_path, crpypt_path, password);
	getchar();
	return 0;
}

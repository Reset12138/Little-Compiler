#include <stdio.h>

#define BUFFER_SIZE 4096

void preprocessing(FILE *in, FILE *out) {

    char buffer[BUFFER_SIZE];

    int is_in_multiline_comments = 0; // 是否在多行注释内

    while (fgets(buffer, BUFFER_SIZE, in) != NULL) { // 每次读取一行

        int is_in_string = 0; // 是否在字符串内

        for (int i = 0; buffer[i] != '\0'; i++) {

            if (is_in_string == 0) { // 如果不在字符串内，才讨论是否是多行注释
                if (buffer[i + 1] != '\0' && buffer[i] == '*' && buffer[i + 1] == '/') { // 如果检测到 */ 置flag为0
                    buffer[i] = ' ';
                    buffer[i + 1] = ' ';
                    is_in_multiline_comments = 0;
                }

                if (buffer[i + 1] != '\0' && buffer[i] == '/' && buffer[i + 1] == '*') { // 如果检测到 /* 置flag为1
                    buffer[i] = '\n';
                    buffer[i + 1] = '\0';
                    is_in_multiline_comments = 1;
                }
            }

            if (is_in_multiline_comments == 0) { // 如果不在多行注释内
                if (buffer[i] == '"') { // 处理字符串中的//
                    is_in_string = !is_in_string; // 如果是双引号，则取反
                }
                if (is_in_string == 0 && buffer[i + 1] != '\0' &&
                    buffer[i] == '/' && buffer[i + 1] == '/') { // 如果检测到//并且不在多行注释与字符串内
                    buffer[i] = '\n';
                    buffer[i + 1] = '\0';
                    break;
                }
            } else {
                if (buffer[i] != '\n') { // 如果在多行注释内部，将除了换行符的字符替换为空格
                    buffer[i] = ' ';
                }
            }

        }

        if (buffer[0] != '\n') // 如果这一行存在除了换行符之外的字符
            fputs(buffer, out);
    }

}

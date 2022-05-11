#include "scanner.h"
#include "pair.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define SYMBOL_TABLE_SIZE 100


struct symbol_table {
	char name[16];
	int type;
} symbol_table[SYMBOL_TABLE_SIZE];


void print_symbol_table(int size_symbol_table) {
	for (int i = 0; i < size_symbol_table; i++) {
		printf("(%s, %d)\n", symbol_table[i].name, symbol_table[i].type);
	}
}

int is_operator(const char token) {
	static const char operator_list[] = { '=', '+', '-', '*', '/', '(', ')', '[', ']', '{', '}', ',', ':', ';', '>', '<' };

	for (size_t i = 0; i < sizeof(operator_list); i++) {
		if (token == operator_list[i])
			return 1;

	}
	return 0;
}

int is_alpha(const char c) {
	if (isalpha(c) || c == '_') {
		return 1;
	}
	else {
		return 0;
	}
}

int is_valid(const char c) {
	if (isdigit(c) || is_alpha(c) || is_operator(c)) {
		return 1;
	}
	else {
		return 0;
	}
}

int is_number(const char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (isdigit(str[i]) == 0) {
			return 0;
		}
	}
	return 1;
}


int get_pair(const char* str) {

	int i = 0;
	static int index_symbol_table = 0;
	static int index_pair = 0;
	while (str[i] != '\0') {

		if (isdigit(str[i])) { // 如果是数字

			int start = i;

			while (isdigit(str[i])) {
				i++;
			}
			if (i - start > 15)
				continue;
			char token[16];
			memcpy(token, str + start, i - start);
			token[i - start] = '\0';

			pair[index_pair].type_id = TYPE_NUMBER;
			pair[index_pair].attr = atoi(token);
			index_pair++;

		}
		else if (is_operator(str[i])) { // 如果是运算符

			int start = i;

			if (is_operator(str[i + 1]) == 1) {
				char tmp[] = { str[i], str[i + 1], '\0' };
				if (get_type_id(tmp) != 0)
					i++;
			}
			i++;
			char token[4];
			memcpy(token, str + start, i - start);
			token[i - start] = '\0';
			pair[index_pair].type_id = get_type_id(token);
			strcpy(pair[index_pair].str, token);
			index_pair++;

		}
		else if (is_alpha(str[i])) { // 如果是字符串
			int start = i;

			while (is_alpha(str[i]) || isdigit(str[i])) {
				i++;
			}
			if (i - start > 15)
				continue;
			char token[16];
			memcpy(token, str + start, i - start);
			token[i - start] = '\0';
			if (is_keyword(token) == 1) { // 如果是关键字
				pair[index_pair].type_id = get_type_id(token);
				strcpy(pair[index_pair].str, token);
				index_pair++;
			}
			else if (is_keyword(token) == 0) { // 如果是标识符
				strcpy(symbol_table[index_symbol_table].name, token);

				pair[index_pair].type_id = TYPE_IDENTIFIER;
				pair[index_pair].attr = index_symbol_table;
				strcpy(pair[index_pair].str, token);

				index_symbol_table++;
				index_pair++;

			}
		}
		else {
			i++;
		}
	}

	//for (i = 0; i < index_symbol_table; i++) {
	//	printf("%s\n", symbol_table[i].name);
	//}

	return index_pair;
}

int main() {
	const char* a = "main()\n{\nint i = 10;\nwhile (i) i = i - 1;\n}";
	//const char *b = "while 6345";

	int size_pair = get_pair(a);
	print_pair(size_pair);
}

int is_keyword(const char* token) {
	static const char* keywords_list[] = { "main", "if", "else", "int", "char", "for", "while" };

	for (size_t i = 0; i < sizeof(keywords_list) / sizeof(*keywords_list); i++) {
		if (strcmp(token, keywords_list[i]) == 0)
			return 1;

	}
	return 0;
}

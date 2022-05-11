#include "pair.h"
#include <stdio.h>
#include <string.h>

void print_pair(int size_pair) {
	for (int i = 0; i < size_pair; i++) {
		if (pair[i].type_id == TYPE_NUMBER) {
			printf("(%d, %d)\n", pair[i].type_id, pair[i].attr);
		}
		else {
			printf("(%d, %s)\n", pair[i].type_id, pair[i].str);
		}
	}
}

// 如果不属于任何一种类型则返回0
int get_type_id(const char* str) {
	if (strcmp(str, "main") == 0) {
		return TYPE_MAIN;
	}
	else if (strcmp(str, "int") == 0) {
		return TYPE_INT;
	}
	else if (strcmp(str, "char") == 0) {
		return TYPE_CHAR;
	}
	else if (strcmp(str, "if") == 0) {
		return TYPE_IF;
	}
	else if (strcmp(str, "else") == 0) {
		return TYPE_ELSE;
	}
	else if (strcmp(str, "for") == 0) {
		return TYPE_FOR;
	}
	else if (strcmp(str, "while") == 0) {
		return TYPE_WHILE;
	}
	else if (strcmp(str, "=") == 0) {
		return TYPE_ASSIGN;
	}
	else if (strcmp(str, "+") == 0) {
		return TYPE_ADD;
	}
	else if (strcmp(str, "-") == 0) {
		return TYPE_SUB;
	}
	else if (strcmp(str, "*") == 0) {
		return TYPE_MULTI;
	}
	else if (strcmp(str, "/") == 0) {
		return TYPE_OBELUS;
	}
	else if (strcmp(str, "(") == 0) {
		return TYPE_OPEN_PAREN;
	}
	else if (strcmp(str, ")") == 0) {
		return TYPE_CLOSE_PAREN;
	}
	else if (strcmp(str, "[") == 0) {
		return TYPE_OPEN_BRACKET;
	}
	else if (strcmp(str, "]") == 0) {
		return TYPE_CLOSE_BRACKET;
	}
	else if (strcmp(str, "{") == 0) {
		return TYPE_OPEN_CURLY;
	}
	else if (strcmp(str, "}") == 0) {
		return TYPE_CLOSE_CURLY;
	}
	else if (strcmp(str, ",") == 0) {
		return TYPE_COMMA;
	}
	else if (strcmp(str, ":") == 0) {
		return TYPE_COLON;
	}
	else if (strcmp(str, ";") == 0) {
		return TYPE_SEMICOLON;
	}
	else if (strcmp(str, ">") == 0) {
		return TYPE_GREATER;
	}
	else if (strcmp(str, "<") == 0) {
		return TYPE_LESS;
	}
	else if (strcmp(str, ">=") == 0) {
		return TYPE_GREATER_EQUAL;
	}
	else if (strcmp(str, "<=") == 0) {
		return TYPE_LESS_EQUAL;
	}
	else if (strcmp(str, "==") == 0) {
		return TYPE_EQUAL;
	}
	else if (strcmp(str, "!=") == 0) {
		return TYPE_NOT_EQUAL;
	}
	else {
		return 0;
	}
}
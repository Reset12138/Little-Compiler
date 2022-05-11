//
// Created by tanyuan on 2022/3/7.
//

#ifndef LITTLE_COMPILER_SCANNER_H
#define LITTLE_COMPILER_SCANNER_H

#define SYMBOL_TABLE_SIZE 100

typedef struct {
    char name[16];
    int type;
} Symbol_table;

int is_keyword(const char *token);

int is_valid(char c);

int get_pair(const char *str);

#endif //LITTLE_COMPILER_SCANNER_H

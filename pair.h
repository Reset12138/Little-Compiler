#ifndef LITTLE_COMPILER_PAIR_H
#define LITTLE_COMPILER_PAIR_H

#define TYPE_MAIN 1
#define TYPE_INT 2
#define TYPE_CHAR 3
#define TYPE_IF 4
#define TYPE_ELSE 5
#define TYPE_FOR 6
#define TYPE_WHILE 7
#define TYPE_IDENTIFIER 10
#define TYPE_NUMBER 20

#define TYPE_ASSIGN 21
#define TYPE_ADD 22
#define TYPE_SUB 23
#define TYPE_MULTI 24
#define TYPE_OBELUS 25
#define TYPE_OPEN_PAREN 26
#define TYPE_CLOSE_PAREN 27
#define TYPE_OPEN_BRACKET 28
#define TYPE_CLOSE_BRACKET 29
#define TYPE_OPEN_CURLY 30
#define TYPE_CLOSE_CURLY 31

#define TYPE_COMMA 32
#define TYPE_COLON 33
#define TYPE_SEMICOLON 34
#define TYPE_GREATER 35
#define TYPE_LESS 36
#define TYPE_GREATER_EQUAL 37
#define TYPE_LESS_EQUAL 38
#define TYPE_EQUAL 39
#define TYPE_NOT_EQUAL 40

#define PAIR_SIZE 1000


struct pair {
    int type_id;
    int attr;
    char str[16];
} pair[PAIR_SIZE];

void print_pair(int size_pair);

int get_type_id(const char *str);


#endif //LITTLE_COMPILER_PAIR_H

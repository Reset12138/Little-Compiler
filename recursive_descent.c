#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "pair.h"
#include "recursive_descent.h"
#include "scanner.h"

extern Pair pair[PAIR_SIZE];
extern Symbol_table symbol_table[SYMBOL_TABLE_SIZE];

static int index = -1;

static int tmp_variable_count = 1;

Quadruple quadruples[QUADRUPLE_SIZE];

static int index_quadruples = 1;


char *get_next() {
    index++;
    return pair[index].str;
}

void roll_back() {
    index--;
}

void error() {
    printf("%d\n", index);
    roll_back();
    char *error_msg = get_next();
    printf("error near %s", error_msg);
    exit(0);
}

void get_code(char *op, char *operand1, char *operand2, char *result) {
    quadruples[index_quadruples].op = op;
    quadruples[index_quadruples].operand1 = operand1;
    quadruples[index_quadruples].operand2 = operand2;
    quadruples[index_quadruples].result = result;
    index_quadruples++;
}

void print_quadruples() {
    for (int i = 1; i < index_quadruples; i++) {
        printf("%2d: (%4s, %3s, %3s, %3s)\n", i, quadruples[i].op, quadruples[i].operand1, quadruples[i].operand2,
               quadruples[i].result);
    }
}

char *itoa(int num) {
    char *str = (char *) malloc(sizeof(char) * 10);
    sprintf(str, "%d", num);
    return str;
}

char *get_tmp_variable(int num) {
    char *str = (char *) malloc(sizeof(char) * 10);
    sprintf(str, "T%d", num);
    return str;
}

Factor *factor() {
    char *c = get_next();

    Factor *node = (Factor *) malloc(sizeof(Factor));
    if (*(c + 1) == '\0' && isdigit(*c)) {
        node->type = 2;
        node->number = *c - '0';

        node->systhesized = c;
    } else if (strcmp(c, "(") == 0) {
        node->type = 3;
        node->expr = expr();
        char *tmp = get_next();
        if (strcmp(tmp, ")") != 0) {
            error();
        }

        node->systhesized = node->expr->systhesized;
    } else {
        node->type = 1;
        node->id = *c;

        node->systhesized = c;
    }

    return node;
}

Term1 *term1(char *to_inherited) {
    char *c = get_next();
    Term1 *node = (Term1 *) malloc(sizeof(Term1));
    node->inherited = to_inherited;
    if (strcmp(c, "*") == 0 || strcmp(c, "/") == 0) {
        node->type = 1;
        node->mulop = *c;
        node->factor = factor();

        char *tmp_variable = get_tmp_variable(tmp_variable_count);
        get_code(c, node->factor->systhesized, node->inherited, tmp_variable);
        tmp_variable_count++;
        node->term1 = term1(node->inherited);
        // node->systhesized = node->term1->systhesized;
        node->systhesized = tmp_variable;
    } else {
        node->type = 2;
        node->systhesized = node->inherited;
        roll_back();
    }

    return node;
}

Term *term() {
    Term *node = (Term *) malloc(sizeof(Term));
    node->factor = factor();
    node->term1 = term1(node->factor->systhesized);

    node->systhesized = node->term1->systhesized;
    return node;
}

Expr1 *expr1(char *to_inherited) {
    char *c = get_next();
    Expr1 *node = (Expr1 *) malloc(sizeof(Expr1));
    node->inherited = to_inherited;
    if (strcmp(c, "+") == 0 || strcmp(c, "-") == 0) {
        node->type = 1;
        node->addop = *c;
        node->term = term();

        char *tmp_variable = get_tmp_variable(tmp_variable_count);
        get_code(c, node->term->systhesized, node->inherited, tmp_variable);
        tmp_variable_count++;
        node->expr1 = expr1(node->inherited);
//        node->systhesized = node->expr1->systhesized;
        node->systhesized = tmp_variable;
    } else {
        node->type = 2;
        node->systhesized = node->inherited;
        roll_back();
    }

    return node;
}

Expr *expr() {
    Expr *node = (Expr *) malloc(sizeof(Expr));
    node->term = term();
    node->expr1 = expr1(node->term->systhesized);

    node->systhesized = node->expr1->systhesized;
    return node;
}

Relop *relop() {
    Relop *node = (Relop *) malloc(sizeof(Relop));
    char *c = get_next();
    strcpy(node->op, c);
    return node;
}

Bool *bool() {
    Bool *node = (Bool *) malloc(sizeof(Bool));

    node->expr_1 = expr();
    node->relop = relop();
    node->expr_2 = expr();

    char *tmp_variable = get_tmp_variable(tmp_variable_count);
    get_code(node->relop->op, node->expr_1->systhesized, node->expr_2->systhesized, tmp_variable);
    tmp_variable_count++;
    node->systhesized = tmp_variable;
    return node;
}

Else *else_() {
    Else *node = (Else *) malloc(sizeof(Else));

    char *c = get_next();
    if (strcmp(c, "else") == 0) {
        node->type = 0;
        node->stmt = stmt();
    } else {
        node->type = 1;
        roll_back();
    }
    return node;
}

Stmt *stmt() {
    Stmt *node = (Stmt *) malloc(sizeof(Stmt));

    char *c = get_next();

    char *tmp = get_next();
    int is_type_0 = 0;
    if (strcmp(tmp, "=") == 0) {
        is_type_0 = 1;
    }
    roll_back();

    if (is_type_0 == 1) {
        node->type = 0;
        strcpy(node->id, c);
        get_next(); // 匹配"="
        node->expr = expr();
        char *tmp1 = get_next();
        if (strcmp(tmp1, ";") != 0) {
            error();
        }
        get_code("=", node->expr->systhesized, "-", c);
    } else if (strcmp(c, "if") == 0) {
        node->type = 1;
        char *tmp2 = get_next();
        if (strcmp(tmp2, "(") != 0) {
            error();
        }
        node->bool = bool();
        char *tmp3 = get_next();
        if (strcmp(tmp3, ")") != 0) {
            error();
        }
        int bne_index = index_quadruples;
        get_code("bne", node->bool->systhesized, "0", "-"); // 如果与0不等，跳转到if结束
        node->stmt = stmt();
        int end_if_index = index_quadruples;
        get_code("goto", "-", "-", "-"); // 如果else存在 ，if语句结束要跳转到else结束
        int else_or_stat_index = index_quadruples;
        quadruples[bne_index].result = itoa(else_or_stat_index);
        node->else_ = else_();
        if (node->else_->type == 1) { // 如果else不存在
            quadruples[end_if_index].result = itoa(else_or_stat_index);
        } else { // 如果else存在
            quadruples[end_if_index].result = itoa(index_quadruples);
        }

    } else if (strcmp(c, "while") == 0) {
        node->type = 2;
        char *tmp4 = get_next();
        if (strcmp(tmp4, "(") != 0) {
            error();
        }
        int bool_index = index_quadruples;
        node->bool = bool();
        char *tmp5 = get_next();
        if (strcmp(tmp5, ")") != 0) {
            error();
        }
        int bne_index = index_quadruples;
        get_code("bne", node->bool->systhesized, "0", "-"); // 如果与0不等，跳转到while结束
        node->stmt = stmt();
        get_code("goto", "-", "-", itoa(bool_index)); // 如果while结束，跳转到while开始
        int end_while_index = index_quadruples;
        quadruples[bne_index].result = itoa(end_while_index);

    } else {
        node->type = 3;
        roll_back();
        node->block = block();
    }
    return node;
}

Stmts1 *stmts1() {
    Stmts1 *node = (Stmts1 *) malloc(sizeof(Stmts1));

    char *c = get_next();
    char *tmp = get_next(); // 判断第二个字符是否为"="
    roll_back();
    if (strcmp(tmp, "=") == 0 || strcmp(c, "if") == 0 || strcmp(c, "while") == 0 || strcmp(c, "{") == 0) {
        roll_back();
        node->type = 0;
        node->stmt = stmt();
        node->stmts1 = stmts1();
    } else {
        roll_back();
        node->type = 1;
    }
    return node;
}

Stmts *stmts() {
    Stmts *node = (Stmts *) malloc(sizeof(Stmts));

    node->stmts1 = stmts1();
    return node;
}

Name *name() {
    Name *node = (Name *) malloc(sizeof(Name));

    char *c = get_next();
    strcpy(node->id, c);
    return node;
}

Type *type() {
    Type *node = (Type *) malloc(sizeof(Type));

    char *c = get_next();
    strcpy(node->type, c);
    return node;
}

Namelist1 *namelist1() {
    Namelist1 *node = (Namelist1 *) malloc(sizeof(Namelist1));

    char *c = get_next();
    if (strcmp(c, ",") == 0) {
        node->type = 0;
        node->name = name();
        node->namelist1 = namelist1();
    } else {
        node->type = 1;
        roll_back();
    }
    return node;
}

Namelist *namelist() {
    Namelist *node = (Namelist *) malloc(sizeof(Namelist));

    node->name = name();
    node->namelist1 = namelist1();
    return node;
}

Decl *decl() {
    Decl *node = (Decl *) malloc(sizeof(Decl));

    node->type = type();
    node->namelist = namelist();
    char *c = get_next();
    if (strcmp(c, ";") != 0) {
        error();
    }
    return node;
}

Decls1 *decls1() {
    Decls1 *node = (Decls1 *) malloc(sizeof(Decls1));

    char *c = get_next();
    if (strcmp(c, "int") == 0) {
        roll_back();
        node->type = 0;
        node->decl = decl();
        node->decls1 = decls1();
    } else {
        roll_back();
        node->type = 1;
    }
    return node;
}

Decls *decls() {
    Decls *node = (Decls *) malloc(sizeof(Decls));

    node->decl = decl();
    node->decls1 = decls1();
    return node;
}

Block *block() {
    Block *node = (Block *) malloc(sizeof(Block));

    char *tmp = get_next();
    if (strcmp(tmp, "{") != 0) {
        error();
    }
    node->decls = decls();
    node->stmts = stmts();
    char *tmp1 = get_next();
    if (strcmp(tmp1, "}") != 0) {
        error();
    }
    return node;
}

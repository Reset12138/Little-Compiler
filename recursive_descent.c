#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

static int index = -1;
static char get_next() {

	const char exp[] = "a+b*2/4-(b+c)*3\0";
	//const char exp[] = "a+b*2/4*3\0";
	//const char exp[] = "*2*2";

	index++;
	return exp[index];
}

void roll_back() {
	index--;
}

typedef struct EXPR Expr;
typedef struct TERM1 Term1;

typedef struct {
	int type;
	char id;
	int number;
	Expr* expr;
}Factor;

typedef struct TERM1 {
	int type;
	char mulop;
	Factor* factor;
	Term1* term1;
}Term1;

typedef struct {
	Factor* factor;
	Term1* term1;
}Term;


typedef struct EXPR1 {
	int type;
	char addop;
	Term* term;
	struct EXPR1* expr1;
}Expr1;

typedef struct EXPR {
	Term* term;
	Expr1* expr1;
}Expr;

Factor* factor();
Term1* term1();
Term* term();
Expr1* expr1();
Expr* expr();

Factor* factor() {
	char c = get_next();
	Factor* node = (Factor*)malloc(sizeof(Factor));
	if (isdigit(c)) {
		node->type = 2;
		node->number = c - '0';
	}
	else if (c == '(') {
		node->type = 3;
		node->expr = expr();
		get_next();
	}
	else {
		node->type = 1;
		node->id = c;
	}

	return node;
}

Term1* term1() {
	char c = get_next();
	Term1* node = (Term1*)malloc(sizeof(Term1));
	if (c == '*' || c == '/') {
		node->type = 1;
		node->mulop = c;
		node->factor = factor();
		node->term1 = term1();
	}
	else {
		node->type = 2;
		roll_back();
	}

	return node;
}

Term* term() {
	Term* node = (Term*)malloc(sizeof(Term));
	node->factor = factor();
	node->term1 = term1();

	return node;
}

Expr1* expr1() {
	char c = get_next();
	Expr1* node = (Expr1*)malloc(sizeof(Expr1));
	if (c == '+' || c == '-') {
		node->type = 1;
		node->addop = c;
		node->term = term();
		node->expr1 = expr1();
	}
	else {
		node->type = 2;
		roll_back();
	}

	return node;
}

Expr* expr() {
	Expr* node = (Expr*)malloc(sizeof(Expr));
	node->term = term();
	node->expr1 = expr1();

	return node;
}

void dfs_factor(Factor* factor);
void dfs_term1(Term1* term1);
void dfs_term(Term* term);
void dfs_expr1(Expr1* expr1);
void dfs_expr(Expr* expr);

void dfs_factor(Factor* factor) {
	if (factor->type == 1) {
		printf("[Factor [%c] ]", factor->id);
	}
	else if (factor->type == 2) {
		printf("[Factor [%d] ]", factor->number);
	}
	else if (factor->type == 3) {
		printf("[Factor [(] ");
		dfs_expr(factor->expr);
		printf("[)] ]");
	}
}

void dfs_term1(Term1* term1) {
	if (term1->type == 1) {
		printf("[Term1 [Mulop[%c]] ", term1->mulop);
		dfs_factor(term1->factor);
		dfs_term1(term1->term1);
		printf("]");
	}
	else if (term1->type == 2) {
		printf("[Term1[empty]] ");
	}
}

void dfs_term(Term* term) {
	printf("[Term ");
	dfs_factor(term->factor);
	dfs_term1(term->term1);
	printf("]");
}

void dfs_expr1(Expr1* expr1) {
	if (expr1->type == 1) {
		printf("[Expr1 [Addop[%c]] ", expr1->addop);
		dfs_term(expr1->term);
		dfs_expr1(expr1->expr1);
		printf("]");
	}
	else if (expr1->type == 2) {
		printf("[Expr1[empty]] ");
	}
}

void dfs_expr(Expr* expr) {
	printf("[Expr ");
	dfs_term(expr->term);
	dfs_expr1(expr->expr1);
	printf("]");
}


int main() {
	Expr* p = expr();
	dfs_expr(p);
}
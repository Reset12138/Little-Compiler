typedef struct FACTOR Factor;
typedef struct TERM1 Term1;
typedef struct TERM Term;
typedef struct EXPR1 Expr1;
typedef struct EXPR Expr;
typedef struct RELOP Relop;
typedef struct BOOL Bool;
typedef struct ELSE Else;
typedef struct STMT Stmt;
typedef struct STMTS1 Stmts1;
typedef struct STMTS Stmts;
typedef struct NAME Name;
typedef struct TYPE Type;
typedef struct NAMELIST1 Namelist1;
typedef struct NAMELIST Namelist;
typedef struct DECL Decl;
typedef struct DECLS1 Decls1;
typedef struct DECLS Decls;
typedef struct BLOCK Block;

typedef struct FACTOR {
    int type;
    char id;
    int number;
    Expr *expr;
} Factor;

typedef struct TERM1 {
    int type;
    char mulop;
    Factor *factor;
    Term1 *term1;
} Term1;

typedef struct TERM {
    Factor *factor;
    Term1 *term1;
} Term;


typedef struct EXPR1 {
    int type;
    char addop;
    Term *term;
    struct EXPR1 *expr1;
} Expr1;

typedef struct EXPR {
    Term *term;
    Expr1 *expr1;
} Expr;

typedef struct RELOP {
    char op[2];
} Relop;

typedef struct BOOL {
    Expr *expr_1;
    char op[2];
    Expr *expr_2;
} Bool;

typedef struct ELSE {
    int type;
    Stmt *stmt;
} Else;

typedef struct STMT {
    int type;
    Expr *expr;
    Bool *bool;
    Stmt *stmt;
    Else *else_;
    Block *block;
} Stmt;

typedef struct STMTS1 {
    int type;
    Stmt *stmt;
    Stmts1 *stmts1;
} Stmts1;

typedef struct STMTS {
    Stmts1 *stmts1;
} Stmts;

typedef struct NAME {
    char id[16];
} Name;

typedef struct TYPE {
    int typeid;
} Type;

typedef struct NAMELIST1 {
    int type;
    Name *name;
    Namelist *namelist;
} Namelist1;

typedef struct NAMELIST {
    Name *name;
    Namelist1 *namelist1;
} Namelist;

typedef struct DECL {
    Type *type;
    Namelist *namelist;
} Decl;


typedef struct DECLS1 {
    int type;
    Decl *decl;
    Decls1 *decls1;
} Decls1;

typedef struct DECLS {
    Decl *decl;
    Decls1 *decls1;
} Decls;

typedef struct BLOCK {
    Decls *decls;
    Stmts *stmts;
} Block;

Factor *factor();

Term1 *term1();

Term *term();

Expr1 *expr1();

Expr *expr();

Relop *relop();

Bool *bool();
Else *else_();
Stmt *stmt();
Stmts1 *stmts1();
Stmts *stmts();
Name *name();
Type *type();
Namelist1 *namelist1();
Namelist *namelist();
Decl *decl();
Decls1 *decls1();
Decls *decls();
Block *block();

void dfs_factor(Factor *factor);

void dfs_term1(Term1 *term1);

void dfs_term(Term *term);

void dfs_expr1(Expr1 *expr1);

void dfs_expr(Expr *expr);

#ifndef LITTLE_COMPILER_PRINT_SYNTAX_TREE_H
#define LITTLE_COMPILER_PRINT_SYNTAX_TREE_H

void dfs_factor(Factor *factor);

void dfs_term1(Term1 *term1);

void dfs_term(Term *term);

void dfs_expr1(Expr1 *expr1);

void dfs_expr(Expr *expr);

void dfs_relop(Relop *relop);

void dfs_bool(Bool *bool);

void dfs_else_(Else *else_);

void dfs_stmt(Stmt *stmt);

void dfs_stmts1(Stmts1 *stmts1);

void dfs_stmts(Stmts *stmts);

void dfs_name(Name *name);

void dfs_type(Type *type);

void dfs_namelist1(Namelist1 *namelist1);

void dfs_namelist(Namelist *namelist);

void dfs_decl(Decl *decl);

void dfs_decls1(Decls1 *decls1);

void dfs_decls(Decls *decls);

void dfs_block(Block *block);

#endif //LITTLE_COMPILER_PRINT_SYNTAX_TREE_H

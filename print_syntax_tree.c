#include <stdio.h>

#include "recursive_descent.h"
#include "print_syntax_tree.h"

// 生成语法树 mshang.ca/syntree/

void dfs_factor(Factor *factor) {
    if (factor->type == 1) {
        printf("[Factor [%c] ]", factor->id);
    } else if (factor->type == 2) {
        printf("[Factor [%d] ]", factor->number);
    } else if (factor->type == 3) {
        printf("[Factor [(] ");
        dfs_expr(factor->expr);
        printf("[)] ]");
    }
}

void dfs_term1(Term1 *term1) {
    if (term1->type == 1) {
        printf("[Term1 [Mulop[%c]] ", term1->mulop);
        dfs_factor(term1->factor);
        dfs_term1(term1->term1);
        printf("]");
    } else if (term1->type == 2) {
        printf("[Term1[empty]] ");
    }
}

void dfs_term(Term *term) {
    printf("[Term ");
    dfs_factor(term->factor);
    dfs_term1(term->term1);
    printf("]");
}

void dfs_expr1(Expr1 *expr1) {
    if (expr1->type == 1) {
        printf("[Expr1 [Addop[%c]] ", expr1->addop);
        dfs_term(expr1->term);
        dfs_expr1(expr1->expr1);
        printf("]");
    } else if (expr1->type == 2) {
        printf("[Expr1[empty]] ");
    }
}

void dfs_expr(Expr *expr) {
    printf("[Expr ");
    dfs_term(expr->term);
    dfs_expr1(expr->expr1);
    printf("]");
}

void dfs_relop(Relop *relop) {
    printf("[%s]", relop->op);
}

void dfs_bool(Bool *bool) {
    printf("[Bool ");
    dfs_expr(bool->expr_1);
    dfs_relop(bool->relop);
    dfs_expr(bool->expr_2);
    printf("]");
}

void dfs_else(Else *else_) {
    printf("[Else ");
    if (else_->type == 0) {
        printf("[else]");
        dfs_stmt(else_->stmt);
    } else if (else_->type == 1) {
        printf("[empty]");
    }
    printf("]");
}

void dfs_stmt(Stmt *stmt) {
    printf("[Stmt ");
    if (stmt->type == 0) {
        printf("[id[%s]] [=]", stmt->id);

//        printf("[%s =]", stmt->id);
        dfs_expr(stmt->expr);
        printf("[;]");
    } else if (stmt->type == 1) {
        printf("[if]");
        printf("[(]");
        dfs_bool(stmt->bool);
        printf("[)]");
        dfs_stmt(stmt->stmt);
        dfs_else(stmt->else_);
    } else if (stmt->type == 2) {
        printf("[while]");
        printf("[(]");
        dfs_bool(stmt->bool);
        printf("[)]");
        dfs_stmt(stmt->stmt);
    } else if (stmt->type == 3) {
        dfs_block(stmt->block);
    }
    printf("]");
}

void dfs_stmts1(Stmts1 *stmts1) {
    printf("[Stmts1 ");
    if (stmts1->type == 0) {
        dfs_stmt(stmts1->stmt);
        dfs_stmts1(stmts1->stmts1);
    } else if (stmts1->type == 1) {
        printf("[empty]");
    }
    printf("]");
}

void dfs_stmts(Stmts *stmts) {
    printf("[Stmts ");

    dfs_stmts1(stmts->stmts1);

    printf("]");
}

void dfs_name(Name *name) {
    printf("[Name [%s]]", name->id);
}

void dfs_type(Type *type) {
    printf("[Type [%s]]", type->type);
}


void dfs_namelist1(Namelist1 *namelist1) {
    printf("[Namelist1 ");
    if (namelist1->type == 0) {
        printf("[,]");
        dfs_name(namelist1->name);
        dfs_namelist1(namelist1->namelist1);
    } else if (namelist1->type == 1) {
        printf("[empty]");
    }
    printf("]");
}

void dfs_namelist(Namelist *namelist) {
    printf("[Namelist ");

    dfs_name(namelist->name);
    dfs_namelist1(namelist->namelist1);
    printf("]");
}

void dfs_decl(Decl *decl) {
    printf("[Decl ");

    dfs_type(decl->type);
    dfs_namelist(decl->namelist);
    printf("[;]");
    printf("]");
}

void dfs_decls1(Decls1 *decls1) {
    printf("[Decls1 ");

    if (decls1->type == 0) {
        dfs_decl(decls1->decl);
        dfs_decls1(decls1->decls1);
    } else if (decls1->type == 1) {
        printf("[empty]");
    }
    printf("]");
}

void dfs_decls(Decls *decls) {
    printf("[Decls ");

    dfs_decl(decls->decl);
    dfs_decls1(decls->decls1);

    printf("]");
}

void dfs_block(Block *block) {
    printf("[Decls ");
    printf("[{]");
    dfs_decls(block->decls);
    dfs_stmts(block->stmts);
    printf("[}]");

    printf("]");
}

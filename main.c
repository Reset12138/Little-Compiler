#include <stdlib.h>
#include "stdio.h"
//#include "preprocessing.h"
#include "recursive_descent.h"
#include "pair.h"
#include "scanner.h"


int main(int argc, char *argv[]) {

//    FILE *in = fopen("in.txt", "r");
//    FILE *out = fopen("out.txt", "w");
//    preprocessing(in, out);
//    fclose(in);
//    fclose(out);

    const char *a = "{\nint x,y;\nint z;\nif(x==0)\nx=y-1;else x=y-2;\nwhile(y==1)x=x+10;}";
//    const char *a = "a+b*2/4-(b+c)*3\0";
    int size_pair = get_pair(a);
    print_pair(size_pair);

//	Expr* p = expr();
//	dfs_expr(p);
    Block *p = block();
    dfs_block(p);
    return 0;
}
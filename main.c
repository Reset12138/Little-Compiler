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

//    const char *a = "{\nint x,y;\nif(x==0)\nx=y-1;\n}";
    const char *a = "a+b*2/4-(b+c)*3\0";
    int size_pair = get_pair(a);
    print_pair(size_pair);

	Expr* p = expr();

    return 0;
}
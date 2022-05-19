#include <stdlib.h>
#include <stdio.h>
#include "preprocessing.h"
#include "recursive_descent.h"
#include "scanner.h"
#include "pair.h"
#include "print_syntax_tree.h"


int main() {

    FILE *in = fopen("in.txt", "r");
    FILE *f = fopen("preprocessed.txt", "w+");
    preprocessing(in, f);
    fclose(in);

    char *buffer = 0;
    long length;

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer) {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer) {
        int size_pair = get_pair(buffer);
//        print_pair(size_pair);
        Block *p = block();
        dfs_block(p);
        printf("\nGet AST in mshang.ca/syntree/\n");
        print_quadruples();
    }
    return 0;
}
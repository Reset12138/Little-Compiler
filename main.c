#include "stdio.h"
#include "preprocessing.h"

int main(int argc, char *argv[]) {

    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
    preprocessing(in, out);

    return 0;
}
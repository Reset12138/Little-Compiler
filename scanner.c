#include "scanner.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>


struct symbol_table {
    char name[16];
    int type;
} symbol_table[100];

int is_char(char c) {
    if (isalpha(c) || c == '_') {
        return 1;
    } else {
        return 0;
    }
}

void get_legal_identifier(const char *str) {

    int i = 0;
    int index_symbol_table = 0;
    while (str[i] != '\0') {

        if (is_char(str[i])) {
            int start = i;
            while (!isspace(str[i])) {
                i++;
            }
            if (i - start > 15)
                continue;
            char token[16];
            memcpy(token, str + start, i - start);
            token[i - start] = '\0';
            if (is_keyword(token) == 0) {
                strcpy(symbol_table[index_symbol_table].name, token);
                index_symbol_table++;
            }

        } else {
            i++;
        }
    }

    for (i = 0; i < index_symbol_table; i++) {
        printf("%s\n", symbol_table[i].name);
    }

}

int main() {
    const char *a = "test double 3312321 dsad21 _12345678912345 _123456789123456 int\n";

    get_legal_identifier(a);

}

int is_keyword(const char *token) {
    static const char *keywords_list[] = {
            "auto",
            "break",
            "case",
            "char",
            "const",
            "continue",
            "default",
            "do",
            "double",
            "else",
            "enum",
            "extern",
            "float",
            "for",
            "goto",
            "if",
            "inlineinline",
            "int",
            "long",
            "register",
            "restrictrestrict",
            "return",
            "short",
            "signed",
            "sizeof",
            "static",
            "struct",
            "switch",
            "typedef",
            "union",
            "unsigned",
            "void",
            "volatile",
            "while",
            "_Alignas_Alignas",
            "_Alignof_Alignof",
            "_Atomic_Atomic",
            "_Bool_Bool",
            "_Complex_Complex",
            "_Generic_Generic",
            "_Imaginary_Imaginary",
            "_Noreturn_Noreturn",
            "_Static_assert_Static_assert",
            "_Thread_local_Thread_local"
    };

    for (size_t i = 0; i < sizeof(keywords_list) / sizeof(*keywords_list); i++) {
        if (strcmp(token, keywords_list[i]) == 0)
            return 1;
    }
    return 0;
}

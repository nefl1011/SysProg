#include <cstdlib>
#include "../includes/String.h"


bool String::compare(const char *lexem1, const char *lexem2) {
    int i = 0;
    while (lexem1[i] != '\0') {
        if (lexem1[i] != lexem2[i]) {
            return false;
        }
        i++;
    }

    return lexem2[i] == '\0';
}

int String::length(const char *lexem) {
    int i = 0;
    while (lexem[i] != '\0') {
        i++;
    }
    return i;
}

char *String::toUpper(const char *source) {
    int i = 0;
    char *str = strdup(source);

    while (str[i]) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] -= 32;
        }
        i++;
    }
    return (str);
}

char *String::strdup(const char *source) {
    char *dup = (char *) malloc(length(source) + 1);
    return String::strcpy(dup, source);
}

char *String::strcpy(char *destination, const char *source) {

    char *s = destination;
    while ((*s++ = *source++) != 0) {};
    return (destination);
}

#include <stdio.h>

int main() {
    char* s = "bonjour";
    char* t = "bonjour";

    s[0] = 'B';

    printf("%p\n", s);
    printf("%p\n", t);

    return 0;
}

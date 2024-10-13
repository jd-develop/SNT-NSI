#include <stdio.h>
#include <stdbool.h>

int main() {
    bool a = true;
    bool b = false;

    printf("a=%d, b=%d, a&&b=%d, a||b=%d, !a=%d\n", a, b, a && b, a || b, !a);
    return 0;
}

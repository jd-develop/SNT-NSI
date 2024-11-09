#include <stdio.h>
#include <assert.h>

int main() {
    FILE* fp = fopen("hello.txt", "w");  // ouverture en mode écriture
    assert(fp != NULL);
    fprintf(fp, "Hello, world %d!\n", 2024);
    fclose(fp);
    return 0;
}

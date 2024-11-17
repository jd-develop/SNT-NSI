#include <stdio.h>
#include <math.h>
#include "src/file_management.h"
#include "src/run_tests.h"

int main() {
    printf("Hello, world!\n");
    printf("%f\n", sin(2*3.14159265));

    run_tests();
}

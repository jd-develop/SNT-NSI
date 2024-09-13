#include <stdio.h>

/* Renvoie le maximum entre x et y */
int max(int x, int y) {
    if (x<y) {
        return y;
    } else {
        return x;
    }
}

int main() {
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int max_temp = a;

    max_temp = max(max_temp, b);
    max_temp = max(max_temp, c);
    max_temp = max(max_temp, d);

    printf("Le maximum est %d\n", max_temp);
    return 0;
}

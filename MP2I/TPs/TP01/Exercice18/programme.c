#include <stdio.h>
#include <time.h>


int main() {
    long int temps = time(NULL);

    int annee = 1970 + temps / (int)(365.24*24*3600);
    temps = temps % (int)(365.24*24*3600);
    int mois = 1 + temps / (int)(30.44*24*3600); // on ajoute 1 car janvier=0
    printf("Nous sommes en %d-%d\n", annee, mois);

    return 0;
}


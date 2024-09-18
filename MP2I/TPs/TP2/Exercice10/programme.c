#include <stdio.h>
#include <unistd.h>

/* Affiche « ping », attend une seconde, puis appelle pong() */
void ping();

/* Affiche « pong », attend une seconde, puis appelle ping() */
void pong() {
    printf("Pong\n");
    sleep(1);
    ping();
}

void ping() {
    printf("Ping\n");
    sleep(1);
    pong();
}

int main() {
    ping();
    return 0;
}

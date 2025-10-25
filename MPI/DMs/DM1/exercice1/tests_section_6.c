#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "knn.h"
#include "lecture_mnist.h"

int main(){
    nb_class_max = 10;
    int dtrain_size = 10000;
    int dtest_size = 1000;

    database dtrain;
    database dtest;

    mnist_input(dtrain_size, &dtrain, dtest_size, &dtest);

    int cmatrix[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cmatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < dtest_size; i++) {
        cmatrix
            [dtest->data[i].class]
            [classify(dtrain, 3, dtest->data[i].vector)]++;
    }

    printf("    0   1   2   3   4   5   6   7   8   9\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
        for (int j = 0; j < 10; j++) {
            printf("%*d ", 3, cmatrix[i][j]);
        }
        printf("\n");
    }

    delete_database(dtrain);
    delete_database(dtest);

    return 0;
}


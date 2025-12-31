#include "tests_uf.h"

uf_partition_t exemple_pour_test_0() {
    // crée la partition donnée en exemple dans l'énoncé du DM
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 11);
    for (int i = 0; i < 11; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
        res[i]->elem = i;
        res[i]->rank = 0;
    }
    res[0]->parent = res[5];
    res[1]->parent = res[2];
    res[2]->parent = res[7];
    res[3]->parent = res[7];
    res[4]->parent = res[4];
    res[5]->parent = res[5];
    res[6]->parent = res[6];
    res[7]->parent = res[7];
    res[8]->parent = res[4];
    res[9]->parent = res[4];
    res[10]->parent = res[4];

    res[2]->rank = 1;
    res[7]->rank = 2;
    res[5]->rank = 1;
    res[4]->rank = 1;

    return res;
}

uf_partition_t exemple_pour_test_1() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
        res[i]->elem = i;
        res[i]->rank = 0;
    }
    res[0]->parent = res[0];
    res[1]->parent = res[2];
    res[2]->parent = res[7];
    res[3]->parent = res[7];
    res[4]->parent = res[8];
    res[5]->parent = res[3];
    res[6]->parent = res[8];
    res[7]->parent = res[7];
    res[8]->parent = res[1];
    res[9]->parent = res[1];

    res[1]->rank = 2;
    res[2]->rank = 3;
    res[3]->rank = 1;
    res[7]->rank = 4;
    res[8]->rank = 1;

    return res;
}

uf_partition_t exemple_pour_test_2() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
        res[i]->elem = i;
        res[i]->rank = 0;
    }
    res[0]->parent = res[0];
    res[1]->parent = res[7];
    res[2]->parent = res[7];
    res[3]->parent = res[7];
    res[4]->parent = res[8];
    res[5]->parent = res[3];
    res[6]->parent = res[8];
    res[7]->parent = res[7];
    res[8]->parent = res[7];
    res[9]->parent = res[1];

    res[1]->rank = 2;
    res[2]->rank = 3;
    res[3]->rank = 1;
    res[7]->rank = 4;
    res[8]->rank = 1;

    return res;
}

void equality_aux(uf_elem_t x, uf_elem_t y) {
    assert(x->rank == y->rank);
    assert(x->elem == y->elem);
    assert((x->parent == x) == (y->parent == y));
    if (x->parent != x) {
        equality_aux(x->parent, y->parent);
    }
}

void equality(uf_partition_t part1, uf_partition_t part2, int size) {
    for (int i = 0; i < size; i++) {
        equality_aux(part1[i], part2[i]);
    }
}

uf_partition_t ex0() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 0;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 0;
    res[4]->elem = 4;
    res[4]->parent = res[4];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[5];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[6];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[7];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[8];
    res[8]->rank = 0;
    res[9]->elem = 9;
    res[9]->parent = res[9];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex1() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 0;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 0;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[5];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[6];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[7];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[8];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[9];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex2() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 0;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 0;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[5];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[7];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[8];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[9];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex3() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 1;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 0;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[5];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[7];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[8];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex4() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 2;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 0;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[5];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[7];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[1];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex5() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 2;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 1;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[3];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[7];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[1];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex6() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 2;
    res[2]->elem = 2;
    res[2]->parent = res[2];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 1;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[3];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[3];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[1];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex7() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 2;
    res[2]->elem = 2;
    res[2]->parent = res[1];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[3];
    res[3]->rank = 1;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[3];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[3];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[1];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex8() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 2;
    res[2]->elem = 2;
    res[2]->parent = res[1];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[1];
    res[3]->rank = 1;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[3];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[3];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[1];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

uf_partition_t ex9() {
    uf_partition_t res = malloc(sizeof(uf_elem_t) * 10);
    for (int i = 0; i < 10; i++) {
        res[i] = malloc(sizeof(struct uf_elem_s));
    }
    res[0]->elem = 0;
    res[0]->parent = res[0];
    res[0]->rank = 0;
    res[1]->elem = 1;
    res[1]->parent = res[1];
    res[1]->rank = 2;
    res[2]->elem = 2;
    res[2]->parent = res[1];
    res[2]->rank = 0;
    res[3]->elem = 3;
    res[3]->parent = res[1];
    res[3]->rank = 1;
    res[4]->elem = 4;
    res[4]->parent = res[8];
    res[4]->rank = 0;
    res[5]->elem = 5;
    res[5]->parent = res[1];
    res[5]->rank = 0;
    res[6]->elem = 6;
    res[6]->parent = res[8];
    res[6]->rank = 0;
    res[7]->elem = 7;
    res[7]->parent = res[3];
    res[7]->rank = 0;
    res[8]->elem = 8;
    res[8]->parent = res[1];
    res[8]->rank = 1;
    res[9]->elem = 9;
    res[9]->parent = res[1];
    res[9]->rank = 0;
    return res;
}

void test_Q1() {
    printf("décommenter le corps de test_Q1 après avoir codé uf_initialize\n");
    /*
    uf_partition_t part_0 = uf_initialize(0);
    int q1_test = 10;
    uf_partition_t part_1 = uf_initialize(q1_test);
    for (int i = 0; i < q1_test; i ++) {
     assert(part_1[i]->rank == 0);
     assert(part_1[i]->elem == i);
     assert(part_1[i]->parent == part_1[i]);
    }
    uf_free(part_1, q1_test);
    printf("Test Q1 OK\n");
    */
}

void test_Q2() {
    printf("décommenter le corps de test_Q2 après avoir codé uf_free\n");
    /*
    uf_partition_t part_0 = uf_initialize(0);
    int q1_test = 10;
    uf_partition_t part_1 = uf_initialize(q1_test);
    uf_free(part_0, 0);
    uf_free(part_1, q1_test);
    printf("Test Q2 OK\n");
    */
}

void test_Q3() {
    printf("décommenter le corps de test_Q3 après avoir codé uf_free\n");
    /*
            uf_partition_t q3_ex = exemple_pour_test_0();
            uf_partition_t q3_ex_copy = exemple_pour_test_0();
            assert(uf_find_no(q3_ex[0]) == q3_ex[5]);
            assert(uf_find_no(q3_ex[1]) == q3_ex[7]);
            assert(uf_find_no(q3_ex[2]) == q3_ex[7]);
            assert(uf_find_no(q3_ex[3]) == q3_ex[7]);
            assert(uf_find_no(q3_ex[4]) == q3_ex[4]);
            assert(uf_find_no(q3_ex[5]) == q3_ex[5]);
            assert(uf_find_no(q3_ex[6]) == q3_ex[6]);
            assert(uf_find_no(q3_ex[7]) == q3_ex[7]);
            assert(uf_find_no(q3_ex[8]) == q3_ex[4]);
            assert(uf_find_no(q3_ex[9]) == q3_ex[4]);
            assert(uf_find_no(q3_ex[10]) == q3_ex[4]);
            equality(q3_ex, q3_ex_copy, 11);
            uf_free(q3_ex, 11);
            uf_free(q3_ex_copy, 11);
            printf("Test Q3 OK\n");
            */
}

void test_Q4() {
    printf("décommenter le corps de test_Q4 après avoir codé uf_free\n");
    /*
            uf_partition_t q4_ex = exemple_pour_test_1();
            uf_partition_t q4_ex_res = exemple_pour_test_2();
            assert(uf_find(q4_ex[8]) == q4_ex[7]);
            equality(q4_ex, q4_ex_res, 10);
            assert(uf_find(q4_ex[0]) == q4_ex[0]);
            assert(uf_find(q4_ex[1]) == q4_ex[7]);
            assert(uf_find(q4_ex[2]) == q4_ex[7]);
            assert(uf_find(q4_ex[3]) == q4_ex[7]);
            assert(uf_find(q4_ex[4]) == q4_ex[7]);
            assert(uf_find(q4_ex[5]) == q4_ex[7]);
            assert(uf_find(q4_ex[6]) == q4_ex[7]);
            assert(uf_find(q4_ex[7]) == q4_ex[7]);
            assert(uf_find(q4_ex[8]) == q4_ex[7]);
            assert(uf_find(q4_ex[9]) == q4_ex[7]);
            assert(q4_ex[0]->rank == q4_ex_res[0]->rank);
            assert(q4_ex[0]->elem == 0);
            assert(q4_ex[0]->parent == q4_ex[0]);
            for (int i = 1; i < 10; i ++) {
             assert(q4_ex[i]->rank == q4_ex_res[i]->rank);
             assert(q4_ex[i]->elem == i);
             assert(q4_ex[i]->parent == q4_ex[7]);
            }
            uf_free(q4_ex, 10);
            uf_free(q4_ex_res, 10);
            printf("Test Q4 OK\n");
            */
}

void test_Q5() {
    printf("décommenter le corps de test_Q5 après avoir codé uf_free\n");
    /*
    int q5_size = 10;
    uf_partition_t q5_ex = uf_initialize(q5_size);

    uf_partition_t uf0 = ex0();
    uf_partition_t uf1 = ex1();
    uf_partition_t uf2 = ex2();
    uf_partition_t uf3 = ex3();
    uf_partition_t uf4 = ex4();
    uf_partition_t uf5 = ex5();
    uf_partition_t uf6 = ex6();
    uf_partition_t uf7 = ex7();
    uf_partition_t uf8 = ex8();
    uf_partition_t uf9 = ex9();

    equality(q5_ex, uf0, q5_size);
    uf_union(q5_ex[4], q5_ex[8]);
    equality(q5_ex, uf1, q5_size);
    uf_union(q5_ex[6], q5_ex[4]);
    equality(q5_ex, uf2, q5_size);
    uf_union(q5_ex[9], q5_ex[1]);
    equality(q5_ex, uf3, q5_size);
    uf_union(q5_ex[8], q5_ex[1]);
    equality(q5_ex, uf4, q5_size);
    uf_union(q5_ex[5], q5_ex[3]);
    equality(q5_ex, uf5, q5_size);
    uf_union(q5_ex[3], q5_ex[7]);
    equality(q5_ex, uf6, q5_size);
    uf_union(q5_ex[1], q5_ex[2]);
    equality(q5_ex, uf7, q5_size);
    uf_union(q5_ex[2], q5_ex[7]);
    equality(q5_ex, uf8, q5_size);
    uf_union(q5_ex[8], q5_ex[5]);
    equality(q5_ex, uf9, q5_size);

    uf_free(q5_ex, q5_size);
    uf_free(uf0, q5_size);
    uf_free(uf1, q5_size);
    uf_free(uf2, q5_size);
    uf_free(uf3, q5_size);
    uf_free(uf4, q5_size);
    uf_free(uf5, q5_size);
    uf_free(uf6, q5_size);
    uf_free(uf7, q5_size);
    uf_free(uf8, q5_size);
    uf_free(uf9, q5_size);
    printf("Test Q5 OK\n");
    */
}

int main() {
    printf("Décommenter les tests dans le fichier tests_uf.c afin de tester "
           "les fonctions de l'exercice 1.\n\n\n");
    /* test_Q1();*/
    /* test_Q2();*/
    /* test_Q3();*/
    /* test_Q4();*/
    /* test_Q5();*/
    return 0;
}

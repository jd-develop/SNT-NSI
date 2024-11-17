#ifndef FILE_MANAGEMENT
#define FILE_MANAGEMENT

/* Écrit l’entier `a` dans le fichier `f`, en convention petit-boutiste,
 * sur `size` octets (1 ⩽ size ⩽ 4)
 */
void write_int(FILE* f, int a, int size);

/* Teste la fonction write_int */
void test_write_int();

#endif


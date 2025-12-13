
/* Question 7 */
struct liste_sc_cell {
    int valeur;
    struct liste_sc_cell* suivant;
};
typedef struct liste_sc_cell * liste_sc_cell_t;

struct liste_sc {
    liste_sc_cell_t tete;
};
typedef struct liste_sc * liste_sc_t;

/* Question 8 */
struct liste_dc_cell {
    int valeur;
    struct liste_sc_cell* precedent;
    struct liste_sc_cell* suivant;
};
typedef struct liste_dc_cell * liste_dc_cell_t;

struct liste_dc {
    liste_dc_cell_t tete;
    liste_dc_cell_t queue;
};
typedef struct liste_dc * liste_dc_t;

/* Question 9 */
struct liste_sc_int_string_cell {
    int entier;
    char* chaine;
    struct liste_sc_int_string_cell* suivant;
};
typedef struct liste_sc_int_string_cell* liste_sc_int_string_cell_t;

struct liste_sc_int_string {
    liste_sc_int_string_cell_t tete;
};
typedef struct liste_sc_int_string* liste_sc_int_string_t;

/* Question 10 */
struct liste_sc_int_tab_cell {
    int valeur;
    int* tableau;
    struct liste_sc_int_tab_cell* suivant;
};
typedef struct liste_sc_int_tab_cell* liste_sc_int_tab_cell_t;

struct liste_sc_int_tab {
    liste_sc_int_tab_cell_t tete;
};
typedef struct liste_sc_int_tab* liste_sc_int_tab_t;


int main () {
    return 0;
}

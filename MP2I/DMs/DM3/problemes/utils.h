/* structure pour les string */
typedef struct {
    int len;
    int len_max;
    char* string;
} String;


/* Crée un string avec src */
String* new_string();

/* Ajoute src dans dest */
void string_append(String* dest, const char* src);

/* Ajoute src dans dest puis libère src */
void string_cat(String* dest, String* src);

/* Libère dest */
void string_free(String* dest);


/* Renvoie la formule au moins une est vraie */
String* au_moins_une(String** l, int n);

/* Renvoie la formule au plus une est vraie */
String* au_plus_une(String** l, int n);

/* Renvoie la formule exactement une est vraie */
String* exactement_une(String** l, int n);

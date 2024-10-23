#include <stdio.h>
#include <assert.h>

/* Renvoie la longueur de 's', caractère nul inclus */
/* '_' pour éviter les conflits avec la fonction strlen de la lib string.h */
int strlen_(char* s) {
    char c = s[0];
    int len = 0;
    int i = 0;
    while (c != '\0') {
        len ++;
        i ++;
        c = s[i];
    }
    return len;
}

/* Renvoie le nombre de fois où le caractère c apparaît dans la chaîne s */
int occurences(char* s, char c) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c)
            count++;
    }
    return count;
}

/* Renvoie 0 si les deux chaînes sont égales, un entier strictement négatif
 * si s1 est avant dans l’ordre alphabétique, un entier positif si s1 est
 * après. En fait, renvoie la différence des codes ASCII des premiers
 * caractères différents
 */
int strcmp_(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    if (s1[i] == s2[i])
        return 0;
    if (s1[i] == '\0')
        return -s2[i];
    else
        return s1[i];
}

/* Écrit src dans la chaîne dst (en écrasant) */
void strcpy_(char* dst, char* src) {
    int i = 0;
    for (; src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
}

/* Concatène src à dst */
void strcat_(char* dst, char* src) {
    int len = strlen_(dst);
    int i = 0;
    for (; src[i] != '\0'; i++) {
        dst[i+len] = src[i];
    }
    dst[i+len] = '\0';
}

int main() {
    char str[10] = {'a', 'b', 'c', '\0', 'd', 'e'};
    assert(strlen_("bonjour") == 7);
    assert(strlen_("") == 0);
    assert(strlen_("ඞ") == 3); /* 3 « caractères ASCII » mais un seul caractère
                                * UTF-8 */
    assert(strlen_(str) == 3);

    assert(occurences("bonjour", 'j') == 1);
    assert(occurences("guten tag", 't') == 2);
    assert(occurences("salut", ' ') == 0);
    assert(occurences("", 'i') == 0);
    assert(
        occurences("Llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch", 'l') == 10
    ); /* non, ça veut dire bonjour dans aucune langue, et tant mieux ! C’est
        * le nom d’un village au Pays de Galles */
    assert(occurences(str, 'c') == 1);
    assert(occurences("ඞථ", 224) == 2);

    assert(strcmp_("god dag", "god dag") == 0);
    assert(strcmp_(str, str) == 0);
    assert(strcmp_("b", "bonjour") == -'o');
    assert(strcmp_("bonjour", "b") == 'o');
    assert(strcmp_("adieusiatz", "adieusiath") == 'z'-'h');
    assert(strcmp_("adieusiatz", "adieusiath") > 0);
    assert(strcmp_("adieusiath", "adieusiatz") == 'h'-'z');
    assert(strcmp_("adieusiath", "adieusiatz") < 0);

    strcpy_(str, "hello");
    assert(strcmp_(str, "hello") == 0);
    char str2[15] = "bonan tagon";
    strcpy_(str2, "hej");
    assert(strcmp_(str2, "hej") == 0);
    strcpy_(str, str2);
    assert(strcmp_(str, str2) == 0);
    assert(strcmp_(str, "hej") == 0);

    strcat_(str, " hej");
    assert(strcmp_(str, "hej hej") == 0);
    char str3[15] = "bonan";
    strcat_(str3, " tagon");
    assert(strcmp_(str3, "bonan tagon") == 0);

    return 0;
}

/*
 * Calculatrice en notation polonaise inverse
 *
 * Supporte quatre opérations : +, -, /, *
 * Fonctionne à l’aide d’une pile de lexèmes, les lexèmes étant des entiers
 * ou des flottants.
 *
 * Par défaut, la calculatrice affiche la dernière valeur de la pile, mais
 * toute la pile peut être affichée en tapant « ps » (print stack)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// limite de 100 caractères en entrée
#define INPUT_SIZE 100
// limite de 100 éléments dans la pile de notre calculatrice
#define STACK_SIZE 100
// limite de 20 caractères aux nombres traités par le parser
#define PARSER_VALUE_SIZE 20
// marge d’erreur pour vérifier si un flottant est égal à 0 (en cas de division
// par exemple)
#define EPSILON 0.001

enum TokenType {
    integer_value,
    float_value
};

struct Token {
    /* Notre calculatrice découpe l’entrée en lexèmes (tokens)
     *
     * Un token représente soit un entier, soit un flottant
     *
     * On sait quelle variable il faut regarder parmi `value` et `float_value`
     * grâce à `type`.
     */
    enum TokenType type;
    long value;
    float float_value;
};

struct Token stack[STACK_SIZE];
int global_stack_index = 0;

void push(struct Token token) {
    /* Ajoute une valeur à la fin de la pile
     *
     * Attention : il faut vérifier que la taille ne soit pas à 100 avant
     * d’exécuter cette fonction
     */
    stack[global_stack_index++] = token;
}

struct Token pop() {
    /* Supprime et renvoie la dernière valeur de la pile
     *
     * Attention : il faut vérifier que la taille ne soit pas à 0 avant
     * d’exécuter cette fonction
     */
    return stack[--global_stack_index];
}

struct Token read() {
    /* Renvoie la dernière valeur de la pile
     *
     * Attention : il faut vérifier que la taille ne soit pas à 0 avant
     * d’exécuter cette fonction
     */
    return stack[global_stack_index-1];
}

int is_empty() {
    // renvoie 1 si la pile est vide
    return (global_stack_index == 0);
}

int print_stack() {
    // affiche la pile
    int index = 0;
    struct Token tok;
    while (index < global_stack_index) {
        tok = stack[index];
        if (tok.type == integer_value) {
            printf("%ld ", tok.value);
        } else {
            printf("%f ", tok.float_value);
        }
        index++;
    }
    printf("\n");
    return 0;
}

int print_last_value() {
    // affiche la dernière valeur de la pile, ou rien si la pile est vide.
    if (is_empty()) {
        return 0;
   }
    struct Token tok = read();
    if (tok.type == integer_value) {
        printf("%ld\n", tok.value);
    } else {
        printf("%f\n", tok.float_value);
    }
    return 0;
}

enum ParserState {
    // Permet de garder en mémoire l’état actuel du parser
    default_state,
    registering_an_integer,
    registering_a_float
};

int parse(char input[INPUT_SIZE]) {
    // découpe l’entrée en lexèmes, calcule et met à jour la pile
    // Renvoie :
    // * 0 si tout est OK
    // * 1 en cas d’overflow de la valeur qu’on est en train d’enregistrer
    // * 2 en cas de stackoverflow
    // * 3 si la pile est vide alors qu’une valeur était attendue
    // * 4 si la valeur a un type invalide
    // * 5 en cas de division par zéro
    unsigned int current_index = 0;  // index courant dans l’entrée
    char current_char = input[current_index];

    enum ParserState state = default_state;

    // valeur en train d’être analysée (entier ou flottant)
    char current_value_registered[PARSER_VALUE_SIZE];
    unsigned int current_len_of_reg_val = 0;
    int is_value_positive = 1;

    while (current_char != '\0' && current_index < INPUT_SIZE) {
        if (state == registering_an_integer || state == registering_a_float) {
            // on est en train d’enregistrer un nombre
            if (current_char == '.' && state == registering_an_integer) {
                state = registering_a_float;
                if (current_len_of_reg_val < PARSER_VALUE_SIZE) {
                    current_value_registered[current_len_of_reg_val++] = '.';

                    current_index++;
                    current_char = input[current_index];
                    continue;
                } // Ici, pas de problème, on aura juste moins de précision
            } else if (isdigit(current_char)) {
                // on ajoute simplement les caractères au fur et à mesure
                if (current_len_of_reg_val < PARSER_VALUE_SIZE) {
                    current_value_registered[current_len_of_reg_val++] =
                        current_char;

                    current_index++;
                    current_char = input[current_index];
                    continue;
                } else {
                    return 1;
                }
            } else {
                // le caractère n’est plus un chiffre, on doit arrêter
                // ici, on doit convertir la chaîne en entier ou en flottant,
                // mettre la longeur à zéro, changer l’état et ajouter le
                // flottant à la pile
                struct Token tok;

                if (state == registering_an_integer) {
                    long value = atol(current_value_registered);

                    if (!is_value_positive) {
                        value *= -1;
                    }

                    tok.type = integer_value;
                    tok.value = value;
                } else {
                    float value = atof(current_value_registered);

                    if (!is_value_positive) {
                        value *= -1;
                    }

                    tok.type = float_value;
                    tok.float_value = value;
                }
                is_value_positive = 1;

                //current_value_registered = "";
                current_len_of_reg_val = 0;
                state = default_state;

                if (global_stack_index+1 >= STACK_SIZE) {
                    return 2;
                }

                push(tok);
            }
        }

        if (current_char == '+') {
            // on effectue une addition
            // on récupère d’abord les deux nombres
            if (is_empty()) {
                return 3;
            }
            struct Token b = pop();

            if (is_empty()) {
                return 3;
            }
            struct Token a = pop();

            struct Token addition;
            // il faut vérifier si notre résultat sera un entier ou un flottant
            if (a.type == float_value || b.type == float_value) {
                addition.type = float_value;
                if (a.type == float_value && b.type == float_value) {
                    addition.float_value = a.float_value + b.float_value;
                } else if (a.type == float_value) {
                    addition.float_value = a.float_value + b.value;
                } else {
                    addition.float_value = a.value + b.float_value;
                }
            } else {
                addition.type = integer_value;
                addition.value = a.value + b.value;
            }

            if (global_stack_index+1 >= STACK_SIZE) {
                return 2;
            }
            push(addition);

            current_index++;
            current_char = input[current_index];
        } else if (current_char == '-') {
            // vérifier d’abord si le prochain caractère de l’entrée est un
            // chiffre ou non, auquel cas il faudra prioriser la multiplication
            // du prochain nombre par -1
            if (
                current_index+1 < INPUT_SIZE && input[current_index+1] != '\0'
            ) {
                if (isdigit(input[current_index+1])) {
                    current_index++;
                    current_char = input[current_index];
                    continue;
                }
            }

            // sinon, on fait une soustraction
            // on commence par récupérer les deux nombres
            if (is_empty()) {
                return 3;
            }
            struct Token b = pop();

            if (is_empty()) {
                return 3;
            }
            struct Token a = pop();

            struct Token subtraction;
            if (a.type == float_value || b.type == float_value) {
            // il faut vérifier si notre résultat sera un entier ou un flottant
                subtraction.type = float_value;
                if (a.type == float_value && b.type == float_value) {
                    subtraction.float_value = a.float_value - b.float_value;
                } else if (a.type == float_value) {
                    subtraction.float_value = a.float_value - b.value;
                } else {
                    subtraction.float_value = a.value - b.float_value;
                }
            } else {
                subtraction.type = integer_value;
                subtraction.value = a.value - b.value;
            }

            if (global_stack_index+1 >= STACK_SIZE) {
                return 2;
            }
            push(subtraction);

            current_index++;
            current_char = input[current_index];
        } else if (current_char == '*') {
            // on fait une multiplication
            // on commence par récupérer les deux nombres
            if (is_empty()) {
                return 3;
            }
            struct Token b = pop();

            if (is_empty()) {
                return 3;
            }
            struct Token a = pop();

            struct Token multiplication;
            // il faut vérifier si notre résultat sera un entier ou un flottant
            if (a.type == float_value || b.type == float_value) {
                multiplication.type = float_value;
                if (a.type == float_value && b.type == float_value) {
                    multiplication.float_value = a.float_value * b.float_value;
                } else if (a.type == float_value) {
                    multiplication.float_value = a.float_value * b.value;
                } else {
                    multiplication.float_value = a.value * b.float_value;
                }
            } else {
                multiplication.type = integer_value;
                multiplication.value = a.value * b.value;
            }

            if (global_stack_index+1 >= STACK_SIZE) {
                return 2;
            }
            push(multiplication);

            current_index++;
            current_char = input[current_index];
        } else if (current_char == '/') {
            // on effectue une division
            // on commence par récupérer les deux nombres
            if (is_empty()) {
                return 3;
            }
            struct Token b = pop();

            if (is_empty()) {
                return 3;
            }
            struct Token a = pop();

            struct Token division;
            // il faut vérifier si notre résultat sera un entier ou un flottant
            if (a.type == float_value || b.type == float_value) {
                division.type = float_value;
                if (a.type == float_value && b.type == float_value) {
                    // on vérifie si on est en train de diviser par 0 ou non
                    if (
                        -EPSILON <= b.float_value && b.float_value <= EPSILON
                    ) {
                        return 5;
                    }
                    division.float_value = a.float_value / b.float_value;
                } else if (a.type == float_value) {
                    if (b.value == 0) {
                        return 5;
                    }
                    division.float_value = a.float_value / b.value;
                } else {
                    // on vérifie si on est en train de diviser par 0 ou non
                    if (
                        -EPSILON <= b.float_value && b.float_value <= EPSILON
                    ) {
                        return 5;
                    }
                    division.float_value =
                        a.value / b.float_value;
                }
            } else {
                division.type = integer_value;
                if (b.value == 0) {
                    return 5;
                }
                division.value = a.value / b.value;
            }

            if (global_stack_index+1 >= STACK_SIZE) {
                return 2;
            }
            push(division);

            current_index++;
            current_char = input[current_index];
        } else if (isspace(current_char)) {
            // on ignore les espaces
            current_index++;
            current_char = input[current_index];
        } else if (isdigit(current_char)) {
            // on vérifie si le nombre est précédé du signe « - »
            if (current_index != 0) {
                char last_char = input[current_index-1];
                if (last_char == '-') {
                    is_value_positive = 0;
                }
            }
            state = registering_an_integer;
        } else {
            if (current_char == '.')
                printf("Illegal character (., 46). Maybe you typed a floating-"
                       "point number with two dots?\n");
            else if (
                !(current_char == -30 ||
                  current_char == -128 ||
                  current_char == -81)
                // je ne sais pas pourquoi, ces caractères aparaissent à la fin
                // de certaines lignes. Ça doit être des codes spéciaux Unicode
                // que l’on peut ignorer. Si ce n’est pas ces caractères, on
                // affiche une erreur
            ) printf(
                "Illegal character (%c, %d)\n", current_char, current_char
            );

            current_index++;
            current_char = input[current_index];
        }
    }

    return 0;
}


int main() {
    char input[INPUT_SIZE];

    // on utilise une boucle infinie que l’on peut quitter avec 'exit'
    while (1) {
        printf("> ");
        /* on est obligé d’utiliser fgets pour éviter les overflows et avoir
         * également les espaces */
        if (fgets(input, INPUT_SIZE, stdin) == NULL)
            break;  // sûrement un EOF

        // on vérifie si on doit arrêter le programme
        if (strcmp(input, "exit\n") == 0) {
            break;
        }

        // on vérifie si on doit afficher la pile
        if (strcmp(input, "ps\n") == 0) {
            print_stack();
            continue;
        }

        // printf("%s", input);
        int parse_result = parse(input);
        switch (parse_result) {
            case 0:
                break;

            case 1:
                printf("Parse value overflow\n");
                return 1;

            case 2:
                printf("Stack overflow\n");
                return 2;

            case 3:
                printf("Not enough values in stack\n");
                return 3;

            case 4:
                printf("Invalid value type\n");
                return 4;

            case 5:
                printf("Division by zero\n");
                return 5;
        }
        print_last_value();
    }

    return 0;
}

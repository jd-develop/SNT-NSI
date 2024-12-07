#ifndef NEW_MELODY
#define NEW_MELODY

/*
 * Lit une piste dans le fichier fp et la renvoie, avec le tempo donné en
 * battement (à la noire) par minute. Plante avec un message d’erreur et renvoie
 * NULL si le fichier n’est pas au bon format
 */
track_t* new_read_track(FILE* fp, int tempo);

/*
 * Lit un morceau dans le buffer fp et le renvoie. Plante avec un message
 * d’erreur et renvoie NULL si le fichier n’est pas au bon format. On supposera
 * que le fichier est valide (i.e. fp est non nul), et que l’entier négatif
 * censé renseigner sur le format du fichier a déjà été consommé.
 */
mix_t* new_load_mix(FILE* fp);

/*
 * Convertit une note str en durée en temps, d’après un certain tempo (à la
 * noire)
 * Renvoie -1 si la note n’existe pas
 * Supporte :
 * * 'ronde' : 4 temps
 * * 'rondepointee' : 6 temps
 * * 'blanche' : 2 temps
 * * 'blanchepointee' : 3 temps
 * * 'noire' : 1 temps
 * * 'noirepointee' : 2 temps
 * * 'croche': 1/2 temps
 * * 'crochepointee' : 3/4 temps
 * * 'triolet' : 1/3 temps
 * * 'doublecroche' : 1/4 temps
 * * 'doublecrochepointee' : 3/8 temps
 * * 'triplecroche' : 1/8 temps
 * * 'triplecrochepointee' : 3/16 temps
 * * 'quadruplecroche' : 1/16 temps
 * * 'quadruplecrochepointee' : 3/32 temps
 */
float note_to_duree(char* note, int tempo);

/*
 * Convertit le nom d’une note en pitch
 * Renvoie -10000 si la note n’existe pas
 * Pour former une note, on écrit son nom ('do', 're', 'mi', 'fa', 'sol', 'la',
 * 'si'), suivi éventuellement d’une altération ('b' pour bémol et '#' pour
 * dièse), puis suivi de l’octave : 0 pour l’octave central du piano (et
 * contenant notemment le la 440), 1 pour l’octave au-dessus, -1 pour celui
 * en dessous, etc.
 *
 * Par exemple :
 * * 'la0' correspond au la 440
 * * 'do0' correspond au do central
 * * 'dob1' correspond au si de l’octave central (do bémol = si de l’octave
 *                                                d’avant !)
 * * 'la#-2' correspond au la dièse du deuxième octave en-dessous de l’octave
 *   central
 */
int note_to_pitch(char* note);

/* teste la fonction note_to_pitch */
void test_note_to_pitch();

#endif

(*
 * Cette version de exercice4.ml fonctionne avec (normalement) toutes les
 * versions d’OCaml.
 *)

type couleur = Coeur | Carreau | Pique | Trefle

type tete = Valet | Dame | Roi

type carte =
    | Nombre of (int * couleur)
    | Tete of (tete * couleur)
    | Joker

(* Renvoie un string correspondant à la couleur c *)
let string_of_couleur (c: couleur) : string = match c with
    | Coeur -> "cœur"
    | Carreau -> "carreau"
    | Pique -> "pique"
    | Trefle -> "trèfle"

(* Renvoie un string correspondant à la tête t *)
let string_of_tete (t: tete) : string = match t with
    | Valet -> "Valet"
    | Dame -> "Dame"
    | Roi -> "Roi"

(* Renvoie un string correspondant à la carte ca *)
let string_of_carte (ca: carte) : string = match ca with
    | Nombre (nb, c) ->
        (if nb == 1 then "As" else string_of_int nb) ^
        " de " ^
        (string_of_couleur c)
    | Tete (t, c) -> (string_of_tete t) ^ " de " ^ (string_of_couleur c)
    | Joker -> "Joker"

(*
 * Renvoie la couleur d’une carte, en supposant que la carte n’est pas un joker
 *)
let couleur_carte (ca: carte) : couleur = match ca with
    | Joker -> failwith "Les Joker n’ont pas de couleur"
    | Nombre (_, c) -> c
    | Tete (_, c) -> c

(*
 * Compare c1, c2 avec la même spécification que compare_carte, mais
 * sans se soucier des couleurs.
 *)
let compare_cartes_meme_couleur (c1: carte) (c2: carte) : int = match c1 with
    | Joker -> -1
    | Nombre (nb1, _) -> (match c2 with
        | Joker -> -1
        | Nombre (nb2, _) ->
            if nb1 = nb2 then 0
            else if nb2 = 1 then -1
            else if nb1 > nb2 || nb1 = 1 then 1
            else -1
        | Tete (t2, _) -> if nb1 = 1 then 1 else -1
    )
    | Tete (t1, _) -> (match c2 with
        | Joker -> -1
        | Nombre (nb2, _) ->
            if nb2 = 1 then -1
            else 1
        | Tete (t2, _) ->
            if t1 > t2 then 1
            else if t1 = t2 then 0
            else -1
    )


(* Compare deux cartes. Renvoie -1 si la carte c1 est inférieure à la carte c2,
 * 0 si elle est égale et 1 si elle est supérieure.
 * L’ordre est le suivant :
 *   * Les cœurs sont plus petits que les carreaux qui sont plus petits que les
 *     piques qui sont plus petits que les trèfles.
 *   * Au sein d’une couleur, l’ordre est 2, 3, …, 10, valet, dame, roi, as.
 *   * Un joker est inférieur à tout (comme l’Excuse au Tarot)
 *)
let compare_carte (c1: carte) (c2: carte) : int =
    if c1 = Joker then (if (c2 = Joker) then 0 else -1)
    else if c2 = Joker then 1
    else
        let coul1 = couleur_carte c1 in
        let coul2 = couleur_carte c2 in
        if coul1 = coul2 then compare_cartes_meme_couleur c1 c2
        else if coul1 < coul2 then -1
        else 1


(* Insère la carte c dans le jeu de cartes jeu supposé trié *)
let rec insert (c: carte) (jeu: carte list) : carte list = match jeu with
    | [] -> c::[]
    | x::q -> if compare_carte c x <= 0 then c::x::q
              else x::(insert c q)

(* Trie le jeu de cartes `jeu` par insertion *)
let rec insert_sort (jeu: carte list) : carte list = match jeu with
    | [] -> []
    | x::q -> insert x (insert_sort q)

(* Renvoie la liste de toutes les cartes de la couleur `c`, dont on connaît la
 * fin de la liste `l`, dans l’ordre de l’as au dix puis valet, dame, roi *)
let rec carte_prec (c: couleur) (l: carte list) = match l with
    | [] -> carte_prec c [Tete (Roi, c)]
    | x::q -> (match x with
        | Joker -> failwith "Il y a un joker dans la liste"
        | Tete (t, c) -> (match t with
            | Roi -> carte_prec c (Tete (Dame, c)::l)
            | Dame -> carte_prec c (Tete (Valet, c)::l)
            | Valet -> carte_prec c (Nombre (10, c)::l))
        | Nombre (n, c) -> if n = 1 then l
                           else carte_prec c (Nombre (n-1, c)::l))

(* Renvoie la liste des 13 cartes de la couleur `c` *)
let gen_couleur (c: couleur) : carte list = carte_prec c []


let test () =
    assert (string_of_couleur Coeur = "cœur");
    assert (string_of_couleur Carreau = "carreau");
    assert (string_of_couleur Trefle = "trèfle");
    assert (string_of_couleur Pique = "pique");
    assert (string_of_tete Valet = "Valet");
    assert (string_of_tete Dame = "Dame");
    assert (string_of_tete Roi = "Roi");

    assert (string_of_carte (Nombre (1, Coeur)) = "As de cœur");
    assert (string_of_carte (Nombre (2, Pique)) = "2 de pique");
    assert (string_of_carte (Nombre (5, Trefle)) = "5 de trèfle");
    assert (string_of_carte (Nombre (10, Carreau)) = "10 de carreau");
    assert (string_of_carte (Tete (Roi, Carreau)) = "Roi de carreau");
    assert (string_of_carte (Tete (Dame, Pique)) = "Dame de pique");
    assert (string_of_carte (Tete (Valet, Trefle)) = "Valet de trèfle");

    assert (compare_carte Joker Joker = 0);
    assert (compare_carte Joker (Nombre (7, Pique)) = -1);
    assert (compare_carte Joker (Tete (Valet, Trefle)) = -1);

    assert (compare_carte (Nombre (1, Coeur)) (Nombre (1, Coeur)) = 0);
    assert (compare_carte (Nombre (1, Coeur)) (Nombre (2, Coeur)) = 1);
    assert (compare_carte (Nombre (2, Coeur)) (Nombre (1, Coeur)) = -1);
    assert (compare_carte (Nombre (3, Coeur)) (Nombre (2, Coeur)) = 1);
    assert (compare_carte (Nombre (2, Coeur)) (Nombre (3, Coeur)) = -1);

    assert (compare_carte (Nombre (1, Carreau)) (Nombre (1, Coeur)) = 1);
    assert (compare_carte (Nombre (1, Coeur)) (Nombre (1, Carreau)) = -1);
    assert (compare_carte (Nombre (1, Pique)) (Nombre (1, Carreau)) = 1);
    assert (compare_carte (Nombre (1, Carreau)) (Nombre (1, Pique)) = -1);
    assert (compare_carte (Nombre (1, Trefle)) (Nombre (1, Pique)) = 1);
    assert (compare_carte (Nombre (1, Pique)) (Nombre (1, Trefle)) = -1);

    assert (compare_carte (Nombre (10, Carreau)) (Nombre (1, Coeur)) = 1);
    assert (compare_carte (Nombre (10, Coeur)) (Nombre (1, Carreau)) = -1);
    assert (compare_carte (Nombre (10, Pique)) (Nombre (1, Carreau)) = 1);
    assert (compare_carte (Nombre (10, Carreau)) (Nombre (1, Pique)) = -1);
    assert (compare_carte (Nombre (10, Trefle)) (Nombre (1, Pique)) = 1);
    assert (compare_carte (Nombre (10, Pique)) (Nombre (1, Trefle)) = -1);

    assert (compare_carte (Nombre (10, Carreau)) (Tete (Valet, Coeur)) = 1);
    assert (compare_carte (Nombre (10, Coeur)) (Tete (Roi, Carreau)) = -1);
    assert (compare_carte (Nombre (10, Pique)) (Tete (Valet, Carreau)) = 1);
    assert (compare_carte (Nombre (10, Carreau)) (Tete (Dame, Pique)) = -1);
    assert (compare_carte (Nombre (10, Trefle)) (Tete (Valet, Pique)) = 1);
    assert (compare_carte (Nombre (10, Pique)) (Tete (Valet, Trefle)) = -1);
    assert (compare_carte (Nombre (1, Pique)) (Tete (Valet, Pique)) = 1);
    assert (compare_carte (Tete (Valet, Pique)) (Nombre (1, Pique)) = -1);

    assert (compare_carte (Nombre (1, Coeur)) Joker = 1);
    assert (compare_carte (Nombre (10, Pique)) Joker = 1);

    assert (compare_carte (Tete (Valet, Coeur)) Joker = 1);
    assert (compare_carte (Tete (Roi, Pique)) Joker = 1);

    assert (compare_carte (Tete (Valet, Coeur)) (Nombre (3, Pique)) = -1);
    assert (compare_carte (Tete (Valet, Pique)) (Nombre (3, Coeur)) = 1);
    assert (compare_carte (Tete (Roi, Pique)) (Nombre (3, Pique)) = 1);

    assert (compare_carte (Tete (Valet, Coeur)) (Tete (Valet, Pique)) = -1);
    assert (compare_carte (Tete (Valet, Pique)) (Tete (Valet, Coeur)) = 1);
    assert (compare_carte (Tete (Valet, Pique)) (Tete (Roi, Coeur)) = 1);
    assert (compare_carte (Tete (Dame, Pique)) (Tete (Valet, Coeur)) = 1);
    assert (compare_carte (Tete (Dame, Carreau)) (Tete (Valet, Trefle)) = -1);

    assert (compare_carte (Tete (Dame, Pique)) (Tete (Valet, Pique)) = 1);
    assert (compare_carte (Tete (Valet, Pique)) (Tete (Dame, Pique)) = -1);
    assert (compare_carte (Tete (Roi, Pique)) (Tete (Valet, Pique)) = 1);
    assert (compare_carte (Tete (Valet, Pique)) (Tete (Roi, Pique)) = -1);
    assert (compare_carte (Tete (Roi, Pique)) (Tete (Dame, Pique)) = 1);
    assert (compare_carte (Tete (Dame, Pique)) (Tete (Roi, Pique)) = -1);

    assert (compare_carte (Tete (Dame, Carreau)) (Tete (Valet, Carreau)) = 1);
    assert (compare_carte (Tete (Valet, Carreau)) (Tete (Dame, Carreau)) = -1);
    assert (compare_carte (Tete (Roi, Carreau)) (Tete (Valet, Carreau)) = 1);
    assert (compare_carte (Tete (Valet, Carreau)) (Tete (Roi, Carreau)) = -1);
    assert (compare_carte (Tete (Roi, Carreau)) (Tete (Dame, Carreau)) = 1);
    assert (compare_carte (Tete (Dame, Carreau)) (Tete (Roi, Carreau)) = -1);
    assert (compare_carte (Tete (Dame, Carreau)) (Tete (Roi, Coeur)) = 1);

    assert (insert (Tete (Dame, Carreau)) [] = [Tete (Dame, Carreau)]);
    assert (insert (Nombre (5, Pique)) [
        Nombre (2, Coeur);
        Tete (Valet, Coeur);
        Nombre (1, Coeur);
        Nombre (4, Pique);
        Nombre (6, Pique);
        Tete (Dame, Pique);
        Tete (Roi, Trefle);
    ] = [
        Nombre (2, Coeur);
        Tete (Valet, Coeur);
        Nombre (1, Coeur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tete (Dame, Pique);
        Tete (Roi, Trefle);
    ]);
    assert (insert (Nombre (5, Pique)) [
        Nombre (2, Coeur);
        Tete (Valet, Coeur);
        Nombre (1, Coeur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tete (Dame, Pique);
        Tete (Roi, Trefle);
    ] = [
        Nombre (2, Coeur);
        Tete (Valet, Coeur);
        Nombre (1, Coeur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tete (Dame, Pique);
        Tete (Roi, Trefle);
    ]);
    assert (insert_sort [] = []);
    assert (insert_sort [Joker] = [Joker]);
    assert (insert_sort [Nombre (4, Pique)] = [Nombre (4, Pique)]);
    assert (insert_sort [Tete (Roi, Coeur)] = [Tete (Roi, Coeur)]);
    assert (insert_sort [
        Nombre (4, Pique);
        Nombre (5, Pique);
        Tete (Roi, Trefle);
        Tete (Valet, Coeur);
        Joker;
        Nombre (6, Pique);
        Nombre (1, Coeur);
        Tete (Dame, Pique);
        Tete (Roi, Trefle);
        Nombre (2, Coeur);
        Joker;
        Nombre (6, Pique);
    ] = [
        Joker;
        Joker;
        Nombre (2, Coeur);
        Tete (Valet, Coeur);
        Nombre (1, Coeur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Nombre (6, Pique);
        Tete (Dame, Pique);
        Tete (Roi, Trefle);
        Tete (Roi, Trefle);
    ]);

    assert (
        insert_sort (carte_prec Coeur [Nombre (3, Coeur)]) =
            [Nombre (2, Coeur); Nombre (3, Coeur); Nombre (1, Coeur)]
    );

    assert (
        insert_sort (carte_prec Carreau [Tete (Valet, Carreau)]) = [
            Nombre (2, Carreau);
            Nombre (3, Carreau);
            Nombre (4, Carreau);
            Nombre (5, Carreau);
            Nombre (6, Carreau);
            Nombre (7, Carreau);
            Nombre (8, Carreau);
            Nombre (9, Carreau);
            Nombre (10, Carreau);
            Tete (Valet, Carreau);
            Nombre (1, Carreau);
        ]
    );

    assert (
        insert_sort (gen_couleur Pique) = [
            Nombre (2, Pique);
            Nombre (3, Pique);
            Nombre (4, Pique);
            Nombre (5, Pique);
            Nombre (6, Pique);
            Nombre (7, Pique);
            Nombre (8, Pique);
            Nombre (9, Pique);
            Nombre (10, Pique);
            Tete (Valet, Pique);
            Tete (Dame, Pique);
            Tete (Roi, Pique);
            Nombre (1, Pique);
        ]
    );

    print_endline "Tous les tests de l’exercice 4 ont réussi."

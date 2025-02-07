(*
 * Cette version de exercice4.ml requiert OCaml version 5.3.0 ou ultérieure.
 * Voir exercice4compat.ml pour une version du fichier fonctionnant sur les
 * versions plus anciennes.
 * (c’est dû au fait que j’utilise des caractères comme œ dans les noms de
 * variables)
 *)

type couleur = Cœur | Carreau | Pique | Trèfle

type tête = Valet | Dame | Roi

type carte =
    | Nombre of (int * couleur)
    | Tête of (tête * couleur)
    | Joker

(* Renvoie un string correspondant à la couleur c *)
let string_of_couleur (c: couleur) : string = match c with
    | Cœur -> "cœur"
    | Carreau -> "carreau"
    | Pique -> "pique"
    | Trèfle -> "trèfle"

(* Renvoie un string correspondant à la tête t *)
let string_of_tête (t: tête) : string = match t with
    | Valet -> "Valet"
    | Dame -> "Dame"
    | Roi -> "Roi"

(* Renvoie un string correspondant à la carte ca *)
let string_of_carte (ca: carte) : string = match ca with
    | Nombre (nb, c) ->
        (if nb == 1 then "As" else string_of_int nb) ^
        " de " ^
        (string_of_couleur c)
    | Tête (t, c) -> (string_of_tête t) ^ " de " ^ (string_of_couleur c)
    | Joker -> "Joker"

(*
 * Renvoie la couleur d’une carte, en supposant que la carte n’est pas un joker
 *)
let couleur_carte (ca: carte) : couleur = match ca with
    | Joker -> failwith "Les Joker n’ont pas de couleur"
    | Nombre (_, c) -> c
    | Tête (_, c) -> c

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
        | Tête (t2, _) -> if nb1 = 1 then 1 else -1
    )
    | Tête (t1, _) -> (match c2 with
        | Joker -> -1
        | Nombre (nb2, _) ->
            if nb2 = 1 then -1
            else 1
        | Tête (t2, _) ->
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
    | [] -> carte_prec c [Tête (Roi, c)]
    | x::q -> (match x with
        | Joker -> failwith "Il y a un joker dans la liste"
        | Tête (t, c) -> (match t with
            | Roi -> carte_prec c (Tête (Dame, c)::l)
            | Dame -> carte_prec c (Tête (Valet, c)::l)
            | Valet -> carte_prec c (Nombre (10, c)::l))
        | Nombre (n, c) -> if n = 1 then l
                           else carte_prec c (Nombre (n-1, c)::l))

(* Renvoie la liste des 13 cartes de la couleur `c` *)
let gen_couleur (c: couleur) : carte list = carte_prec c []


let test () =
    assert (string_of_couleur Cœur = "cœur");
    assert (string_of_couleur Carreau = "carreau");
    assert (string_of_couleur Trèfle = "trèfle");
    assert (string_of_couleur Pique = "pique");
    assert (string_of_tête Valet = "Valet");
    assert (string_of_tête Dame = "Dame");
    assert (string_of_tête Roi = "Roi");

    assert (string_of_carte (Nombre (1, Cœur)) = "As de cœur");
    assert (string_of_carte (Nombre (2, Pique)) = "2 de pique");
    assert (string_of_carte (Nombre (5, Trèfle)) = "5 de trèfle");
    assert (string_of_carte (Nombre (10, Carreau)) = "10 de carreau");
    assert (string_of_carte (Tête (Roi, Carreau)) = "Roi de carreau");
    assert (string_of_carte (Tête (Dame, Pique)) = "Dame de pique");
    assert (string_of_carte (Tête (Valet, Trèfle)) = "Valet de trèfle");

    assert (compare_carte Joker Joker = 0);
    assert (compare_carte Joker (Nombre (7, Pique)) = -1);
    assert (compare_carte Joker (Tête (Valet, Trèfle)) = -1);

    assert (compare_carte (Nombre (1, Cœur)) (Nombre (1, Cœur)) = 0);
    assert (compare_carte (Nombre (1, Cœur)) (Nombre (2, Cœur)) = 1);
    assert (compare_carte (Nombre (2, Cœur)) (Nombre (1, Cœur)) = -1);
    assert (compare_carte (Nombre (3, Cœur)) (Nombre (2, Cœur)) = 1);
    assert (compare_carte (Nombre (2, Cœur)) (Nombre (3, Cœur)) = -1);

    assert (compare_carte (Nombre (1, Carreau)) (Nombre (1, Cœur)) = 1);
    assert (compare_carte (Nombre (1, Cœur)) (Nombre (1, Carreau)) = -1);
    assert (compare_carte (Nombre (1, Pique)) (Nombre (1, Carreau)) = 1);
    assert (compare_carte (Nombre (1, Carreau)) (Nombre (1, Pique)) = -1);
    assert (compare_carte (Nombre (1, Trèfle)) (Nombre (1, Pique)) = 1);
    assert (compare_carte (Nombre (1, Pique)) (Nombre (1, Trèfle)) = -1);

    assert (compare_carte (Nombre (10, Carreau)) (Nombre (1, Cœur)) = 1);
    assert (compare_carte (Nombre (10, Cœur)) (Nombre (1, Carreau)) = -1);
    assert (compare_carte (Nombre (10, Pique)) (Nombre (1, Carreau)) = 1);
    assert (compare_carte (Nombre (10, Carreau)) (Nombre (1, Pique)) = -1);
    assert (compare_carte (Nombre (10, Trèfle)) (Nombre (1, Pique)) = 1);
    assert (compare_carte (Nombre (10, Pique)) (Nombre (1, Trèfle)) = -1);

    assert (compare_carte (Nombre (10, Carreau)) (Tête (Valet, Cœur)) = 1);
    assert (compare_carte (Nombre (10, Cœur)) (Tête (Roi, Carreau)) = -1);
    assert (compare_carte (Nombre (10, Pique)) (Tête (Valet, Carreau)) = 1);
    assert (compare_carte (Nombre (10, Carreau)) (Tête (Dame, Pique)) = -1);
    assert (compare_carte (Nombre (10, Trèfle)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Nombre (10, Pique)) (Tête (Valet, Trèfle)) = -1);
    assert (compare_carte (Nombre (1, Pique)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Nombre (1, Pique)) = -1);

    assert (compare_carte (Nombre (1, Cœur)) Joker = 1);
    assert (compare_carte (Nombre (10, Pique)) Joker = 1);

    assert (compare_carte (Tête (Valet, Cœur)) Joker = 1);
    assert (compare_carte (Tête (Roi, Pique)) Joker = 1);

    assert (compare_carte (Tête (Valet, Cœur)) (Nombre (3, Pique)) = -1);
    assert (compare_carte (Tête (Valet, Pique)) (Nombre (3, Cœur)) = 1);
    assert (compare_carte (Tête (Roi, Pique)) (Nombre (3, Pique)) = 1);

    assert (compare_carte (Tête (Valet, Cœur)) (Tête (Valet, Pique)) = -1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Valet, Cœur)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Roi, Cœur)) = 1);
    assert (compare_carte (Tête (Dame, Pique)) (Tête (Valet, Cœur)) = 1);
    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Valet, Trèfle)) = -1);

    assert (compare_carte (Tête (Dame, Pique)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Dame, Pique)) = -1);
    assert (compare_carte (Tête (Roi, Pique)) (Tête (Valet, Pique)) = 1);
    assert (compare_carte (Tête (Valet, Pique)) (Tête (Roi, Pique)) = -1);
    assert (compare_carte (Tête (Roi, Pique)) (Tête (Dame, Pique)) = 1);
    assert (compare_carte (Tête (Dame, Pique)) (Tête (Roi, Pique)) = -1);

    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Valet, Carreau)) = 1);
    assert (compare_carte (Tête (Valet, Carreau)) (Tête (Dame, Carreau)) = -1);
    assert (compare_carte (Tête (Roi, Carreau)) (Tête (Valet, Carreau)) = 1);
    assert (compare_carte (Tête (Valet, Carreau)) (Tête (Roi, Carreau)) = -1);
    assert (compare_carte (Tête (Roi, Carreau)) (Tête (Dame, Carreau)) = 1);
    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Roi, Carreau)) = -1);
    assert (compare_carte (Tête (Dame, Carreau)) (Tête (Roi, Cœur)) = 1);

    assert (insert (Tête (Dame, Carreau)) [] = [Tête (Dame, Carreau)]);
    assert (insert (Nombre (5, Pique)) [
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (1, Cœur);
        Nombre (4, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ] = [
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (1, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ]);
    assert (insert (Nombre (5, Pique)) [
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (1, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ] = [
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (1, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
    ]);
    assert (insert_sort [] = []);
    assert (insert_sort [Joker] = [Joker]);
    assert (insert_sort [Nombre (4, Pique)] = [Nombre (4, Pique)]);
    assert (insert_sort [Tête (Roi, Cœur)] = [Tête (Roi, Cœur)]);
    assert (insert_sort [
        Nombre (4, Pique);
        Nombre (5, Pique);
        Tête (Roi, Trèfle);
        Tête (Valet, Cœur);
        Joker;
        Nombre (6, Pique);
        Nombre (1, Cœur);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
        Nombre (2, Cœur);
        Joker;
        Nombre (6, Pique);
    ] = [
        Joker;
        Joker;
        Nombre (2, Cœur);
        Tête (Valet, Cœur);
        Nombre (1, Cœur);
        Nombre (4, Pique);
        Nombre (5, Pique);
        Nombre (6, Pique);
        Nombre (6, Pique);
        Tête (Dame, Pique);
        Tête (Roi, Trèfle);
        Tête (Roi, Trèfle);
    ]);

    assert (
        insert_sort (carte_prec Cœur [Nombre (3, Cœur)]) =
            [Nombre (2, Cœur); Nombre (3, Cœur); Nombre (1, Cœur)]
    );

    assert (
        insert_sort (carte_prec Carreau [Tête (Valet, Carreau)]) = [
            Nombre (2, Carreau);
            Nombre (3, Carreau);
            Nombre (4, Carreau);
            Nombre (5, Carreau);
            Nombre (6, Carreau);
            Nombre (7, Carreau);
            Nombre (8, Carreau);
            Nombre (9, Carreau);
            Nombre (10, Carreau);
            Tête (Valet, Carreau);
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
            Tête (Valet, Pique);
            Tête (Dame, Pique);
            Tête (Roi, Pique);
            Nombre (1, Pique);
        ]
    );

    print_endline "Tous les tests de l’exercice 4 ont réussi."

#!/usr/bin/env ocaml

type 'a ab =
  | V (* Vide *)
  | N of 'a * 'a ab * 'a ab (* Nœud : élément, sous-arbre gauche, sous-arbre droit *)

let t = N(3,
  N(5,
    V,
    N(8, V, V)
  ),
  N(7, V, V))

let t2 = N(1,
  N(2,
    N(4, V, V),
    N(5,
      N(6, V, V),
      N(7, N(8, V, V), V))),
  N(3, V,
    N(9, V,
      N(10,
        N(11, V, V),
        N(12, V, V)))))

let t3 = N(2,
  N(3,
    N(5, V, V),
    N(6,
      N(7, V, V),
      N(8, N(9, V, V), V))),
  N(4, V,
    N(10, V,
      N(11,
        N(12, V, V),
        N(13, V, V)))))

(* `taille a` renvoie le nombre total de nœuds de a *)
let rec taille (a: 'a ab) : int = match a with
  | V -> 0
  | N(x, g, d) -> 1 + taille g + taille d


let test_taille (taille_func: 'a ab -> int) =
  assert (taille_func V = 0);
  assert (taille_func t = 4);
  assert (taille_func (N(2, t, t)) = 9)


(* Calcule la hauteur de `a` *)
let rec hauteur (a: 'a ab) : int = match a with
  | V -> -1
  | N(x, g, d) -> 1 + max (hauteur g) (hauteur d)


let test_hauteur () =
  assert (taille V = 0);
  assert (taille t = 4);
  assert (taille (N(2, t, t)) = 9)


(* Renvoie true si `a` est une feuille, i.e. si ses deux enfants
 * sont vides
 *)
let est_feuille (a: 'a ab) : bool = match a with
  | N(x, V, V) -> true
  | _ -> false


let test_est_feuille () =
  assert (not (est_feuille V));
  assert (not (est_feuille (N(2, t, t))));
  assert (not (est_feuille (N(2, V, t))));
  assert (not (est_feuille (N(2, t, V))));
  assert (not (est_feuille t));
  assert (est_feuille (N(2, V, V)))


(* Renvoie le nombre de feuilles de `a` *)
let rec feuilles (a: 'a ab) : int = match a with
  | V -> 0
  | N(x, V, V) -> 1
  | N(x, g, v) -> feuilles g + feuilles v


let test_feuilles () =
  assert (feuilles V = 0);
  assert (feuilles (N(1, V, V)) = 1);
  assert (feuilles t = 2);
  assert (feuilles (N(1, t, V)) = 2);
  assert (feuilles (N(1, t, t)) = 4)


(* Renvoie l’étiquette du nœud correspondant au chemin `c` dans
 * l’arbre `a` (où true désigne la gauche et false la droite).
 * Lève une erreur en cas de chemin invalide
 *)
let rec etiquette (a: 'a ab) (c: bool list) : 'a = match c, a with
  | _, V -> failwith "Chemin invalide"
  | [], N(x, _, _) -> x
  | x::q, N(_, g, d) -> if x then etiquette g q
                        else etiquette d q


let test_etiquette () =
  assert (etiquette (N(1, V, V)) [] = 1);
  assert (etiquette (N(1, N(2, V, V), N(3, V, V))) [] = 1);
  assert (etiquette (N(1, N(2, V, V), N(3, V, V))) [true] = 2);
  assert (etiquette (N(1, N(2, V, V), N(3, V, V))) [false] = 3);
  assert (etiquette t [] = 3);
  assert (etiquette t [true] = 5);
  assert (etiquette t [true; false] = 8);
  assert (etiquette t [false] = 7);
  assert (etiquette (N(1, t, V)) [] = 1);
  assert (etiquette (N(1, t, V)) [true] = 3);
  assert (etiquette (N(1, t, V)) [true;true] = 5);
  assert (etiquette (N(1, t, V)) [true;true; false] = 8);
  assert (etiquette (N(1, t, V)) [true;false] = 7);
  assert (etiquette (N(1, V, t)) [] = 1);
  assert (etiquette (N(1, V, t)) [false] = 3);
  assert (etiquette (N(1, V, t)) [false;true] = 5);
  assert (etiquette (N(1, V, t)) [false;true; false] = 8);
  assert (etiquette (N(1, V, t)) [false;false] = 7)


(* Renvoie l’étiquette du nœud correspondant au chemin `c` dans
 * l’arbre `a` (où true désigne la gauche et false la droite).
 * Renvoie None en cas de chemin invalide.
 *)
let rec etiquette_opt (a: 'a ab) (c: bool list) : 'a option = match c, a with
  | _, V -> None
  | [], N(x, _, _) -> Some x
  | x::q, N(_, g, d) -> if x then etiquette_opt g q
                        else etiquette_opt d q


let test_etiquette_opt () =
  assert (etiquette_opt V [] = None);
  assert (etiquette_opt V [true] = None);
  assert (etiquette_opt V [false] = None);
  assert (etiquette_opt (N(1, V, V)) [] = Some 1);
  assert (etiquette_opt (N(1, V, V)) [true] = None);
  assert (etiquette_opt (N(1, V, V)) [false] = None);
  assert (etiquette_opt (N(1, N(2, V, V), N(3, V, V))) [] = Some 1);
  assert (etiquette_opt (N(1, N(2, V, V), N(3, V, V))) [true] = Some 2);
  assert (etiquette_opt (N(1, N(2, V, V), N(3, V, V))) [false] = Some 3);
  assert (etiquette_opt t [] = Some 3);
  assert (etiquette_opt t [true] = Some 5);
  assert (etiquette_opt t [true; false] = Some 8);
  assert (etiquette_opt t [false] = Some 7);
  assert (etiquette_opt t [true; true] = None);
  assert (etiquette_opt t [true; false; true] = None);
  assert (etiquette_opt t [true; false; false] = None);
  assert (etiquette_opt t [false; true] = None);
  assert (etiquette_opt t [false; false] = None);
  assert (etiquette_opt (N(1, t, V)) [] = Some 1);
  assert (etiquette_opt (N(1, t, V)) [true] = Some 3);
  assert (etiquette_opt (N(1, t, V)) [true;true] = Some 5);
  assert (etiquette_opt (N(1, t, V)) [true;true; false] = Some 8);
  assert (etiquette_opt (N(1, t, V)) [true;false] = Some 7);
  assert (etiquette_opt (N(1, V, t)) [] = Some 1);
  assert (etiquette_opt (N(1, V, t)) [false] = Some 3);
  assert (etiquette_opt (N(1, V, t)) [false;true] = Some 5);
  assert (etiquette_opt (N(1, V, t)) [false;true; false] = Some 8);
  assert (etiquette_opt (N(1, V, t)) [false;false] = Some 7)


(* Affiche les étiquettes de l’arbre binaire d’entiers `a` dans l’ordre
 * _préfixe_
 *)
let rec print_prefixe (a: int ab) : unit = match a with
  | V -> ()
  | N(x, g, d) -> print_int x; print_string " "; print_prefixe g; print_prefixe d


(* Affiche les étiquettes de l’arbre binaire d’entiers `a` dans l’ordre
 * _postfixe_
 *)
let rec print_postfixe (a: int ab) : unit = match a with
  | V -> ()
  | N(x, g, d) -> print_postfixe g; print_postfixe d; print_int x; print_string " "


(* Affiche les étiquettes de l’arbre binaire d’entiers `a` dans l’ordre
 * _infixe_
 *)
let rec print_infixe (a: int ab) : unit = match a with
  | V -> ()
  | N(x, g, d) -> print_infixe g; print_int x; print_string " "; print_infixe d


(* Calcule la taille de a et lui ajoute n *)
let rec taille_add (a: int ab) (n: int) : int = match a with
  | V -> n
  | N(x, g, d) -> let ng = taille_add g (n+1) in taille_add d ng


(* Calcule la taille de a *)
let taille2 (a: int ab) = taille_add a 0


(* Renvoie la liste des éléments de `a` dans l’ordre postfixe *)
let liste_postfixe (a: 'a ab) : 'a list =
  (* Renvoie (liste_postfixe a)@l *)
  let rec postfixe_concat (a: 'a ab) (l: 'a list) : 'a list = match a with
    | V -> l
    | N(x, g, d) -> let ld = postfixe_concat d (x::l) in (postfixe_concat g ld)
  in postfixe_concat a []


let test_liste_postfixe () =
  assert (liste_postfixe V = []);
  assert (liste_postfixe (N(1, V, V)) = [1]);
  assert (liste_postfixe (N(1, N(2, V, V), V)) = [2; 1]);
  assert (liste_postfixe (N(1, N(2, V, V), N(3, V, V))) = [2; 3; 1]);
  assert (liste_postfixe t2 = [4; 6; 8; 7; 5; 2; 11; 12; 10; 9; 3; 1])


(* applique la fonction f à chaque nœud de l’arbre a et renvoie l’arbre
 * qui en résulte
 *)
let rec tree_map (f: 'a -> 'b) (a: 'a ab) : 'b ab = match a with
  | V -> V
  | N(x, g, d) -> N(f x, tree_map f g, tree_map f d)


let test_tree_map () =
  assert (tree_map taille2 V = V);
  assert (tree_map (fun x -> x) t = t);
  assert (tree_map (fun x -> x) t2 = t2);
  assert (tree_map (fun x -> x+1) t2 = t3);
  assert (tree_map (fun x -> x-1) t3 = t2)


(* Calule la somme de tous les entiers contenus dans `a` *)
let rec tree_sum (a: int ab) : int = match a with
  | V -> 0
  | N(x, g, d) -> x + tree_sum g + tree_sum d


let test_tree_sum () =
  assert (tree_sum V = 0);
  assert (tree_sum t = 23);
  assert (tree_sum t2 = 78);
  assert (tree_sum t3 = 90);
  assert (tree_sum t3 = tree_sum t2 + taille2 t2)


let test () =
  test_taille taille;
  test_taille taille2;
  test_hauteur ();
  test_est_feuille ();
  test_feuilles ();
  test_etiquette ();
  test_etiquette_opt ();
  test_liste_postfixe ();
  test_tree_map ();
  test_tree_sum ()


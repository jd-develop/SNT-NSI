#!/usr/bin/env ocaml

(* DÉBUT SDC file *)
type 'a file = 'a list * 'a list

(* Renvoie une file vide *)
let file_vide () : 'a file = [], []

(* Enfile elt dans f *)
let enfiler (f: 'a file) (elt: 'a) : 'a file =
  let t, q = f in
  t, elt::q

(* Défile un élément de f, et renvoie cet élément ainsi que f sans cet
 * élément. Si la pile est vide, lève une erreur
 * Fait au maximum un appel récursif
 *)
let rec defiler (f: 'a file) : 'a * 'a file =
  let t, q = f in
  match t, q with
  | [], [] -> failwith "File vide"
  | [], q -> defiler (List.rev q, [])
  | x::t', q -> x, (t', q)


(* Renvoie true si la liste est vide, false sinon *)
let est_vide (f: 'a file) : bool = f = ([], [])

let test_files () =
  assert (est_vide (file_vide ()));
  assert (enfiler (enfiler (file_vide ()) 1) 2 = ([], [2;1]));
  assert (defiler (enfiler (enfiler (file_vide ()) 1) 2) = (1, ([2], [])));
  assert (enfiler (enfiler ([2], []) 3) 4 = ([2], [4; 3]));
  assert (defiler ([2], [4; 3]) = (2, ([], [4; 3])));
  assert (enfiler ([], [4; 3]) 5 = ([], [5; 4; 3]));
  assert (defiler ([], [5; 4; 3]) = (3, ([4; 5], [])));
  assert (defiler ([4; 5], []) = (4, ([5], [])));
  assert (defiler ([5], []) = (5, file_vide ()))
(* FIN SDC file *)

type 'a tree =
  Node of 'a * ('a tree list)


(* Arbre ternaire de taille 14, de hauteur 4, ayant 8 feuilles *)
let t = Node(1, [
  Node(2, []);
  Node(3, [
    Node(4, []);
    Node(5, []);
    Node(6, [Node(7, [])])
  ]);
  Node(8, [
    Node(9, []);
    Node(10, [
      Node(11, [
        Node(12, []);
        Node(13, []);
        Node(14, [])
    ])
    ])
  ])
])


(* Calcule la hauteur de l’arbre Node(x, l) *)
let rec hauteur (Node (x, l) : 'a tree) = 1 + max_hauteur l


(* Calcule la hauteur maximale parmi les arbres de l *)
and max_hauteur (l: 'a tree list) = match l with
  | [] -> -1
  | x::q -> let m = max_hauteur q in let h = hauteur x in max m h


let test_hauteur () =
  assert (hauteur (Node(1, [])) = 0);
  assert (hauteur t = 4)


(* Renvoie l’étiquette du nœud correspondant au chemin c dans l’arbre
 * Node(x, l). c est une liste d’entiers : 0 pour tout à gauche, 1 pour le
 * deuxième en partant de la gauche, …
 * Renvoie None si le chemin est invalide *)
let rec etiquette (Node(x, l): 'a tree) (c: int list) : 'a option =
  match x, l, c with
  | x, _, [] -> Some x
  | _, [], x::q -> None
  | _, l, x::q -> begin match List.nth_opt l x with
    | Some a -> etiquette a q
    | None -> None
    end


let test_etiquette () =
  assert (etiquette (Node(1, [])) [] = Some 1);
  assert (etiquette (Node(1, [])) [1] = None);
  assert (etiquette (Node(1, [Node(2, [])])) [0] = Some 2);
  assert (etiquette (Node(1, [Node(2, [])])) [1] = None);
  assert (etiquette t [] = Some 1);
  assert (etiquette t [0] = Some 2);
  assert (etiquette t [0; 0] = None);
  assert (etiquette t [0; 1] = None);
  assert (etiquette t [1; 0] = Some 4);
  assert (etiquette t [1; 1] = Some 5);
  assert (etiquette t [1; 2] = Some 6);
  assert (etiquette t [1; 2; 0] = Some 7);
  assert (etiquette t [1; 2; 1] = None);
  assert (etiquette t [1; 3] = None);
  assert (etiquette t [2] = Some 8);
  assert (etiquette t [2; 0] = Some 9);
  assert (etiquette t [2; 1] = Some 10);
  assert (etiquette t [2; 1; 0] = Some 11);
  assert (etiquette t [2; 1; 0; 0] = Some 12);
  assert (etiquette t [2; 1; 0; 1] = Some 13);
  assert (etiquette t [2; 1; 0; 2] = Some 14);
  assert (etiquette t [2; 1; 0; 3] = None)



(* Renvoie la liste des éléments de Node(x, l) dans l’ordre préfixe *)
let rec liste_prefixe (Node(x, l): 'a tree) : 'a list =
  x::(List.fold_left (@) [] (List.map liste_prefixe l))


(* preconcat Node(x, l) l' = liste_prefixe Node(x, l) @ l' * )
let rec preconcat (Node(x, l): 'a tree) (l': 'a list) : 'a list = match l with
  | [] -> x::l'
  | a1::q -> x::(List.concat_map liste_prefixe2 q) *)


(* Comme liste_prefixe *)
let rec liste_prefixe2 (Node(x, l): 'a tree): 'a list =
  x::(List.concat_map liste_prefixe2 l)


let test_liste_prefixe (prefixe_func: 'a tree -> 'a list) =
  assert (prefixe_func (Node(1, [])) = [1]);
  assert (prefixe_func (Node(1, [Node(2, [])])) = [1; 2]);
  assert (prefixe_func (Node(1, [Node(2, []); Node(3, [])])) = [1; 2; 3]);
  assert (prefixe_func t = List.init 14 (fun x -> x+1))


(* Renvoie la liste des éléments de Node(x, l) dans l’ordre postfixe *)
let rec liste_postfixe (Node(x, l): 'a tree) : 'a list =
  (List.fold_right (@) (List.map liste_postfixe l) [x])


(* postconcat Node(x, l), l' = liste_postfixe Node(x, l) @ l' *)
let rec postfixe_concat (Node(x, l): 'a tree) (l': 'a list): 'a list = match l with
  | [] -> x::l'
  | a1::q -> postfixe_concat a1 (postfixe_concat (Node(x, q)) l')


let liste_postfixe2 (a: 'a tree) : 'a list = postfixe_concat a []


let test_liste_postfixe (postfixe_func: 'a tree -> 'a list) =
  assert (postfixe_func (Node(1, [])) = [1]);
  assert (postfixe_func (Node(1, [Node(2, [])])) = [2; 1]);
  assert (postfixe_func (Node(1, [Node(2, []); Node(3, [])])) = [2; 3; 1]);
  assert (postfixe_func t = [2; 4; 5; 7; 6; 3; 9; 12; 13; 14; 11; 10; 8; 1])


(* Enfile chaque élément de l dans f et renvoie la file obtenue *)
let rec enfiler_liste (f: 'a file) (l: 'a list) : 'a file = match l with
  | [] -> f
  | x::q -> enfiler_liste (enfiler f x) q


let test_enfiler_liste () =
  assert (enfiler_liste (file_vide ()) ([]) = file_vide ());
  assert (enfiler_liste (file_vide ()) ([1; 2; 3; 4; 5]) = ([], [5; 4; 3; 2; 1]))


(* Renvoie la liste des étiquettes de a de(x, l) dans l’ordre du parcours
 * en largeur
 *)
let liste_largeur (a: 'a tree) : 'a list =
  (* Applique la boucle du parcours en largeur de a, à partir
   * de la file de nœuds f. Renvoie la liste des éléments visités
   *)
  let rec liste_largeur_file (f: 'a tree file) : 'a list =
    if est_vide f then []
    else let x, f' = defiler f in
    match x with
    | Node(e, []) -> e::(liste_largeur_file f')
    | Node(e, q) -> e::(liste_largeur_file (enfiler_liste f' q))
  in
  let file_depart = enfiler (file_vide ()) a in
  liste_largeur_file file_depart


let test_liste_largeur () =
  assert (liste_largeur (Node(1, [])) = [1]);
  assert (liste_largeur t = [1;2;3;8;4;5;6;9;10;7;11;12;13;14])


let test () =
  test_files ();
  test_hauteur ();
  test_etiquette ();
  test_liste_prefixe (liste_prefixe);
  test_liste_prefixe (liste_prefixe2);
  test_liste_postfixe (liste_postfixe);
  test_liste_postfixe (liste_postfixe2);
  test_enfiler_liste ();
  test_liste_largeur ()


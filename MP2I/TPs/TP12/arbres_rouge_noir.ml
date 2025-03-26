#!/usr/bin/env ocaml

type couleur = Rouge | Noir

type 'a n_arn =
  | Feuille of 'a
  | N of couleur * 'a * 'a n_arn * 'a n_arn

type 'a arn = 'a n_arn option (* None représente l’arbre vide *)


exception Erreur_hauteur_noire


(* Renvoie la couleur de la racine de a (Noir si a est une feuille) *)
let couleur_racine (a: 'a n_arn) : couleur = match a with
  | Feuille _ -> Noir
  | N(c, _, _, _) -> c


let test_couleur_racine () =
  assert (couleur_racine (Feuille 1) = Noir);
  assert (couleur_racine (N(Rouge, 1, Feuille 0, Feuille 3)) = Rouge);
  assert (couleur_racine (N(Noir, 1, Feuille 0, Feuille 3)) = Noir)


(* Renvoie true si a (arbre rouge-noir relaxé) contient deux nœuds rouges
 * succesifs
 *)
let rec contient_deux_noeuds_rouges (a: 'a n_arn) : bool = match a with
  | Feuille _ -> false
  | N(Noir, _, g, d) -> contient_deux_noeuds_rouges g || contient_deux_noeuds_rouges d
  | N(Rouge, _, g, d) ->
      couleur_racine g = Rouge || couleur_racine d = Rouge ||
      contient_deux_noeuds_rouges g || contient_deux_noeuds_rouges d


let test_contient_deux_noeuds_rouges () =
  assert (not (contient_deux_noeuds_rouges (Feuille 3)));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, Feuille 3, Feuille 4))));
  assert (not (contient_deux_noeuds_rouges (N(Rouge, 3, Feuille 3, Feuille 4))));
  assert (not (contient_deux_noeuds_rouges (N(Rouge, 3, N(Noir, 2, Feuille 2, Feuille 3), Feuille 4))));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, N(Noir, 2, Feuille 2, Feuille 3), Feuille 4))));
  assert (contient_deux_noeuds_rouges (N(Rouge, 3, N(Rouge, 2, Feuille 2, Feuille 3), Feuille 4)));
  assert (contient_deux_noeuds_rouges (N(Rouge, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6))));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, Feuille 3, N(Noir, 5, Feuille 4, Feuille 6)))));
  assert (not (contient_deux_noeuds_rouges (N(Rouge, 3, Feuille 3, N(Noir, 5, Feuille 4, Feuille 6)))))


(* Calcule la hauteur noire de l’arbre rouge-noir a, et lève
 * Erreur_hauteur_noire en cas d’incohérence
 *)
let rec hauteur_noire (a: 'a n_arn) : int = match a with
  | Feuille _ -> 0
  | N(c, _, g, d) ->
      let hg = hauteur_noire g in
      let hd = hauteur_noire d in
      if hd <> hg then raise Erreur_hauteur_noire
      else if c = Noir then 1+hg
      else hg


let test_hauteur_noire () =
  assert (hauteur_noire (Feuille(0)) = 0);
  assert (hauteur_noire (N(Rouge, 0, Feuille(0), Feuille(0))) = 0);
  assert (hauteur_noire (N(Noir, 0, Feuille(0), Feuille(0))) = 1);
  assert (hauteur_noire (N(Noir, 0, N(Noir, 0, Feuille(0), Feuille(0)), N(Noir, 0, Feuille(0), Feuille(0)))) = 2);
  try (assert (hauteur_noire (N(Noir, 0, N(Rouge, 0, Feuille(0), Feuille(0)), N(Noir, 0, Feuille(0), Feuille(0)))) < 0)) with
  | Erreur_hauteur_noire -> assert (true)


(* Renvoie true si l’arbre a est un arbre rouge-noir valide, false sinon, à
 * condition que a soit un arbre binaire de recherche strict *)
let arn_valide (a: 'a arn) : bool = match a with
  | None -> true
  | Some Feuille _ -> true
  | Some n -> begin
    (not (contient_deux_noeuds_rouges n)) &&
    couleur_racine n = Noir &&
    (try ignore (hauteur_noire n); true with | Erreur_hauteur_noire -> false) end


let test_arn_valide () =
  assert (arn_valide None);
  assert (arn_valide (Some(Feuille(3))));
  assert (not (arn_valide (Some(
    N(Rouge, 3, Feuille 3, N(Noir, 5, Feuille 4, Feuille 6)
  ))))); (* Hauteur noire différente à gauche et à droite *)
  assert (not (arn_valide (Some(
    N(Rouge, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)
  ))))); (* Deux nœuds rouges d’affilée *)
  assert (arn_valide (Some(
    N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)
  ))));
  assert (arn_valide (Some(
    N(Noir, 0, N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)), N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))
  )));
  assert (not (arn_valide (Some(
    N(Rouge, 0, N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)), N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))
  )))); (* Racine rouge *)
  assert (not (arn_valide (Some(
    N(Noir, 0, N(Rouge, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)), N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))
  )))); (* Deux rouges d’affilée *)
  assert (not (arn_valide (Some(
    N(Noir, 0, N(Rouge, 3, Feuille 3, N(Noir, 5, Feuille 4, Feuille 6)), N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))
  )))); (* Déséquilibre de hauteur noire *)
  assert (arn_valide (Some(
    N(Noir, 0, N(Rouge, 3, N(Noir, 0, Feuille 0, Feuille 0), N(Noir, 5, Feuille 4, Feuille 6)), N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))
  )))


(* Corrige l’arbre a après une insertion, d’après les 4 cas possibles. En
 * sortie : un arbre rouge-noir relaxé de même hauteur noire. *)
let correctionARN (a: 'a n_arn) : 'a n_arn =
  match a with
  | N(Noir, z, N(Rouge, y, N(Rouge, x, a, b), c), d)
  | N(Noir, z, N(Rouge, x, a, N(Rouge, y, b, c)), d)
  | N(Noir, x, a, N(Rouge, z, N(Rouge, y, b, c), d))
  | N(Noir, x, a, N(Rouge, y, b, N(Rouge, z, c, d)))
    -> N(Rouge, y, N(Noir, x, a, b), N(Noir, z, c, d))
  | _ -> a


(* Insère x dans l’arbre rouge-noir a, et renvoie le résultat sous forme
 * d’arbre rouge-noir relaxé *)
let rec insertionARNrelax (x: 'a) (a: 'a n_arn) : 'a n_arn = match a with
  | Feuille e when x < e -> N(Rouge, x, Feuille x, Feuille e)
  | Feuille e when x > e -> N(Rouge, e, Feuille e, Feuille x)
  | N(c, y, g, d) when x < y -> correctionARN (N(c, y, insertionARNrelax x g, d))
  | N(c, y, g, d) when x > y -> correctionARN (N(c, y, g, insertionARNrelax x d))
  | _ -> a


(* Insère x dans l’arbre rouge-noir a, et renvoie le résultat sous forme d’arbre
 * rouge-noir *)
let insertionARN (x: 'a) (a: 'a arn) : 'a arn = match a with
  | None -> Some(Feuille x)
  | Some n -> begin
    match (insertionARNrelax x n) with
    | Feuille y -> Some(Feuille y)
    | N(c, y, g, d) -> Some(N(Noir, y, g, d))
  end


let test_insertionARN () =
  let a = Some(Feuille(20)) in
  let a = insertionARN 17 a in
  let a = insertionARN 22 a in
  let a = insertionARN 9 a in
  let a = insertionARN 3 a in
  let a = insertionARN 25 a in
  let a = insertionARN 15 a in
  let a = insertionARN 30 a in
  let a = insertionARN 17 a in
  let a = insertionARN 23 a in
  let a = insertionARN 8 a in
  let a = insertionARN 6 a in
  let a = insertionARN 24 a in
  assert (a = Some (
    N (Noir, 20,
     N (Noir, 9,
      N (Rouge, 6, N (Noir, 3, Feuille 3, Feuille 6),
       N (Noir, 8, Feuille 8, Feuille 9)),
      N (Noir, 17, N (Rouge, 15, Feuille 15, Feuille 17), Feuille 20)),
     N (Noir, 23, N (Noir, 22, Feuille 22, Feuille 23),
      N (Noir, 25, N (Rouge, 24, Feuille 24, Feuille 25), Feuille 30)))))


let rec b (n: int) : int arn =
  if n < 0 then failwith "n doit être positif"
  else if n = 0 then Some(Feuille(0))
  else insertionARN (n) (b (n-1))


(* Renvoie la hauteur de l’arbre a *)
let rec hauteur (a: 'a arn) : int = match a with
  | None -> -1
  | Some Feuille _ -> 0
  | Some N(_, _, g, d) -> 1 + (max (hauteur (Some g)) (hauteur (Some d)))


let test_b () =
  (* Teste b avec tout entier ⩽ n *)
  let rec test_b_n (n: int) =
    if n < 0 then ()
    else
      let bn = (match b n with
        | None -> failwith "b n est vide"
        | Some(a) -> a)
      in
      assert (arn_valide (Some bn));
      assert (float_of_int (hauteur (Some bn)) <= 2. *. (log (float_of_int (2*n + 1)))/.(log 2.));
      test_b_n (n-1)
  in
  test_b_n 100



let time_b (n: int) : float =
  let time_start = Sys.time () in
  let _ = b n in
  Sys.time () -. time_start


(* Renvoie la liste des résultats de time_b sur 0, 100, 200, …, (n-1)×100 *)
let time_b_n_times (n: int) : float list =
  List.map time_b (List.init n (fun x -> x*100))


(* Renvoie une liste de flottants sous forme de liste Python *)
let list_to_python_list (l: float list) : string =
  (* Pareil mais sans [ et ] *)
  let rec list_to_interior_python_list (l: float list) : string = match l with
    | [] -> ""
    | x::[] -> string_of_float x
    | x::q -> (string_of_float x)^", "^(list_to_interior_python_list q)
  in "["^(list_to_interior_python_list l)^"]"

let test () =
  test_couleur_racine ();
  test_contient_deux_noeuds_rouges ();
  test_hauteur_noire ();
  test_arn_valide ();
  test_insertionARN ();
  test_b ()

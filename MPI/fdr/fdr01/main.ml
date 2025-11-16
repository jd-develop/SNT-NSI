(* Fiche de révisions numéro 1 *)

(* Renvoie la liste [offset; offset+1; …; offset+n-1] *
 * (j’ai utilisé cette fonction dans plusieurs tests) *)
let list_make n offset =
  List.init n (fun x -> x+offset)


(* Renvoie le dernier élément de l, et lève une erreur Invalid_argument si l
 * est vide *)
let rec dernier (l: 'a list) : 'a =
  match l with
  | [] -> raise (Invalid_argument("La liste est vide"))
  | [x] -> x
  | _::q -> dernier q

let test_dernier : unit =
  assert (dernier [1] = 1);
  assert (dernier [1; 2; 3; 4] = 4);
  assert (dernier (dernier [[4; 3; 6]; [2; 1; 4]; [1; 2]]) = 2);
  assert begin
    try (dernier []) with
    | Invalid_argument(_) -> true
    | _ -> false
  end


(* Renvoie le dernier élément de l (dans un type option), ou None si l est vide
 *)
let rec dernier_opt (l: 'a list) : 'a option =
  match l with
  | [] -> None
  | [x] -> Some x
  | _::q -> dernier_opt q

let test_dernier_opt : unit =
  assert (dernier_opt [1] = Some 1);
  assert (dernier_opt [1; 2; 3; 4] = Some 4);
  assert (dernier_opt [] = None)


(* Renvoie le miroir de l, i.e. List.rev l (mais n’utilise pas List.rev) *)
let miroir (l: 'a list) : 'a list =
  (* Renvoie le miroir de l' concaténé avec accu *)
  let rec miroir_aux (l': 'a list) (accu: 'a list) : 'a list =
    match l' with
    | [] -> accu
    | x::q -> miroir_aux q (x::accu)
  in
  miroir_aux l []

let test_miroir : unit =
  assert (miroir [] = []);
  assert (miroir ["test"] = ["test"]);
  assert (miroir [1; 2; 3; 4] = [4; 3; 2; 1])


(* miroir2 l = miroir l (= List.rev l) *)
let miroir2 (l: 'a list) : 'a list =
  List.fold_left (fun l' x -> x::l') [] l

let test_miroir2 : unit =
  assert (miroir2 [] = []);
  assert (miroir2 ["test"] = ["test"]);
  assert (miroir2 [1; 2; 3; 4] = [4; 3; 2; 1])


(* concat l1 l2 = l1@l2 *)
let concat (l1: 'a list) (l2: 'a list) : 'a list =
  (* concat_rev l1' l2' = (List.rev l1')@l2' *)
  let rec concat_rev (l1': 'a list) (l2': 'a list) : 'a list =
    match l1' with
    | [] -> l2'
    | x::q -> concat_rev q (x::l2')
  in
  concat_rev (miroir l1) l2

let test_concat : unit =
  assert (concat [] [] = []);
  assert (concat [1; 2; 3] [4; 5; 6] = list_make 6 1);
  assert (concat ["test1"] ["test2"] = ["test1"; "test2"])


(* concat2 l1 l2 = l1@l2 *)
let concat2 (l1: 'a list) (l2: 'a list) : 'a list =
  List.fold_left (fun l x -> x::l) l2 (miroir l1)

let test_concat2 : unit =
  assert (concat2 [] [] = []);
  assert (concat2 [1; 2; 3] [4; 5; 6] = list_make 6 1);
  assert (concat2 ["test1"] ["test2"] = ["test1"; "test2"])


(* Renvoie la liste l sans les occurences de x *)
let supprime_occurences (l: 'a list) (x: 'a) : 'a list =
  (* Renvoie la liste l' sans les occurrences de x, concaténée avec
   * List.rev accu *)
  let rec supprime_occurences_aux (l': 'a list) (accu: 'a list) : 'a list =
    match l' with
    | [] -> miroir accu
    | a::q ->
      if a = x then
        supprime_occurences_aux q accu
      else
        supprime_occurences_aux q (a::accu)
  in
  supprime_occurences_aux l []

let test_supprime_occurences : unit =
  assert (supprime_occurences [] () = []);
  assert (supprime_occurences [1; 2; 3] 4 = [1; 2; 3]);
  assert (supprime_occurences [1] 2 = [1]);
  assert (supprime_occurences [1; 2; 3] 2 = [1; 3]);
  assert (supprime_occurences [1] 1 = [])


(* Renvoie deux sous-listes : celle des éléments de l d’indice strictement
 * inférieur à i, et celle des élémenst de l d’indice supérieur à i.
 * En syntaxe python : (l[:i], l[i:]).
 * Si i < 0, renvoie ([], l) et si i ⩾ List.length l, renvoie (l, []) *)
let rec sous_listes (l: 'a list) (i: int) : 'a list * 'a list =
  if i <= 0 then
    [], l
  else begin
    match l with
    | [] -> [], []
    | x::q ->
        let l1, l2 = sous_listes q (i-1) in
        x::l1, l2
  end

let test_sous_listes : unit =
  assert (sous_listes [] 0 = ([], []));
  assert (sous_listes [1] 0 = ([], [1]));
  assert (sous_listes [1] 1 = ([1], []));
  assert (sous_listes [1; 2] 1 = ([1], [2]));
  assert (sous_listes (list_make 10 0) 5 = (list_make 5 0, list_make 5 5));
  assert (sous_listes (list_make 10 0) 2 = (list_make 2 0, list_make 8 2))


(* La question 9 est presque similaire à la question 8. Voici le diff :
 *  4c4
 *  < ne pas faire appel à une fonction récursive auxiliaire
 *  ---
 *  > ne pas faire appel à des fonctions récursives auxiliaires.
 *)


(* Renvoie le couple de la liste des éléments d’indice pairs dans l et de
 * la liste des éléments d’indice impairs dans l. On conserve l’ordre des
 * éléments *)
let pair_impair (l: 'a list) : 'a list * 'a list =
  (* Pareil, mais si pair est à faux, on renvoie le couple inverse, i.e.
   * formé de la liste des élémenst d’indice impairs puis celle des éléments
   * d’indice pairs dans l' *)
  let rec pair_impair_aux (l': 'a list) (pair: bool) : 'a list * 'a list =
    match l' with
    | [] -> [], []
    | x::q ->
      let l1, l2 = pair_impair_aux q (not pair) in
      if pair then x::l1, l2 else l1, x::l2
  in
  pair_impair_aux l true

let test_pair_impair : unit =
  assert (pair_impair [] = ([], []));
  assert (pair_impair [0] = ([0], []));
  assert (pair_impair [0; 1] = ([0], [1]));
  assert (pair_impair [0; 1; 2; 3] = ([0; 2], [1; 3]));
  assert (pair_impair [0; 1; 2; 3; 4] = ([0; 2; 4], [1; 3]));
  assert (pair_impair (list_make 10 0) = ([0; 2; 4; 6; 8], [1; 3; 5; 7; 9]));
  assert (pair_impair (list_make 11 0) = ([0; 2; 4; 6; 8; 10], [1; 3; 5; 7; 9]))


(* Idem que pair_impair, mais récursif terminal *)
let pair_impair_tr (l: 'a list) : 'a list * 'a list =
  (* Idem que pair_impair_aux, mais concatène la première des deux listes
   * avec (miroir accu1) et la deuxième avec (miroir accu2) *)
  let rec pair_impair_tr_aux
      (l': 'a list) (pair: bool) (accu1: 'a list) (accu2: 'a list)
      : 'a list * 'a list =
    match l' with
    | [] -> miroir accu1, miroir accu2
    | x::q ->
        if pair then
          pair_impair_tr_aux q false (x::accu1) accu2
        else
          pair_impair_tr_aux q true accu1 (x::accu2)
  in
  pair_impair_tr_aux l true [] []

let test_pair_impair_tr : unit =
  assert (pair_impair_tr [] = ([], []));
  assert (pair_impair_tr [0] = ([0], []));
  assert (pair_impair_tr [0; 1] = ([0], [1]));
  assert (pair_impair_tr [0; 1; 2; 3] = ([0; 2], [1; 3]));
  assert (pair_impair_tr [0; 1; 2; 3; 4] = ([0; 2; 4], [1; 3]));
  assert (
    pair_impair_tr (list_make 11 0) = ([0; 2; 4; 6; 8; 10], [1; 3; 5; 7; 9])
  )


(* Renvoie true si la liste est un palindrome *)
let palindrome (l: 'a list) : bool =
  (* O(n) pour miroir et O(n) pour la comparaison *)
  miroir l = l

let test_palindrome : unit =
  assert (palindrome []);
  assert (palindrome [1]);
  assert (palindrome [0; 1; 2; 1; 0]);
  assert (palindrome [0; 1; 2; 2; 1; 0]);
  assert (not (palindrome [0; 1]));
  assert (not (palindrome [0; 1; 2]))

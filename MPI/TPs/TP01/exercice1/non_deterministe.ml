
(* Renvoie le numéro correspondant à la lettre c, c étant une lettre sans
 * diacritiques de l’alphabet latin (i.e. appartenant à la table ASCII).
 * La numérotation commence à 0 : a->0, b->1, …, z->25 *)
let int_of_letter (c: char) : int =
  if 'a' <= c && c <= 'z' then
    int_of_char c - 0x61
  else
    failwith (
      "int_of_letter: le caractère donné n’est pas une lettre minuscule de " ^
      "l’alphabet latin sans diacritiques."
    )
(* La fonction int_of_letter est testée dans deterministe_complet.ml *)


(* Renvoie true si atomate_nd est déterministe, false sinon *)
let est_deterministe (a: automate_nd) =
  (* Un automate déterminste aura au + 1 transition (q, a, q’) pour
   * q et a fixés, i.e. List.length trans.(q).(a) <= 1. *)
  if List.length a.init > 1 then
    false
  else begin
    let result = ref true in
    for i = 0 to Array.length a.trans - 1 do
      for j = 0 to Array.length a.trans.(i) - 1 do
        result := !result && List.length a.trans.(i).(j) <= 1;
      done
    done;
    !result
  end

let test_est_deterministe : unit =
  assert (not (est_deterministe auto_2));
  assert (not (est_deterministe test_deter));
  let auto_deterministe = {
    init = [0];
    trans =
      [|
        [| [0]; [];  [1] |];
        [| [2]; [0]; [] |];
        [| [1]; [1]; [2] |];
      |];
    fin = [];
  } in
  assert (est_deterministe auto_deterministe);
  let trop_etats_initiaux = {
    init = [0;1];
    trans =
      [|
        [| [0]; [];  [1] |];
        [| [2]; [0]; [] |];
        [| [1]; [1]; [2] |];
      |];
    fin = [];
  } in
  assert (not (est_deterministe trop_etats_initiaux))


(* Renvoie une copie de la liste l mais sans doublons.
 * En cas de doublons, le *dernier* doublon est gardé uniquement. *)
let enleve_doublons (l: 'a list) : 'a list =
  (* Renvoie List.rev accu suivie d’une copie de la liste l mais sans
   * doublons (en cas de doublons, le *dernier* doublon est gardé
   * uniquement). Cette fonction est récursive terminale. *)
  let rec enleve_doublons_concat (l: 'a list) (accu: 'a list) =
    match l with
    | [] -> List.rev accu
    | x::q -> if List.mem x q then enleve_doublons_concat q accu
              else enleve_doublons_concat q (x::accu)
  in
  enleve_doublons_concat l []

let test_enleve_doublons : unit =
  assert (enleve_doublons [1; 2; 4; 3; 2; 2; 6; 1; 3] = [4; 2; 6; 1; 3]);
  assert (enleve_doublons [1; 2; 3] = [1; 2; 3]);
  assert (enleve_doublons [] = []);
  assert (enleve_doublons [1; 1; 1; 2; 2; 2; 1; 1; 1] = [2; 1])


(* Étant donné un automate a, un état q et une lettre l, renvoie
 * l’ensemble des états q’ tels que (q, l, q’) soit une transition
 * de a *)
let delta_singleton (a: automate_nd) (q: int) (l: char) =
  enleve_doublons (a.trans.(q).(int_of_letter l))

let test_delta_singleton : unit =
  assert (delta_singleton auto_2 3 'b' = [3]);
  assert (delta_singleton auto_2 0 'a' = [0; 1]);
  assert (delta_singleton auto_2 2 'a' = []);
  let auto_avec_doublons = {
    init = [0];
    trans =
      [| [| [1; 1]; [0] |];
         [| [0]; [0; 1; 1; 0] |];
      |];
    fin = [1];
  } in
  assert (delta_singleton auto_avec_doublons 0 'a' = [1]);
  assert (delta_singleton auto_avec_doublons 1 'b' = [1; 0]);
  assert (delta_singleton auto_avec_doublons 1 'a' = [0])


(* Étant donné un automate a, un ensemble d’états s (sans doublons)
 * et une lettre l, renvoie l’ensemble (liste sans doublons) des états q’
 * accessibles depuis un des états q de s par une transition (q, l, q’) *)
let rec delta (a: automate_nd) (s: int list) (l: char) : int list =
  let rec delta_concat
  (a: automate_nd) (s: int list) (l: char) (accu: int list) =
    match s with
    | [] -> enleve_doublons accu
    | x::q -> delta_concat a q l ((delta_singleton a x l)@accu)
  in
  delta_concat a s l []


let test_delta : unit =
  assert (delta auto_2 [0] 'a' = [0; 1]);
  assert (delta auto_2 [0; 1] 'a' = [2; 0; 1]);
  assert (delta auto_2 [] 'a' = [])


(* Étant donné un automate a, un ensemble d’états s et un mot w, renvoie
 * l’ensemble des états q’ atteints en lisant le mot w en partant d’un état
 * de s dans a. s est supposée sans doublons et la liste de sortie est
 * sans doublons *)
let rec delta_etoile (a: automate_nd) (s: int list) (w: string) : int list =
  let n = String.length w in
  if n = 0 then
    s
  else
    delta_etoile a (delta a s w.[0]) (String.sub w 1 (n-1))

let test_delta_etoile : unit =
  assert (delta_etoile auto_2 [0] "ab" = [2; 0]);
  assert (delta_etoile auto_2 [0] "abc" = [3]);
  assert (delta_etoile auto_2 [] "abc" = []);
  assert (delta_etoile auto_2 [1; 2] "ba" = []);
  assert (delta_etoile auto_2 [0; 3] "aab" = [3; 2; 0])


(* Étant donné un automate a et un mot w, renvoie true si w est reconnu par
 * a, false sinon *)
let accepte (a: automate_nd) (w: string) : bool =
  let etats_fin = delta_etoile a a.init w in
  (* renvoie true si l’intersection de a et b est non vide, false sinon *)
  let rec intersection_non_vide (l: 'a list) (l': 'a list) : bool =
    match l with
    | [] -> false
    | x::q -> if List.mem x l' then true
              else intersection_non_vide q l'
  in intersection_non_vide etats_fin a.fin

let test_accepte (f_accepte: automate_nd -> string -> bool) : unit =
  (* appelé 2 fois dans teste_toutes_les_fonctions_accepte *)
  assert (accepte auto_2 "abab");
  assert (accepte auto_2 "abaaabc");
  assert (accepte auto_2 "cabcacbcacc");
  assert (accepte auto_2 "aa");
  assert (accepte auto_2 "c");
  assert (not (accepte auto_2 "a"));
  assert (not (accepte auto_2 "b"));
  assert (not (accepte auto_2 "ba"));
  assert (not (accepte auto_2 "bbbba"))


(* Renvoie true si la lecture de w à partir de l'indice i, dans l'automate a,
 * en partant de l'état q, conduit à un état final *)
let rec accepte_depuis (a: automate_nd) (q: int) (w: string) (i: int) : bool =
  let n = String.length w in
  if i = n then
    List.mem q a.fin
  else
    List.exists
      (fun x -> accepte_depuis a x w (i+1))
      a.trans.(q).(int_of_letter (w.[i]))

let test_accepte_depuis : unit =
  assert (accepte_depuis auto_2 0 "abab" 0);
  assert (accepte_depuis auto_2 2 "abaaabc" 7);
  assert (accepte_depuis auto_2 2 "cabcacbcacc" 3);
  assert (accepte_depuis auto_2 0 "aa" 0);
  assert (accepte_depuis auto_2 1 "c" 0);
  assert (not (accepte_depuis auto_2 1 "c" 1));
  assert (not (accepte_depuis auto_2 0 "b" 0));
  assert (not (accepte_depuis auto_2 2 "ba" 1));
  assert (not (accepte_depuis auto_2 0 "bbbba" 3));
  assert (not (accepte_depuis auto_2 0 "aa" 1))

(* Pareil que accepte *)
let accepte_v2 (a: automate_nd) (w: string) : bool =
  accepte_depuis a 0 w 0

let teste_toutes_les_fonctions_accepte : unit =
  test_accepte accepte;
  test_accepte accepte_v2


(************************************************
 * Partie 1 : Automates déterministes
 ************************************************)

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

let test_int_of_letter : unit =
  assert (int_of_letter 'a' = 0);
  assert (int_of_letter 'b' = 1);
  assert (int_of_letter 'z' = 25);
  let msg_erreur = (
      "int_of_letter: le caractère donné n’est pas une lettre minuscule de " ^
      "l’alphabet latin sans diacritiques."
  ) in
  assert (try (let _ = int_of_letter '@' in false)
          with | Failure x when x = msg_erreur -> true | _ -> false);
  assert (try (let _ = int_of_letter 'A' in false)
          with | Failure x when x = msg_erreur -> true | _ -> false)


(* Étant donné un automate a, un état q et une lettre l, renvoie l’état q'
 * atteint grâce à la transition (q, a, q') *)
let delta (a: automate_d) (q: int) (l: char) : int =
  a.trans.(q).(int_of_letter l)

let test_delta : unit =
  assert (delta auto_1 0 'a' = 1);
  assert (delta auto_1 0 'b' = 0);
  assert (delta auto_1 0 'd' = 4);
  assert (delta auto_1 2 'a' = 3);
  assert (delta auto_1 2 'c' = 2);
  assert (delta auto_1 2 'd' = 4);
  assert (delta auto_1 4 'a' = 4);
  assert (delta auto_1 4 'b' = 4);
  assert (delta auto_1 4 'e' = 4)


(* Étant donné un automate a, un état q et un mot w, renvoie l’état q'
 * atteint en lisant le mot w en partant de q dans a. *)
let rec delta_etoile (a: automate_d) (q: int) (w: string) : int =
  let n = String.length w in
  if n = 0 then
    q
  else
    delta_etoile a (delta a q w.[0]) (String.sub w 1 (n-1))

let test_delta_etoile : unit =
  assert (delta_etoile auto_1 0 "addddabccaabad" = 1);
  assert (delta_etoile auto_1 1 "aceacbacecacbcacecced" = 4);
  assert (delta_etoile auto_1 1 "aaaab" = 4);
  assert (delta_etoile auto_1 2 "bccbcbcbccbcb" = 2);
  assert (delta_etoile auto_1 4 "acbddcacbdecadbcacedbdbacdbd" = 4)


(* Étant donné un automate a et un mot w, renvoie true si w est accepté par a
 * et false sinon *)
let accepte (a: automate_d) (w: string) : bool =
  let etat_fin = delta_etoile a 0 w in
  List.mem etat_fin a.fin

let test_accepte (f_accepte: automate_d -> string -> bool) : unit =
  (* appelé 2 fois dans teste_toutes_les_fonctions_accepte *)
  assert (f_accepte auto_1 "bcadabc");
  assert (not (f_accepte auto_1 "d"));
  assert (f_accepte auto_1 "aa");
  assert (not (f_accepte auto_1 "aabaa"))


(* Renvoie true si la lecture de w à partir de l'indice i, dans l'automate a,
 * en partant de l'état q, conduit à un état final *)
let rec accepte_depuis (a: automate_d) (q: int) (w: string) (i: int) : bool =
  let n = String.length w in
  if i = n then
    List.mem q a.fin
  else if i > n then
    raise (Invalid_argument "accepte_depuis : indice hors de la plage.")
  else
    accepte_depuis auto_1 (delta auto_1 q w.[i]) w (i+1)

let test_accepte_depuis : unit =
  assert (accepte_depuis auto_1 1 "debcabc" 4);
  assert (not (accepte_depuis auto_1 1 "debcabc" 3));
  assert (accepte_depuis auto_1 2 "d" 1);
  assert (accepte_depuis auto_1 2 "" 0);
  assert (not (accepte_depuis auto_1 4 "" 0));
  let err_msg = "accepte_depuis : indice hors de la plage." in
  assert (try (let _ = accepte_depuis auto_1 0 "a" 2 in false)
          with | Invalid_argument x when x = err_msg -> true | _ -> false)


(* Exactement la même chose que accepte *)
let accepte_v2 (a: automate_d) (w: string) : bool =
  accepte_depuis a 0 w 0

let teste_toutes_les_fonctions_accepte : unit =
  test_accepte accepte;
  test_accepte accepte_v2


(************************************************
 * Partie 2 : Automates non déterministes
 ************************************************)


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


(* Étant donné un automate non déterministe a, un ensemble d’états s
 * (sans doublons) et une lettre l, renvoie l’ensemble (liste sans doublons) des
 * états q’ accessibles depuis un des états q de s par une transition
 * (q, l, q’) *)
let rec delta_nd (a: automate_nd) (s: int list) (l: char) : int list =
  let rec delta_concat
  (a: automate_nd) (s: int list) (l: char) (accu: int list) =
    match s with
    | [] -> enleve_doublons accu
    | x::q -> delta_concat a q l ((delta_singleton a x l)@accu)
  in
  delta_concat a s l []


let test_delta_nd : unit =
  assert (delta_nd auto_2 [0] 'a' = [0; 1]);
  assert (delta_nd auto_2 [0; 1] 'a' = [2; 0; 1]);
  assert (delta_nd auto_2 [] 'a' = [])


(* Étant donné un automate non déterministe a, un ensemble d’états s et un mot
 * w, renvoie * l’ensemble des états q’ atteints en lisant le mot w en partant
 * d’un état de s dans a. s est supposée sans doublons et la liste de sortie est
 * sans doublons *)
let rec delta_etoile_nd (a: automate_nd) (s: int list) (w: string) : int list =
  let n = String.length w in
  if n = 0 then
    s
  else
    delta_etoile_nd a (delta_nd a s w.[0]) (String.sub w 1 (n-1))

let test_delta_etoile_nd : unit =
  assert (delta_etoile_nd auto_2 [0] "ab" = [2; 0]);
  assert (delta_etoile_nd auto_2 [0] "abc" = [3]);
  assert (delta_etoile_nd auto_2 [] "abc" = []);
  assert (delta_etoile_nd auto_2 [1; 2] "ba" = []);
  assert (delta_etoile_nd auto_2 [0; 3] "aab" = [3; 2; 0])


(* Étant donné un automate non déterministe a et un mot w, renvoie true si w est
 * reconnu par a, false sinon *)
let accepte_nd (a: automate_nd) (w: string) : bool =
  let etats_fin = delta_etoile_nd a a.init w in
  (* renvoie true si l’intersection de a et b est non vide, false sinon *)
  let rec intersection_non_vide (l: 'a list) (l': 'a list) : bool =
    match l with
    | [] -> false
    | x::q -> if List.mem x l' then true
              else intersection_non_vide q l'
  in intersection_non_vide etats_fin a.fin

let test_accepte_nd (f_accepte: automate_nd -> string -> bool) : unit =
  (* appelé 2 fois dans teste_toutes_les_fonctions_accepte *)
  assert (f_accepte auto_2 "abab");
  assert (f_accepte auto_2 "abaaabc");
  assert (f_accepte auto_2 "cabcacbcacc");
  assert (f_accepte auto_2 "aa");
  assert (f_accepte auto_2 "c");
  assert (not (f_accepte auto_2 "a"));
  assert (not (f_accepte auto_2 "b"));
  assert (not (f_accepte auto_2 "ba"));
  assert (not (f_accepte auto_2 "bbbba"))


(* Renvoie true si la lecture de w à partir de l'indice i, dans l'automate non
 * déterministe a, en partant de l'état q, conduit à un état final *)
let rec accepte_depuis_nd (a: automate_nd) (q: int) (w: string) (i: int) : bool =
  let n = String.length w in
  if i = n then
    List.mem q a.fin
  else
    List.exists
      (fun x -> accepte_depuis_nd a x w (i+1))
      a.trans.(q).(int_of_letter (w.[i]))

let test_accepte_depuis_nd : unit =
  assert (accepte_depuis_nd auto_2 0 "abab" 0);
  assert (accepte_depuis_nd auto_2 2 "abaaabc" 7);
  assert (accepte_depuis_nd auto_2 2 "cabcacbcacc" 3);
  assert (accepte_depuis_nd auto_2 0 "aa" 0);
  assert (accepte_depuis_nd auto_2 1 "c" 0);
  assert (not (accepte_depuis_nd auto_2 1 "c" 1));
  assert (not (accepte_depuis_nd auto_2 0 "b" 0));
  assert (not (accepte_depuis_nd auto_2 2 "ba" 1));
  assert (not (accepte_depuis_nd auto_2 0 "bbbba" 3));
  assert (not (accepte_depuis_nd auto_2 0 "aa" 1))

(* Pareil que accepte_nd *)
let accepte_nd_v2 (a: automate_nd) (w: string) : bool =
  accepte_depuis_nd a 0 w 0

let teste_toutes_les_fonctions_accepte_nd : unit =
  test_accepte_nd accepte_nd;
  test_accepte_nd accepte_nd_v2


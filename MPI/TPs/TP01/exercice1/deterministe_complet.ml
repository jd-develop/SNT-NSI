
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

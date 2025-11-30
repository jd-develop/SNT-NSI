
type 'a btree =
  | E  (* arbre vide *)
  | N of 'a * 'a btree * 'a btree  (* nœud *)

type 'a gtree =
  | GN of 'a * 'a gtree list


(* Arbre général un peu grand pour faire des tests. Cet arbre possède 6 nœuds
 * internes et 8 feuilles (donc 14 nœuds) et sa hauteur est 3. *)
let g0 : int gtree =
  GN (1, [
    GN (2, [
      GN (7, []);
      GN (8, [])
    ]);
    GN (3, []);
    GN (4, [
      GN (9, [])
    ]);
    GN (5, [
      GN (10, []);
      GN (11, []);
      GN (12, [])
    ]);
    GN (6, [
      GN (13, [
        GN(14, [])
      ])
    ])
  ])



(* R3-1 *)
(* Renvoie vrai si t est vide, faux sinon *)
let est_vide (t: 'a btree) : bool =
  t = E

let test_est_vide : unit =
  assert (est_vide E);
  assert (not (est_vide (N (1, E, E))))


(* R3-2 *)
(* Renvoie la hauteur de l’arbre t (-1 si l’arbre est vide) *)
let rec hauteur (t: 'a btree) : int =
  match t with
  | E -> -1
  | N(_, gauche, droite) -> 1 + max (hauteur gauche) (hauteur droite)

let test_hauteur : unit =
  assert (hauteur E = -1);
  assert (hauteur (N(1, E, E)) = 0);
  assert (hauteur (N(1, N(2, E, E), E)) = 1);
  assert (hauteur (N(1, N(2, E, N(3, E, E)), N(1, E, E))) = 2)


(* R3-3 *)
(* Renvoie le nombre de nœuds de t *)
let rec taille (t : 'a gtree) : int =
  let GN (_, l) = t in
  1 + taille_liste l
(* Renvoie la somme du nombre de nœuds de chaque arbre de l *)
and taille_liste (l: 'a gtree list) : int =
  match l with
  | [] -> 0
  | x::q -> taille x + taille_liste q

let test_taille : unit =
  assert (taille (GN (1, [])) = 1);
  assert (taille (GN (1, [GN (2, []); GN(3, [GN (4, [])])])) = 4);
  assert (taille g0 = 14)


(* R3-4 *)
(* Renvoie le nombre de nœuds de t *)
let rec taille2 (t : 'a gtree) : int =
  let GN (_, l) = t in
  List.fold_left
    (fun (somme: int) (arbre: 'a gtree) -> somme + (taille2 arbre))
    1 l

let test_taille2 : unit =
  assert (taille2 (GN (1, [])) = 1);
  assert (taille2 (GN (1, [GN (2, []); GN(3, [GN (4, [])])])) = 4);
  assert (taille2 g0 = 14)


(* R3-5 *)
(* Renvoie le nombre de nœuds de t *)
let taille3 (t : 'a gtree) : int =
  (* Renovie la somme des sommes des nombres de nœuds des arbres des listes
   * de ll + accu *)
  let rec taille_accu (ll: 'a gtree list list) (accu: int) : int =
    match ll with
    | [] -> accu  (* aucune liste d’arbres *)
    (* première liste d’arbres vide : on n’ajoute rien à accu et on continue
     * avec le reste de listes d’arbres *)
    | []::q' -> taille_accu q' accu
    (* on rencontre une liste non vide : on ajoute les sous-arbres du premier
     * nœud à notre liste de listes d’arbres *)
    | (t'::q_arbres)::q_listes ->
        let GN (_, l') = t' in
        taille_accu (l'::q_arbres::q_listes) (accu+1)
  in taille_accu [[t]] 0

let test_taille3 : unit =
  assert (taille3 (GN (1, [])) = 1);
  assert (taille3 (GN (1, [GN (2, []); GN(3, [GN (4, [])])])) = 4);
  assert (taille3 g0 = 14)


(* R3-6 *)
(* Renvoie true si e est une étiquette de t, false sinon *)
let rec appartient (e: 'a) (t: 'a btree) : bool =
  match t with
  | E -> false
  | N (x, g, d) -> e=x || appartient e g || appartient e d

let test_appartient : unit =
  assert (appartient 1 (N(1, E, E)));
  assert (not (appartient 1 E));
  assert (appartient 3 (N(1, N(2, E, E), N(3, E, N(4, E, E)))));
  assert (not (appartient 5 (N(1, N(2, E, E), N(3, E, N(4, E, E))))))


(* R3-7 *)
(* Renvoie None si t est vide et Some(minimum, maximum) sinon, où minimum est
 * le minimum des étiquettes de l’arbre, et maximum est leur maximum *)
let rec min_max (t: int btree) : (int * int) option =
  match t with
  | E -> None
  | N(i, g, d) ->
      let min_max_g = min_max g in
      let min_max_d = min_max d in
      match (min_max_d, min_max_g) with
      | None, None -> Some (i, i)
      | Some(min_, max_), None
      | None, Some(min_, max_) ->
          Some (min min_ i, max max_ i)
      | Some (min_g, max_g), Some (min_d, max_d) ->
          Some (
            min (min min_g min_d) i,
            max (max max_g max_d) i
          )

let test_min_max_f (min_max_f: int btree -> (int * int) option) : unit =
  assert (min_max_f E = None);
  assert (min_max_f (N(1, E, E)) = Some (1, 1));
  assert (min_max_f (N(1, N(2, E, E), E)) = Some (1, 2));
  assert (min_max_f (N(1, E, N(2, E, E))) = Some (1, 2));
  assert (min_max_f (N(1, N(0, E, E), E)) = Some (0, 1));
  assert (min_max_f (N(1, E, N(0, E, E))) = Some (0, 1));
  assert (min_max_f (N(1, N(0, E, E), N(2, E, E))) = Some (0, 2));
  assert (min_max_f (N(1, N(2, E, E), N(0, E, E))) = Some (0, 2));
  assert (min_max_f (N(0, N(1, E, E), N(2, E, E))) = Some (0, 2));
  assert (min_max_f (N(0, N(2, E, E), N(1, E, E))) = Some (0, 2));
  assert (min_max_f (N(2, N(0, E, E), N(1, E, E))) = Some (0, 2));
  assert (min_max_f (N(2, N(1, E, E), N(0, E, E))) = Some (0, 2));
  assert (min_max_f (N(1, N(1, E, E), N(0, E, E))) = Some (0, 1));
  assert (min_max_f (N(1, N(1, E, E), N(1, E, E))) = Some (1, 1))

let test_min_max : unit = test_min_max_f min_max


(* R3-8 *)
(* Comme min_max, mais récursif terminal *)
let min_max_tr (t: int btree) : (int * int) option =
  (* Renvoie le min et le max de tous les arbres de l, mais si
   * accu = Some(mi, ma), renvoie le minimum entre le minimum des arbres de l et
   * mi et le maximum entre le maximum des arbres de l et ma *)
  let rec aux (l: int btree list) (accu : (int * int) option) :
      (int * int) option =
    match l with
    | [] -> accu
    | E::q -> aux q accu
    | (N(i, g, d))::q ->
        let new_accu = match accu with
        | None -> Some (i, i)
        | Some (mi, ma) -> Some (min mi i, max ma i)
        in
        aux (g::d::q) new_accu
  in
  aux [t] None

let test_min_max_tr : unit = test_min_max_f min_max_tr


(* R3-9 *)
(* Teste si t et t' ont la même forme, i.e. sont égaux lorsqu’on retire les
 * étiquettes *)
let rec meme_forme (t: 'a btree) (t': 'b btree) : bool =
  match (t, t') with
  | E, E -> true
  | N(_, _, _), E
  | E, N(_, _, _) -> false
  | N(_, g1, d1), N(_, g2, d2) -> meme_forme g1 g2 && meme_forme d1 d2

let test_meme_forme : unit =
  assert (meme_forme E E);
  assert (meme_forme (N(1, E, N(2, E, E))) (N(E, E, N(E, E, E))));
  assert (not (meme_forme E (N(1, E, E))));
  assert (not (meme_forme (N(2, E, E)) E));
  assert (not (meme_forme (N(1, E, N(2, E, E))) (N(1, N(2, E, E), E))))


(* R3-10 *)
(* Renvoie, si cela existe, Some(p) où p est la profondeur d’un nœud d’étiquette
 * paire. Renvoie None sinon. *)
let profondeur_pair (t: int btree) : int option =
  let exception Fini of int in
  (* S’il existe un nœud d’étiquette paire dans t', plante avec Fini(profondeur
   * du nœud + profondeur_actuelle). Si un tel nœud n’existe pas, renvoie (). *)
  let rec aux (t': int btree) (profondeur_actuelle: int) : unit =
    match t' with
    | E -> ()
    | N(i, _, _) when i mod 2 = 0 -> raise (Fini (profondeur_actuelle))
    | N(_, g, d) ->
        (aux g (profondeur_actuelle+1); aux d (profondeur_actuelle+1))
  in
  try
    aux t 0; None
  with
  | Fini(p) -> Some(p)

let test_profondeur_pair : unit =
  assert (profondeur_pair E = None);
  assert (profondeur_pair (N(1, E, E)) = None);
  assert (profondeur_pair (N(2, E, E)) = Some(0));
  assert (profondeur_pair (N(1, N(3, E, E), N(2, E, E))) = Some(1));
  (* dans le cas suivant, puisque profondeur_pair regarde à gauche puis à
   * droite, c’est 2 qui est renvoyé et non 1. *)
  assert (profondeur_pair (N(1, N(3, E, N(2, E, E)), N(4, E, E))) = Some(2))

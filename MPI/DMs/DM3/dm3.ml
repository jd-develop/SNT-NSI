(* Renvoie le pgcd de a et de b en suivant l’algorithme d’Euclide. *)
let rec gcd (a: int) (b: int) =
  if a < 0 then
    gcd (-a) b
  else if b < 0 then
    gcd a (-b)
  else if b = 0 then
    a
  else
    gcd b (a mod b)


module Q = struct
  type t = int * int
  (* (a, b) encode a/b*)
  (* invariant : a ∧ b = 1 et b > 0 et si a = 0 alors b = 1 *)
  (* NB: vu l'invariant, l'égalité syntaxique de OCaml (a, b)=(c, d)*)
  (*     encode en fait l'égalité sémantique de Q : a/b = c/d *)
  let print ((a, b): t) = Printf.printf "%d/%d" a b
  let dirty_print ((a, b): t) =
    Printf.printf "%.2f" ((float_of_int a) /. (float_of_int b))

  (* Renvoie une représentation de (a, b) satisfaisant l’invariant *)
  let simplify ((a, b): t) : t =
    let pgcd = gcd a b in
    if b < 0 then ((-a)/pgcd, (-b)/pgcd)
    else (a/pgcd, b/pgcd)

  (* a/b + c/d *)
  let (+..) ((a, b): t) ((c, d): t) : t =
    simplify (a*d + c*b, b*d)

  (* a/b - c/d *)
  let (-..) ((a, b): t) ((c, d): t) : t =
    (a, b) +.. (-c, d)

  (* -(a/b) *)
  let oppose ((a, b): t) : t =
    (-a, b)

  (* (a/b)(c/d) *)
  let ( *.. ) ((a, b): t) ((c, d): t) : t =
    simplify (a*c, b*d)

  (* (a/b)/(c/d) *)
  let (/..) ((a, b): t) ((c, d): t) : t =
    simplify (a*d, b*c)

  (* convertit un entier en rationnel *)
  let rational_of_int (a: int) : t =
    (a, 1)

  (* renvoie le signe (-1, 0 ou 1) de a/b *)
  let sign ((a, b): t) : int =
    if a < 0 then -1
    else if a = 0 then 0
    else 1

  (* a/b < c/d *)
  let (<..) ((a, b): t) ((c, d): t) : bool =
    if (sign (a, b) < sign (c, d)) then
      true
    else if (sign (a, b) > sign (c, d)) then
      false
    else if c = 0 then
      (* alors a aussi est nul *)
      false
    else
      (* ici, ils sont de même signe et tous deux non nuls, le résultat du
       * rapport est donc strictement positif *)
      let rapport = (a, b) /.. (c, d) in
      fst rapport < snd rapport

  (* a/b <= c/d *)
  let (<=..) ((a, b): t) ((c, d): t) : bool =
    (a, b) = (c, d) || (a, b) <.. (c, d)

  (* a/b > (c/d) *)
  let (>..)  ((a, b): t) ((c, d): t) : bool =
    not ((a, b) <=.. (c, d))

  (* a/b >= (c/d) *)
  let (>=..)  ((a, b): t) ((c, d): t) : bool =
    not ((a, b) <.. (c, d))

  (* a/b est entier *)
  let is_int ((a, b): t) : bool =
    b = 1
end

(* Les tests sont plus loin *)


type sad =
  {
    n  : int;                (* le nombre d’objets                  *)
    wi : int array;          (* le tableau des poids, de taille n   *)
    vi : int array;          (* le tableau des valeurs, de taille n *)
    p  : int                 (* le poids maximal du sac à dos, >=0  *)
}

let ex =
  {
    n  = 6;
    wi = [|6  ; 8 ; 10; 14; 2; 5|];
    vi = [|13 ; 16; 19; 24; 3; 5|];
    p  = 20;
  }


type masque = bool option array

type solution = bool array

type qsolution = Q.t array

(* Fonction d'affichage d'un tableau *)
let affiche_array_param (pp: 'a -> unit) (m: 'a array) =
  let n = Array.length m in
  Printf.printf "[|";
  for i = 0 to n-2 do
    pp m.(i) ; Printf.printf "; "
  done;
  if n > 0 then pp m.(n-1);
  Printf.printf "|]"

(* Affiche un masque *)
let affiche_masque (m: masque) =
  let print_masque_atom (bo: bool option) =
    match bo with
    | None        -> Printf.printf " "
    | Some(true)  -> Printf.printf "Y"
    | Some(false) -> Printf.printf "N"
  in
  affiche_array_param print_masque_atom m

(* Affichage d'une solution entière *)
let affiche_solution (m: solution) =
  let print_solution_atom (bo: bool) =
    Printf.printf (if bo then "1" else "0")
  in
  affiche_array_param print_solution_atom m

(* Affichage d'une solution fractionnaire *)
let affiche_qsolution (m: qsolution) =
  affiche_array_param Q.print m

(* ======= FIN DU COMPAGNON ======= *)

(* PARTIE 1 *)

(* Question 1 *)
(* Renvoie true si l’instance `sac` est valide, false sinon *)
let est_sad_valide (sac: sad) : bool =
  (* Renvoie a/b <= c/d (fonction réécrite après la partie 5) *)
  let (<=.) ((a, b): int * int) ((c, d): int * int) =
    Q.( simplify (a, b) <=.. simplify (c, d) )
  in

  let n = Array.length sac.vi in
  let longueurs_valides = (sac.n = n && n = Array.length sac.wi) in
  let contenance_valide = sac.p >= 0 in
  if (longueurs_valides && contenance_valide) then
    (* on ne vérifie les rapports que si les tailles sont correctes *)
    let exception Invalide in
    try
      for i = 1 to n-1 do
        if not ((sac.vi.(i), sac.wi.(i)) <=. (sac.vi.(i-1), sac.wi.(i-1))) then
          raise Invalide
      done;
      true
    with
    | Invalide -> false
  else
    false

let test_est_sad_valide : unit =
  assert (est_sad_valide ex);
  assert (not (est_sad_valide {ex with n = 5}));
  assert (not (est_sad_valide {ex with wi = [||]}));
  assert (not (est_sad_valide {ex with vi = [|13; 8; 19; 24; 3; 5|]}));
  assert (not (est_sad_valide {ex with vi = [|6; 16; 19; 24; 3; 5|]}));
  assert (not (est_sad_valide {ex with vi = [|13; 16; 19; 24; 3; 10|]}))


(* Question 2 *)
(* Si a = [|a_0; ...; a_n-1] et b = [|b_0; ...; b_n-1], renvoie
 * f (f (... f acc a_0 b_0 ...) a_n-2 b_n-2) a_n-1 b_n-1. Plante avec
 * Invalid_argument si les deux tableaux ne font pas la même taille.
 * Cette fonction est similaire à List.fold_left2 mais pour les tableaux. *)
let array_fold_left2 (f: 'acc -> 'a -> 'b -> 'acc) (acc: 'acc) (a: 'a array)
    (b: 'b array) : 'acc =

  let n = Array.length a in
  if Array.length b <> n then
    raise (Invalid_argument "array_fold_left2");

  let acc_ref = ref acc in
  for i = 0 to n-1 do
    acc_ref := f (!acc_ref) a.(i) b.(i)
  done;
  !acc_ref


(* Renvoie la somme des éléments de a d’indices i pour lesquels choix.(i) est
 * vrai. Plante avec Invalid_argument si les deux tableaux ne sont pas de même
 * taille. *)
let somme_select (choix: bool array) (a: int array) : int =
  array_fold_left2 (
    fun (somme_courante: int) (valeur: int) (a_prendre: bool) ->
      somme_courante + (if a_prendre then valeur else 0)
  ) 0 a choix

(* Renvoie la valeur de la solution sol sachant l’instance sac. On suppose en
 * entrée que l’instance est valide. *)
let valeur_sol (sac: sad) (sol: solution) : int =
  somme_select sol sac.vi

let test_valeur_sol : unit =
  assert (valeur_sol ex [|true; false; true; true; false; false|] = 13+19+24);
  assert (valeur_sol ex [|false; false; false; false; true; true|] = 8);
  assert (valeur_sol ex [|false; false; false; false; false; false|] = 0)


(* Renvoie le poids de la solution sol sachant l’instance sac. On suppose en
 * entrée que l’instance est valide. *)
let poids_sol (sac: sad) (sol: solution) : int =
  somme_select sol sac.wi

let test_poids_sol : unit =
  assert (poids_sol ex [|true; false; true; true; false; false|] = 6+10+14);
  assert (poids_sol ex [|false; false; false; false; true; true|] = 7);
  assert (poids_sol ex [|false; false; false; false; false; false|] = 0)

(* Question 3 *)
(* Transforme un masque en solution en gardant les « oui » et les « non »,
 * mais en transformant les « peut-être » (None) en « non » (false) *)
let masque_vers_solution (m: masque) : solution =
  (* On fait ça avec Option.value, qui prend un argument default de type 'a
   * (utilisé pour le cas None) et un 'a option. *)
  Array.map (Option.value ~default: false) m


(* Renvoie true si la sous-instance donnée par l’instance sac et le masque
 * m est valide au regard de la capacité du sac. On suppose en entrée que
 * l’instance est valide. *)
let est_masque_valide (sac: sad) (m: masque) : bool =
  let m' = masque_vers_solution m in
  let p = poids_sol sac m' in
  p <= sac.p

let test_est_masque_valide : unit =
  assert (est_masque_valide ex [|
    Some true; Some false; Some true; None; None; None
  |]);
  assert (not (est_masque_valide ex [|
    Some false; None; Some true; Some true; None; Some false
  |]))


(* PARTIE 2 *)

(* Question 4 *)
(* Modifie le tableau de booléens sol pour contenir le prochain tableau de
 * booléens suivant l’ordre d’énumération de l’énoncé. Si sol est déjà le
 * dernier tableau possible, cette fonction remet sol à la première des
 * valeurs. Plante si m et sol n’ont pas la même taille. *)
let next (m: masque) (sol: solution) : unit =
  let n = Array.length m in
  let retenue = ref true in
  for i = 0 to n-1 do
    if m.(i) = None && !retenue then
      if sol.(i) then
        sol.(i) <- false
      else begin
        sol.(i) <- true;
        retenue := false
      end
  done


let test_next : unit =
  let m = [|Some(true); None; None; Some(false); None; None|] in
  let sol = [|true; false; false; false; false; false|] in
  next m sol;
  assert (sol = [|true; true; false; false; false; false|]);
  next m sol;
  assert (sol = [|true; false; true; false; false; false|]);
  next m sol;
  assert (sol = [|true; true; true; false; false; false|]);
  next m sol;
  assert (sol = [|true; false; false; false; true; false|]);
  next m sol;
  assert (sol = [|true; true; false; false; true; false|]);
  next m sol;
  assert (sol = [|true; false; true; false; true; false|]);
  next m sol;
  assert (sol = [|true; true; true; false; true; false|]);
  next m sol;
  assert (sol = [|true; false; false; false; false; true|]);
  next m sol;
  next m sol;
  next m sol;
  next m sol;
  next m sol;
  next m sol;
  next m sol;
  next m sol;
  (* On a fait 2⁴ appels à next, on retombe sur la solution de départ *)
  assert (sol = [|true; false; false; false; false; false|])


(* Question 5 *)
(* Résoud le problème du sac à dos sur la sous-instance donnée par l’instance
 * sol et le masque m, en donnant une solution optimale ainsi que sa valeur.
 * On suppose que cette sous-instance admet des solutions. *)
let brute_force (sac: sad) (m: masque) : (solution * int) =
  let solution_optimale = ref (masque_vers_solution m) in
  let valeur_opt = ref (valeur_sol sac !solution_optimale) in
  let nombre_none_dans_m =
    Array.fold_left (
      fun (nb_actuel: int) (suivant: bool option) ->
        nb_actuel + (if suivant = None then 1 else 0)
    ) 0 m in
  let possibilites = 1 lsl nombre_none_dans_m in (* 2^nombre_none *)
  let sol_courante = masque_vers_solution m in

  for _ = 1 to possibilites do
    if (
        poids_sol sac sol_courante <= sac.p &&
        valeur_sol sac sol_courante > !valeur_opt
    ) then begin
      solution_optimale := Array.copy sol_courante;
      valeur_opt := valeur_sol sac sol_courante
    end;
    next m sol_courante
  done;

  !solution_optimale, !valeur_opt


let test_brute_force : unit =
  let masque1 = Array.make ex.n None in
  let sol, val_sol = brute_force ex masque1 in
  assert (val_sol = 38);
  assert (valeur_sol ex sol = val_sol);
  assert (poids_sol ex sol <= ex.p);
  let masque2 = Array.make 2 None in
  let ex2 = {
    n = 2;
    vi = [|10; 5|];
    wi = [|1; 1|];
    p = 10
  } in
  let sol2, val_sol2 = brute_force ex2 masque2 in
  assert (val_sol2 = 15);
  assert (valeur_sol ex2 sol2 = val_sol2);
  assert (poids_sol ex2 sol2 = 2);
  assert (sol2 = [|true; true|]);
  let sol3, val_sol3 = brute_force {ex2 with wi = [|50; 50|]} masque2 in
  assert (val_sol3 = 0);
  assert (sol3 = [|false; false|])


(* PARTIE 3 *)

(* Question 6 *)
(* Génère en complexité pire cas O(nP) le tableau de prog. dyn. décrit
 * dans l’énoncé pour l’instance sac du problème KNAPSACK. *)
let prog_dyn_tab (sac: sad) : int array array =
  let resultat = Array.init (sac.n+1) (fun _ -> Array.make (sac.p+1) 0) in
  for j = 0 to sac.p do
    for i = 1 to sac.n do
      if sac.wi.(i-1) <= j then
        resultat.(i).(j) <-
          max resultat.(i-1).(j)
              (sac.vi.(i-1) + resultat.(i-1).(j-sac.wi.(i-1)))
      else
        resultat.(i).(j) <- resultat.(i-1).(j)
    done;
  done;
  resultat


(* Question 7 *)
(* Résoud le problème du sac à dos sur l’instance sac, en donnant une solution
 * optimale ainsi que sa valeur. *)
let prog_dyn (sac: sad) : solution * int =
  let tab = prog_dyn_tab sac in
  let sol = Array.make sac.n false in
  (* On parcourt le tableau ligne par ligne, en vérifiant à chaque fois si
   * on a ou non pris l’objet *)
  let j = ref sac.p in
  for i = sac.n downto 1 do
    if sac.wi.(i-1) > !j then
      ()  (* on n’a pas pris l’objet i, on reste sur la même colonne *)
    else if tab.(i-1).(!j) <= sac.vi.(i-1) + tab.(i-1).(!j-sac.wi.(i-1)) then
    begin
      (* on a pris l’objet i *)
      sol.(i-1) <- true;
      j := !j - sac.wi.(i-1)
    end else
      () (* on n’a pas pris l’objet i et on reste sur la même colonne *)
  done;
  sol, tab.(sac.n).(sac.p)


let test_prog_dyn : unit =
  let sol, val_sol = prog_dyn ex in
  assert (val_sol = 38);
  assert (valeur_sol ex sol = val_sol);
  assert (poids_sol ex sol <= ex.p);
  let ex2 = {
    n = 2;
    vi = [|10; 5|];
    wi = [|1; 1|];
    p = 10
  } in
  let sol2, val_sol2 = prog_dyn ex2 in
  assert (val_sol2 = 15);
  assert (valeur_sol ex2 sol2 = val_sol2);
  assert (poids_sol ex2 sol2 = 2);
  assert (sol2 = [|true; true|]);
  let sol3, val_sol3 = prog_dyn {ex2 with wi = [|50; 50|]} in
  assert (val_sol3 = 0);
  assert (sol3 = [|false; false|])


(* PARTIE 4 *)

(* Question 8 *)
(* Tente de résoudre au mieux la sous-instance du problème du sac à dos donnée
 * par l’instance sac et le masque m, en renvoyant une solution et sa valeur.
 * Si la sous-instance n’admet pas de solution, renvoie None. *)
let glouton_n (sac: sad) (m: masque) : (solution * int) option =
  let sol = masque_vers_solution m in
  if est_masque_valide sac m then begin
    let valeur = ref (valeur_sol sac sol) in
    let poids = ref (poids_sol sac sol) in
    (* On parcourt chaque objet en ajoutant ceux qu’on peut ajouter *)
    for i = 0 to sac.n-1 do
      if m.(i) = None && !poids + sac.wi.(i) <= sac.p then begin
        valeur := !valeur + sac.vi.(i);
        poids := !poids + sac.wi.(i);
        sol.(i) <- true
      end
    done;
    Some (sol, !valeur)
  end else
    None


let test_glouton_n : unit =
  let masque1 = Array.make ex.n None in
  match glouton_n ex masque1 with
  | None -> assert false
  | Some (sol, val_sol) ->
      assert (sol = [|true; true; false; false; true; false|]);
      assert (val_sol = 32);

  let masque2 = [|Some false; Some true; Some true; None; None; None|] in
  match glouton_n ex masque2 with
  | None -> assert false
  | Some (sol, val_sol) ->
      assert (sol = [|false; true; true; false; true; false|]);
      assert (val_sol = 38);

  let masque3 = [|Some false; Some true; Some true; None; Some true; None|] in
  match glouton_n ex masque3 with
  | None -> assert false
  | Some (sol, val_sol) ->
      assert (sol = [|false; true; true; false; true; false|]);
      assert (val_sol = 38);

  let masque4 = [|Some false; Some true; Some true; None; Some true; Some true|]
  in assert (glouton_n ex masque4 = None)


(* PARTIE 5 *)

(* Question 9 *)
let test_Q : unit =
  Q.(
    assert ((1, 2) +.. (1, 2) = (1, 1));
    assert ((1, 4) +.. (1, 4) = (1, 2));
    assert ((-4, 9) +.. (4, 9) = (0, 1));
    assert ((97, 100) -.. (11, 50) = (3, 4));

    assert (oppose (5, 8) = (-5, 8));
    assert (oppose (rational_of_int 0) = (0, 1));

    assert ((17, 20) *.. (15, 17) = (3, 4));
    assert ((-17, 20) *.. (-15, 17) = (3, 4));
    assert ((15, 31) /.. (-3, 62) = (-10, 1));

    assert (rational_of_int (-56) = (-56, 1));
    assert (sign (0, 1) = 0);
    assert (sign (-56, 29) = -1);
    assert (sign (35, 2) = 1);
    assert (sign (rational_of_int 0) = 0);

    assert ((1, 2) <.. (3, 4));
    assert ((-3, 4) <.. (1, 2));
    assert (not ((3, 4) <.. (1, 2)));
    assert (not ((2, 3) <.. (2, 3)));
    assert ((1, 2) <=.. (3, 4));
    assert ((-3, 4) <=.. (1, 2));
    assert (not ((3, 4) <=.. (1, 2)));
    assert ((2, 3) <=.. (2, 3));

    assert (not ((-3, 4) >.. (1, 2)));
    assert ((3, 4) >.. (1, 2));
    assert (not ((1, 2) >=.. (3, 4)));
    assert (not ((-3, 4) >=.. (1, 2)));
    assert ((3, 4) >=.. (1, 2));
    assert ((2, 3) >=.. (2, 3));

    assert (is_int (rational_of_int 0));
    assert (is_int ((3, 1)));
    assert (is_int (rational_of_int (-4)));
    assert (not (is_int (3, 4)));
    assert (not (is_int (-4, 3)))
  )


(* PARTIE 6 *)
(* Transforme un masque en solution fractionnaire en gardant les « oui » et les
 * « non », mais en transformant les « peut-être » (None) en « non » (0/1) *)
let solution_vers_qsolution (sol: solution) : qsolution =
  Array.map (fun x -> if x then (1, 1) else (0, 1)) sol


(* Résoud le problème du sac à dos fractionnaire sur la sous-instance du
 * problème donnée par le sac `sac` et le masque `m`. Renvoie une solution
 * optimale et sa valeur. *)
let glouton_r (sac: sad) (m: masque) : (qsolution * Q.t) option =
  let sol = masque_vers_solution m in

  if est_masque_valide sac m then begin
    let valeur = ref (valeur_sol sac sol) in
    let poids = ref (poids_sol sac sol) in
    let exception Stop of int in (* indice de l’objet sur lequel on s’arrête *)

    (* On parcourt chaque objet tant qu’on peut en ajouter *)
    try (
      for i = 0 to sac.n-1 do
        if m.(i) = None && !poids + sac.wi.(i) <= sac.p then begin
          valeur := !valeur + sac.vi.(i);
          poids := !poids + sac.wi.(i);
          sol.(i) <- true
        end else if m.(i) = None then
          (* Ici, on ne peut plus ajouter l’objet en entier *)
          raise (Stop i)
      done;
      (* On a pu ajouter tous les objets en entier *)
      Some (solution_vers_qsolution sol, Q.rational_of_int (!valeur))

    ) with Stop i ->
      (* On n’a pas pu ajouter tous les objets en entier : l’objet i ne rentre
       * pas *)
      let sol' = solution_vers_qsolution sol in
      let place_restante = sac.p - !poids in
      let fraction = Q.simplify (place_restante, sac.wi.(i)) in
      sol'.(i) <- fraction;
      let nouvelle_valeur = Q.(
        rational_of_int (!valeur) +.. (fraction *.. rational_of_int sac.vi.(i))
      ) in
      Some (sol', nouvelle_valeur)
  end else
    None

let test_glouton_r : unit =
  let masque1 = Array.make ex.n None in
  let sol1, val1 = Option.get (glouton_r ex masque1) in
  assert (sol1 = [|(1, 1); (1, 1); (3, 5); (0, 1); (0, 1); (0, 1)|]);
  assert (val1 = (202, 5));
  masque1.(2) <- Some false;
  masque1.(5) <- Some true;
  let sol2, val2 = Option.get (glouton_r ex masque1) in
  assert (sol2 = [|(1, 1); (1, 1); (0, 1); (1, 14); (0, 1); (1, 1)|]);
  assert Q.(val2 = (13, 1) +.. (16, 1) +.. (12, 7) +.. (5, 1));
  assert (val2 = (250, 7));
  masque1.(3) <- Some true;
  masque1.(4) <- Some true;
  assert (glouton_r ex masque1 = None)


(* PARTIE 7 *)

(* Question 11 *)
(* Renvoie un nouveau masque, copie de m, dans laquelle l’objet d’indice i
 * doit ou ne doit pas être pris en fonction de doit_etre_pris *)
let impose_i (m: masque) (i: int) (doit_etre_pris: bool) : masque =
  let m' = Array.copy m in
  m'.(i) <- Some doit_etre_pris;
  m'


let test_impose_i : unit =
  let masque1 = Array.make ex.n None in
  masque1.(2) <- Some true;
  let masque2 = impose_i masque1 3 false in
  assert (masque2.(3) = Some false);
  assert (masque1.(3) = None);
  assert (masque2.(2) = Some true);
  assert (masque1.(2) = Some true);
  assert (masque2.(0) = None && masque1.(0) = None);
  masque2.(2) <- Some false;
  assert (masque1.(2) = Some true);
  assert (masque2.(2) = Some false)

(* Question 12 *)
(* Renvoie l’indice du premier objet pour lequel la fraction indiquée par sol
 * n’est pas entière. Plante avec Invalid_argument s’il n’existe pas de tel
 * objet. *)
let find_i_frac (sol: qsolution) : int =
  let res = ref (-1) in
  for i = 0 to Array.length sol do
    if !res = -1 && not (Q.is_int sol.(i)) then
      res := i
  done;
  if !res = -1 then
    raise (Invalid_argument "Solution entière !");
  !res


let test_find_i_frac : unit =
  let sol = [|(1, 1); (1, 1); (0, 1); (1, 14); (0, 1); (1, 1)|] in
  assert (find_i_frac sol = 3);
  sol.(4) <- (9, 14);
  assert (find_i_frac sol = 3);
  sol.(1) <- (5, 1);
  assert (find_i_frac sol = 3);
  sol.(0) <- (1, 5);
  assert (find_i_frac sol = 0);
  let sol2 = [|(5, 1); (3, 2)|] in
  assert (find_i_frac sol2 = 1);
  sol2.(1) <- Q.rational_of_int (-12);
  try
    let _ = find_i_frac sol2 in assert false
  with
  | Invalid_argument _ -> ();
  try
    let _ = find_i_frac [||] in assert false
  with
  | Invalid_argument _ -> ()


(* Question 13 *)
(* Résoud le problème du sac à dos sur l’instance sac en donnant une solution
 * optimale de la forme (solution, valeur), en utilisant un algorithme de
 * séparation-évaluation *)
let branch_and_bound (sac: sad) : solution * int =
  (* Effectue le branchement sur l’instance inst en fonction de la solution
   * du relâché fractionnaire sol_frac sur inst, i.e. renvoie deux
   * sous-instances : celle où on prend l’objet dont une partie a été prise
   * par sol_frac, et celle où on ne le prend pas *)
  let branchement (inst: masque) (sol_frac: qsolution) : masque * masque =
    let i = find_i_frac sol_frac in
    impose_i inst i true, impose_i inst i false
  in

  let meilleure_val = ref 0 in
  let meilleure_sol = ref (Array.make sac.n false) in
  let instance_init = Array.make sac.n None in
  let todo = Queue.create () in
  Queue.push instance_init todo;

  while not (Queue.is_empty todo) do
    let instance = Queue.pop todo in
    match glouton_r sac instance with
    | None -> ()
    | Some (sol_frac, val_frac) ->
      if Q.(val_frac >.. rational_of_int !meilleure_val) then begin
        match glouton_n sac instance with
        | None -> ()
        | Some (sol_entiere, val_entiere) ->
          if val_entiere > !meilleure_val then begin
            meilleure_val := val_entiere;
            meilleure_sol := sol_entiere
          end;
          if Q.(val_frac >=.. rational_of_int (val_entiere+1)) then begin
            let i1, i2 = branchement instance sol_frac in
            Queue.push i1 todo;
            Queue.push i2 todo
          end
        end
  done;

  !meilleure_sol, !meilleure_val


let test_branch_and_bound : unit =
  let sol, val_sol = branch_and_bound ex in
  assert (val_sol = 38);
  assert (valeur_sol ex sol = val_sol);
  assert (poids_sol ex sol <= ex.p);
  let ex2 = {
    n = 2;
    vi = [|10; 5|];
    wi = [|1; 1|];
    p = 10
  } in
  let sol2, val_sol2 = branch_and_bound ex2 in
  assert (val_sol2 = 15);
  assert (valeur_sol ex2 sol2 = val_sol2);
  assert (poids_sol ex2 sol2 = 2);
  assert (sol2 = [|true; true|]);
  let sol3, val_sol3 = branch_and_bound {ex2 with wi = [|50; 50|]} in
  assert (val_sol3 = 0);
  assert (sol3 = [|false; false|])


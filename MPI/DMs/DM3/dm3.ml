module Q = struct
  type t = int * int
  (* (a, b) encode a/b*)
  (* invariant : a ∧ b = 1 et b > 0 et si a = 0 alors b = 1 *)
  (* NB: vu l'invariant, l'égalité syntaxique de OCaml (a, b)=(c, d)*)
  (*     encode en fait l'égalité sémantique de Q : a/b = c/d *)
  let print ((a, b): t) = Printf.printf "%d/%d" a b
  let dirty_print ((a, b): t) =
    Printf.printf "%.2f" ((float_of_int a) /. (float_of_int b))
end

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
(* Renvoie a/b <= c/d *)
let (<=.) ((a, b): int * int) ((c, d): int * int) =
  if (b > 0 && d > 0) || (b < 0 && d < 0) then
    (a*d) <= (c*b)
  else (* s’ils n’ont pas le même signe, le sens de l’inégalité change une fois
        * lorsqu’on met sur le même dénominateur *)
    (a*d) >= (c*b)


(* Renvoie true si l’instance `sac` est valide, false sinon *)
let est_sad_valide (sac: sad) : bool =
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
let somme_select (choix: bool array) (a: int array) =
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
  (* On fait ça avec
   * Option.value, qui prend un argument default de type 'a (utilisé pour le
   * cas None) et un 'a option. *)
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
    Some(true); Some(false); Some(true); None; None; None
  |]);
  assert (not (est_masque_valide ex [|
    Some(false); None; Some(true); Some(true); None; Some(false)
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
  let masque = Array.make ex.n None in
  let sol, val_sol = brute_force ex masque in
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



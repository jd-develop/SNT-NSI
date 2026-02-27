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
let (<=.) ((a, b): Q.t) ((c, d): Q.t) =
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
(* Renvoie true si la sous-instance donnée par l’instance sac et le masque
 * m est valide au regard de la capacité du sac. On suppose en entrée que
 * l’instance est valide. *)
let est_masque_valide (sac: sad) (m: masque) : bool =
  (* On crée un masque où les « peut-être » sont des « non », i.e. on
   * transforme les Some(b) en b et les None en false. On fait ça avec
   * Option.value, qui prend un argument default de type 'a (utilisé pour le
   * cas None) et un 'a option. *)
  let m' = Array.map (Option.value ~default: false) m in
  let p = poids_sol sac m' in
  p <= sac.p

let test_est_masque_valide : unit =
  assert (est_masque_valide ex [|
    Some(true); Some(false); Some(true); None; None; None
  |]);
  assert (not (est_masque_valide ex [|
    Some(false); None; Some(true); Some(true); None; Some(false)
  |]))

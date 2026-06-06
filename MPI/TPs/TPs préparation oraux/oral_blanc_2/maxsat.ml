
type litteral = Var of int | Neg of int
type clause = litteral list
type fnc = clause list

type valuation = bool array

let () = Random.self_init ()

(* -0,1,-2;0,-1,2;0,1,2;-0,-1 *)
let phi = [
  [Neg 0; Var 1; Neg 2];
  [Var 0; Neg 1; Var 2];
  [Var 0; Var 1; Var 2];
  [Neg 0; Neg 1]
]
(* 0,1,2;-3,-4,-5 *)
let psi = [
  [Var 0; Var 1; Var 2];
  [Neg 3; Neg 4; Neg 5]
]

(* Satisfait 4 clauses de phi *)
let v1 = [|false; false; true|]
(* Satisfait 3 clauses de phi et 2 clauses de psi *)
let v2 = [|true; true; false; false; true; true|]
(* Satisfait 3 clauses de phi et 0 clauses de psi *)
let v3 = [|false; false; false; true; true; true|]

let print_valuation (v: valuation) : unit =
  print_string "[|";
  for i = 0 to Array.length v - 1 do
    if v.(i) then print_string "true; " else print_string "false; "
  done;
  print_endline "|]"

(* Partie 1 *)

(* Question 1 *)
let lire_fichier (filename: string) : string list =
  (* Lit une ligne s du fichier fp et renvoie s::acc *)
  let rec ajouter_ligne (fp: in_channel) (acc: string list) : string list =
    try
      let s = input_line fp in
      ajouter_ligne fp (s::acc)
    with
    | End_of_file -> acc
  in
  let fp = open_in filename in
  let res = List.rev (ajouter_ligne fp []) in
  close_in fp;
  res

(*
let _ =
  List.iter print_endline (lire_fichier "formules.txt")
*)

(* Question 2 *)
let fnc_ligne (ligne: string) : fnc =
  let litteral_of_string (s: string) : litteral =
    let neg = s.[0] = '-' in
    let id = abs (int_of_string s) in
    if neg then
      Neg id
    else
      Var id
  in
  let clause_of_string (s: string) : clause =
    let litteraux = String.split_on_char ',' s in
    List.map litteral_of_string litteraux
  in
  let clauses = String.split_on_char ';' ligne in
  List.map clause_of_string clauses

let test_fnc_ligne : unit =
  assert (fnc_ligne "-0,1,-2;0,-1,2;0,1,2;-0,-1" = phi);
  print_endline "OK fnc_ligne"


(* Question 3 *)
let tab_fnc (filename: string) : fnc array =
  let contenu = lire_fichier filename in
  Array.of_list (List.map fnc_ligne contenu)

let test_tab_fnc : unit =
  assert (tab_fnc "petit_fichier.txt" = [|phi; psi|]);
  print_endline "OK tab_fnc"


(* Partie 2 *)

(* Question 4 *)

(* Calcule le max d'une liste non vide *)
let list_max (l: 'a list) : 'a =
  match l with
  | [] -> raise (Invalid_argument "list_max : Liste vide")
  | x::q -> List.fold_left max x q

let int_of_litteral (l: litteral) : int =
  match l with Var i | Neg i -> i

let taille_V (f: fnc) : int =
  let max_var_of_clause (c: clause) : int =
    List.map int_of_litteral c
    |> list_max
  in
  list_max (List.map max_var_of_clause f) + 1

let test_taille_V : unit =
  assert (taille_V phi = 3);
  assert (taille_V psi = 6);
  print_endline "OK taille_V"

(* Question 5 *)

(* Renvoie le booléen correspondant au littéral l dans la valuation v *)
let rho (v: valuation) (l: litteral) : bool =
  match l with
  | Var i -> v.(i)
  | Neg i -> not (v.(i))

let int_of_bool (b: bool) : int =
  if b then 1 else 0

let evaluer (c: clause) (v: valuation) : int =
  c
  |> List.map (rho v)
  |> List.fold_left (||) false
  |> int_of_bool

let test_evaluer : unit =
  let c = [Var 0; Neg 1; Var 2] in
  let v1 = [|true; true; true|] in
  let v2 = [|false; true; false|] in
  assert (evaluer c v1 = 1);
  assert (evaluer c v2 = 0);
  print_endline "OK evaluer"


(* Question 6 *)
let taille_J (f: fnc) (v: valuation) : int =
  List.map ((Fun.flip evaluer) v) f
  |> List.fold_left (+) 0

let test_taille_J : unit =
  assert (taille_J phi v1 = 4);
  assert (taille_J phi v2 = 3);
  assert (taille_J psi v2 = 2);
  assert (taille_J phi v3 = 3);
  assert (taille_J psi v3 = 0);
  print_endline "OK taille_J"


(* Question 7 *)
let valuation (n: int) (k: int) : valuation =
  let res = Array.make n false in
  let k' = ref k in
  for i = n-1 downto 0 do
    res.(i) <- !k' mod 2 = 1;
    k' := !k' / 2
  done;
  res

let test_valuation : unit =
  assert (valuation 1 0 = [|false|]);
  assert (valuation 1 1 = [|true|]);
  assert (valuation 8 10 = [|
    false; false; false; false; true; false; true; false
  |]);
  assert (valuation 8 45 = [|
    false; false; true; false; true; true; false; true
  |]);
  print_endline "OK valuation"

(* Question 8 *)

(* Écrase les éléments de src dans dst *)
let ecraser_tab (src: 'a array) (dst: 'a array) : unit =
  Array.blit src 0 dst 0 (Array.length src)

let maxsat_naif (f: fnc) : valuation =
  let n = taille_V f in
  let v = Array.make n false in
  let max_courant = ref (taille_J f v) in
  for k = 1 to (1 lsl n - 1) do
    let v' = valuation n k in
    let taille_courante = taille_J f v' in
    if taille_courante > !max_courant then begin
      max_courant := taille_courante;
      ecraser_tab v' v
    end
  done;
  v

let _ =
  let t = tab_fnc "formules.txt" in
  let v0 = maxsat_naif (t.(0)) in
  print_int (taille_J t.(0) v0); print_newline ();
  let v1 = maxsat_naif (t.(1)) in
  print_int (taille_J t.(1) v1); print_newline ();
  let v2 = maxsat_naif (t.(2)) in
  print_int (taille_J t.(2) v2); print_newline ();
  print_endline "fini maxsat_naif"


(* Partie 3 *)

(* Question 12 *)
let bool_of_int (i: int) : bool =
  i <> 0

let maxsat_alea (f: fnc) : valuation =
  let n = taille_V f in
  Array.init n (fun _ -> bool_of_int (Random.int 2))

(*
let _ =
  print_valuation (maxsat_alea phi)
*)

(* Question 13 *)
let simulation (f: fnc) (m: int) : float =
  (* Fait m' simulation et renvoie acc+(somme des résultats) *)
  let rec simulation_somme (m': int) (acc: int) : int =
    if m' = 0 then acc
    else
      let v = maxsat_alea f in
      simulation_somme (m'-1) (acc+(taille_J f v))
  in
  let j_etoile = taille_J f (maxsat_naif f) in
  let moyenne = (float_of_int (simulation_somme m 0)) /. (float_of_int m) in
  moyenne /. (float_of_int j_etoile)
 

(* Question 14 *)
let _ =
  let t = tab_fnc "formules.txt" in
  let r0 = simulation (t.(0)) 1000 in
  print_float r0; print_newline ();
  let r1 = simulation (t.(1)) 1000 in
  print_float r1; print_newline ();
  let r2 = simulation (t.(2)) 1000 in
  print_float r2; print_newline ();
  print_endline "fini simulation maxsat_alea"


(* Partie 4 *)

(* Question 18 *)
(* O(n) *)
let proba_condi (c: clause) (v: valuation) (i: int) : float =
  (* v est remplie de v.(0) à v.(i) *)
  if List.exists (fun l -> int_of_litteral l <= i && rho v l) c then
    1.0
  else if
    List.for_all (fun l -> int_of_litteral l <= i && (not (rho v l))) c
  then
    0.0
  else
    (* Il n'y a aucun littéral évalué à vrai sur les littéraux portant
     * sur les variables <= i, il faut compter les autres pour avoir
     * P(C | μ_i) *)
    let c_entiers = List.map int_of_litteral c in
    let k =
      List.fold_left (fun acc j -> acc+(if j > i then 1 else 0)) 0 c_entiers in
    1. -. (1. /. (float_of_int (1 lsl k)))


let (=.) a b =
  let epsilon = 0.0001 in
  a <= b +. epsilon && a >= b -. epsilon

let test_proba_condi : unit =
  let c = [Var 0; Neg 3; Var 2; Neg 1] in
  let v = [|false; false; false; false|] in
  assert (proba_condi c v 0 =. 1. -. 0.125);
  assert (proba_condi c v 1 =. 1.);
  assert (proba_condi c [|false; true; false; true|] 3 =. 0.);
  print_endline "OK proba_condi"


(* Question 19 *)
(* O(mn) *)
let esperance_condi (f: fnc) (v: valuation) (i: int) : float =
  (* v est remplie de v.(0) à v.(i) *)
  let liste_probas_clauses = List.map (fun c -> proba_condi c v i) f in
  List.fold_left (+.) 0.0 liste_probas_clauses

let test_esperance_condi : unit =
  assert (esperance_condi phi v1 0 =. 2. +. 2.*.(1. -. 1./.4.));
  assert (esperance_condi phi v1 1 =. 3. +. 1./.2.);
  assert (esperance_condi phi v2 0 =. 2. +. 1./.2. +. (1. -. 1./.4.));
  assert (esperance_condi phi v2 1 =. 3.);
  assert (esperance_condi psi v2 0 =. 1. +. (1. -. 1./.8.));
  assert (esperance_condi psi v2 1 =. 1. +. (1. -. 1./.8.));
  assert (esperance_condi psi v2 2 =. 1. +. (1. -. 1./.8.));
  assert (esperance_condi psi v2 3 =. 2.);
  print_endline "OK esperance_condi"


(* Question 20 *)

(* O(n^2m) *)
let maxsat_2approx (f: fnc) : valuation =
  let n = taille_V f in
  let mu = Array.make n false in
  let rec choisir_i (i: int) : unit =
    if i = n then
      ()
    else begin
      mu.(i) <- false;
      let esperance0 = esperance_condi f mu i in
      mu.(i) <- true;
      if esperance_condi f mu i < esperance0 then
        mu.(i) <- false
      else
        ()
    end
  in
  choisir_i 0;
  mu

let _ =
  let t = tab_fnc "formules.txt" in
  let v0 = maxsat_2approx (t.(0)) in
  print_int (taille_J t.(0) v0); print_newline ();
  let v1 = maxsat_2approx (t.(1)) in
  print_int (taille_J t.(1) v1); print_newline ();
  let v2 = maxsat_2approx (t.(2)) in
  print_int (taille_J t.(2) v2); print_newline ();
  print_endline "fini maxsat_2approx"



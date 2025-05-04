type formule =
  | Top
  | Bot
  | Var of string
  | And of formule * formule
  | Or  of formule * formule
  | Not of formule


type valuation = (string * bool) list

type sat_result = valuation option

let implique (f1, f2) = Or(Not f1, f2)
let equivalence (f1, f2) = And(implique (f1, f2), implique (f2, f1))

(*** PARSER ***)

exception Erreur_syntaxe
exception Fichier_invalide

(* Symboles:
  'T' -> true
  'F' -> false
  '&' -> And
  '|' -> Or
  '~' -> Not
  '>' -> implication
  '=' -> équivalence
 *)

(* Détermine si c correspond à un opérateur binaire logique *)
let is_binop (c: char) : bool = match c with
  | '&' |  '|' |  '>' |  '='  -> true
  | _ -> false

(*
 * Priorité de l'opérateur c. Permet de déterminer comment interpréter une
 * formule sans parenthèses. Par exemple, "x&y|z" sera interprété comme
 * "(x&y)|z" car & est plus prioritaire que |
 *)
let priority (c: char) : int = match c with
  | '&' -> 4
  | '|' -> 3
  | '=' -> 2
  | '>' -> 1
  | _ -> raise Erreur_syntaxe (* c n'est pas un opérateur *)


(*
 * Indice de l'opérateur le moins prioritaire parmi ceux qui ne sont pas entre
 * parenthèses entre s.[i] et s.[j] inclus
 *)
 let find_op_surface (s: string) (i: int) (j: int) : int =
   (*
    * Renvoie l'indice de l'opérateur le moins prioritaire entre
    * i et j, sachant que res est l'indice du meilleur opérateur
    * entre i et k-1.
    * paren_lvl: niveau d'imbrication actuel des parenthèses
    *)
   let rec find_op_paren (k:int) (res:int) (paren_lvl: int) : int  =
     if k = j+1 then res else
     if s.[k] = '(' then find_op_paren (k+1) res (paren_lvl+1)
     else if s.[k] = ')' then find_op_paren (k+1) res (paren_lvl-1)

     (* Le caractère lu est pris si l'on est hors des parenthèses,
      * que le caractère est bien un opérateur, et qu'il est moins
      * prioritaire que le meilleur résultat jusqu'ici *)
     else if paren_lvl = 0
        && is_binop s.[k]
        && (res = -1 || priority s.[k] < priority s.[res])
        then find_op_paren (k+1) k (paren_lvl)
     else find_op_paren (k+1) res (paren_lvl)
   in find_op_paren i (-1) 0


(*
 * Renvoie une formule construite à partir de la chaîne s.
 * Lève une exception Erreur_syntaxe si la chaîne ne représente pas une formule
 * valide.
 *)
let parse (s: string) : formule =
  let n = String.length s in
  (* construit une formule à partir de s[i..j] *)
  let rec parse_aux (i: int) (j:int) =
    assert (0 <= i && i < n && 0 <= j && j < n && i <= j );
    if s.[i] = ' ' then parse_aux (i+1) j
    else if s.[j] = ' ' then parse_aux i (j-1)
    else let k = find_op_surface s i j in
    if k = -1 then
      if s.[i] = '~' then
        Not (parse_aux (i+1) j)
      else if s.[i] = '(' then
        begin
          if (s.[j] != ')') then (print_int j; failwith "mauvais parenthésage")
          else parse_aux (i+1) (j-1)
        end
      else if (i = j && s.[i] = 'T') then Top
      else if (i = j && s.[i] = 'F') then Bot
      else Var(String.sub s i (j-i+1))

    else match s.[k] with
      | '&' -> And(parse_aux i (k-1), parse_aux (k+1) j)
      | '|' -> Or(parse_aux i (k-1), parse_aux (k+1) j)
      | '=' -> equivalence(parse_aux i (k-1), parse_aux (k+1) j)
      | '>' -> implique(parse_aux i (k-1), parse_aux (k+1) j)
      | _ -> raise Erreur_syntaxe
  in parse_aux 0 (String.length s -1)

(*
 * Renvoie une formule construire à partir du contenu du fichier fn.
 * Lève une exception Erreur_syntaxe si le contenu du fichier n'est pas une
 * formule valide.
 * Lève une exception Sys_error(message_erreur) si le nom du fichier n'est pas
 * valide.
 *)
let from_file (filename: string) : formule =
  (* concatène toutes les lignes de f en une seule chaîne *)
  let rec read_lines f =
    try
      let next_line = input_line f in
      let s = read_lines f in
      next_line ^ s
    with
      | End_of_file -> ""
  in
  let f = open_in filename in
  let s = read_lines f in
  parse s


let test_parse () =
  assert (parse "a | (b & ~c)" = Or(Var "a", And(Var "b", Not (Var "c"))));
  assert (parse "ŵềδ€ß⍼" = Var "ŵềδ€ß⍼");
  assert (parse "a = b" = And(Or(Not(Var "a"), Var "b"), Or(Not(Var "b"), Var "a")));
  assert (parse "T & F" = And(Top, Bot));

  assert (from_file "tests/test1" = Or(Not(Or(Var "a", Or(Var "b", And(Var "c", Not(Var "d"))))), And(Var "a", Var "ceci_est_un_nom_de_variable_très_long_qui_contient_même_une_espace_insécable_fine ici")));
  assert (from_file "tests/test2" = Or(Or(Top, Or(Var "…", Or(Var "ﷺ", Var "j’♥️_unicode"))), Or(And(Or(Not(Bot), Var "4"), Or(Not(Var "4"), Bot)), And(Or(Not(Var "1"), Var "12"), Or(Not(Var "12"), Var "1")))));
  assert (from_file "tests/test3" = Or(Var "a", And(Var "b", Not(Var "c"))));
  assert (from_file "tests/test4" = And(Or(Var "a", Var "b"), Not(Var "c")));
  assert (from_file "tests/test5" = Or(Var "a", And(Var "b", Not(Var "c"))));
  assert (from_file "tests/zerowidthspace" = Var "​");  (* (Neo)Vim affiche <200b>, mais pas emacs (ce qui prouve bien que Vim est supérieur (même si ed est le standard)) *)
  print_string "Tests parse et from_file         OK\n"


(*
 * Renvoie le contenu du fichier fn sous forme de chaîne de caractères.
 * Le fichier ne doit contenir qu’une seule ligne
 *)
let read_file (fn: string) : string =
  let ic = open_in fn in
  let res = input_line ic in
  close_in ic; res


(* Compte_ops f renvoie le nombre d’opérateurs utilisés dans f *)
let rec compte_ops (f: formule) : int = match f with
  | Top | Bot | Var _ -> 0
  | And (f1, f2)
  | Or (f1, f2) -> 1 + compte_ops f1 + compte_ops f2
  | Not f1 -> 1 + compte_ops f1


let test_compte_ops () =
  assert (compte_ops (parse "x | (y & ~z)") = 3);
  assert (compte_ops (parse "~(x | (x & ~z) | y)") = 5);
  assert (compte_ops (from_file "tests/test1") = 7);
  assert (compte_ops (from_file "tests/test2") = 15);
  assert (compte_ops (from_file "tests/zerowidthspace") = 0);
  print_string "Tests compte_ops                 OK\n"


(* Renvoie true si l est triée et sans doublon, false sinon *)
let rec est_strictement_croissante (l: 'a list) =
  match l with
  | [] | _::[] -> true
  | x::y::q when x < y -> est_strictement_croissante (y::q)
  | x::y::q -> false


let test_est_strictement_croissante () =
  assert (est_strictement_croissante []);
  assert (est_strictement_croissante [1]);
  assert (est_strictement_croissante [1; 2; 3; 7; 10; 90]);
  assert (not (est_strictement_croissante [1; 2; 3; 3; 7; 10; 90]));
  assert (not (est_strictement_croissante [1; 1]));
  assert (not (est_strictement_croissante [1; 2; 3; -7; 7; 10; 90]));
  print_string "Tests est_strictement_croissante OK\n"


(* si l1 et l2 sont des listes triées sans doublons, `union l1 l2` est une liste
 * triée sans doublons contenant les éléments de l1 et ceux de l2 *)
let rec union (l1: 'a list) (l2: 'a list) : 'a list =
  match l1, l2 with
  | l, []
  | [], l -> l
  | x1::q1, x2::q2 when x1 = x2 -> x1::(union q1 q2)
  | x1::q1, x2::q2 when x1 < x2 -> x1::(union q1 l2)
  | x1::q1, x2::q2  (* x2<x1 *) -> x2::(union l1 q2)


let test_union () =
  assert (union [] [] = []);
  assert (union [] [1] = [1]);
  assert (union [1; 4; 78] [] = [1; 4; 78]);
  assert (union [1; 4; 42] [3; 7; 9; 50] = [1; 3; 4; 7; 9; 42; 50]);
  assert (union ["Bonjour"; "Guten tag"] ["Chocolatine"; "Pain au chocolat"]
    = ["Bonjour"; "Chocolatine"; "Guten tag"; "Pain au chocolat"]);
  print_string "Tests union                      OK\n"


(*
(* Renvoie la liste des variables contenues dans la formule, sans doublons et
 * dans l’ordre croissant *)
let rec liste_variables (f: formule) : string list =
  match f with
  | Top
  | Bot -> []
  | Var v -> [v]
  | And(a, b)
  | Or(a, b) -> union (liste_variables a) (liste_variables b)
  | Not f' -> liste_variables f'
*)


(* Renvoie la liste des variables contenues dans la formule, sans doublons et
 * dans l’ordre croissant. Récursif terminal *)
let liste_variables (f: formule) : string list =
  let rec list_var_rec (f': formule) (l: string list) : string list =
    match f' with
    | Top | Bot -> l
    | Var s -> s::l
    | And (a, b) | Or (a, b) -> list_var_rec a (list_var_rec b l)
    | Not a -> list_var_rec a l
  in List.sort_uniq compare (list_var_rec f [])


let test_liste_variables () =
  assert (liste_variables Top = []);
  assert (liste_variables Bot = []);
  assert (liste_variables (Var "A") = ["A"]);
  assert (liste_variables (parse "x | (y & ~z)") = ["x"; "y"; "z"]);
  assert (liste_variables (from_file "tests/test2") = ["1"; "12"; "4"; "j’♥️_unicode"; "…"; "ﷺ"]);
  assert (liste_variables (from_file "tests/zerowidthspace") = ["​"]);
  print_string "Tests liste_variables            OK\n"


(* Évalue la formule f avec la valuation v. Si une variable apparaît dans f
 * mais pas dans v, par défaut cette variable est considérée comme fausse *)
let rec evaluer (f: formule) (v: valuation) : bool =
  match f with
  | Top -> true
  | Bot -> false
  | Var x ->
      begin try (List.assoc x v) with
      | Not_found -> false
      end
  | And(a, b) -> (evaluer a v) && (evaluer b v)
  | Or(a, b) -> (evaluer a v) || (evaluer b v)
  | Not f' -> not (evaluer f' v)


let test_evaluer () =
  assert (evaluer Top [] = true);
  assert (evaluer Bot [] = false);
  assert (evaluer (parse "x | (y & ~z)") [] = false);
  assert (evaluer (parse "x | (y & ~z)") [("x", true)] = true);
  assert (evaluer (parse "x | (y & ~z)") [("x", false); ("y", true); ("z", false)] = true);
  assert (evaluer (parse "x | (y & ~z)") [("x", false); ("y", true); ("z", true)] = false);
  assert (evaluer (parse "x | (y & ~z)") [("x", true); ("y", true); ("z", true)] = true);
  assert (evaluer (parse "x | (y & ~z)") [("y", true); ("z", true)] = false);
  assert (evaluer (parse "x | (y & ~z)") [("y", false); ("z", true)] = false);
  assert (evaluer (parse "x | (y & ~z)") [("y", true)] = true);
  print_string "Tests evaluer                    OK\n"


(* « Ajoute 1 » à une liste de booléens représentant un entier en binaire
 * (représenté avec le bit de poids faible à gauche *)
let rec add_one (entier: bool list) : bool list =
  match entier with
  | [] -> [true]
  | x::q -> if not x then true::q
            else false::(add_one q)


let test_add_one () =
  assert (add_one [] = [true]);
  assert (add_one [false] = [true]);
  assert (add_one [false; false; false] = [true; false; false]);
  assert (add_one [false; true; false; false; true; true] = [true; true; false; false; true; true]);
  assert (add_one [true; true; false; false; true; true] = [false; false; true; false; true; true]);
  assert (add_one [false; false; true; false; true; true] = [true; false; true; false; true; true]);
  assert (add_one [true; true; true; true; true; true] = [false; false; false; false; false; false; true]);
  print_string "Tests add_one                    OK\n"


let valuation_next (v: valuation) : valuation option =
  let s, l = List.split v in
  if (List.for_all Fun.id l) then None
  else Some (List.combine s (add_one l))


let test_valuation_next () =
  assert (valuation_next [] = None);
  assert (valuation_next ["a", true; "b", false] = Some ["a", false; "b", true]);
  assert (valuation_next ["a", false; "b", true] = Some ["a", true; "b", true]);
  assert (valuation_next ["a", true; "b", true] = None);
  print_string "Tests valuation_next             OK\n"


(* Renvoie la valuation pour laquelle toutes les variables contenues dans l sont
 * fausses. *)
let rec valuation_init (l: string list) : valuation =
  List.map (fun x -> (x, false)) l


let test_valuation_init () =
  assert (valuation_init [] = []);
  assert (valuation_init ["a"; "b"; "d"; "z"] = ["a", false; "b", false; "d", false; "z", false]);
  print_string "Tests valuation_init             OK\n"


(* Renvoie une valuation satisfiant f, ou None si f est insatisfiable *)
let satsolver_naif (f: formule) : sat_result =
  (* Renvoie une valuation (supérieure à v) satisfiant f, ou None si f est
   * insatisfiable avec des valuations supérieures à v *)
  let rec satsolver_rec (f': formule) (v: valuation option) : sat_result =
    match v with
    | None -> None
    | Some v' when evaluer f' v' -> Some v'
    | Some v' -> satsolver_rec f' (valuation_next v')
  in satsolver_rec f (Some (valuation_init (liste_variables f)))


let test_satsolver_naif () =
  assert (satsolver_naif Top = Some []);
  assert (satsolver_naif Bot = None);
  let res1 = satsolver_naif (from_file "tests/test1") in
  match res1 with
  | None -> failwith "Échec : pas de valuation trouvée pour tests/test1"
  | Some v -> assert (evaluer (from_file "tests/test1") v);
  assert (satsolver_naif (parse "(a | b) & (~a | c) & (~c | ~b)") = Some ["a", false; "b", true; "c", false]);
  assert (satsolver_naif (parse "(a | b) & (~a | ~b)") = Some ["a", true; "b", false]);
  assert (satsolver_naif (parse "x & (y > (~z | (x & w))) & (y | ~z) & (z | ~x) & ~w") = None);
  assert (satsolver_naif (parse "x | (y & ~z)") = Some [("x",true);("y",false);("z",false)]);
  assert (satsolver_naif (parse "x & (y & ~z)") = Some [("x",true);("y",true);("z",false)]);
  assert (satsolver_naif (parse "x | (y & ~x)") = Some [("x",true);("y",false)]);
  assert (satsolver_naif (parse "x & (y & ~x)") = None);
  print_string "Tests satsolver_naif             OK\n"


(********* algorithme de Quine *********)

(*
 * Applique une étape de simplification de la formule f et renvoie
 * la formule simplifée. Renvoie également un booléen qui indique si une
 * simplification a réellement été effectuée (true dans ce cas) ou si on a
 * atteint un point fixe (false)
 *)
let rec simpl_step (f: formule) : formule * bool =
  match f with
  | And(Top, phi) | And(phi, Top) -> phi, true
  | And(Bot, phi) | And(phi, Bot) -> Bot, true
  | Or (Bot, phi) | Or (phi, Bot) -> phi, true
  | Or (Top, phi) | Or (phi, Top) -> Top, true
  | Not(Not(phi)) -> phi, true
  | Not(Top) -> Bot, true
  | Not(Bot) -> Top, true
  | And(phi, psi) ->
      let phi', simpl_done_phi = simpl_step phi in
      let psi', simpl_done_psi = simpl_step psi in
      And(phi', psi'), (simpl_done_phi || simpl_done_psi)
  | Or (phi, psi) ->
      let phi', simpl_done_phi = simpl_step phi in
      let psi', simpl_done_psi = simpl_step psi in
      Or (phi', psi'), (simpl_done_phi || simpl_done_psi)
  | Not(phi) ->
      let phi', simpl_done_phi = simpl_step phi in
      Not(phi'), simpl_done_phi
  | phi -> phi, false


(* Simplifie la formule f *)
let rec simpl_full_bad (f: formule) : formule =
  match simpl_step f with
  | phi, true -> simpl_full_bad phi
  | phi, false -> phi

(* Simplifier la formule f (mais en mieux) *)
let rec simpl_full (f: formule) : formule =
  let f' = match f with
  | And (a, b) -> And (simpl_full a, simpl_full b)
  | Or  (a, b) -> Or  (simpl_full a, simpl_full b)
  | Not a      -> Not (simpl_full a)
  | _ -> f
  in match f' with
  | And (a, Top) | And (Top, a) -> a
  | And (a, Bot) | And (Bot, a) -> Bot
  | Or  (a, Top) | Or  (Top, a) -> Top
  | Or  (a, Bot) | Or  (Bot, a) -> a
  | Not (Not a) -> a
  | Not Top -> Bot
  | Not Bot -> Top
  | _ -> f'

let test_simpl () =
  assert (
    simpl_step (parse "x & (y > (~z | (x & w))) & (y | ~z) & (z | ~x) & ~w")
    = (parse "x & (~y | (~z | (x&w))) & (y | ~z) & (z | ~x) & ~w", false)
   (* ça ne se simplifie pas… *)
  );
  assert (
    simpl_step (parse "~~(x & ~(~F | x))") = (parse "x & ~(~F | x)", true)
  );
  assert (simpl_step (parse "x & ~(~F | x)") = (parse "x & ~(T | x)", true));
  assert (simpl_step (parse "x & ~(T | x)") = (parse "x & ~T", true));
  assert (simpl_step (parse "x & ~T") = (parse "x & F", true));
  assert (simpl_step (parse "x & F") = (parse "F", true));
  assert (simpl_step (parse "F") = (parse "F", false));
  assert (simpl_full (parse "~~(x & ~(~F | x))") = Bot);
  print_string "Tests test_simpl                 OK\n"


(* Remplace toutes les occurences de x par g dans la formule f *)
let rec subst (f: formule) (x: string) (g: formule) =
  match f with
  | Var (s) when s = x -> g
  | Top | Bot | Var (_) -> f
  | Or  (f1, f2) -> Or  (subst f1 x g, subst f2 x g)
  | And (f1, f2) -> And (subst f1 x g, subst f2 x g)
  | Not (f') -> Not(subst f' x g)


let test_subst () =
  assert (subst (parse "a & (b | c) & (c > a)") "c" (parse "a > d") = parse "a & (b | (a > d)) & ((a > d) > a)");
  assert (subst (parse "a & (b | c) & (c > a)") "a" (parse "b & d") = parse "(b & d) & (b | c) & (c > (b & d))");
  assert (subst Top "x" Bot = Top);
  assert (subst (parse "T & x") "x" Bot = (parse "T & F"));
  print_string "Tests subst                      OK\n"


(* Renvoie une variable quelconque présente dans f une formule simplifiée *)
let rec var_in_formule (f: formule) : string = match f with
  | Top | Bot -> failwith "f n'a pas de variable"
  | Var s -> s
  | And (a, _) | Or (a, _) | Not a -> var_in_formule a


(* Renvoie une valuation satisfiant f, ou None si f est insatisfiable *)
let rec quine (f:formule) :sat_result =
  match simpl_full f with
  | Top -> Some []
  | Bot -> None
  | f' ->
    let x = var_in_formule f' in
      match quine (subst f' x Bot) with
      | Some v -> Some ((x, false)::v)
      | None ->
        match quine (subst f' x Top) with
        | Some v -> Some ((x, true)::v)
        | None -> None


let test_quine () =
  assert (quine Top = Some []);
  assert (quine Bot = None);
  let res1 = quine (from_file "tests/test1") in
  match res1 with
  | None -> failwith "Échec : pas de valuation trouvée pour tests/test1"
  | Some v -> assert (evaluer (from_file "tests/test1") v);
  assert (quine (parse "(a | b) & (~a | c) & (~c | ~b)") = Some ["a", false; "b", true; "c", false]);
  let a = quine (parse "(a | b) & (~a | ~b)") in
  assert (a = Some ["a", true; "b", false] || a = Some ["a", false; "b", true]);
  assert (quine (parse "x & (y > (~z | (x & w))) & (y | ~z) & (z | ~x) & ~w") = None);
  assert (quine (parse "x | (y & ~z)") = Some [("x",false);("y",true);("z",false)]);
  assert (quine (parse "x & (y & ~z)") = Some [("x",true);("y",true);("z",false)]);
  assert (quine (parse "x | (y & ~x)") = Some [("x",false);("y",true)]);
  assert (quine (parse "x | (y & ~y)") = Some [("x",true)]);
  assert (quine (parse "x & (y & ~x)") = None);
  assert (quine (from_file "tests/test_impossible") = None);
  print_string "Tests quine                      OK\n"


(*
 * Affiche toutes les variables de v qui sont à `true` à raison d’une variable
 * par ligne.
 *)
let rec print_true (v: valuation) : unit =
  match v with
  | [] -> ()
  | (x, true)::q -> print_string x; print_newline (); print_true q
  | (_, false)::q -> print_true q


let test () =
  print_string "Exécution des tests…\n";
  test_parse ();
  test_compte_ops ();
  test_est_strictement_croissante ();
  test_union ();
  test_liste_variables ();
  test_evaluer ();
  test_add_one ();
  test_valuation_next ();
  test_valuation_init ();
  test_satsolver_naif ();
  test_simpl ();
  test_subst ();
  test_quine ();
  print_string "Tous les tests ont réussi !\n"


let main () =
  let argc = Array.length Sys.argv in
  if argc = 1 then
    failwith "1 too few argument given to the program."
  else if Sys.argv.(1) = "test" then
    test ()
  else
    try
    let f = from_file Sys.argv.(1) in
    let v = quine f in
    begin match v with
    | Some v' -> print_string "La formule est satisfiable en assignant 1 aux ";
                 print_string "variables suivantes et 0 aux autres :\n";
                 print_true v'
    | None    -> print_string "La formule est insatisfiable.\n"
    end;
    print_string "Temps d'exécution : ";
    print_float (Sys.time ());
    print_string " s\n"
    with Sys_error(no_such_file) -> print_string no_such_file; print_newline ()


let _ = main ()

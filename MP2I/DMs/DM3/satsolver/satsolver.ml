
type formule =
  | Top
  | Bot
  | Var of string
  | And of formule * formule
  | Or  of formule * formule
  | Not of formule


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
  assert (from_file "tests/zerowidthspace" = Var "​");  (* (Neo)Vim affiche <200b>, mais pas emacs (ce qui prouve bien que Vim est supérieur (même si ed est le standard)) *)
  print_string "Tests parser OK\n"


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
  print_string "Tests compte_ops OK\n"


(* Renvoie true si l est triée et sans doublon, false sinon *)
let est_strictement_croissante (l: 'a list) =
  (* Renvoie true si l est triée, sans doublon et que le premier élément est
   * strictement supérieur à previous *)
  let rec est_strictement_croissante_prev (l: 'a list) (previous: 'a) =
    match l with
    | [] -> true
    | x::q -> (x > previous) && est_strictement_croissante_prev q x
  in
  match l with
  | [] -> true
  | x::q -> est_strictement_croissante_prev q x


let test_est_strictement_croissante () =
  assert (est_strictement_croissante []);
  assert (est_strictement_croissante [1]);
  assert (est_strictement_croissante [1; 2; 3; 7; 10; 90]);
  assert (not (est_strictement_croissante [1; 2; 3; 3; 7; 10; 90]));
  assert (not (est_strictement_croissante [1; 1]));
  assert (not (est_strictement_croissante [1; 2; 3; -7; 7; 10; 90]));
  print_string "Tests est_strictement_croissante OK\n"


let test () =
  test_parse ();
  test_compte_ops ();
  test_est_strictement_croissante ();
  print_string "Tous les tests ont réussi !\n"


let main () =
  let argc = Array.length Sys.argv in
  if argc = 1 then
    failwith "1 too few argument given to the program."
  else if Sys.argv.(1) = "test" then
    test()
  else
    (print_string Sys.argv.(1); print_string "\n")


let _ = main ()

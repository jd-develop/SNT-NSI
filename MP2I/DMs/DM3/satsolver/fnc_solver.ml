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

(* Renvoie la liste des variables contenues dans la formule, sans doublons et
 * dans l’ordre croissant *)
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

(********* algorithme de Quine *********)

(* Simplifier la formule f *)
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


(* Remplace toutes les occurences de x par g dans la formule f *)
let rec subst (f: formule) (x: string) (g: formule) =
  match f with
  | Var s when s = x -> g
  | Top | Bot | Var _ -> f
  | Or  (f1, f2) -> Or  (subst f1 x g, subst f2 x g)
  | And (f1, f2) -> And (subst f1 x g, subst f2 x g)
  | Not f' -> Not(subst f' x g)


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

(********* ARN *********)

type coul = Rouge | Noir
type 'a arn_r = F of 'a | N of coul * 'a * 'a arn_r * 'a arn_r
type 'a arn = 'a arn_r option

(* Renvoie Si k est dans a *)
let rec getARNrelax (a: 'a arn_r)(k: 'a) : bool = match a with
  | N (_, x, g, d) when k > x -> getARNrelax d k
  | N (_, x, g, d) -> getARNrelax g k
  | F x when x=k -> true
  | F x -> false

(* Renvoie Si k est dans a *)
let rec getARN (a: 'a arn)(k: 'a) : bool = match a with
  | None -> false
  | Some a' -> getARNrelax a' k

(* Corrige l'anomalie Rouge Rouge *)
let correctionARN (a': 'a arn_r) : 'a arn_r = match a' with
  | N(Noir, z, N(Rouge, y, N(Rouge, x, a, b), c), d)
  | N(Noir, z, N(Rouge, x, a, N(Rouge, y, b, c)), d)
  | N(Noir, x, a, N(Rouge, z, N(Rouge, y, b, c), d))
  | N(Noir, x, a, N(Rouge, y, b, N(Rouge, z, c, d))) -> N(Rouge, y, N(Noir, x, a, b), N(Noir, z, c, d))
  | _ -> a'

(* Insere x dans a *)
let rec insertARNrelax (a: 'a arn_r)(x: 'a) : 'a arn_r = match a with
  | N(c, y, g, d) when x > y -> correctionARN(N(c, y, g, insertARNrelax d x))
  | N(c, y, g, d) when x < y -> correctionARN(N(c, y, insertARNrelax g x, d))
  | N(c, y, g, d) -> a
  | F y when x > y -> N(Rouge, y , F y, F x)
  | F y when x < y -> N(Rouge, x, F x, F y)
  | F y -> a

(* Insert x dans a *)
let insertARN (a: 'a arn)(x: 'a) : 'a arn = match a with
  | None -> Some (F x)
  | Some a' ->
  match insertARNrelax a' x with
  | N(_, y, g, d) -> Some (N(Noir, y, g, d))
  | F y -> Some (F y)

(* Corrige l'anomalie de hauteur Noir a gauche *)
let correctionARNg (a': 'a arn_r) : 'a arn_r * bool = match a' with
  | N (coul, x, a, N(Noir, y, b, N(Rouge, z, c, d)))
  | N (coul, x, a, N(Noir, z, N(Rouge, y, b, c), d))                   -> N (coul, y, N(Noir, x, a, b), N(Noir, z, c, d)), false
  | N (coul, x, a, N(Noir, y, b, c))                                   -> N (Noir, x, a, N(Rouge, y, b, c)), coul=Noir
  | N (Noir, x, a, N(Rouge, y, N(Noir, y', b, N(Rouge, x', c, d)), e))
  | N (Noir, x, a, N(Rouge, y, N(Noir, x', N(Rouge, y', b, c), d), e)) -> N (Noir, y, N(Rouge, y', N(Noir, x, a, b), N(Noir, x', c, d)), e), false
  | N (Noir, x, a, N(Rouge, z, N(Noir, y, b, c), d))                   -> N (Noir, z, N(Noir, x, a, N(Rouge, y, b, c)), d), false
  | _ -> a', false

(* Corrige l'anomalie de hauteur Noir a droite *)
let correctionARNd (a': 'a arn_r) : 'a arn_r * bool = match a' with
  | N (coul, z, N(Noir, y, N(Rouge, x, a, b), c), d)
  | N (coul, z, N(Noir, x, a, N(Rouge, y, b, c)), d)                   -> N (coul, y, N(Noir, x, a, b), N(Noir, z, c, d)), false
  | N (coul, y, N(Noir, x, a, b), c)                                   -> N (Noir, y, N(Rouge, x, a, b), c), coul=Noir
  | N (Noir, y, N(Rouge, x, a, N(Noir, x', N(Rouge, y', b, c), d)), e)
  | N (Noir, y, N(Rouge, x, a, N(Noir, y', b, N(Rouge, x', c, d))), e) -> N (Noir, x, a, N(Rouge, x', N(Noir, y', b, c), N(Noir, y, c, d))), false
  | N (Noir,z, N(Rouge, x, a, N(Noir, y, b, c)), d)                    -> N (Noir, x, a, N(Noir, z, N(Rouge, y, b, c), d)), false
  | _ -> a', false

(* Supprime k dans a' *)
let rec supprARNrelax (a': 'a arn_r)(k: 'a) : 'a arn_r * bool = match a' with
  | N (coul, _, F x, d) when k = x -> d, coul=Noir
  | N (coul, _, g, F x) when k = x -> g, coul=Noir
  | N (c, x, g, d) when k > x -> let s, h = supprARNrelax d k in
                               if h then correctionARNd (N(c, x, g, s))
                               else N(c, x, g, s), false
  | N (c, x, g, d) -> let s, h = supprARNrelax g k in
                      if h then correctionARNg (N(c, x, s, d))
                      else N(c, x, s, d), false
  | F x -> F x, false

(* Supprime k dans a *)
let supprARN (a: 'a arn)(k: 'a) : 'a arn = match a with
  | None -> None
  | Some F x when k = x -> None
  | Some a' ->
match supprARNrelax a' k with
  | N (_, x, g, d), _ -> Some (N(Noir, x, g, d))
  | F x, _ -> Some(F x)

(********* FNC *********)

type litteral = YesVar of string | NotVar of string
type clause = litteral arn
type fnc = clause list

(* Renvoie f en litteral,
 * Lève une exception Failure si f n'est pas un litteral *)
let litteral_of_formule (f: formule) : litteral = match f with
  | Var s -> YesVar s
  | Not (Var s) -> NotVar s
  | _ -> failwith "f n'est pas un fnc"

(* Renvoie f en clause,
 * Lève une exception Failure si f n'est pas une clause *)
let clause_of_formule (f: formule) : clause =
  let rec clause_rec (f': formule)(c: clause) : clause = match f' with
    | Or (a,b) -> clause_rec a (clause_rec b c)
    | _ -> insertARN c (litteral_of_formule f')
  in clause_rec f None

(* Renvoie f en fnc, ou None si f n'est pas un fnc *)
let fnc_of_formule (f: formule) : fnc option =
  let rec fnc_rec (f': formule)(fn: fnc) : fnc = match f' with
    | And (a,b) -> fnc_rec a (fnc_rec b fn)
    | _ -> (clause_of_formule f')::fn
  in try Some (fnc_rec f []) with
    | Failure _ -> None

let test_fnc_of_formule () =
  assert (fnc_of_formule(parse "a") = Some [Some (F (YesVar "a"))]);
  assert (fnc_of_formule(parse "~a") = Some [Some (F (NotVar "a"))]);
  assert (fnc_of_formule(parse "~a | b | ~c") = Some [Some (N (Noir, YesVar "b", F (YesVar "b"), N (Rouge, NotVar "a", F (NotVar "a"), F (NotVar "c"))))]);
  assert (fnc_of_formule(parse "(~a | b) & ~c") = Some [Some (N (Noir, YesVar "b", F (YesVar "b"), F (NotVar "a"))); Some (F (NotVar "c"))]);
  assert (fnc_of_formule(parse "(~a & b) | ~c") = None);
  print_string "Tests fnc_of_formule             OK\n"

(* Renvoie si une clause de f est vide *)
let rec clause_vide (f: fnc) : bool = match f with
  | [] -> false
  | None::f' -> true
  | _::f' -> clause_vide f'

(* Remplace tous les s par v dans f *)
let rec substFNC (f: fnc)(s: string)(v: bool) : fnc = match f, v with
  | [], _ -> []
  | c::f', true when getARN c (YesVar s) -> substFNC f' s v 
  | c::f', true when getARN c (NotVar s) -> (supprARN c (NotVar s))::(substFNC f' s v) 
  | c::f', false when getARN c (NotVar s) -> substFNC f' s v 
  | c::f', false when getARN c (YesVar s) -> (supprARN c (YesVar s))::(substFNC f' s v)
  | c::f', _ -> c::(substFNC f' s v)

(* Renvoie une variable dans une clause unitaire,
 * v sans cette variable,
 * et la valeur a mettre pour cette variable,
 * ou None si aucune clause n'est unitaire *)
let rec propagation_unitaire (f: fnc)(v: string list) : (string * string list * bool) option =
  match f with
  | [] -> None
  | (Some (F (YesVar s)))::q -> Some (s, List.filter (fun x -> x<>s) v, true)
  | (Some (F (NotVar s)))::q -> Some (s, List.filter (fun x -> x<>s) v, false)
  | _::q -> propagation_unitaire q v

(* Renvoie une solution de f, ou None si il n'y en a pas *)
let rec quineFNC (f: fnc)(v: string list) : sat_result =
  match f with
  | [] -> Some []
  | _ when clause_vide f -> None
  | _ ->
  match propagation_unitaire f v with
  | Some (s, v', b) ->
      begin match quineFNC (substFNC f s b) v' with
	  | Some r -> Some ((s,b)::r) 
	  | None -> None
	  end
  | None ->
  match v with
  | [] -> Some []
  | s::v' ->
  match quineFNC (substFNC f s false) v' with
  | Some r -> Some ((s,false)::r) 
  | None ->
  match quineFNC (substFNC f s true) v' with
  | Some r -> Some ((s,true)::r) 
  | None -> None

let test_quineFNC () =
  assert (quineFNC([Some (F (YesVar "a"))]) ["a"] = Some [("a", true)]);
  assert (quineFNC([Some (F (NotVar "a"))]) ["a"] = Some [("a", false)]);
  assert (quineFNC([Some (N (Rouge, YesVar "b", F (YesVar "b"), N (Rouge, NotVar "a", F (NotVar "a"), F (NotVar "c"))))]) ["a";"b";"c"] = Some [("a", false)]);
  assert (quineFNC([Some (N (Rouge, YesVar "b", F (YesVar "b"), F (NotVar "a"))); Some (F (NotVar "c"))]) ["a";"b";"c"] = Some [("a", false); ("b", false); ("c", false)]);
  print_string "Tests quineFNC                   OK\n"

(*
 * Affiche toutes les variables de v qui sont à `true` à raison d’une variable
 * par ligne.
 *)
let rec print_true (v: valuation) : unit = match v with
  | [] -> ()
  | (x, true)::q -> print_string x; print_newline (); print_true q
  | (_, false)::q -> print_true q


let test () =
  print_string "Exécution des tests…\n";
  test_parse ();
  test_liste_variables ();
  test_subst ();
  test_quine ();
  test_fnc_of_formule ();
  test_quineFNC ();
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
    let v =
      begin match fnc_of_formule f with
      | Some f' -> print_string "La formule est fnc\n";
                   quineFNC f' (liste_variables f)
      | None -> quine f
      end in
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

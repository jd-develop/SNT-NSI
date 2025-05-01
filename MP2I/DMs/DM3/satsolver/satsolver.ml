type formule =
	| Var of string
	| Top
	| Bot
	| And of formule * formule
	| Or of formule * formule
	| Not of formule

type valuation = (string * bool) list
type sat_result = valuation option

let implique (f1, f2) = Or(Not f1, f2)
let equivalence (f1, f2) = And(implique (f1, f2), implique (f2, f1))

(*** PARSER ***)

exception Erreur_arguments of string
exception Erreur_syntaxe
exception Fichier_invalide

(* Symboles:
	'T' -> true
	'F' -> false
	'&' -> And
	'|' -> Or
	'~' -> Not
	'>' -> implication
	'=' -> equivalence
 *)

(* Détermine si c correspond à un opérateur binaire logique *)
let is_binop (c:char) :bool = match c with 
	| '&' |  '|' |  '>' |  '='  -> true
	| _ -> false 

(* Priorité de l'opérateur c. Permet de déterminer
	comment interpréter une formule sans parenthèses.
	Par exemple, "x&y|z" sera interprété comme "(x&y)|z"
	car & est plus prioritaire que | *)
let priority (c:char) :int = match c with
	| '&' -> 4
	| '|' -> 3
	| '=' -> 2
	| '>' -> 1
	| _ -> raise Erreur_syntaxe (* c n'est pas un opérateur *)

(* indice de l'opérateur le moins prioritaire parmis ceux
   qui ne sont pas entre parenthèses entre s.[i] et s.[j] 
   inclus *)
 let find_op_surface (s:string) (i:int) (j:int) :int =
 	(* 
 	   Renvoie l'indice de l'opérateur le moins prioritaire entre
 	   i et j, sachant que res est l'indice du meilleur opérateur
 	   entre i et k-1.
 	   paren_lvl: niveau d'imbrication actuel des parenthèses *)
 	let rec find_op_paren (k:int) (res:int) (paren_lvl:int) :int  =
 		if k=j+1 then res else
 		if s.[k] = '(' then find_op_paren (k+1) res (paren_lvl+1)
 		else if s.[k] = ')' then find_op_paren (k+1) res (paren_lvl-1) 

 		(* Le caractère lu est pris si l'on est hors des parenthèses,
 		   que le caractère est bien un opérateur, et qu'il est moins
 		   prioritaire que le meilleur résultat jusqu'ici *)
 		else if paren_lvl = 0 
 			 && is_binop s.[k] 
 			 && (res = -1 || priority s.[k] < priority s.[res]) 
 			 then find_op_paren (k+1) k (paren_lvl)
 		else find_op_paren (k+1) res (paren_lvl)
 	in find_op_paren i (-1) 0;;

(* Renvoie une formule construite à partir de la chaîne s.
   Lève une exception Erreur_syntaxe si la chaîne ne représente pas une formule valide. *)
let parse (s:string) :formule =
	let n = String.length s in
	(* construit une formule à partir de s[i..j] *)
	let rec parse_aux (i:int) (j:int) =
		assert (0 <= i && i < n && 0 <= j && j < n && i <= j );
		if s.[i] = ' ' then parse_aux (i+1) j
		else if s.[j] = ' ' then parse_aux i (j-1)
		else let k = find_op_surface s i j in 
		if k = -1 then
			if s.[i] = '~' then 
				Not (parse_aux (i+1) j)
			else if s.[i] = '(' then
				begin 
					if (s.[j] != ')') then (print_int j; failwith "mauvais parenthésage") else
					parse_aux (i+1) (j-1)
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

(* Renvoie une formule construire à partir du contenu du fichier fn.
   Lève une exception Erreur_syntaxe si le contenu du fichier n'est pas une formule valide.
   Lève une exception Sys_error(message_erreur) si le nom du fichier n'est pas valide. *)
let from_file (filename:string) :formule = 
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

(* Renvoie le contenu du fichier fn sous forme de string.
   Le fichier ne doit contenir qu'une seule ligne *)
let read_file (fn:string) :string =
	let ic = open_in fn in
	let res = input_line ic in
	close_in ic ; res

(* Renvoie le nombre d'opérateurs utilisés dans f *)
let rec compte_ops (f:formule) :int = match f with
	| Top | Bot | Var _ -> 0
	| And (a, b) | Or (a, b) -> 1 + compte_ops a + compte_ops b
	| Not a -> 1 + compte_ops a

(* Si l est trie et sans doublons (trie strict)*)
let rec est_trie_strict (l:'a list) :bool = match l with
	| [] | _::[] -> true
	| x::y::q when x < y -> est_trie_strict (y::q)
	| x::y::q -> false

(* Renvoie l'union de l1 et l2 avec l1 et l2 des listes trie strict *)
let rec union (l1:'a list)(l2:'a list) :'a list = match l1, l2 with
	| [], [] -> []
	| x::q, [] | [], x::q -> x::q
	| x::q, x'::q' when x < x' -> x::(union q (x'::q'))
	| x::q, x'::q' when x > x' -> x'::(union (x::q) q')
	| x::q, x'::q' -> x::(union q q')

(* Renvoie la liste des variables de f *)
let rec list_var (f:formule) :string list = match f with
	| Top | Bot -> []
	| Var s -> s::[]
	| And (a, b) | Or (a, b) -> union (list_var a)(list_var b)
	| Not a -> list_var a

(* Renvoie la liste des variables de f (mais en mieux) *)
let  list_var (f:formule) :string list =
	let rec list_var_rec (f':formule)(l:string list) :string list =
	match f' with
		| Top | Bot -> l
		| Var s -> s::l
		| And (a, b) | Or (a, b) -> list_var_rec a (list_var_rec b l)
		| Not a -> list_var_rec a l
	in List.sort_uniq compare (list_var_rec f [])

(* Interprète f avec v *)
let rec eval (f:formule)(v:valuation) :bool = match f with
	| Top -> true
	| Bot -> false
	| Var s -> List.assoc s v
	| And (a, b) -> eval a v && eval b v
	| Or (a, b) -> eval a v || eval b v
	| Not a -> not (eval a v)

(* Ajoute 1 à la représentation binaire de l *)
let rec add_one (l:bool list) :bool list =
	let rec add_rec (l':bool list)(b:bool) :bool list =
	match l' with
		| [] -> []
		| x::q -> (x <> b)::(add_rec q (x && b))
	in add_rec l true

(* Renvoie la valuation suivante de v,
   None si il n'y en a plus *)
let valuation_next (v:valuation) :valuation option =
	let s, l = List.split v in
	if (List.for_all Fun.id l)
	then None
	else Some (List.combine s (add_one l))

(* Renvoie la 1er valuation de variable s *)
let valuation_init (s:string list) :valuation =
	List.map (fun x -> (x,false)) s

(* Renvoie une solution de f
   None si il n'y en a pas *)
let satsolver_naif (f:formule) :sat_result =
	let rec satsolver_rec (f':formule)(v:valuation option) :sat_result =
	match v with
		| None -> None
		| Some v' when eval f' v' -> Some v'
		| Some v' -> satsolver_rec f' (valuation_next v')
	in satsolver_rec f (Some (valuation_init (list_var f)))

(* Renvoie f simplifier une fois et si f a été modifier *)
let rec simpl_step (f:formule) :formule * bool = match f with
	| And (a, Top) | And (Top, a) -> a, true
	| And (a, Bot) | And (Bot, a) -> Bot, true
	| Or (a, Top) | Or (Top, a) -> Top, true
	| Or (a, Bot) | Or (Bot, a) -> a, true
	| Not (Not a) -> a, true
	| Not Top -> Bot, true
	| Not Bot -> Top, true
	| And (a, b) -> let a', ma = simpl_step a in
					let b', mb = simpl_step b in
					And (a', b'), ma || mb
	| Or (a, b) -> let a', ma = simpl_step a in
					let b', mb = simpl_step b in
					Or (a', b'), ma || mb
	| _ -> f, false

(* Renvoie f simplifier *)
let rec simpl_full (f:formule) :formule =
	let f', m = simpl_step f in
	if m then simpl_full f'
	else f'

(* Renvoie f simplifier (mais en mieux) *)
let rec simpl_full (f:formule) :formule =
	let f' = match f with
	| And (a, b) -> And (simpl_full a, simpl_full b)
	| Or (a, b) -> Or (simpl_full a, simpl_full b)
	| Not a -> Not (simpl_full a)
	| _ -> f
	in match f' with
	| And (a, Top) | And (Top, a) -> a
	| And (a, Bot) | And (Bot, a) -> Bot
	| Or (a, Top) | Or (Top, a) -> Top
	| Or (a, Bot) | Or (Bot, a) -> a
	| Not (Not a) -> a
	| Not Top -> Bot
	| Not Bot -> Top
	| _ -> f'

(* Remplace tous les Var s par f' dans f *)
let rec subst (f:formule)(s:string)(f':formule) = match f with
	| Var s' when s' = s -> f'
	| And (a,b) -> And (subst a s f', subst b s f')
	| Or (a,b) -> Or (subst a s f', subst b s f')
	| Not a -> Not (subst a s f')
	| _ -> f

(* Renvoie une variable présente dans f une formule simplifié *)
let rec var_in_formule (f:formule) :string = match f with
	| Top  | Bot -> failwith "f n'a pas de variable"
	| Var s -> s
	| And (a, _) | Or (a, _) | Not a -> var_in_formule a

(* Renvoie une solution de f
   None si il n'y en a pas *)
let rec quine (f:formule) :sat_result =
	match simpl_full f with
	| Top -> Some []
	| Bot -> None
	| f' ->
	let x = var_in_formule f' in
	match quine (subst f' x Bot) with
	| Some v -> Some ((x,false)::v) 
	| None ->
	match quine (subst f' x Top) with
	| Some v -> Some ((x,true)::v) 
	| None -> None

(* Affiche les variables de valeur vrai *)
let rec print_true (v:valuation) :unit = match v with
	| [] -> ()
	| (s, b)::q when b -> print_string s; print_newline (); print_true q
	| (s, b)::q -> print_true q


(*** TESTS ***)

let test_parse () =
	assert (parse "a | (b & ~c)" = Or(Var "a", And(Var "b", Not (Var "c"))));
	print_string "Tests parse          OK\n"

let test_from_file () =
	assert (from_file "tests/test_from_file1.txt" = Or(Var "a", And(Var "b", Not(Var "c"))));
	assert (from_file "tests/test_from_file2.txt" = And(Or(Var "a", Var "b"), Not(Var "c")));
	assert (from_file "tests/test_from_file3.txt" = Or(Var "a", And(Var "b", Not(Var "c"))));
	print_string "Tests from_file      OK\n"

let test_compte_ops () =
	assert (compte_ops (parse "x | (y & ~z)") = 3);
	assert (compte_ops (parse "~(x | (x & ~z) | y)") = 5);
	print_string "Tests compte_ops     OK\n"

let test_satsolver_naif () =
	assert (satsolver_naif (parse "x | (y & ~z)") = Some [("x",true);("y",false);("z",false)]);
	assert (satsolver_naif (parse "x & (y & ~z)") = Some [("x",true);("y",true);("z",false)]);
	assert (satsolver_naif (parse "x | (y & ~x)") = Some [("x",true);("y",false)]);
	assert (satsolver_naif (parse "x & (y & ~x)") = None);
	print_string "Tests satsolver_naif OK\n"

let test_quine () =
	assert (quine (parse "x | (y & ~z)") = Some [("x",false);("y",true);("z",false)]);
	assert (quine (parse "x & (y & ~z)") = Some [("x",true);("y",true);("z",false)]);
	assert (quine (parse "x | (y & ~x)") = Some [("x",false);("y",true)]);
	assert (quine (parse "x | (y & ~y)") = Some [("x",true)]);
	assert (quine (parse "x & (y & ~x)") = None);
	assert (quine (from_file "tests/test_impossible.txt") = None);
	print_string "Tests quine          OK\n"

let test () =
	test_parse ();
	test_from_file ();
	test_compte_ops ();
	test_satsolver_naif ();
	test_quine ();
	print_string "Tous les tests ont réussi.\n"


(*** MAIN ***)

(* Execute le programme principal *)
let exec () =
	begin
	match quine (from_file Sys.argv.(1)) with
	| None -> print_string "La formule est insatisfiable\n"
	| Some v -> print_string "La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres:\n";
				print_true v
	end;
	print_string "Temps d'exécution : ";
	print_float (Sys.time ());
	print_string " s\n"

(* Execute test si le 1er argument est test sinon exec *)
let main () =
	if (Array.length Sys.argv < 2)
	then raise (Erreur_arguments "1 argument demande")
	else match Sys.argv.(1) with
	| "test" -> test ()
	| _ -> exec ()

let _ = main ()

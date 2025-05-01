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

(* Renvoie la liste des variables de f (mais en mieux) *)
let  list_var (f:formule) :string list =
	let rec list_var_rec (f':formule)(l:string list) :string list =
	match f' with
		| Top | Bot -> l
		| Var s -> s::l
		| And (a, b) | Or (a, b) -> list_var_rec a (list_var_rec b l)
		| Not a -> list_var_rec a l
	in List.sort_uniq compare (list_var_rec f [])

(* Renvoie f simplifier *)
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


(*** ARN ***)

type coul = Rouge | Noir
type 'a arn_r = F of 'a | N of coul * 'a * 'a arn_r * 'a arn_r
type 'a arn = 'a arn_r option

(* Renvoie Si k est dans a *)
let rec getARNrelax (a:'a arn_r)(k:'a) :bool = match a with
	| N (_, x, g, d) when k>x -> getARNrelax d k
	| N (_, x, g, d) when k<x -> getARNrelax g k
	| N (_, x, g, d) -> true
	| F x when x=k -> true
	| F x -> false

(* Renvoie Si k est dans a *)
let rec getARN (a:'a arn)(k:'a) :bool = match a with
	| None -> false
	| Some a' -> getARNrelax a' k

(* Corrige l'anomalie Rouge Rouge *)
let correctionARN (a':'a arn_r) :'a arn_r = match a' with
	| N(Noir, z, N(Rouge, y, N(Rouge, x, a, b), c), d)
	| N(Noir, z, N(Rouge, x, a, N(Rouge, y, b, c)), d)
	| N(Noir, x, a, N(Rouge, z, N(Rouge, y, b, c), d))
	| N(Noir, x, a, N(Rouge, y, b, N(Rouge, z, c, d))) -> N(Rouge, y, N(Noir, x, a, b), N(Noir, z, c, d))
	| _ -> a'

(* Insere x dans a *)
let rec insertARNrelax (a:'a arn_r)(x:'a) :'a arn_r = match a with
	| N(c, y, g, d) when x>y -> correctionARN(N(c, y, g, insertARNrelax d x))
	| N(c, y, g, d) when x<y -> correctionARN(N(c, y, insertARNrelax g x, d))
	| N(c, y, g, d) -> a
	| F y when x>y -> N(Rouge, y , F y, F x)
	| F y when x<y -> N(Rouge, x, F x, F y)
	| F y -> a

(* Insert x dans a *)
let insertARN (a:'a arn)(x:'a) :'a arn = match a with
	| None -> Some (F x)
	| Some a' ->
	match insertARNrelax a' x with
	| N(_, y, g, d) -> Some (N(Noir, y, g, d))
	| F y -> Some (F y)

(* Corrige l'anomalie de hauteur Noir a gauche *)
let correctionARNg (a':'a arn_r) :'a arn_r * bool = match a' with
	| N (coul, x, a, N(Noir, y, b, N(Rouge, z, c, d)))
	| N (coul, x, a, N(Noir, z, N(Rouge, y, b, c), d)) -> N (coul, y, N(Noir, x, a, b), N(Noir, z, c, d)), false
	| N (coul, x, a, N(Noir, y, b, c)) -> N (Noir, x, a, N(Rouge, y, b, c)), coul=Noir
	| N (Noir, x, a, N(Rouge, y, N(Noir, y', b, N(Rouge, x', c, d)), e))
	| N (Noir, x, a, N(Rouge, y, N(Noir, x', N(Rouge, y', b, c), d), e)) -> N (Noir, y, N(Rouge, y', N(Noir, x, a, b), N(Noir, x', c, d)), e), false
	| N (Noir, x, a, N(Rouge, z, N(Noir, y, b, c), d)) -> N (Noir, z, N(Noir, x, a, N(Rouge, y, b, c)), d), false
	| _ -> a', false

(* Corrige l'anomalie de hauteur Noir a droite *)
let correctionARNd (a':'a arn_r) :'a arn_r * bool = match a' with
	| N (coul, z, N(Noir, y, N(Rouge, x, a, b), c), d)
	| N (coul, z, N(Noir, x, a, N(Rouge, y, b, c)), d) -> N (coul, y, N(Noir, x, a, b), N(Noir, z, c, d)), false
	| N (coul, y, N(Noir, x, a, b), c) -> N (Noir, y, N(Rouge, x, a, b), c), coul=Noir
	| N (Noir, y, N(Rouge, x, a, N(Noir, x', N(Rouge, y', b, c), d)), e)
	| N (Noir, y, N(Rouge, x, a, N(Noir, y', b, N(Rouge, x', c, d))), e) -> N (Noir, x, a, N(Rouge, x', N(Noir, y', b, c), N(Noir, y, c, d))), false
	| N (Noir,z, N(Rouge, x, a, N(Noir, y, b, c)), d) -> N (Noir, x, a, N(Noir, z, N(Rouge, y, b, c), d)), false
	| _ -> a', false

(* Supprime k dans a' *)
let rec supprARNrelax (a':'a arn_r)(k:'a) :'a arn_r * bool = match a' with
	| N (coul, _, F x, d) when k=x -> d, coul=Noir
	| N (coul, _, g, F x) when k=x -> g, coul=Noir
	| N (c, x, g, d) when k>x -> let s, h = supprARNrelax d k in
							if h then correctionARNd (N(c, x, g, s))
							else N(c, x, g, s), false
	| N (c, x, g, d) -> let s, h = supprARNrelax g k in
							if h then correctionARNg (N(c, x, s, d))
							else N(c, x, s, d), false
	| F x -> F x, false

(* Supprime k dans a *)
let supprARN (a:'a arn)(k:'a) :'a arn = match a with
	| None -> None
	| Some F x when k=x -> None
	| Some a' ->
match supprARNrelax a' k with
	| N (_, x, g, d), _ -> Some (N(Noir, x, g, d))
	| F x, _ -> Some(F x)

(* Concatène a et b *)
let rec concatARNrelax (a:'a arn_r)(b:'a arn_r) :'a arn_r = match a with
	| F x -> insertARNrelax b x
	| N (_, x, g, d) -> concatARNrelax g (concatARNrelax d b)

(* Concatène a et b *)
let rec concatARN (a:'a arn)(b:'a arn) :'a arn = match a, b with
	| ab, None | None, ab -> ab
	| Some a', Some b' -> Some (concatARNrelax a' b')


(*** FNC ***)

type litteral = YesVar of string | NotVar of string
type clause = litteral arn
type fnc = clause list

(* Renvoie f en litteral, None si ce n'est pas un litteral *)
let litteral_of_formule (f:formule) :litteral option = match f with
	| Var s -> Some (YesVar s)
	| Not (Var s) -> Some(NotVar s)
	| _ -> None

(* Renvoie f en clause, None si ce n'est pas une clause *)
let clause_of_formule (f:formule) :clause option =
	let rec clause_rec (f':formule) :clause = match f' with
		| Or (a,b) -> concatARN (clause_rec a)(clause_rec b)
		| _ ->
		match litteral_of_formule f' with
		| None -> failwith "pas un litteral"
		| Some l -> Some (F l)
	in try Some (clause_rec f) with
		| Failure _ -> None

(* Renvoie f en fnc, None si ce n'est pas un fnc *)
let fnc_of_formule (f:formule) :fnc option =
	let rec fnc_rec (f':formule) :fnc = match f' with
		| And (a,b) -> (fnc_rec a) @ (fnc_rec b)
		| _ ->
		match clause_of_formule f' with
		| None -> failwith "pas une clause"
		| Some c -> c::[]
	in try Some (fnc_rec f) with
		| Failure _ -> None

(* Renvoie si une clause de f est vide *)
let rec clause_vide (f:fnc) :bool = match f with
	| [] -> false
	| x::f' when x=None -> true
	| x::f' -> clause_vide f'

(* Remplace tous les s par v dans f *)
let rec substFNC (f:fnc)(s:string)(v:bool) :fnc = match f, v with
	| [], _ -> []
	| c::f', true when getARN c (YesVar s) -> substFNC f' s v 
	| c::f', true -> (supprARN c (NotVar s))::(substFNC f' s v) 
	| c::f', false when getARN c (NotVar s) -> substFNC f' s v 
	| c::f', false -> (supprARN c (YesVar s))::(substFNC f' s v)

(* Renvoie une solution de f
   None si il n'y en a pas *)
let rec quineFNC (f:fnc)(v:string list) :sat_result =
	match f with
	| [] -> Some []
	| _ when clause_vide f -> None
	| _ ->
	match v with
	| [] -> Some []
	| s::v' ->
	match quineFNC (substFNC f s false) v' with
	| Some r -> Some ((s,false)::r) 
	| None ->
	match quineFNC (substFNC f s true) v' with
	| Some r -> Some ((s,true)::r) 
	| None -> None


(*** TESTS ***)

let test_parse () =
	assert (parse "a | (b & ~c)" = Or(Var "a", And(Var "b", Not (Var "c"))));
	print_string "Tests parse          OK\n"

let test_from_file () =
	assert (from_file "tests/test_from_file1.txt" = Or(Var "a", And(Var "b", Not(Var "c"))));
	assert (from_file "tests/test_from_file2.txt" = And(Or(Var "a", Var "b"), Not(Var "c")));
	assert (from_file "tests/test_from_file3.txt" = Or(Var "a", And(Var "b", Not(Var "c"))));
	print_string "Tests from_file      OK\n"

let test_quine () =
	assert (quine (parse "x | (y & ~z)") = Some [("x",false);("y",true);("z",false)]);
	assert (quine (parse "x & (y & ~z)") = Some [("x",true);("y",true);("z",false)]);
	assert (quine (parse "x | (y & ~x)") = Some [("x",false);("y",true)]);
	assert (quine (parse "x | (y & ~y)") = Some [("x",true)]);
	assert (quine (parse "x & (y & ~x)") = None);
	assert (quine (from_file "tests/test_impossible.txt") = None);
	print_string "Tests quine          OK\n"

let test_fnc_of_formule () =
	assert (fnc_of_formule(parse "a") = Some [Some (F (YesVar "a"))]);
	assert (fnc_of_formule(parse "~a") = Some [Some (F (NotVar "a"))]);
	assert (fnc_of_formule(parse "~a | b | ~c") = Some [Some (N (Rouge, YesVar "b", F (YesVar "b"), N (Rouge, NotVar "a", F (NotVar "a"), F (NotVar "c"))))]);
	assert (fnc_of_formule(parse "(~a | b) & ~c") = Some [Some (N (Rouge, YesVar "b", F (YesVar "b"), F (NotVar "a"))); Some (F (NotVar "c"))]);
	assert (fnc_of_formule(parse "(~a & b) | ~c") = None);
	print_string "Tests fnc_of_formule OK\n"

let test () =
	test_parse ();
	test_from_file ();
	test_quine ();
	test_fnc_of_formule ();
	print_string "Tous les tests ont réussi.\n"

(*** MAIN ***)

(* Execute le programme principal *)
let exec () =
	let f = from_file Sys.argv.(1) in
	begin
	match fnc_of_formule f with
	| Some fnc -> print_string "La formule est fnc\n";
		begin
		match quineFNC fnc (list_var f) with
		| None -> print_string "La formule est insatisfiable\n"
		| Some v -> print_string "La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres:\n";
					print_true v
		end
	| None ->
		begin
		match quine f with
		| None -> print_string "La formule est insatisfiable\n"
		| Some v -> print_string "La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres:\n";
					print_true v
		end
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

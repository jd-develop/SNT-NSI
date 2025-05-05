open Parser
open ARN

let test_parse () =
	assert (parse "a | (b & ~c)" = Or(Var "a", And(Var "b", Not (Var "c"))));
	assert (parse "a | (b & (c > ~b)) | (a = F)" = Or(Var "a", Or(And(Var "b", implique (Var "c", Not(Var "b"))), equivalence (Var "a", Bot))));
	assert (parse "((a | b) & c) > d" = implique (And(Or(Var "a", Var "b"), Var "c"), Var "d"));
	try
    let _ = parse "a & (b | c" in
    assert false;
  	with
  	| Failure("mauvais parenthésage") -> assert true;
	
	(* try
    let _ = parse "a $ b" in
    assert false;
  	with
  	| Erreur_syntaxe -> assert true; *)
	print_string "Tests OK\n"

let test_from_file () =
	assert (from_file "tests/test1.txt" =
	Or (Not (Or (Var "a", And (Var "b", Not (Var "c")))),
 And
  (Or (And (Or (Not (Var "d"), Var "e"), Or (Not (Var "e"), Var "d")),
    And (Var "f", Not (Var "g"))),
  Or (Not (Var "h"), Or (Var "i", Var "j")))))

exception Not_enough_arguments of string

(* Renvoie le contenu de la première ligne du fichier file *)
let read_file (file: string) : string = 
	let ic = open_in file in
	let res = input_line ic in
	close_in ic; res

(* Compte le nombres de OR / AND / NOT dans une formule f *)
let rec compte_ops (f: formule) : int =
	match f with
	| Top | Bot | Var(_) -> 0
	| Not(f') -> 1 + compte_ops f'
	| And(f1, f2) | Or(f1, f2) -> 1 + compte_ops f1 + compte_ops f2

let test_compte_ops () = 
	assert (compte_ops (parse "x | (y & ~z)") = 3);
	assert (compte_ops (parse "~(x | (x & ~z) | y)") = 5)

(* Vérifie qu'une liste est strictement croissante *)
let rec is_sort (l: 'a list) : bool =
	match l with
	| [] | _::[] -> true
	| x::y::q -> x < y && is_sort (y::q)

(* Fusionne l1 et l2, deux listes strictement croissante en une nouvelle liste strictement croissante *)
let rec union (l1: 'a list) (l2: 'a list) : 'a list =
	match l1, l2 with
	| l, [] | [], l -> l 
	| x::q, y::p -> if x < y then x::(union q (y::p)) 
						else if x > y then y::(union (x::q) p) 
						else x::(union q p

(* Retourne la liste des variables de f *)
let rec var_list (f: formule) : string list =
	match f with
	| Top | Bot -> []
	| Var(q) -> [q]
	| Not(f') -> var_list f'
	| And(f1, f2) | Or(f1, f2) -> union (var_list f1) (var_list f2)

(* Retourne l'ensemble des variable de f sous forme d'arn *)
let var_arn (f: formule) : string arn =
	let rec insert_var_arn (f: formule) (t: string arn) : string arn =
		match f with
		| Top | Bot -> t
		| Var(q) -> insertionARN q t
		| Not(f') -> insert_var_arn f' t
		| And(f1, f2) | Or(f1, f2) -> insert_var_arn f1 (insert_var_arn f2 t)
	in insert_var_arn f None

(* transforme l'arn des variables en liste *)
let list_var_from_arn (t: string arn) : string list =
	let rec list_arn_aux (t: string arn) (l: string list) : string list = 
		match t with
		| None -> l
		| Some Feuille(a) -> a::l
		| Some Noeud(_, _, t1, t2) -> list_arn_aux (Some t1) (list_arn_aux (Some t2) l)
	in list_arn_aux t []

type valuation = (string * bool) list
type sat_result = valuation option

(* Evalue f avec la valuation v *)
let rec evaluate (f: formule) (v: valuation) : bool =
	match f with
	| Top -> true
	| Bot -> false
	| Var(q) -> List.assoc q v
	| Not(f') -> not (evaluate f' v)
	| Or(f1, f2) -> evaluate f1 v || evaluate f2 v
	| And(f1, f2) -> evaluate f1 v && evaluate f2 v

(* 
Soit l l'écriture binaire de x. add_one l est l'écriture binaire de x + 1.
les bits de poids faibles sont à gauche
*)
let rec add_one (l: bool list) : bool list =
	match l with
	| [] -> [true]
	| false::q -> true::q
	| true::q -> false::(add_one q)	

(* Renvoie la prochaine valuation à tester *)
let rec valuation_next (v: valuation) : valuation option =
	match v with
	| [] -> Some []
	| [(_, true)] -> None	
	| (x, y)::q when y = false -> Some ((x, true)::q)
	| (x, y)::q -> match valuation_next q with
	| None -> None
	| Some q' -> Some ((x, false)::q')

let rec valuation_init (l: string list) : valuation =
	List.map (fun x -> (x, false)) l

let satsolver_naif (f: formule) : sat_result =
	let var_l = list_var_from_arn (var_arn f) in
	let valo = valuation_init var_l in
	let rec satsolver_aux (f: formule) (v: valuation) : sat_result =
		if evaluate f v then Some v else 
		match valuation_next v with
		| None -> None
		| Some v' -> satsolver_aux f v'
	in satsolver_aux f valo

let test () = 
	test_parse ();
	test_from_file ();
	test_compte_ops ();
	print_string "Tous les tests ont réussi\n"

(* let main () =
	if Array.length Sys.argv <> 2 then
		raise (Not_enough_arguments "il faut un argument")
	else
		match Sys.argv.(1) with
		| "test" -> test ()
		| file -> print_string (read_file file) ; print_newline () *)

(* affiche seuleument les variable dont la valuation est true *)
let rec print_true (v: valuation) : unit = 
	match v with
	| [] -> ()
	| (x, true)::q -> print_string x; print_newline (); print_true q
	| (x, false)::q -> print_true q	

let main () =
	if Array.length Sys.argv <> 2 then
		raise (Not_enough_arguments "il faut un argument")
	else
		match Sys.argv.(1) with
		(* | "test" -> test () *)
		| file ->
			let t0 = Sys.time () in
			let res = satsolver_naif (from_file file) in
			let time = Sys.time () -. t0 in
			print_string "Temps d'execution: "; print_float time; print_string "s\n";
			match res with
			| None -> print_string "La formule n'est pas satisfiable\n"
			| Some v -> print_string "La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres:\n";
				print_true v

let _ = main ()
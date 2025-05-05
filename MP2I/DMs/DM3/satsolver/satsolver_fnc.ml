open Parser
open ARN
open Dico

(* Supprime v dans l'arn de dico à la clée k *)
let del_arn (dico: ('k, 'v arn) dico) (k: 'k) (v: 'v) : ('k, 'v arn) dico =
	match get dico k with
	| None -> dico
	| Some (Some (Feuille v')) when v' = v-> del dico k
	| Some t -> set dico k (deleteARN v t)

(* Insère v dans l'arn de dico à la clée k *)
let set_arn (dico: ('k, 'v arn) dico) (k: 'k) (v: 'v) : ('k, 'v arn) dico =
	match get dico k with
	| None -> set dico k (Some (Feuille v))
	| Some t -> set dico k (insertionARN v t)

type valuation = (string * bool) list
type sat_result = valuation option

type litteral = Var of string | NotVar of string
type clause = litteral arn
type fnc = clause list

let is_litteral (f: formule) : bool =
	match f with
	| Var _ | Not(Var _) -> true
	| _ -> false

let rec is_clause (f: formule) : bool =
	match f with
	| Or(f1, f2) -> is_clause f1 && is_clause f2
	| _ -> is_litteral f

let rec is_fnc (f: formule) : bool =
	match f with
	| And(f1, f2) -> is_fnc f1 && is_fnc f2
	| _ -> is_clause f

(* convertie f en clause. Précondition: f est une clause*)
let clause_of_formule (f: formule) : clause =
	let rec clause_of_formule_insert (f: formule) (c: clause) : clause =
		match f with
		| Var x -> insertionARN (Var x) c
		| Not (Var x) -> insertionARN (NotVar x) c
		| Or(f1, f2) -> clause_of_formule_insert f1 (clause_of_formule_insert f2 c)
		| _ -> None
	in clause_of_formule_insert f None

(* convertie f en fnc. Précondition: f est sous fnc *)
let fnc_of_formule (f: formule) : fnc = 
	let rec fnc_of_formule_concat (f: formule) (f': fnc) : fnc = 
		match f with
		| And(c1, c2) -> fnc_of_formule_concat c1 (fnc_of_formule_concat c2 f')
		| c -> (clause_of_formule c)::f'
	in fnc_of_formule_concat f []

(* On stocke les variables avec un triplet de dictionaire.
le premier contentant toutes les variables est trié par nom de variable
le second contient les variables dont la valuation n'est pas certaine; trié par nombre d'occurence
(les valeurs sont des arn qui contiennent les variables de même occurence)
le dernier contient les variables dont la valuation est certaine: càd qui apparait sous
une seule forme (positive ou négatige) dans toute la formule.
(les valeurs sont des arn qui contiennent les variables de même occurence)
 *)
type all_var = (string, int*int) dico
type uncertain_var = (int, (string*bool) arn) dico
type certain_var = (int, (string*bool) arn) dico
type variables = all_var * uncertain_var * certain_var

(* Ajoute l dans d et met à jours le nombre d'occurence*)
let add_var (d: all_var) (l: litteral) : all_var =
	match l with
	| Var x -> (match get d x with
					   | None -> set d x (1, 0)
					   | Some (pos, neg) -> set d x (pos + 1, neg))
	| NotVar x -> match get d x with
					   		| None -> set d x (0, 1)
					   		| Some (pos, neg) -> set d x (pos, neg + 1)

(* Ajoute les variables de c dans d *)
let rec add_clause (c: clause) (d: all_var): all_var =
	match c with
	| None -> None
	| Some (Feuille l) -> add_var d l
	| Some (Noeud(_, _, c1, c2)) -> add_clause (Some c1) (add_clause (Some c2) d)

(* Retourne le dictionaire contenant toutes les variables en clée
et le nombre d'occurence positive / négative en clée *)
let find_var (f: fnc) : all_var = 
	let rec find_var_set (f: fnc) (d: all_var) : all_var =
		match f with
		| [] -> d
		| c::f' -> find_var_set f' (add_clause c d)
	in find_var_set f None

(* Génère les des autres dictionaires: certain / uncertain _var à partir de all_var et renvoie 
let triplet.
*)
let gen_var (d: all_var) : variables =
	let rec gen_var_aux (v: variables) : uncertain_var * certain_var = 
		let d1, d2, d3 = v in
		match d1 with
		| None -> None, None
		| Some (Feuille (x, (pos, 0))) -> d2, set_arn d3 pos (x, true)
		| Some (Feuille (x, (0, neg))) -> d2, set_arn d3 neg (x, false)
		| Some (Feuille (x, (pos, neg))) -> set_arn d2 (pos + neg) (x, pos >= neg), d3
		| Some (Noeud(_, _, v1, v2)) -> let d2', d3' = gen_var_aux ((Some v1), d2, d3) in
																		gen_var_aux ((Some v2), d2', d3')
	in let d2, d3 = gen_var_aux (d, None, None)
	in d, d2, d3

let is_pos (l: litteral) : bool =
	match l with
	| Var x -> true
	| NotVar x -> false

let str_of_lit (l: litteral) : string = 
	match l with
	| Var x | NotVar x -> x

(* supprime une occurence de l dans vars*)
let update_var_from_litteral (l: litteral) (vars: variables) : variables =
	let d1, d2, d3 = vars in
	match l with
	| Var x -> begin
			 match get d1 x with
			 | None -> vars
			 | Some (1, 0) -> del d1 x, d2, del_arn d3 1 (x, true) 
			 | Some (1, neg) -> 
			 		set d1 x (0, neg), del_arn d2 (1+neg) (x, 1 = neg), set_arn d3 neg (x, false)
			 | Some (pos, 0) -> set d1 x (pos-1, 0), d2, set_arn (del_arn d3 pos (x, true)) (pos-1) (x, true)
			 | Some (pos, neg) -> 
			 		set d1 x (pos-1, neg), set_arn (del_arn d2 (pos+neg) (x, pos >= neg)) (pos+neg-1) (x, pos-1>= neg), d3
			 end
	| NotVar x -> match get d1 x with
				 | None -> vars
				 | Some (0, 1) -> del d1 x, d2, del_arn d3 1 (x, false)
				 | Some (pos, 1) -> set d1 x (pos, 0), del_arn d2 (1+pos) (x, true), set_arn d3 pos (x, true)
				 | Some (0, neg) -> set d1 x (0, neg-1), d2, set_arn (del_arn d3 neg (x, false)) (neg-1) (x, false)
				 | Some (pos, neg) ->
				 		set d1 x (pos, neg-1), set_arn (del_arn d2 (pos+neg) (x, pos >= neg)) (pos+neg-1) (x, pos >= neg-1), d3

(* supprime une occurence de tous les littéraux de c dans vars*)
let rec update_var_from_clause (c: clause) (vars: variables) : variables =
	match c with
	| None -> vars
	| Some (Feuille l) -> update_var_from_litteral l vars
	| Some (Noeud(_, _, c1, c2)) -> 
			update_var_from_clause (Some c1) (update_var_from_clause (Some c2) vars)

(* substitue x par v dans c, simplifie f et met à jour vars et lc. Attention, si la clause est satisfaite, 
rien ne change.
*)
let subst_clause (x: string) (v: bool) (c: clause) (vars: variables) (lc: valuation) : clause * variables * valuation =
	match c, v with
	| None, _ -> None, (None, None, None), []
	| Some (Feuille (Var y)), false  when y = x -> None, (None, None, None), []
	| Some (Feuille (NotVar y)), true when y = x -> None, (None, None, None), []
	| Some (Noeud(_, _, Feuille (Var y), Feuille l)), false when y = x ->
			Some (Feuille l), update_var_from_litteral (Var x) vars, (str_of_lit l, is_pos l)::lc
	| Some (Noeud(_, _, Feuille l, Feuille (Var y))), false when y = x ->
			Some (Feuille l), update_var_from_litteral (Var x) vars, (str_of_lit l, is_pos l)::lc
	| Some (Noeud(_, _, Feuille (NotVar y), Feuille l)), true when y = x ->
			Some (Feuille l), update_var_from_litteral (NotVar x) vars, (str_of_lit l, is_pos l)::lc
	| Some (Noeud(_, _, Feuille l, Feuille (NotVar y))), true when y = x ->
			Some (Feuille l), update_var_from_litteral (NotVar x) vars, (str_of_lit l, is_pos l)::lc
	| _, false when recherche (Var x) c -> deleteARN (Var x) c, update_var_from_litteral (Var x) vars, lc
	| _, true when recherche (NotVar x) c -> deleteARN (NotVar x) c, update_var_from_litteral (NotVar x) vars, lc
	| _ -> c, vars, lc

(* substitue x par v dans f, simplifie f et met à jour vars et lc (les clauses littérals)*)
let rec subst_fnc (x: string) (v: bool) (f: fnc) (vars: variables) (lc: valuation) : fnc * variables * valuation =
	match f, v with
	| [], _ -> [], vars, lc
	| None::_, _ -> [None], (None, None, None), []
	| c::f', true when recherche (Var x) c -> subst_fnc x v f' (update_var_from_clause c vars) lc
	| c::f', false when recherche (NotVar x) c -> subst_fnc x v f' (update_var_from_clause c vars) lc
	| c::f', _ -> let c', vars', lc' = subst_clause x v c vars lc in
								if c' = None then [None], (None, None, None), []
						 		else let f'', vars'', lc'' = subst_fnc x v f' vars' lc' in
						 		(c'::f''), vars'', lc''

(* Renvoie la plus grande valeur de d *)
let rec max_dict_arn (dico: ('k, 'v arn) dico) : 'v option = 
	match dico with
	| None -> None
	| Some (Feuille (_, t)) -> max_arn t
	| Some (Noeud(_, _, _, d)) -> max_dict_arn (Some d)

(* Substitue  les variables de lc dans f*)
let rec subst_lit_clause (f: fnc) (vars: variables) (lc: valuation) (l: valuation) : fnc * variables * valuation * valuation =
	match lc with
	| [] -> f, vars, lc, l
	| (x, v)::lc' -> let f', vars', lc'' = subst_fnc x v f vars lc' in
			subst_lit_clause f' vars' lc'' ((x, v)::l)

(* Substitue les variables de certain_var dans f *)
let rec subst_certain_var (f: fnc) (vars: variables) (lc: valuation) (l: valuation): fnc * variables * valuation * valuation =
	let _, _, d = vars in
	match max_dict_arn d with
	| None -> f, vars, lc, l
	| Some (x, v) -> let f', vars', lc' = subst_fnc x v f vars lc in
	subst_certain_var f' vars' lc' ((x, v)::l)

let rec quine_fnc_aux (f: fnc) (vars: variables) (lc: valuation) (v: valuation): sat_result =
	let f', vars', lc', l = subst_lit_clause f vars lc v in
	let f'', (d1, d2, d3), lc'', l' = subst_certain_var f' vars' lc' l in
	match	f'' with
	| [] -> Some l'
	| None::_ -> None
	| _ -> match max_dict_arn d2 with
				 | None -> None
				 | Some (x, v) -> let f1, vars1, lc1 = subst_fnc x v f'' (d1, d2, d3) lc'' in
				 		match quine_fnc_aux f1 vars1 lc1 l' with
				 		| Some l1 -> Some ((x, v)::l1)
				 		| None ->  let f2, vars2, lc2 = subst_fnc x (not v) f'' (d1, d2, d3) lc'' in
				 					 match quine_fnc_aux f2 vars2 lc2 l' with
				 					 | None -> None
				 					 | Some l2 -> Some ((x, not v)::l2)

(* Retourne la liste des clauses littérals sous forme de valuation*)
let rec find_lit_clause (f: fnc) : valuation = 
	match f with
	| [] -> []
	| (Some (Feuille l))::f' -> (str_of_lit l, is_pos l)::find_lit_clause f'
	| _::f' -> find_lit_clause f'

let quine_fnc (f: formule) : sat_result = 
	if is_fnc f then
		let f' = fnc_of_formule f in
		let vars = gen_var (find_var f') in
		let lc = find_lit_clause f' in
		quine_fnc_aux f' vars lc []
	else failwith "la formule n'est pas sous fnc"

(* affiche seuleument les variable dont la valuation est true *)
let rec print_true (v: valuation) : unit = 
	match v with
	| [] -> ()
	| (x, true)::q -> print_string x; print_newline (); print_true q
	| (x, false)::q -> print_true q	

exception Not_enough_arguments of string

let main () =
	if Array.length Sys.argv <> 2 then
		raise (Not_enough_arguments "il faut un argument")
	else
		match Sys.argv.(1) with
		(* | "test" -> test () *)
		| file ->
			let f = from_file file in
			let t0 = Sys.time () in
			let res = quine_fnc f in
			let time = Sys.time () -. t0 in
			print_string "Temps d'execution: "; print_float time; print_string "s\n";
			match res with
			| None -> print_string "La formule n'est pas satisfiable\n"
			| Some v -> print_string "La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres:\n";
				print_true v


let _ = main ()	
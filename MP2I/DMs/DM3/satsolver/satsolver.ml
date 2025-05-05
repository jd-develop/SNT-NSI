open Parser
open ARN
open Dico

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
let list_var_from_arn (t: 'a arn) : 'a list =
	let rec list_arn_aux (t: 'a arn) (l: 'a list) : 'a list = 
		match t with
		| None -> l
		| Some Feuille(a) -> a::l
		| Some Noeud(_, _, g, d) -> list_arn_aux (Some g) (list_arn_aux (Some d) l)
	in list_arn_aux t []

type valuation = (string * bool) list
type sat_result = valuation option

let rec valuation_init (l: string list) : valuation =
	List.map (fun x -> (x, false)) l

(* renvoie f simplifié si possible et un booléen indiquant si la formule à été simplifiée ou non*)
let rec simpl_step (f: formule) : formule * bool =
	match f with
	| Or(Top, _) | Or(_, Top) | Not Bot -> Top, true
	| And(Bot, _) | And(_, Bot) | Not Top -> Bot, true
	| And(Top, f') | And(f', Top) | Or(f', Bot) | Or(Bot, f') | Not(Not f')-> f', true
	| Or(f1, f2) -> let (f1', x), (f2', y) = simpl_step f1, simpl_step f2 in
						 Or(f1', f2'), (x || y)
	| And(f1, f2) -> let (f1', x), (f2', y) = simpl_step f1, simpl_step f2 in
						 And(f1', f2'), (x || y)
	| Not f' -> let f2, x = simpl_step f' in Not f2, x
	| _ -> f, false 

(* Simplifie f si possible *)
let rec simpl_full (f: formule) : formule =
	let f', x = simpl_step f in
	if x then simpl_full f'
	else f

(* Simplifie f en temps linéaire*)
let rec simpl (f: formule) : formule =
  match f with
  | Not (Not f') -> simpl f'
  | Not f' -> 
      let f'' = simpl f' in
      (match f'' with
       | Top -> Bot
       | Bot -> Top
       | Not fc -> simpl fc
       | _ -> Not f'')

  | And (f1, f2) ->
      let f1' = simpl f1 in
      let f2' = simpl f2 in
      (match f1', f2' with
       | Bot, _ | _, Bot -> Bot
       | Top, f3 | f3, Top -> f3
       | _ -> And(f1', f2'))

  | Or (f1, f2) ->
      let f1' = simpl f1 in
      let f2' = simpl f2 in
      (match f1', f2' with
       | Top, _ | _, Top -> Top
       | Bot, f3 | f3, Bot -> f3
       | _ -> Or(f1', f2'))

  | _ -> f

(* Remplace v dans f par g *)
let rec subst (f: formule) (v: string) (g: formule) : formule =
	match f with
	| Var x when x = v -> g
	| Bot | Top | Var _ -> f
	| Not f' -> Not (subst f' v g)
	| Or(f1, f2) -> Or(subst f1 v g, subst f2 v g)
	| And(f1, f2) -> And(subst f1 v g, subst f2 v g)

let quine (f: formule) : sat_result =
	let rec quine_aux (f: formule) (v: string list): sat_result = 
		match f with
		| Top -> Some []
		| Bot -> None
		| _ ->
			match v with
			| [] -> quine_aux (simpl f) [] 
			| x::q -> let f' = simpl (subst f x Top) in
				match quine_aux f' q with
				| Some v' -> Some ((x, true)::v')
				| None -> let f' = simpl (subst f x Bot) in
					match quine_aux f' q with
					| None -> None
					| Some v2' -> Some ((x, false)::v2')
	in 
	let v = list_var_from_arn (var_arn f) in
	quine_aux (simpl f) v

(* Renvoie la variable dont la fréquence d'apparition dans f est la plus élevé. *)
let find_var (f: formule) : string =
	let rec find_var_aux (f: formule) (dico: (string, int) dico) (m: string*int): (string*int) * (string, int) dico =
		match f with
		| Top | Bot -> m, dico
		| Var(q) -> 
				begin
				match get dico q with
				| None when snd m < 1 -> (q, 1), set dico q 1
				| None -> m, set dico q 1 
				| Some v when snd m <= v -> (q, v+1), set dico q (v + 1)
				| Some v -> m, set dico q (v + 1)
				end
		| Not(f') -> find_var_aux f' dico m
		| And (f1, f2) | Or(f1, f2) -> let m', d' = find_var_aux f2 dico m in
			find_var_aux f1 d' m'
	in fst(fst(find_var_aux f None ("", 0)))

(* quine en utilisant find_var (lent) *)
let rec quine2 (f: formule) : sat_result =
	if f = Top then Some []
		else if f = Bot then None
		else match find_var f with
		| "" -> quine (simpl f)
		| x -> let f' = simpl (subst f x Top) in
			match quine f' with
			| Some v -> Some ((x, true)::v)
			| None -> let f'' = simpl (subst f x Bot) in
				match quine f'' with
				| None -> None
				| Some v' -> Some ((x, false)::v')

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
			let res = quine f in
			let time = Sys.time () -. t0 in
			print_string "Temps d'execution: "; print_float time; print_string "s\n";
			match res with
			| None -> print_string "La formule n'est pas satisfiable\n"
			| Some v -> print_string "La formule est satisfiable en assignant 1 aux variables suivantes et 0 aux autres:\n";
				print_true v


let _ = main ()
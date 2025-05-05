type couleur = Rouge | Noir
type ('k, 'v) noeud_arn_dico = 
	| Feuille of 'k * 'v
	| Noeud of couleur * 'k * ('k, 'v) noeud_arn_dico * ('k, 'v) noeud_arn_dico  
type ('k, 'v) dico = ('k, 'v) noeud_arn_dico option

(* Corrige t après insertion (deux neuds rouges)*)
let correctionARN_d (t: ('k, 'v) noeud_arn_dico) : ('k, 'v) noeud_arn_dico = 
	match t with
	| Noeud(Noir, z, Noeud(Rouge, y, Noeud(Rouge, x, a, b), c), d)
	| Noeud(Noir, z, Noeud(Rouge, x, a, Noeud(Rouge, y, b, c)), d) 
	| Noeud(Noir, x, a, Noeud(Rouge, z, Noeud(Rouge, y, b, c), d))
	| Noeud(Noir, x, a, Noeud(Rouge, y, b, Noeud(Rouge, z, c, d)))
	-> Noeud(Rouge, y, Noeud(Noir, x, a, b), Noeud(Noir, z, c, d))
	| _ -> t

(* insert la valeur v dans dico à la clée k et renvoie un arn relaxé*)
let rec set_relax (dico: ('k, 'v) noeud_arn_dico) (k: 'k) (v: 'v) : ('k, 'v) noeud_arn_dico =
	match dico with
	| Feuille (k', v') when k' < k -> Noeud(Rouge, k', Feuille (k', v'), Feuille (k, v))
	| Feuille (k', v') when k' = k -> Feuille (k, v)
	| Feuille (k', v') -> Noeud(Rouge, k, Feuille (k, v), Feuille (k', v'))
 	| Noeud(c, k', g, d) when k' < k -> correctionARN_d (Noeud(c, k', g, set_relax d k v))
 	| Noeud(c, k', g, d) -> correctionARN_d (Noeud(c, k', set_relax g k v, d))	

(* insert la valeur v dans dico à la clée k *)
let set (d: ('k, 'v) dico) (k: 'k) (v: 'v) : ('k, 'v) dico =
	match d with
	| None -> Some (Feuille (k, v))
	| Some dico -> let dico' = set_relax dico k v in
		match dico' with
		| Feuille _ -> Some dico'
		| Noeud(_, k', g, d) -> Some (Noeud(Noir, k', g, d))

(* Renvoie la valeur contenue dans dico à la clée k *)
let rec get (dico: ('k, 'v) dico) (k :'k) : 'v option =
	match dico with
	| None -> None
	| Some (Feuille (k', v')) when k = k' -> Some v'
	| Some (Feuille _) -> None
	| Some (Noeud(_, k', g, d)) when k' < k -> get (Some d) k
	| Some (Noeud(_, k', g, _)) -> get (Some g) k

(* même chose que correction_del_left mais pour un dictionaire*)
let correction_del_left_d (dico: ('k, 'v) noeud_arn_dico) : ('k, 'v) noeud_arn_dico * bool = 
	match dico with
	(* fils noir et petit fils rouge *)
	| Noeud(c, x, g, Noeud(Noir, y, g', Noeud(Rouge, z, d', d)))
	| Noeud(c, x, g, Noeud(Noir, z, Noeud(Rouge, y, g', d'), d))
		-> Noeud(c, y, Noeud(Noir, x, g, g'), Noeud(Noir, z, d', d)), false
	
	(* fils et petits fils noirs *)
	| Noeud(c, x, g, Noeud(Noir, y, g', d')) -> Noeud(Noir, x, g, Noeud(Rouge, y, g', d')), (c = Noir)
	
	(* fils et arrière petits fils rouge *)
	| Noeud(Noir, w, g, Noeud(Rouge, z, Noeud(Noir, y, Noeud(Rouge, x, g', g''), d'), d))
	| Noeud(Noir, w, g, Noeud(Rouge, z, Noeud(Noir, x, g', Noeud(Rouge, y, g'', d')), d))
		-> Noeud(Noir, z, Noeud(Rouge, x, Noeud(Noir, w, g, g'), Noeud(Noir, y, g'', d')), d), false

	(* fils rouge et arrière petit fils noirs *)
	| Noeud(Noir, x, g, Noeud(Rouge, z, Noeud(Noir, y, g', d'), d)) 
		-> Noeud(Noir, z, Noeud(Noir, x, g, Noeud(Rouge, y, g', d')), d), false
	| _ -> dico, false

(* t est un arbre avec un défaut de hauteur noir à droite de 1. 
Renvoie l'arbre corrigé et un booléen indiquant si la taille du nouvel arbre à changé (-1) ou non
*)
let correction_del_right_d (dico: ('k, 'v) noeud_arn_dico) : ('k, 'v) noeud_arn_dico * bool = 
	match dico with
	(* fils noir et petit fils rouge *)
	| Noeud(c, z, Noeud(Noir, y, Noeud(Rouge, x, g, g'), d'), d)
	| Noeud(c, z, Noeud(Noir, x, g, Noeud(Rouge, y, g', d')), d)
			-> Noeud(c, y, Noeud(Noir, x, g, g'), Noeud(Noir, z, d', d)), false
	
	(* fils et petits fils noirs *)
	| Noeud(c, x, Noeud(Noir, y, g', d'), d) -> Noeud(Noir, x, Noeud(Rouge, y, g', d'), d), (c = Noir)

	(* fils et arrière petits fils rouge *)
	| Noeud(Noir, z, Noeud(Rouge, w, g, Noeud(Noir, y, Noeud(Rouge, x, g', g''), d')), d) 
	| Noeud(Noir, z, Noeud(Rouge, w, g, Noeud(Noir, x, g', Noeud(Rouge, y, g'', d'))), d)
		-> Noeud(Noir, w, g, Noeud(Rouge, y, Noeud(Noir, x, g', g''), Noeud(Noir, z, d', d))), false
	
	(* fils rouge et arrière petit fils noirs *)
	| Noeud(Noir, z, Noeud(Rouge, x, g, Noeud(Noir, y, g', d')), d) -> Noeud(Noir, x, g, Noeud(Noir, z, Noeud(Rouge, y, g', d'), d)), false
	| _ -> dico, false

(* Supprime k dans dico et renvoie un arn relaxé *)
let rec del_relax (dico: ('k, 'v) noeud_arn_dico) (k: 'k) : ('k, 'v) noeud_arn_dico * bool= 
	match dico with
	| Noeud(c, y, g, Feuille (k', _)) when k' = k -> g, (c = Noir)
	| Noeud(c, y, Feuille (k', _), d) when k' = k -> d, (c = Noir)
	| Noeud(c, y, g, d) when y < k -> let d', b = del_relax d k in 
		if b then correction_del_right_d (Noeud(c, y, g, d'))
		else Noeud(c, y, g, d'), false
	| Noeud(c, y, g, d) -> let g', b = del_relax g k in 
		if b then correction_del_left_d (Noeud(c, y, g', d))
		else Noeud(c, y, g', d), false
	| _ -> dico, false

(* Supprime k dans dico *)
let del (dico: ('k, 'v) dico) (k: 'k) : ('k, 'v) dico = 
	match dico with
	| None -> None
	| Some (Feuille (k', _)) when k = k' -> None
	| Some dico' -> match fst (del_relax dico' k) with
		| Feuille (k', v) -> Some (Feuille (k', v))
		| Noeud (_, y, g, d) -> Some (Noeud (Noir, y, g, d))
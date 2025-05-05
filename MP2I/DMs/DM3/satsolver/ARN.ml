type couleur = Rouge | Noir
type 'a noeud_arn = Feuille of 'a | Noeud of couleur * 'a * 'a noeud_arn * 'a noeud_arn
type 'a arn = 'a noeud_arn option

(* Teste si t contient x *)
let rec recherche (x: 'a) (t: 'a arn) : bool = 
	match t with
	| Some (Feuille e) when x = e -> true
	| Some (Noeud(_, e, g, d)) when e < x -> recherche x (Some d) 
	| Some (Noeud(_, e, g, d)) -> recherche x (Some g)
	| _ -> false

(* Corrige t après insertion *)
let correctionARN (t: 'a noeud_arn) : 'a noeud_arn = 
	match t with
	| Noeud(Noir, z, Noeud(Rouge, y, Noeud(Rouge, x, a, b), c), d)
	| Noeud(Noir, z, Noeud(Rouge, x, a, Noeud(Rouge, y, b, c)), d) 
	| Noeud(Noir, x, a, Noeud(Rouge, z, Noeud(Rouge, y, b, c), d))
	| Noeud(Noir, x, a, Noeud(Rouge, y, b, Noeud(Rouge, z, c, d)))
	-> Noeud(Rouge, y, Noeud(Noir, x, a, b), Noeud(Noir, z, c, d))
	| _ -> t

(* insert x dans t et renvoie un arn relaxé *)
let rec insertionARNrelax (x: 'a) (t: 'a noeud_arn ) : 'a noeud_arn =
	match t with
	| Feuille e when e < x -> Noeud(Rouge, e, Feuille e, Feuille x)
	| Feuille e when e = x -> t
	| Feuille e -> Noeud(Rouge, x, Feuille x, Feuille e)
 	| Noeud(c, e, g, d) when e < x -> correctionARN (Noeud(c, e, g, insertionARNrelax x d))
 	| Noeud(c, e, g, d) -> correctionARN (Noeud(c, e, insertionARNrelax x g, d))

(* insert x dans t *)
let insertionARN (x: 'a) (t: 'a arn) : 'a arn =
	match t with
	| None -> Some (Feuille x)
	| Some t' -> match insertionARNrelax x t' with
					| Noeud(c, e, g, d) -> Some (Noeud(Noir, e, g, d))
					| Feuille e -> Some (Feuille e)	

(* t est un arbre avec un défaut de hauteur noir à gauche de 1. 
Renvoie l'arbre corrigé et un booléen indiquant si la taille du nouvel arbre à changé (-1) ou non
*)
let correction_del_left (t: 'a noeud_arn) : 'a noeud_arn * bool = 
	match t with
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
	| _ -> t, false

(* t est un arbre avec un défaut de hauteur noir à droite de 1. 
Renvoie l'arbre corrigé et un booléen indiquant si la taille du nouvel arbre à changé (-1) ou non
*)
let correction_del_right (t: 'a noeud_arn) : 'a noeud_arn * bool = 
	match t with
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
	| _ -> t, false

(* supprime x dans t et renvoie un arn relaxé *)
let rec deleteARNrelax (x: 'a) (t: 'a noeud_arn) : 'a noeud_arn * bool= 
	match t with
	| Noeud(c, y, g, Feuille z) when z = x -> g, (c = Noir)
	| Noeud(c, y, Feuille z, d) when z = x -> d, (c = Noir)
	| Noeud(c, y, g, d) when y < x -> let d', b = deleteARNrelax x d in 
		if b then correction_del_right (Noeud(c, y, g, d'))
		else Noeud(c, y, g, d'), false
	| Noeud(c, y, g, d) -> let g', b = deleteARNrelax x g in 
		if b then correction_del_left (Noeud(c, y, g', d))
		else Noeud(c, y, g', d), false
	| _ -> t, false

(* supprime x dans t *)
let deleteARN (x: 'a) (t: 'a arn) : 'a arn = 
	match t with
	| None -> None
	| Some (Feuille y) when y = x -> None
	| Some t' -> match fst (deleteARNrelax x t') with
		| Feuille y -> Some (Feuille y)
		| Noeud (_, y, g, d) -> Some (Noeud (Noir, y, g, d))

(* Renvoie le plus grand élément de t *)
let rec max_arn (t: 'a arn) : 'a option =
	match t with
	| None -> None
	| Some (Feuille x) -> Some x
	| Some (Noeud(_, _, _, d)) -> max_arn (Some d)


type 'a arbre =
    | Vide
    | Noeud of 'a * 'a arbre * 'a arbre

(* coupe une liste en deux au niveau de 'elt'. Supprime elt de la liste *)
let rec separer_liste (l: 'a list) (elt: 'a) : 'a list * 'a list = match l with
    | [] -> [], []
    | x::q -> if x = elt then [], q
              else let a, b = (separer_liste q elt) in x::a, b

(* Retrouve l’arbre correspondant aux parcours préfixe et infixe donnés *)
let rec parcours_to_arbre (prefixe: 'a list) (infixe: 'a list) : 'a arbre * 'a list =
    if infixe = [] then Vide, prefixe else
    match prefixe with
    | [] -> Vide, []
    | [x] -> Noeud (x, Vide, Vide), []
    | x::q -> let a, b = (separer_liste infixe x) in
              let g, prefixe_reste = parcours_to_arbre q a in
              let d, prefixe_reste2 = parcours_to_arbre prefixe_reste b in
              Noeud(x, g, d), prefixe_reste2


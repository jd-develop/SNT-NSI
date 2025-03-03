(* Q1 : les opérations élémentaires d’une pile sont :
    * création d’une pile vide
    * empilage d’un élément au sommet
    * dépilage de l’élément au sommet
    * vérification de si la pile est vide
 *)

type 'a pile =
    | PileVide
    | Sommet of 'a*('a pile)

(* Renvoie une pile vide *)
let creer_pile_vide () : 'a pile = PileVide

(* Empile v au sommet de p *)
let empiler (p: 'a pile) (v: 'a) : 'a pile = Sommet (v, p)

(* Dépile l’élément au sommet de p et renvoie cet élément et p sans cet élément.
 * Plante si la pile est vide
 *)
let depiler (p: 'a pile) : 'a*('a pile) = match p with
    | PileVide -> failwith "Ne peut pas dépiler une pile vide"
    | Sommet (x, q) -> (x, q)

(* Renvoie true si la pile est vide, false sinon *)
let est_vide (p: 'a pile) : bool = p = PileVide

type value =
    | Int of int
    | Float of float

(* Renvoie a+b sous forme de value *)
let add (a: value) (b: value) : value = match a, b with
    | Int n, Int m -> Int (n+m)
    | Int n, Float g -> Float ((float_of_int n) +. g)
    | Float f, Int m -> Float (f +. (float_of_int m))
    | Float f, Float g -> Float (f +. g)

(* Il n’y aura rien à modifier dans creer_pile_vide, empiler, depiler, 
   est_vide pour manipuler des values *)

(* Renvoie l’élément le plus grand parmi a et b *)
let max_val (a: value) (b: value) : value = match a, b with
    | Int n, Int m -> Int (max n m)
    | Float f, Float g -> Float (max f g)
    | Int n, Float g -> if (float_of_int n) > g then a else b
    | Float f, Int m -> if (float_of_int m) > f then b else a

(* Renvoie la plus grande somme de deux values consécutives dans p. Plante
 * i la pile est vide ou si la pile ne contient que s. *)
let rec sum_max (p: value pile) : value = match p with
    | PileVide -> failwith "La pile est vide"
    | Sommet (a, PileVide) -> failwith "La pile ne contient qu’un élément"
    | Sommet (a, Sommet(b, PileVide)) -> (add a b)
    | Sommet (a, Sommet(b, q)) -> max_val (add a b) (sum_max (Sommet (b, q)))

(* Évalue la formule postfixée f sous forme de pile de chaîne de caractères.
 * Plante si la pile est vide.
 * Renvoie la valeur de retour et le reste de la pile
 *)
let rec eval (f: string pile) : int*(string pile) = match f with
    | PileVide -> failwith "La pile est vide"
    | Sommet (s, p1) -> begin match s with
        | "+" -> let a, p2 = eval p1 in let b, p3 = eval p2 in (a+b, p3)
        | "-" -> let a, p2 = eval p1 in let b, p3 = eval p2 in (a-b, p3)
        | "*" -> let a, p2 = eval p1 in let b, p3 = eval p2 in (a*b, p3)
        | "/" -> let a, p2 = eval p1 in let b, p3 = eval p2 in
                 if b = 0 then failwith "Division par zéro"
                 else (a/b, p3)
        | _ -> int_of_string s, p1
        end
(* La fonction est en O(n) *)


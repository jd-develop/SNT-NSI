(* question 1 *)
(* renvoie la fonction f+g *)
let add_fun (f: int -> int) (g: int->int) : (int->int) =
    (fun x -> (f x) + (g x))

(* question 2 *)
(* fonction identité *)
let id (x: 'a) : 'a = x

(* applique un « non » logique au résultat de la fonction f *)
let negate (f: 'a -> bool) : ('a -> bool) = (fun x -> not (f x))

(* « inverse » l'ordre des arguments de la fonction f *)
let flip (f: 'a -> 'b -> 'c) : ('b -> 'a -> 'c) =
    (fun y x -> f x y)

(* question 3 *)
(* renvoie une fonction qui à m associe true si m divise n, false sinon *)
let divise (n: int) : (int -> bool) = (fun m -> n mod m == 0)

(* renvoie une fonction qui à m associe true si n≠m, false sinon *)
let est_different (n: int) : (int -> bool) = (fun m -> n != m)

(* renvoie le premier entier i entre a et n-1 inclus vérifiant f *)
let rec first_check (f: int -> bool) (n: int) (a: int) : int =
    if a == n then n
    else if f a then a
    else first_check f n (a+1)

(* renvoie true si n vérifie p et q, false sinon *)
let prop_and (p: int -> bool) (q: int -> bool) (n: int) : bool = (p n) && (q n)

(* renvoie true si n vérifie p ou (inclusif) q, false sinon *)
let prop_or (p: int -> bool) (q: int -> bool) (n: int) : bool = (p n) || (q n)

(* renvoie false si n vérifie p, true sinon *)
let prop_not (p: int -> bool) (n: int) : bool = not (p n)


(* question 6 *)
(* vérifie si n est premier *)
let est_premier (n: int) : bool =
    if n <= 1 then false
    else (first_check (divise n) n 2) = n

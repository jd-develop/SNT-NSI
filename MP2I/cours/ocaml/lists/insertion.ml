(* Insère un élément au bon endroit dans la liste l *)
let rec insertion (l: 'a list) (e: 'a) : 'a list = match l with
    | [] -> [e]
    | x::q -> if x >= e then e::x::q else x::(insertion q e)


(* Trie l par insertion dans l’ordre croissant *)
let rec insertion_sort (l: 'a list) : 'a list = match l with
    | [] -> []
    | x::q -> insertion (insertion_sort q) x


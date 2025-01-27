(* Renvoie le minimum de l et l moins une occurence du minimum *)
let rec minimum (l: 'a list) : 'a*'a list = match l with
    | [] -> failwith "La liste est vide"
    | x::[] -> (x, [])
    | x::q -> let m, q' = minimum q in (min x m, (max x m)::q')


(* trie l dans l’ordre croissant par sélection *)
let rec selection_sort (l: 'a list) : 'a list = match l with
    | [] -> []
    | _ -> let m, l' = minimum l in m::(selection_sort l')

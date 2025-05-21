type graphe = int list array


let g0 = [|
    [1];
    [2;3];
    [0;3];
    [];
|];;

let g1 = [|
    [1; 2];  (* voisins de A *)
    [0; 2];  (* voisins de B *)
    [0; 1];  (* voisins de C *)

    [4; 6];     (* voisins de D *)
    [3; 5; 6];  (* voisins de E *)
    [4; 6];     (* voisins de F *)
    [3; 4; 5];  (* voisins de G *)

    [8; 11];  (* voisins de H *)
    [7; 9];   (* voisins de I *)
    [8; 10];  (* voisins de J *)
    [9; 11];  (* voisins de K *)
    [7; 10];  (* voisins de L *)
|]

(* Renvoie accu + nombre d’éléments dans l *)
let rec somme_liste (accu: int) (l: int list) : int =
    match l with
    | [] -> accu
    | x::q -> somme_liste (accu+1) q


(* Renvoie le nombre d’arcs que contient g *)
let nb_arcs (g: graphe) : int =
    Array.fold_left somme_liste 0 g


(* Entrées :
 *  - g un graphe avec n sommets
 *  - 0 <= s < n indice d’un sommet de g
 *  - k un entier positif
 *  - c tableau de n entiers dont aucune case ne vaut k
 * Effet : modifie c pour écrire k dans toutes les cases correspondant aux
 * sommets de la composante connexe de s dans g
 *)
let noter_composante_source
(g: graphe) (s: int) (k: int) (c: int array) : unit =

    (* Entrées :
     *  - voisins la liste des voisins d’un certain sommet d’un graphe
     *  - k un entier positif
     *  - c tableau de n entiers dont certaintes cases peuvent valoir k
     *  - pile une pile de sommets
     * Effet : modifie c pour écrire k dans les cases correspondant aux voisins
     * et modifie pile pour empiler les voisins qui n’ont pas encore été vus
     *)
    let rec traiter_sommet
    (voisins: int list) (k: int) (c: int array) (pile: int Stack.t) : unit =
        match voisins with
        | [] -> ()
        | x::q -> begin
            if c.(x) <> k then begin
                Array.set c x k;
                Stack.push x pile
            end;
            traiter_sommet q k c pile
        end
    in

    let pile = Stack.create () in
    Stack.push s pile;
    Array.set c s k;

    while not (Stack.is_empty pile) do
        let u = Stack.pop pile in
        Array.set c u k;
        traiter_sommet g.(u) k c pile
    done


(* Renvoie un tableau C associant à chaque sommet du graphe g le numéro
 * de sa composante connexe *)
let composantes_connexes (g: graphe) : int array =
    let n = Array.length g in
    let c = Array.init n (fun _ -> 0) in
    let k = ref 1 in
    for i = 0 to n-1 do
        if c.(i) = 0 then begin
            noter_composante_source g i !k c;
            incr k;
        end
    done;
    c


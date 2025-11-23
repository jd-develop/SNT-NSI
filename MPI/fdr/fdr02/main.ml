(* Renvoie l’indice du premier 0 dans le tableau t, ou -1 si t ne contient pas
 * de 0. *)
let premier_0 (t: int array) : int =
  let n = Array.length t in
  let indice_retour = ref (-1) in
  let indice_actuel = ref 0 in
  while !indice_retour = -1 && !indice_actuel < n do
    if t.(!indice_actuel) = 0 then
      indice_retour := !indice_actuel;
    incr indice_actuel
  done;
  !indice_retour

let test_premier_0 : unit =
  assert (premier_0 [||] = -1);
  assert (premier_0 [|2; -3; 1; 2|] = -1);
  assert (premier_0 [|2; 0; 1; 2; 0|] = 1);
  assert (premier_0 [|2; -3; 1; 0|] = 3);
  assert (premier_0 [|2; -3; 1; 0; 0; 0|] = 3);
  assert (premier_0 [|0|] = 0)


(* Renvoie l’indice du premier 0 dans le tableau t, ou -1 si t ne contient pas
 * de 0. *)
let premier_0_for (t: int array) : int =
  let exception Zero of int in
  let n = Array.length t in
  try
    for i = 0 to (n-1) do
      if t.(i) = 0 then
        raise (Zero(i))
    done;
    -1
  with
  | Zero(i) -> i

let test_premier_0_for : unit =
  assert (premier_0_for [||] = -1);
  assert (premier_0_for [|2; -3; 1; 2|] = -1);
  assert (premier_0_for [|2; 0; 1; 2; 0|] = 1);
  assert (premier_0_for [|2; -3; 1; 0|] = 3);
  assert (premier_0_for [|2; -3; 1; 0; 0; 0|] = 3);
  assert (premier_0_for [|0|] = 0)


(* Renvoie l’indice du dernier 0 dans le tableau t, ou -1 si t ne contient pas
 * de 0. *)
let dernier_0 (t: int array) : int =
  let n = Array.length t in
  let indice_retour = ref (-1) in
  let indice_actuel = ref 0 in
  while !indice_actuel < n do
    if t.(!indice_actuel) = 0 then
      indice_retour := !indice_actuel;
    incr indice_actuel
  done;
  !indice_retour

let test_dernier_0 : unit =
  assert (dernier_0 [||] = -1);
  assert (dernier_0 [|2; -3; 1; 2|] = -1);
  assert (dernier_0 [|2; 0; 1; 2; 0|] = 4);
  assert (dernier_0 [|2; -3; 1; 0|] = 3);
  assert (dernier_0 [|2; -3; 1; 0; 0; 0|] = 5);
  assert (dernier_0 [|0|] = 0)


(* Renvoie true si le tableau t contient un 0, false sinon *)
let contient_0 (t: int array) : bool =
  let n = Array.length t in
  let zero_trouve = ref false in
  let indice_actuel = ref 0 in
  while (not !zero_trouve) && !indice_actuel < n do
    if t.(!indice_actuel) = 0 then
      zero_trouve := true;
    incr indice_actuel
  done;
  !zero_trouve

let test_contient_0 : unit =
  assert (contient_0 [|0|]);
  assert (contient_0 [|1; 2; 8; -1; 0; 2; 3; 0|]);
  assert (contient_0 [|0; 1; -3; 2|]);
  assert (contient_0 [|8; 0; 1; -3; 2|]);
  assert (contient_0 [|0|]);
  assert (not (contient_0 [|2; 3; -1; 9; 2|]));
  assert (not (contient_0 [|3; 24; 9; 16; 57|]));
  assert (not (contient_0 [|577|]))


(* Renvoie true si le tableau t contient un 0, false sinon *)
let contient_0_iter (t: int array) : bool =
  let exception Zero in
  try
    Array.iter (fun x -> if x = 0 then raise Zero else ()) t;
    false
  with
  | Zero -> true

let test_contient_0_iter : unit =
  assert (contient_0_iter [|0|]);
  assert (contient_0_iter [|1; 2; 8; -1; 0; 2; 3; 0|]);
  assert (contient_0_iter [|0; 1; -3; 2|]);
  assert (contient_0_iter [|8; 0; 1; -3; 2|]);
  assert (contient_0_iter [|0|]);
  assert (not (contient_0_iter [|2; 3; -1; 9; 2|]));
  assert (not (contient_0_iter [|3; 24; 9; 16; 57|]));
  assert (not (contient_0_iter [|577|]))


(* Renvoie la somme des éléments de t. Renvoie 0 si t est vide *)
let sum (t: int array) : int =
  let n = Array.length t in
  let result = ref 0 in
  for i = 0 to (n-1) do
    result := !result + t.(i)
  done;
  !result

let test_sum : unit =
  assert (sum [|6; 5; 32; -1720; 1685|] = 8);
  assert (sum [||] = 0);
  assert (sum [|1; 8; -9|] = 0);
  assert (sum [|1; 2; 3|] = 6)


(* Renvoie la somme des éléments de t. Renvoie 0 si t est vide *)
let sum_fold_left (t: int array) : int =
  Array.fold_left (+) 0 t

let test_sum_fold_left : unit =
  assert (sum_fold_left [|6; 5; 32; -1720; 1685|] = 8);
  assert (sum_fold_left [||] = 0);
  assert (sum_fold_left [|1; 8; -9|] = 0);
  assert (sum_fold_left [|1; 2; 3|] = 6)


(* Renvoie l’indice du minimum dans le tableau t. Lève l’execption
 * Invalid_argument lorsque t est vide *)
let indice_minimum (t: int array) : int =
  let n = Array.length t in
  if n = 0 then raise (Invalid_argument "indice_minimum: t est vide.");
  let min_courant = ref t.(0) in
  let indice_min = ref 0 in
  for i = 1 to (n-1) do
    if t.(i) < !min_courant then begin
      min_courant := t.(i);
      indice_min := i
    end;
  done;
  !indice_min

let test_indice_mininum : unit =
  assert (indice_minimum [|3; 7; 0; 6; -2; 4|] = 4);
  assert (
    try
      let _ = indice_minimum [||] in false
    with
    | Invalid_argument _ -> true
  );
  assert (indice_minimum [|0; 1; 7; 2|] = 0);
  assert (indice_minimum [|0; 1; 7; 2; 0|] = 0);
  assert (indice_minimum [|7|] = 0)


(* Renvoie l’indice du maximum dans le tableau t. Lève l’exception
 * Invalid_argument lorsque t est vide *)
let indice_maximum (t: int array) : int =
  let n = Array.length t in
  if n = 0 then raise (Invalid_argument "indice_maximum: t est vide");
  (* l’accumulateur est un couple (indice actuel, indice maximum, maximum) *)
  let _, idx, _ = Array.fold_left
    (fun (idx_actuel, idx_maximum, maximum: int * int * int) (elt: int) ->
      if elt > maximum then (idx_actuel+1, idx_actuel, elt)
      else (idx_actuel+1, idx_maximum, maximum))
    (0, 0, t.(0)) t
  in
  idx

let test_indice_maximum : unit =
  assert (indice_maximum [|3; 7; 0; 6; -2; 4|] = 1);
  assert (
    try
      let _ = indice_maximum [||] in false
    with
    | Invalid_argument _ -> true
  );
  assert (indice_maximum [|0; 1; 7; 2|] = 2);
  assert (indice_maximum [|7|] = 0);
  assert (indice_maximum [|0; 7; 1; 7; 2|] = 1)


(* Renvoie un tableau t', de même taille que t, contenant les sommes cumulées
 * des éléments de t, i.e. t'.(i) = t.(0) + ... + t.(i) *)
let sommes_cumulees (t: int array) : int array =
  let n = Array.length t in
  let t' = Array.make n 0 in
  let somme = ref 0 in
  for i = 0 to (n-1) do
    somme := !somme + t.(i);
    t'.(i) <- !somme
  done;
  t'

let test_sommes_cumulees : unit =
  assert (sommes_cumulees [||] = [||]);
  assert (sommes_cumulees [|1|] = [|1|]);
  assert (sommes_cumulees [|5; 2; -1; 4; 12|] = [|5; 7; 6; 10; 22|])


(* Modifie t de façon à ce qu’à la fin de l’appel, t.(i) contienne
 * i::(l’ancienne valeur de t.(i)) *)
let ajoute_indices (t: int list array) : unit =
  let n = Array.length t in
  for i = 0 to (n-1) do
    t.(i) <- i::(t.(i))
  done

let test_ajoute_indices : unit =
  let t1 = [||] in
  ajoute_indices t1;
  assert (t1 = [||]);
  let t2 = [|[]; [5; 2]; [23; 4]|] in
  ajoute_indices t2;
  assert (t2 = [|[0]; [1; 5; 2]; [2; 23; 4]|]);
  ajoute_indices t2;
  assert (t2 = [|[0; 0]; [1; 1; 5; 2]; [2; 2; 23; 4]|])


(* Renvoie le tableau t' de même taille que t tel que t'.(i) = x::t.(i) *)
let ajoute_entier (t: int list array) (x: int) : int list array =
  Array.map (fun l -> x::l) t

let test_ajoute_entier : unit =
  assert (ajoute_entier [||] 2 = [||]);
  assert (ajoute_entier [|[]|] 5 = [|[5]|]);
  assert (
    ajoute_entier [|[]; [5; 2]; [23; 4]|] 3 = [|[3]; [3; 5; 2]; [3; 23; 4]|]
  )


(* Étant donné t un tableau d’entiers à valeurs dans [|0, m-1|], renvoie
 * l’entier de [|0, m-1|] ayant le plus d’occurences dans t *)
let plus_d_occurrences (t: int array) (m: int) : int =
  (* On stocke le nombre d’occurences de chaque entier dans t' *)
  let t' = Array.make m 0 in
  Array.fold_left (fun () elt -> t'.(elt) <- t'.(elt)+1) () t;
  (* On renvoie l’entier avec le + d’occurences *)
  indice_maximum t'


let test_plus_d_occurrences : unit =
  assert (plus_d_occurrences [||] 1 = 0);
  assert (plus_d_occurrences [|100|] 120 = 100); (* ici, une approche avec des
                                                  * Hashtbl aurait sûrement été
                                                  * plus judicieuse *)
  assert (plus_d_occurrences [|7; 4; 3; 4; 5; 3; 2; 0; 2; 4|] 8 = 4)


(* Trie le tableau t par ordre croissant (modifie t) *)
let bubble_sort (t: int array) : unit =
  let n = Array.length t in
  for i = (n-1) downto 1 do
    for j = 0 to (i-1) do
      if t.(j) > t.(j+1) then begin
        let temp = t.(j+1) in
        t.(j+1) <- t.(j);
        t.(j) <- temp
      end
    done
  done

let test_bubble_sort : unit =
  let t1 = [||] in
  bubble_sort t1;
  assert (t1 = [||]);
  let t2 = [|1|] in
  bubble_sort t2;
  assert (t2 = [|1|]);
  let t3 = [|5; 9; 6; -1; 4; 6; 7; 12; 0; -25|] in
  bubble_sort t3;
  assert (t3 = [|-25; -1; 0; 4; 5; 6; 6; 7; 9; 12|])

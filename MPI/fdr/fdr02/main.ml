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


(* Renvoie l’indice du minimum dans le tableau t. Lève l’exection
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
  assert (indice_minimum [|7|] = 0)


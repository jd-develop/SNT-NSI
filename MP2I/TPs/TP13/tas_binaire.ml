#!/usr/bin/env ocaml

(* `est_tas t i` renvoie true si les i premières cases de t forment un tas *)
let est_tas (t: 'a array) (i: int) : bool =
  let est_tas = ref true in
  for j = 1 to i-1 do
    let parent = (j-1)/2 in
    if t.(parent) > t.(j) then (est_tas := false)
  done;
  !est_tas


(* échange les cases i et j du tableau t (précondition : i et j sont des indices
 * valides du tableau) *)
let echanger (t: 'a array) (i: int) (j: int) : unit =
  let c = t.(i) in
  t.(i) <- t.(j);
  t.(j) <- c


(* Renvoie l’indice du parent du nœud i dans le tas t. Précondition : i n’est
 * pas 0 *)
let parent (i: int) : int = (i-1)/2

(* Renvoie l’indice de l’enfant gauche du nœud i dans le tas t. *)
let gauche (i: int) : int = 2*i + 1

(* Renvoie l’indice de l’enfant droit du nœud i dans le tas t. *)
let droite (i: int) : int = 2*i + 2


(* Insère un élément dans le tas (t, i) *)
let inserer (t: 'a array) (i: int) (elt: 'a) : unit =
  t.(i) <- elt;

  if i = 0 then ()
  else begin
    let f = ref i in
    let p = ref (parent i) in
    while !f <> 0 && t.(!f) < t.(!p) do
      echanger t !f !p;
      f := !p;
      p := parent !f;
    done
  end

(*
 * Transforme le tableau t en tas (en le modifiant)
 *)
let tasifier (t: 'a array) : unit =
  let n = Array.length t in
  for i = 0 to n-1 do
    inserer t i (t.(i))
  done


(* `est_bien_place t i j` renvoie true si le nœud d’indice j dans le tas
 * (t, i) est plus petit que son ou ses enfants *)
let est_bien_place (t: 'a array) (i: int) (j: int) : bool =
  let g = gauche j in
  let d = droite j in
  let x = t.(j) in
  (g >= i || x < t.(g) && d >= i || x < t.(d))
  (* TODO tester *)


let test () =
  assert (est_tas [|2; 5; 3; 6; 10; 9|] 6);
  assert (est_tas [|2; 2; 3; 6; 10; 9|] 6);
  assert (not (est_tas [|2; 5; 3; 6; 10; 2|] 6));
  assert (est_tas [|2; 5; 3; 6; 10; 2|] 5);
  assert (est_tas [||] 0);
  assert (est_tas [|1|] 0);
  assert (est_tas [|1|] 1);
  let t = [|2; 5; 3; 6; 10; 9; 0; 0; 0; 0|] in
  inserer t 6 1;
  assert (t = [|1; 5; 2; 6; 10; 9; 3; 0; 0; 0|]);
  let t2 = [|7; 1; 2; 0; 90; 12; 234567|] in
  tasifier t2;
  assert (est_tas t2 7)


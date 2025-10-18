#!/usr/bin/env ocaml

type graphe = int list array

let g0: graphe =
  [|
    [1; 2; 3]; (* 0 *)
    [4];       (* 1 *)
    [];        (* 2 *)
    [];        (* 3 *)
    [5];       (* 4 *)
    []         (* 5 *)
  |]

let g1: graphe =
  [|
    [1; 2; 3]; (* 0 ou a*)
    [4];       (* 1 ou b*)
    [3; 4];    (* 2 ou c*)
    [5];       (* 3 ou d*)
    [5];       (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g2: graphe =
  [|
    [1];       (* 0 ou a*)
    [2; 4];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [];        (* 3 ou d*)
    [0];       (* 4 ou e*)
    [3]        (* 5 ou f*)
  |]

let g3: graphe =
  [|
    [1; 4];    (* 0 ou a*)
    [5; 6];    (* 1 ou b*)
    [1];       (* 2 ou c*)
    [0];       (* 3 ou d*)
    [3; 5];    (* 4 ou e*)
    [6];       (* 5 ou f*)
    [2; 7];    (* 6 ou g*)
    [2]        (* 7 ou h*)
  |]

let g4: graphe =
  [|
    [5];       (* 0 ou a*)
    [0; 2];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [1];       (* 3 ou d*)
    [0; 3];    (* 4 ou e*)
    [4]        (* 5 ou f*)
  |]

let g5: graphe =
  [|
    [2; 3];    (* 0 ou a*)
    [0];       (* 1 ou b*)
    [5];       (* 2 ou c*)
    [2; 4];    (* 3 ou d*)
    [];        (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g6: graphe =
  [|
    [];        (* 0 *)
    [0; 2];    (* 1 *)
    [1; 3];    (* 2 *)
    [4];       (* 3 *)
    [2];       (* 4 *)
    [3];       (* 5 *)
    [4; 7];    (* 6 *)
    [5; 6];    (* 7 *)
  |]


let largeur (g: graphe) : 'a list =
  let n = Array.length g in
  let file = Queue.create () in
  let result = ref [] in
  let deja_vus = Array.make n false in

  let exploration () =
    while not (Queue.is_empty file) do
      let u = Queue.pop file in
      if deja_vus.(u) then ()
      else begin
        deja_vus.(u) <- true;
        result := u::!result;
        List.iter (fun x -> Queue.add x file) g.(u)
      end
    done
  in

  for i = 0 to n-1 do
    Queue.add i file;
    exploration ()
  done;
  List.rev !result


let test_largeur : unit =
  assert (largeur g0 = [0; 1; 2; 3; 4; 5]);
  assert (largeur g1 = [0; 1; 2; 3; 4; 5]);
  assert (largeur g2 = [0; 1; 2; 4; 3; 5]);
  assert (largeur g3 = [0; 1; 4; 5; 6; 3; 2; 7]);
  assert (largeur g4 = [0; 5; 4; 3; 1; 2]);
  assert (largeur g5 = [0; 2; 3; 5; 4; 1]);
  assert (largeur g6 = [0; 1; 2; 3; 4; 5; 6; 7])


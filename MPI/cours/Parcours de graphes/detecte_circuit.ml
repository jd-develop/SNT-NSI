type graphe =  (* graphes par table de listes de successeurs *)
  int list array

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

let g5 =
  [|
    [2; 3];    (* 0 ou a*)
    [0];       (* 1 ou b*)
    [5];       (* 2 ou c*)
    [2; 4];    (* 3 ou d*)
    [];        (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g6 =
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


type etat =
  | NonVu
  | Ouvert
  | Ferme


let detecte_circuit (g: graphe) : bool =
  let n = Array.length(g) in
  let etats = Array.make n NonVu in
  let circuit = ref false in
  let rec explore_depuis (profondeur: int) (s: int) : unit =
    if etats.(s) = Ferme then ()
    else if etats.(s) = Ouvert then begin
      circuit := true
    end
    else begin
      etats.(s) <- Ouvert;
      List.iter (explore_depuis (profondeur+1)) g.(s) ;
      etats.(s) <- Ferme;
    end
  in
  for s = 0 to n - 1 do
    if not !circuit then
      explore_depuis 0 s;
  done;
  !circuit


let test_detecte_circuit : unit =
  assert (not (detecte_circuit g0));
  assert (not (detecte_circuit g1));
  assert (detecte_circuit g2);
  assert (detecte_circuit g3);
  assert (detecte_circuit g4);
  assert (not (detecte_circuit g5));
  assert (detecte_circuit g6)

#!/usr/bin/env ocaml

let naif (u: string) (v: string) =
  let n = String.length u in
  let m = String.length v in
  let tableau = (Array.make_matrix (n+1) (m+1) 0) in

  let max = ref 0 in
  for i = 1 to n do
    for j = 1 to m do
      if u.[i-1] = v.[j-1] then begin
        tableau.(i).(j) <- 1 + tableau.(i-1).(j-1);
        if tableau.(i).(j) > !max then
          max := tableau.(i).(j)
        end
      else
        tableau.(i).(j) <- 0
    done
  done;
  !max


let pas_naif (u: string) (v: string) =
  let n = String.length u in
  let m = String.length v in
  let ij_from_diago_indice (diago_indice: int) : (int*int) =
    if diago_indice <= n then (n-diago_indice, 0)
    else (0, diago_indice-n)
  in
  let rec diagonales (max_courant: int) (diago_indice: int) : int =
    if diago_indice > n+m then max_courant else
    let rec diagonale (max_courant: int) (derniere_valeur: int) (ij: int * int) =
      let i, j = fst ij, snd ij in
      if i = 0 || j = 0 then diagonale max_courant 0 (i+1, j+1) else
      if i > n || j > m then max_courant else begin
        if u.[i-1] = v.[j-1] then
          diagonale (max max_courant (1+derniere_valeur)) (1+derniere_valeur) (i+1, j+1)
        else
          diagonale max_courant 0 (i+1, j+1)
      end
    in
    let ij = ij_from_diago_indice diago_indice in
    let new_potential_max = diagonale max_courant 0 ij in
    diagonales (max new_potential_max max_courant) (diago_indice+1)

  in diagonales 0 0


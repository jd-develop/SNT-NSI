(* ========================================================================== *)
(*                            Début du code fourni                            *)
(* ========================================================================== *)

(* Définition d'un type représentant les automates déterministes complets *)
type automate_d = {
  init  : int;                  (* l'état initial *)
  trans : int array array;      (* la table des transitions *)
  fin   : int list              (* la liste des états finaux *)
}

(* Automate exemple de l'énoncé *)
let auto_1 = {
  init = 0;
  trans =
    (*  | a | b | c | d | e |*)
    [| [| 1 ; 0 ; 0 ; 4 ; 4 |]; (* état 0 *)
       [| 2 ; 4 ; 4 ; 1 ; 4 |]; (* état 1 *)
       [| 3 ; 2 ; 2 ; 4 ; 4 |]; (* état 2 *)
       [| 0 ; 4 ; 4 ; 4 ; 3 |]; (* état 3 *)
       [| 4 ; 4 ; 4 ; 4 ; 4 |]; (* état 4 *)
    |];
  fin = [2]
}

(* Définition d'un type représentant les automates déterministes complets *)
type automate_nd = {
  init  : int list;             (* les états initiaux *)
  trans : int list array array; (* la table des transitions *)
  fin   : int list              (* les états finaux *)
}

(* Automate exemple de l'énoncé *)
let auto_2 = {
  init = [0];
  trans =
(* lettres |   a   |   b   |   c   |*)
       [| [| [0; 1]; [0]   ; [3]   |];    (* état 0 *)
          [| [2]   ; [2]   ; [3]   |];    (* état 1 *)
          [| []    ; []    ; [3]   |];    (* état 2 *)
          [| [3]   ; [3]   ; [3]   |]     (* état 3 *)
       |];
  fin = [2; 3]
}

(* Définition d'un automate permettant de tester l'algorithme de déterminisation *)
let test_deter = {
  init = [0];
  trans =
(* lettres | a  | b      |*)
       [| [| [0]; [0; 1] |];    (* état 0 *)
          [| [2]; [2]    |];    (* état 1 *)
          [| [3]; [3]    |];    (* état 2 *)
          [| [] ; []     |]     (* état 3 *)
    |];
  fin = [3]
}

(* ========================================================================== *)
(*                             Fin du code fourni                             *)
(* ========================================================================== *)

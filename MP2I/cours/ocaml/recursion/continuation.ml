#!/usr/bin/env ocaml

(* Programmation par continuation ou CPS pour Continuation Passing Style *)

let rec mult_non_cps (x: int) (y: int) =
    if x = 0 then 0
    else mult_non_cps (x-1) y + y

(* Renvoie k(x*y) *)
let rec mult_cont (x: int) (y: int) (k: int->int) =
    (* mult x y k = k(x*y)
                  = k((x-1)×y + y)
                  = (r |-> k(r+y))((x-1)×y)
                  = mult (x-1) y (k')
     *)
    if x = 0 then k 0 else
    mult_cont (x-1) y (fun r -> k (r+y))


let mult x y = mult_cont x y (fun r -> r)

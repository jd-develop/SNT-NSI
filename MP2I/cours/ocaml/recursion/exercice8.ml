#!/usr/bin/env ocaml

type expr =
    | Int of int
    | Plus of expr * expr

let rec eval_non_cps (e: expr) : int = match e with
    | Int n -> n
    | Plus (e1, e2) -> eval_non_cps e1 + eval_non_cps e2


let rec eval_cont ((e, k): expr*(int->int)) : int = match e with
    | Int n -> k n
    | Plus (e1, e2) ->
        (*
            k(eval e) = k(eval e1 + eval e2)
                      = (r -> k(r+eval e2))(eval e1)
                      = eval_cont e1 (r -> k(r+eval e2))
                      = (s -> eval_cont e1 (r -> k(r+s)))(eval e2)
                      = eval_cont e2 (s -> eval_cont e1 (r -> k(r+s)))
         *)
        eval_cont (e2, (fun s -> eval_cont (e1, (fun r -> k (r+s)))))


let eval e = eval_cont (e, (fun x -> x))


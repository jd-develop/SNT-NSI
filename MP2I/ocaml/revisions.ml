#!/usr/bin/env ocaml

let rec length (l: 'a list) : int =
    let rec length_accu (l: 'a list) (r: int) : int = match l with
        | [] -> r
        | x::q -> (length_accu q r+1)
    in length_accu l 0

let rec mem (elt: 'a) (l: 'a list) : bool = match l with
    | [] -> false
    | x::q -> if elt = x then true else (mem elt q)

let rec map (f: 'a -> 'b) (l: 'a list) : 'b list = match l with
    | [] -> []
    | x::q -> (f x)::(map f q)

let rev (l: 'a list) : 'a list =
    let rec rev_accu (l: 'a list) (accu: 'a list) : 'a list = match l with
        | [] -> accu
        | x::q -> rev_accu q (x::accu)
    in rev_accu l []

let init (len: int) (f: int -> 'a) : 'a list =
    let rec init_with_total_len
            (len: int) (f: int -> 'a) (total_len: int) : 'a list =
        if len = 0 then []
        else (f (total_len-len))::(init_with_total_len (len-1) f total_len)
    in init_with_total_len len f len

let rec fold_left (f: 'b -> 'a -> 'b) (init: 'b) (l: 'a list) : 'b =
    match l with
    | [] -> failwith "La liste ne doit pas être vide"
    | [x] -> f init x
    | x::q -> fold_left f (f init x) q

let rec fold_right (f: 'a -> 'b -> 'b) (l: 'a list) (init: 'b) : 'b =
    match l with
    | [] -> failwith "La liste ne doit pas être vide"
    | [x] -> f x init
    | x::q -> f x (fold_right f q init)

#!/usr/bin/env ocaml

let rec puiss x n =
    if n < 0 then failwith "Puissance à un entier négatif"
    else if n = 0 then 1.
    else x *. puiss (x) (n-1)


let rec reste a b =
    if a < 0 then failwith "Le dividande doit être positif"
    else if b <= 0 then failwith "Le diviseur doit être strictement positif"
    else if a < b then a
    else reste (a-b) b


let rec pgcd a b =
    if a < 0 then failwith "a doit être positif"
    else if b <= 0 then failwith "b doit être strictement positif"
    else if reste a b = 0 then b
    else pgcd b (reste a b)


let rec puiss_rapide x n =
    if n < 0 then failwith "Puissance à un entier négatif"
    else if n = 0 then 1.
    else if n = 1 then x
    else if n mod 2 = 0 then puiss_rapide (x*.x) (n/2)
    else x *. puiss_rapide (x*.x) (n/2)


let rec div_euclid a b =
    if a < 0 then failwith "Le dividande doit être positif"
    else if b <= 0 then failwith "Le diviseur doit être strictement positif"
    else if a < b then (0, a)
    else let (c, d) = div_euclid (a-b) b in (c+1, d)

let rec decomp b x =
    if b < 1 then failwith "La base doit être supérieure ou égale à 1"
    else if x < b then print_int x
    else (decomp b (x/b) ; print_int (reste x b))


let rec a_racine f =
    let rec teste_racines n = (if f n = 0 || f (-n) = 0 then true else teste_racines (n+1)) in
    teste_racines 0


#!/usr/bin/env ocaml

let max x y =
    if x < y then y
    else x


let rec factorielle n =
    if n = 0 || n = 1 then 1
    else n * factorielle (n-1)


let rec exp a b =
    if b = 0 then 1
    else if b = 1 then a
    else if (b mod 2) = 1 then a * (exp (a*a) (b/2))
    else (exp (a*a) (b/2))


#!/usr/bin/env ocaml

let double a = a*2

let first (a, b) = a
let second (a, b) = b

let somme3 (a, b, c) = a +. b +. c

let est_pair n = n mod 2 = 0

let divise a b = b mod a = 0

let ajouteur k = (fun a -> a+k)

let est_racine f x = f x = 0

let id x = x

let composee f g = (fun a -> f (g a))

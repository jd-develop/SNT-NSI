#!/usr/bin/ocaml

let print_pair n = match n mod 2 with
    | 0 -> print_int n ; print_newline ()
    | _ -> ();;

let print_pairs (a, b, c) = print_pair a; print_pair b; print_pair c

let print_retour s = print_string s; print_newline ();;

print_retour "Hello, world!";;

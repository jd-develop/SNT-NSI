#!/usr/bin/env ocaml

(*** Partie I : Gestion d’exceptions ***)

(* Renvoie true si aucune erreur d’assertion n’est levée, false sinon *)
let valider (f: unit -> unit) : bool =
  try (f (); true) with
  | Assert_failure _ -> false


let test_valider () =
  let test1 () = assert (1=1) in
  let test2 () = assert (1=2) in
  assert (valider test1);
  assert (not (valider test2))


(*** Partie II : Arbres binaires de recherche ***)
type 'a arbre =
  | V
  | N of 'a arbre * 'a * 'a arbre


(* Recherche x dans l’arbre a. Renvoie true si x est dans a, false sinon,
 * à condition que a soit un arbre binaire de recherche
 *)
let rec recherche (x: 'a) (a: 'a arbre) : bool = match a with
  | V -> false
  | N(g, e, d) -> if x=e then true else (recherche x g) || (recherche x d)


let test_recherche () =
  assert (not (recherche 1 V));
  assert (recherche 1 (N(V, 1, V)));
  assert (not (recherche 1 (N(V, 2, V))));
  assert (recherche 1 (N(N(V, 1, V), 3, N(V, 5, V))));
  assert (recherche 3 (N(N(V, 1, V), 3, N(V, 5, V))));
  assert (recherche 5 (N(N(V, 1, V), 3, N(V, 5, V))));
  assert (not (recherche (-1) (N(N(V, 1, V), 3, N(V, 5, V)))));
  assert (not (recherche 2 (N(N(V, 1, V), 3, N(V, 5, V)))));
  assert (not (recherche 4 (N(N(V, 1, V), 3, N(V, 5, V)))));
  assert (not (recherche 7 (N(N(V, 1, V), 3, N(V, 5, V)))))


(* Ajoute x à l’arbre a et renvoie le résultat, à condition que a soit
 * un arbre binaire de recherche. Renvoie un arbre binaire de recherche.
 *)
let rec ajoute (x: 'a) (a: 'a arbre) : 'a arbre = match a with
  | V -> N(V, x, V)
  | N(g, y, d) -> if x = y then a
                  else if x < y then N((ajoute x g), y, d)
                  else N(g, y, (ajoute x d))


let test_ajoute () =
  assert (ajoute 1 V = N(V, 1, V));
  assert (ajoute 1 (N(V, 1, V)) = N(V, 1, V));
  assert (ajoute 2 (N(V, 1, V)) = N(V, 1, N(V, 2, V)));
  assert (ajoute 0 (N(V, 1, V)) = N(N(V, 0, V), 1, V))


(* Renvoie l’élément maximum m de l’arbre a ainsi que l’arbre a duquel cet
 * élément m a été retiré, à condition que a soit un arbre binaire de recherche
 * non vide.
 *)
let rec extraire_max (a: 'a arbre) : 'a * 'a arbre = match a with
  | V -> failwith "L’arbre dans extraire_max est vide"
  | N(g, x, V) -> (x, g)
  | N(g, x, d) -> let m, a' = extraire_max d in (m, N(g, x, a'))


let test_extraire_max () =
  assert (extraire_max (N(V, 1, V)) = (1, V));
  assert (extraire_max (N(N(V, 0, V), 1, V)) = (1, N(V, 0, V)));
  assert (extraire_max (N(N(V, 0, V), 1, N(V, 2, V))) = (2, N(N(V, 0, V), 1, V)));
  assert (extraire_max
    (N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V)))))
    = (72, N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(V, 42, N(V, 50, V))))))
  )


(* `supprime x a` renvoie un arbre binaire de recherche contenant les
 * élémets de a sauf x. Si x n’est pas un élément de `a`, lève une erreur
 * Failure.
 * Précondition : `a` doit être un arbre binaire de recherche.
 *)
let rec supprimer (x: int) (a: int arbre) : int arbre = match a with
  | V -> (failwith ("L’arbre dans `supprimer` ne contient pas "^(string_of_int x)))
  | N(g, e, d) ->
      if x=e then
        if g = V then d else
        let m, g' = extraire_max g in N(g', m, d)
      else if x<e then N(supprimer x g, e, d)
      else N(g, e, supprimer x d)


let test_supprimer () =
  assert (supprimer 1 (N(V, 1, V)) = V);
  assert (supprimer 1 (N(N(V, 0, V), 1, V)) = N(V, 0, V));
  assert (supprimer 0 (N(N(V, 0, V), 1, V)) = N(V, 1, V));
  assert (supprimer 0 (N(N(V, 0, V), 1, N(V, 2, V))) = N(V, 1, N(V, 2, V)));
  assert (supprimer 1 (N(N(V, 0, V), 1, N(V, 2, V))) = N(V, 0, N(V, 2, V)));
  assert (supprimer 2 (N(N(V, 0, V), 1, N(V, 2, V))) = N(N(V, 0, V), 1, V));
  assert (supprimer 1
    (N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V)))))
    = N(V, 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V))))
  );
  assert (supprimer 2
    (N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V)))))
    = N(V, 1, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V))))
  );
  assert (supprimer 5
    (N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V)))))
    = N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(N(V, 42, N(V, 50, V)), 72, V)))
  );
  assert (supprimer 42
    (N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 42, N(V, 50, V)), 72, V)))))
    = N(N(V, 1, V), 2, N(N(V, 3, V), 4, N(V, 5, N(N(V, 50, V), 72, V))))
  )


let rec a (n: int) =
  if n = 0 then V
  else ajoute n (a (n-1))


let time_a (n: int) : float =
  let time_start = Sys.time () in
  let _ = a n in
  Sys.time () -. time_start


let test () =
  test_valider ();
  test_recherche ();
  test_ajoute ();
  test_extraire_max ();
  test_supprimer ();


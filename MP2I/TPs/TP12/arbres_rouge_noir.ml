#!/usr/bin/env ocaml

type couleur = Rouge | Noir

type 'a n_arn =
  | Feuille of 'a
  | N of couleur * 'a * 'a n_arn * 'a n_arn

type 'a arn = 'a n_arn option (* None représente l’arbre vide *)


(* Renvoie la couleur de la racine de a (Noir si a est une feuille) *)
let couleur_racine (a: 'a n_arn) : couleur = match a with
  | Feuille _ -> Noir
  | N(c, _, _, _) -> c


let test_couleur_racine () =
  assert (couleur_racine (Feuille 1) = Noir);
  assert (couleur_racine (N(Rouge, 1, Feuille 0, Feuille 3)) = Rouge);
  assert (couleur_racine (N(Noir, 1, Feuille 0, Feuille 3)) = Noir)


(* Renvoie true si a (arbre rouge-noir relaxé) contient deux nœuds rouges
 * succesifs
 *)
let rec contient_deux_noeuds_rouges (a: 'a n_arn) : bool = match a with
  | Feuille _ -> false
  | N(Noir, _, g, d) -> contient_deux_noeuds_rouges g || contient_deux_noeuds_rouges d
  | N(Rouge, _, g, d) ->
      couleur_racine g = Rouge || couleur_racine d = Rouge ||
      contient_deux_noeuds_rouges g || contient_deux_noeuds_rouges d


let test_contient_deux_noeuds_rouges () =
  assert (not (contient_deux_noeuds_rouges (Feuille 3)));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, Feuille 3, Feuille 4))));
  assert (not (contient_deux_noeuds_rouges (N(Rouge, 3, Feuille 3, Feuille 4))));
  assert (not (contient_deux_noeuds_rouges (N(Rouge, 3, N(Noir, 2, Feuille 2, Feuille 3), Feuille 4))));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, N(Noir, 2, Feuille 2, Feuille 3), Feuille 4))));
  assert (contient_deux_noeuds_rouges (N(Rouge, 3, N(Rouge, 2, Feuille 2, Feuille 3), Feuille 4)));
  assert (contient_deux_noeuds_rouges (N(Rouge, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6))));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, Feuille 3, N(Rouge, 5, Feuille 4, Feuille 6)))));
  assert (not (contient_deux_noeuds_rouges (N(Noir, 3, Feuille 3, N(Noir, 5, Feuille 4, Feuille 6)))));
  assert (not (contient_deux_noeuds_rouges (N(Rouge, 3, Feuille 3, N(Noir, 5, Feuille 4, Feuille 6)))))


let test () =
  test_couleur_racine ();
  test_contient_deux_noeuds_rouges ()

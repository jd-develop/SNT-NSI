type 'a ab =
  | VideB
  | NdB of 'a * ('a ab) * ('a ab)

type 'a arbre_g =
  | Vide
  | Nd of 'a * ('a arbre_g) list


let a5 = Nd(1, [Nd(2, [Nd(4, [Vide]);
                       Nd(5, [Nd(7, [Vide]); Nd(8, [Vide])]);
                       Nd(6, [Nd(9, [Vide])])]) ;
                Nd(3, [Vide]) ])


(* Question 2&3 *)
(* Affiche les étiquettes des nœuds de a selon un parcours préfixe *)
let rec affiche_arbre_g_prefixe (a: int arbre_g) : unit =
  match a with
  | Vide -> ()
  | Nd (x, l) ->
      print_int x;
      print_string " ";
      List.iter affiche_arbre_g_prefixe l

(* appelé par executer_les_tests_supplementaires *)
let test_affiche_arbre_g_prefixe () : unit =
  print_endline "affiche_arbre_g_prefixe :";
  print_endline "Affichage attendu : 1 2 4 5 7 8 6 9 3";
  print_string  "Affichage obtenu  : ";
  affiche_arbre_g_prefixe a5;
  print_newline ()


(* Ancienne version de la fonction :
(* Affiche les étiquettes de a niveau par niveau de gauche à droite. *)
let affiche_arbre_g_niveau_rt (a: int arbre_g) : unit =
  (* Affiche les étiquettes des arbres de en_cours_de_traitement une par une,
   * en ajoutant au fur et à mesure la liste des sous-arbres de chaque arbre de
   * en_cours_de_traitement au début de a_traiter. Une fois avoir terminé, copie
   * le dernier élément de a_trier dans en_cours_de_traitement, et continue
   * jusqu’à avoir terminé. *)
  (* On peut noter que a_traiter est une file, car c’est une structure premier-
   * entré-premier-sorti : on implémente donc un parcours en largeur *)
  let rec affiche_arbres_g_niveau_rt
      (en_cours_de_traitement: int arbre_g list)
      (a_traiter: int arbre_g list list) : unit =
    match en_cours_de_traitement with
    | [] ->
        begin match List.rev a_traiter with
        | [] -> ()
        | l::q -> affiche_arbres_g_niveau_rt l (List.rev q)
        end
    | Vide::q -> affiche_arbres_g_niveau_rt q a_traiter
    | Nd(n, l')::q ->
        print_int n;
        print_string " ";
        affiche_arbres_g_niveau_rt q (l'::a_traiter)
  in
  affiche_arbres_g_niveau_rt [a] []
*)

(* Affiche les étiquettes de a niveau par niveau de gauche à droite. *)
let affiche_arbre_g_niveau_rt (a: int arbre_g) : unit =
  (* Affiche les étiquettes de chaque arbre de en_cours_de_traitement en
   * ajoutant (à l’envers) ses enfants au début de a_traiter. Lorsque
   * en_cours_de_traitement est vide, recopie a_traiter à l’envers dans
   * en_cours_de_traitement et laisse a_traiter vide. *)
  let rec affiche_arbres_g_niveau_rt
      (en_cours_de_traitement: int arbre_g list)
      (a_traiter: int arbre_g list) : unit =
    match en_cours_de_traitement with
    | [] ->
        begin match List.rev a_traiter with
        | [] -> ()
        | l -> affiche_arbres_g_niveau_rt l []
        end
    | Vide::q -> affiche_arbres_g_niveau_rt q a_traiter
    | Nd(n, l')::q ->
        print_int n;
        print_string " ";
        affiche_arbres_g_niveau_rt q (List.rev_append l' a_traiter)
  in
  affiche_arbres_g_niveau_rt [a] []

(* appelé par executer_les_tests_supplementaires *)
let test_affiche_arbre_g_niveau_rt () : unit =
  print_endline "affiche_arbre_g_niveau_rt :";
  print_endline "Affichage attendu : 1 2 3 4 5 6 7 8 9";
  print_string  "Affichage obtenu  : ";
  affiche_arbre_g_niveau_rt a5;
  print_newline ()


let executer_les_tests_supplementaires () : unit =
  test_affiche_arbre_g_prefixe ();
  test_affiche_arbre_g_niveau_rt ()

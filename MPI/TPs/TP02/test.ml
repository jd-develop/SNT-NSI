
(* Empile chaque élément de la liste l sur p. Les éléments seront dans l’ordre
 * inverse sur p (le dernier élément de l sera premier sur p, etc.) *)
let rec vider_liste_dans_pile (l: 'a list) (p: 'a Stack.t) : unit =
  match l with
  | [] -> ()
  | x::q ->
      Stack.push x p;
      vider_liste_dans_pile q p
      vider_liste_dans_pile (List.rev g.(courant)) pile


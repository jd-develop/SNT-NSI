
type graphe = (* graphes par table de listes de successeurs *)
  int list array


let g0: graphe =
  [|
    [1; 2; 3]; (* 0 *)
    [4];       (* 1 *)
    [];        (* 2 *)
    [];        (* 3 *)
    [5];       (* 4 *)
    []         (* 5 *)
  |]

let g1: graphe =
  [|
    [1; 2; 3]; (* 0 ou a*)
    [4];       (* 1 ou b*)
    [3; 4];    (* 2 ou c*)
    [5];       (* 3 ou d*)
    [5];       (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g2: graphe =
  [|
    [1];       (* 0 ou a*)
    [2; 4];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [];        (* 3 ou d*)
    [0];       (* 4 ou e*)
    [3]        (* 5 ou f*)
  |]

let g3: graphe =
  [|
    [1; 4];    (* 0 ou a*)
    [5; 6];    (* 1 ou b*)
    [1];       (* 2 ou c*)
    [0];       (* 3 ou d*)
    [3; 5];    (* 4 ou e*)
    [6];       (* 5 ou f*)
    [2; 7];    (* 6 ou g*)
    [2]        (* 7 ou h*)
  |]

let g4: graphe =
  [|
    [5];       (* 0 ou a*)
    [0; 2];    (* 1 ou b*)
    [3];       (* 2 ou c*)
    [1];       (* 3 ou d*)
    [0; 3];    (* 4 ou e*)
    [4]        (* 5 ou f*)
  |]

let g5 =
  [|
    [2; 3];    (* 0 ou a*)
    [0];       (* 1 ou b*)
    [5];       (* 2 ou c*)
    [2; 4];    (* 3 ou d*)
    [];        (* 4 ou e*)
    []         (* 5 ou f*)
  |]


let g6 =
  [|
    [];        (* 0 *)
    [0; 2];    (* 1 *)
    [1; 3];    (* 2 *)
    [4];       (* 3 *)
    [2];       (* 4 *)
    [3];       (* 5 *)
    [4; 7];    (* 6 *)
    [5; 6];    (* 7 *)
  |]


(* Question 2 *)
(* Affiche les sommets du graphe g dans un ordre de parcours en profondeur. On
 * suppose que tous les sommets sont accessibles depuis le sommet 0 *)
let imprime_parcours_profondeur_2 (g: graphe) : unit =
  let n = Array.length g in
  let deja_faits: bool array = Array.make n false in
  (* Effectue un parcours en profondeur depuis le sommet `sommet`, sauf si
   * ce dernier a déjà été visité (i.e. est dans deja_faits) *)
  let rec explore_depuis (sommet: int) : unit =
    if deja_faits.(sommet) then
      ()
    else begin
      print_int sommet;
      print_string " ";
      deja_faits.(sommet) <- true;
      List.iter explore_depuis g.(sommet)
    end
  in
  explore_depuis 0


(* Question 5 *)
(* Affiche chaque étiquette du graphe g dans l’ordre du parcours en profondeur.
 *)
let imprime_parcours_profondeur_4 (g: graphe) : unit =
  let n = Array.length g in
  let deja_faits: bool array = Array.make n false in
  let pile: int Stack.t = Stack.create () in

  for i = 0 to n-1 do
    if deja_faits.(i) then
      ()
    else
      Stack.push i pile;
      while not (Stack.is_empty pile) do
        let courant = Stack.pop pile in
        if deja_faits.(courant) then
          ()
        else begin
          print_int courant; print_string " ";
          deja_faits.(courant) <- true;
          List.iter (fun x -> Stack.push x pile) (List.rev g.(courant))
        end
      done
  done


(* Question 6 *)
(* Affiche chaque étiquette du graphe g dans l’ordre du parcours en largeur. *)
let imprime_parcours_largeur (g: graphe) : unit =
  let n = Array.length g in
  let deja_faits: bool array = Array.make n false in
  let file: int Queue.t = Queue.create () in

  for i = 0 to n-1 do
    if deja_faits.(i) then
      ()
    else
      Queue.push i file;
      while not (Queue.is_empty file) do
        let courant = Queue.pop file in
        if deja_faits.(courant) then
          ()
        else begin
          print_int courant; print_string " ";
          deja_faits.(courant) <- true;
          List.iter (fun x -> Queue.push x file) g.(courant)
        end
      done
  done

(* Question 7 *)
(* Renvoie la liste de chaque étiquette du graphe g dans l’ordre du parcours en
 * profondeur. *)
let liste_parcours_profondeur_imperatif (g: graphe) : int list =
  let n = Array.length g in
  let resultat: int list ref = ref [] in
  let deja_faits: bool array = Array.make n false in
  let pile: int Stack.t = Stack.create () in

  for i = 0 to n-1 do
    if deja_faits.(i) then
      ()
    else
      Stack.push i pile;
      while not (Stack.is_empty pile) do
        let courant = Stack.pop pile in
        if deja_faits.(courant) then
          ()
        else begin
          resultat := courant::!resultat;
          deja_faits.(courant) <- true;
          List.iter (fun x -> Stack.push x pile) (List.rev g.(courant))
        end
      done
  done;
  List.rev !resultat


(* Pour le test, voir question 8 *)



(* Question 8 *)
(* Renvoie la liste de chaque étiquette du graphe g dans l’ordre du parcours en
 * profondeur. *)
let liste_parcours_profondeur_recursif (g: graphe) : int list =
  let n = Array.length g in
  let resultat: int list ref = ref [] in
  let deja_faits = Array.make n false in

  (* Effectue un parcours en profondeur depuis le sommet `sommet`, sauf si
   * ce dernier a déjà été visité (i.e. est dans deja_faits) *)
  let rec explore_depuis (sommet: int) : unit =
    if deja_faits.(sommet) then
      ()
    else begin
      resultat := sommet::!resultat;
      deja_faits.(sommet) <- true;
      List.iter explore_depuis g.(sommet)
    end
  in

  for i = 0 to n-1 do
    if deja_faits.(i) then
      ()
    else
      explore_depuis i
  done;

  List.rev !resultat

let test_liste_parcours_profondeur : unit =
  let teste_une_fonction (f_parcours_profondeur: graphe -> int list) : unit =
    assert (f_parcours_profondeur g0 = [0; 1; 4; 5; 2; 3]);
    assert (f_parcours_profondeur g1 = [0; 1; 4; 5; 2; 3]);
    assert (f_parcours_profondeur g2 = [0; 1; 2; 3; 4; 5]);
    assert (f_parcours_profondeur g3 = [0; 1; 5; 6; 2; 7; 4; 3]);
    assert (f_parcours_profondeur g4 = [0; 5; 4; 3; 1; 2]);
    assert (f_parcours_profondeur g5 = [0; 2; 5; 3; 4; 1]);
    assert (f_parcours_profondeur g6 = [0; 1; 2; 3; 4; 5; 6; 7])
  in
  teste_une_fonction liste_parcours_profondeur_imperatif;
  teste_une_fonction liste_parcours_profondeur_recursif


(* définition de quelques graphes non orientés pour tester la fonction *)
let gn0 = [|
  [1];
  [0; 2; 3; 4];
  [1; 3];
  [1; 2];
  [1];
  [6; 7];
  [5; 7];
  [5; 6];
  []
|]


(* Question 9 *)
(* Pour trouver toutes les composantes connexes d’un graphe non orienté, il
 * suffit de faire un parcours, de choisir un sommet non encore visité,
 * et de recommencer un parcours. On recommence tant qu’on a des sommets non
 * visités. *)
let composantes_connexes (g: graphe) : int list list =
  let n = Array.length g in
  let resultat: int list list ref = ref [] in
  let composante_connexe_en_cours: int list ref = ref [] in
  let deja_faits = Array.make n false in

  (* Effectue un parcours en profondeur depuis le sommet `sommet`, sauf si
   * ce dernier a déjà été visité (i.e. est dans deja_faits) *)
  let rec explore_depuis (sommet: int) : unit =
    if deja_faits.(sommet) then
      ()
    else begin
      composante_connexe_en_cours:= sommet::!composante_connexe_en_cours;
      deja_faits.(sommet) <- true;
      List.iter explore_depuis g.(sommet)
    end
  in

  for i = 0 to n-1 do
    if deja_faits.(i) then
      ()
    else begin
      explore_depuis i;
      resultat := (List.rev !composante_connexe_en_cours)::!resultat;
      composante_connexe_en_cours := []
    end
  done;

  List.rev !resultat

let test_composantes_connexes : unit =
  assert (composantes_connexes gn0 = [[0; 1; 2; 3; 4]; [5; 6; 7]; [8]]);
  assert (composantes_connexes [||] = [])

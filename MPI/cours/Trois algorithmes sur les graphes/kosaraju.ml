
type graph = int list array

(* Graphes utilisés pour les tests *)
(* 0 --> 1
 * ^     ^
 * |     |
 * |     v
 * 3 --> 2 *)
let g1 = [|
  [1];
  [2];
  [1];
  [0; 2]
|]

(* 0 <-- 1
 * |     ^
 * |     |
 * v     v
 * 3 <-- 2 *)
let g1t = [|
  [3];
  [0; 2];
  [1; 3];
  []
|]

(* 0 --> 1 --> 2
 * |      ^   /
 * v       \ v
 * 4 <----- 3
 * ^
 * |
 * v
 * 5
 *)
let g2 = [|
  [1; 4];
  [2];
  [3];
  [1; 4];
  [5];
  [4];
|]

(* 0 <-- 1 <-- 2
 * |      \   ^
 * v       v /
 * 4 -----> 3
 * ^
 * |
 * v
 * 5
 *)
let g2t = [|
  [];
  [0; 3];
  [1];
  [2];
  [0; 3; 5];
  [4];
|]

(* Renvoie true si g et g' sont égaux, false sinon. *)
(* Fonction utilisée dans les tests *)
let egal (g: graph) (g': graph) : bool =
  let n = Array.length g in
  if n = Array.length g' then
    let res = ref true in
    for i = 0 to (n-1) do
      if List.sort compare g.(i) <> List.sort compare g'.(i) then
        res := false
    done;
    !res
  else
    false

let test_egal : unit =
  assert (egal g1 g1);
  assert (egal g2 g2);
  assert (not (egal g1 g2));
  assert (not (egal g1t g2t));
  assert (not (egal g1 g1t));
  assert (not (egal g2 g2t));
  assert (egal g1 [|[1]; [2]; [1]; [2; 0]|]);
  assert (not (egal g1 [|[1]; [2]; [1]; [2; 0; 3]|]))


(* Calcule et renvoie la transposée du graphe g, en O(n+m) avec n le nombre de
 * sommets de g et m son nombre d’arcs *)
let transpose (g: graph) : graph =
  (* Ajoute l’arc (i, j) au graphe g', en le modifiant par effet de bord *)
  let ajoute_arc (i: int) (j: int) (g': graph) : unit =
    g'.(i) <- j::(g'.(i))
  in
  (* Ajoute les arcs (i, j) pour tout les i dans l au graphe g', en le
   * modifiant par effet de bord *)
  let rec ajoute_arcs (j: int) (l: int list) (g': graph) : unit =
    match l with
    | [] -> ()
    | i::q -> (ajoute_arc i j g'; ajoute_arcs j q g')
  in
  let n = Array.length g in
  let res = Array.make n [] in (* O(n) *)
  (* boucle en O(n+m) *)
  for i = 0 to (n-1) do
    ajoute_arcs i (g.(i)) res
  done;
  res

let test_transpose : unit =
  assert (egal (transpose g1) g1t);
  assert (egal (transpose g1t) g1);
  assert (egal (transpose g2) g2t);
  assert (egal (transpose g2t) g2);
  assert (transpose [||] = [||]);
  assert (transpose [|[]|] = [|[]|])


(* Calcule et renvoie un tri préfixe de g, en O(n+m) *)
let prefix_sort (g: graph) : int array =
  let n = Array.length g in
  let res = Array.make n (-1) in
  let indice_courant = ref (n-1) in  (* on remplit res en partant de la fin *)
  let visites = Array.make n false in

  (* Explore depuis le sommet s, en ignorant les sommets déjà visités, en
   * mettant à jour la liste res en rajoutant les sommets visités dans l’ordre
   * dans lequel ils ont été visités *)
  let rec explore_depuis (s: int) : unit =
    if visites.(s) then
      ()
    else begin
      visites.(s) <- true;
      List.iter explore_depuis g.(s);
      res.(!indice_courant) <- s;
      decr indice_courant
    end
  in

  for i = 0 to (n-1) do
    explore_depuis i
  done;
  res

let test_prefix_sort : unit =
  assert (prefix_sort g1 = [|3; 0; 1; 2|]);
  assert (prefix_sort g1t = [|1; 2; 0; 3|]);
  assert (prefix_sort g2 = [|0; 1; 2; 3; 4; 5|]);
  assert (prefix_sort g2t = [|4; 5; 1; 3; 2; 0|])


(* Calcule et renvoie les composantes fortement connexes de g en O(n+m), sous
 * la forme d’un tableau où la i-ème case contient le numéro de la composante
 * connexe du sommet i *)
let kosaraju (g: graph) : int array =
  let n = Array.length g in
  let res = Array.make n (-1) in
  let visites = Array.make n false in

  (* Explore depuis le sommet s, en ignorant les sommets déjà visités, en
   * mettant à jour le tableau res en mettant `numero_composante` dans les cases
   * des sommets visités *)
  let rec explore_depuis (numero_composante: int) (s: int) : unit =
    if visites.(s) then
      ()
    else begin
      visites.(s) <- true;
      res.(s) <- numero_composante;
      List.iter (explore_depuis numero_composante) g.(s)
    end
  in

  let gt = transpose g in
  let tri_prefixe = prefix_sort gt in
  (* parcours en choisissant les point de régénération selon tri_prefixe *)
  for i = 0 to (n-1) do
    let t_i = tri_prefixe.(i) in
    explore_depuis t_i t_i
  done;
  res

let test_kosaraju : unit =
  assert (kosaraju g1 = [|0; 1; 1; 3|]);
  assert (kosaraju g1t = [|0; 1; 1; 3|]);
  assert (kosaraju g2 = [|0; 1; 1; 1; 4; 4|]);
  assert (kosaraju g2t = [|0; 1; 1; 1; 4; 4|])


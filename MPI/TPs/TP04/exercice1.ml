
(* Distance au carré entre v1 et v2 *)
let dist_square (v1: Vector.t) (v2: Vector.t) : float =
  Vector.sq_norm Vector.(v2 - v1)

let test_dist_sqare : unit =
  assert (dist_square [|3.; 3.|] [|-2.; 4.|] = 26.)


(* Renvoie l'indice dans ce du vecteur de ce minimisant la distance à v *)
let find_closest_center (ce: data) (v: Vector.t) : int =
  if ce = [||] then
    failwith "Tableau vide !"
  else
    let n = Array.length ce in
    let argmin = ref 0 in
    let min = ref (dist_square v ce.(0)) in
    for i = 0 to n-1 do
      let nouvelle_distance = dist_square v ce.(i) in
      if nouvelle_distance <= !min then begin
        min := nouvelle_distance;
        argmin := i
      end
    done;
    !argmin

let test_find_closest_center : unit =
  try (let _ = find_closest_center [||] [|3.|] in assert false)
  with | Failure x when x="Tableau vide !" -> ();
  let centres = [|[|1.; 2.|]; [|10.; 10.|]|] in
  assert (find_closest_center centres [|1.; 2.|] = 0);
  assert (find_closest_center centres [|10.; 10.|] = 1);
  assert (find_closest_center centres [|9.; 2.|] = 0);
  assert (find_closest_center centres [|11.; 75.|] = 1)


(* Remplit le tableau cl pour y mettre pour chaque case d'indice i, l'indice
 * dans ce du vecteur le + proche de d.(i). Renvoie true si et seulement
 * si le tableau cl a été modifié. d et cl doivent avoir la même taille *)
let modify_clustering (ce: data) (d: data) (cl: int array) : bool =
  let is_cl_modified = ref false in
  let n = Array.length cl in
  (* n = Array.length d également *)
  for i = 0 to n-1 do
    let closest_center = find_closest_center ce d.(i) in
    if closest_center <> cl.(i) then begin
      is_cl_modified := true;
      cl.(i) <- closest_center
    end
  done;
  !is_cl_modified

let test_modify_clustering : unit =
  let ce = [|
    [|1.; -2.|];
    [|-2.; 1.|];
    [|3.; 3.|]
  |] in
  let d = [|
    [|-1.; 1.|];
    [|-1.; 2.|];
    [|1.; 0.|];
    [|2.; 3.|];
    [|2.; -1.|];
    [|3.; 4.|]
  |] in
  let cl = [|1; 2; 0; 1; 1; 0|] in
  assert (modify_clustering ce d cl);
  assert (cl = [|1; 1; 0; 2; 0; 2|]);
  assert (not (modify_clustering ce d cl));
  assert (cl = [|1; 1; 0; 2; 0; 2|])


(* Met à jour ce en y mettant dans chaque case i le centre du groupe i *)
let recompute_centers (ce: data) (d: data) (cl: int array) : unit =
  let k = Array.length ce in
  let n = Array.length cl in
  let dim = Array.length d.(0) in
  let sommes_vecteurs = Array.init k (fun _ -> Vector.null dim) in
  let nombres_vecteurs = Array.make k 0 in
  for i = 0 to n-1 do
    let groupe = cl.(i) in
    sommes_vecteurs.(groupe) <- Vector.(+) sommes_vecteurs.(groupe) d.(i);
    nombres_vecteurs.(groupe) <- nombres_vecteurs.(groupe) + 1
  done;
  for i = 0 to k-1 do
    if nombres_vecteurs.(i) = 0 then
      ce.(i) <- Vector.null dim
    else begin
      let lambda = 1. /. (float_of_int nombres_vecteurs.(i)) in
      ce.(i) <- Vector.( * ) lambda sommes_vecteurs.(i)
    end
  done

let test_recompute_centers : unit =
  let ce = [|
    [|1.; -2.|];
    [|-2.; 1.|];
    [|3.; 3.|]
  |] in
  let d = [|
    [|-1.; 1.|];
    [|-1.; 2.|];
    [|1.; 0.|];
    [|2.; 3.|];
    [|2.; -1.|];
    [|3.; 4.|]
  |] in
  let cl =[|1; 1; 0; 2; 0; 2|] in
  recompute_centers ce d cl;
  assert (ce = [|
    [|1.5; -0.5|];
    [|-1.; 1.5|];
    [|2.5; 3.5|]
  |])


(* Effectue une étape de l'algo des k-moyennes (recalcul des classes, recalcul
 * des centres) puis renvoie true si on a modifié cl, et false sinon. Les
 * notations sont les mêmes que pour les fonctions précédentes *)
let k_means_update (ce: data) (d: data) (cl: int array) : bool =
  let modifie = modify_clustering ce d cl in
  if modifie then
    recompute_centers ce d cl
  else ();
  modifie


(* À partir d'un jeu de données d et d'un entier k, calcule les k moyennes
 * avec l'algorithme des k moyennes. Renvoie le tableau contenant les classes
 * des points *)
let k_means (k: int) (d: data) : int array =
  let n = Array.length d in
  let ce = Array.init k (fun i -> d.(i)) in
  let cl = Array.init n (fun i -> max i k-1) in
  let stable = ref false in
  while not !stable do
    stable := not (k_means_update ce d cl)
  done;
  cl


(* Pareil que k_means mais avec graphics *)
let k_means_anim (k: int) (d: data) : int array =
  Graphics.open_graph " 1000x1000";
  draw_data d;
  let _ = Graphics.wait_next_event [Graphics.Key_pressed] in
  let ce = Array.init k (fun i -> d.(i)) in
  let cl = Array.init k (fun i -> max i k) in
  let stable = ref false in
  while not !stable do
    stable := not (k_means_update ce d cl);
    draw_clustering_w_centers ce d cl;
    let _ = Graphics.wait_next_event [Graphics.Key_pressed] in ()
  done;
  cl


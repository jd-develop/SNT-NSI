type vector = float array

type kd_tree =
  | Vide
  | Node of int * vector * kd_tree * kd_tree


(* GÉNÉRATION JEU TEST *)
let genere_jeu_donnes (n: int) : vector array =
  Array.init n (fun _ -> Array.init 2 (fun _ -> Random.float 1.))

(* OUTILS GRAPHIQUES *)

let yellow = Graphics.rgb 210 160 4
let blue = Graphics.rgb 0 0 255
let red = Graphics.rgb 255 0 0
let cx = 1000
let cy = 1000
let to_x pt = (pt *. (float_of_int cx)) |> int_of_float
let to_y pt = (pt *. (float_of_int cy)) |> int_of_float

let rec draw_kd_tree_aux (t: kd_tree) swx swy nex ney (l: vector list) =
  match t with
  | Vide -> ()
  | Node(dim, v_sep, g, d) ->
    begin
      let dx, dy = to_x v_sep.(0), to_y v_sep.(1) in
      let colour = if List.mem v_sep l then red else yellow in
      if dim = 0 then
        begin
          Graphics.set_color Graphics.black;
          Graphics.moveto dx swy; Graphics.lineto dx ney;
          Graphics.set_color colour;
          Graphics.fill_circle dx dy 5;
          draw_kd_tree_aux g swx swy dx ney l;
          draw_kd_tree_aux d dx swy nex ney l;
        end
      else
        begin
          Graphics.set_color Graphics.black;
          Graphics.moveto swx dy; Graphics.lineto nex dy;
          Graphics.set_color colour;
          Graphics.fill_circle dx dy 5;
          draw_kd_tree_aux g swx swy nex dy l;
          draw_kd_tree_aux d swx dy nex ney l;
        end;
    end


let draw_kd_tree_knn (t: kd_tree) (l: vector list) (x: vector option) =
  (* Hyp : fenêtre graphique de taille cx * cy ouverte
   * dessine l'arbre t, avec des couleurs différentes pour les éléments de l.
   * dessine de + en une troisième couleur x, s’il n’est pas à None *)
  draw_kd_tree_aux t 0 0 cx cy l;
  match x with
  | None -> ()
  | Some x' -> begin
    let dx, dy = to_x x'.(0), to_y x'.(1) in
    Graphics.set_color blue;
    Graphics.fill_circle dx dy 5;
  end


let draw_kd_tree = (fun t -> draw_kd_tree_knn t [] None)


(* Renvoie la fonction de comparaison entre deux vecteurs sur la i+1-ième
 * composante *)
let f_cmp (i: int) : (vector -> vector -> bool) =
  (fun (v1: vector) (v2: vector) -> v1.(i) <= v2.(i))


let test_f_cmp : unit =
  let v1 = [|0.; 2.; 3.14|] in
  let v2 = [|3.; 1.; 1.5|] in
  assert (f_cmp 0 v1 v2);
  assert (not (f_cmp 0 v2 v1));
  assert (f_cmp 1 v2 v1);
  assert (not (f_cmp 1 v1 v2));
  assert (f_cmp 2 v2 v1);
  assert (not (f_cmp 2 v1 v2))


(* Échange t.(a) et t.(b) et renvoie la valeur de t.(a) d’avant l’appel (i.e.
 * la valeur de t.(b) après l’appel *)
let echange (t: 'a array) (a: int) (b: int) : 'a =
  let temp = t.(a) in
  t.(a) <- t.(b);
  t.(b) <- temp;
  temp


(* Affiche le tableau t d’éléments pouvant être affichés avec print_prime_a.
 * Affiche ^ avant les éléments d’indices présents dans indices_a_afficher.
 * Cette fonction est en O(nm) où n = Array.length t et m = max(List.length
 * indices_a_afficher, 1). *)
(* Fonction utile pour déboguer *)
let print_array (t: 'a array) (print_prime_a: 'a -> unit)
    (indices_a_afficher: int list) : unit =
  print_string "[|";
  for i = 0 to Array.length t - 1 do
    if List.mem i indices_a_afficher then
      print_string "^";
    print_prime_a t.(i);
    if i <> Array.length t - 1 then
      print_string ", "
  done;
  print_endline "|]"


(* Permute le tableau t entre les indices d et f de telle sorte à ce que si
 * d ⩽ i < q, alors t.(i) < t.(q) ; et si q ⩽ i ⩽ f, alors t.(i) ⩾ t.(q) ; avec
 * q le nouvel indice de la valeur de t.(p) avant l’appel.
 * L’indice q est renvoyé.
 * La relation d’ordre considérée est donnée par la fonction cmp.
 * Plante si d > f, p < d ou p > f. *)
let partionner (t: 'a array) (d: int) (f: int) (p: int) (cmp: 'a -> 'a -> bool)
    : int =
  if d > f then
    failwith "L’indice de début est après l’indice de fin";
  if p < d || p > f then
    failwith "Le pivot doit être entre l’indice de début et celui de fin";

  let pivot = echange t p d in
  let a = ref (d+1) in
  let b = ref f in

  while !a <= !b do
    if cmp t.(!a) pivot then
      a := !a+1
    else begin
      let _ = echange t !a !b in
      b := !b-1
    end;
  done;

  let _ = echange t d (!a-1) in
  !a-1


let test_partitionner : unit =
  let test_array = [|3; 1; 0; 6; -3; 2|] in
  assert (partionner test_array 1 4 2 (<=) = 2);
  assert (test_array = [|3; -3; 0; 6; 1; 2|])


(* Renvoie une valeur de rang r dans t entre d et f, selon la relation d’ordre
 * donnée par cmp. Renvoie None si le tableau est vide ou si r est un indice
 * hors de [[d, f]] *)
let rec selection_rapide (t: 'a array) (r: int) (d: int) (f: int)
    (cmp: 'a -> 'a -> bool) :
    'a option =
  if d > f then
    None
  else begin
    let p = if f = d then d
            else d + Random.int (f-d)
    in
    let q = partionner t d f p cmp in
    if r = q then
      Some t.(r)
    else if r < q then
      selection_rapide t r d (q-1) cmp
    else
      selection_rapide t r (q+1) f cmp
  end


let test_selection_rapide : unit =
  let test_array = [|0; 4; -3; 6; 12; -2; -3|] in
  (* test_array trié est [|-3; -3; -2; 0; 4; 6; 12|]) *)
  assert (selection_rapide test_array (-1) 0 6 (<=) = None);
  assert (selection_rapide test_array 0 0 6 (<=) = Some (-3));
  assert (selection_rapide test_array 1 0 6 (<=) = Some (-3));
  assert (selection_rapide test_array 2 0 6 (<=) = Some (-2));
  assert (selection_rapide test_array 3 0 6 (<=) = Some 0);
  assert (selection_rapide test_array 4 0 6 (<=) = Some 4);
  assert (selection_rapide test_array 5 0 6 (<=) = Some 6);
  assert (selection_rapide test_array 6 0 6 (<=) = Some 12);
  assert (selection_rapide test_array 7 0 6 (<=) = None)


(* Crée un arbre k-dimensionnel à partir du tableau t de vecteurs de ℝ^k, en
 * commençant à brancher sur la composante 0 *)
let creer_arbre_kd (t: vector array) : kd_tree =
  if t = [||] then
    Vide
  else

  let k = Array.length t.(0) in
  (* Crée un arbre k-dimensionnel à partir du tableau t de vecteurs de ℝ^k, en
   * commençant à brancher sur la composante i, entre les cases d et f du
   * tableau t (inclus) *)
  let rec creer_arbre_kd_branchement (i: int) (d: int) (f: int) : kd_tree =
    if d > f then
      Vide
    else begin
      (* On peut remarquer qu’une des conséquences de selection_rapide est
       * que les éléments inférieurs à la médianne sont situés avant elle,
       * et les élément supérieurs sont situés après elle *)
      let rang_medianne = d + (f-d+1)/2 in
      let medianne =
        match selection_rapide t rang_medianne d f (f_cmp i) with
        | None -> failwith "Pas de médianne mais d <= f…"
        | Some v -> v
      in
      let ag = creer_arbre_kd_branchement ((i+1) mod k) d (rang_medianne-1) in
      let ad = creer_arbre_kd_branchement ((i+1) mod k) (rang_medianne+1) f in
      Node(i, medianne, ag, ad)
    end
  in
  creer_arbre_kd_branchement 0 0 (Array.length t - 1)


(* Renvoie la distance cartésienne entre les vecteurs u et v *)
let distance (u: vector) (v: vector) : float =
  let somme = ref 0.0 in
  let n = Array.length u in
  for i = 0 to n-1 do
    let diff = u.(i) -. v.(i) in
    somme := !somme +. diff*.diff
  done;
  sqrt !somme


(* Presque égal à *)
let (=.) (x: float) (y: float) =
  let epsilon = 0.0001 in
  x-.epsilon <= y && y <= x+.epsilon


let test_distance : unit =
  assert (distance [|0.5; 1.|] [|1.; 1.|] = 0.5);
  assert (distance [|0.; 0.|] [|1.; 1.|] = sqrt 2.);
  assert (distance [|-1.; 1.|] [|1.; -1.|] = sqrt 8.);
  assert (distance [|-1.; 1.|] [|-1.; 1.|] = 0.);
  assert (distance [|0.5; 1.; 3.|] [|2.; 1.; -6.3|] =. sqrt 88.74);
  assert (distance [||] [||] = 0.)


(* Renvoie une liste l de longueur r ⩽ k, contenant les r vecteurs parmi ceux
 * de l1 (de longueur r1), l2 (de longueur r2) et x qui sont les plus proches
 * de input.
 * Hypothèse : les vecteurs de l1 et l2 sont triés par distance décroissante.
 * Renvoie (r, l), avec l triée par distance décroissante *)
let merge (l1: vector list) (r1: int) (l2: vector list) (r2: int)
    (x: vector) (k: int) (input: vector) : (int * vector list) =
  (* Insère x dans l triée par distance décroissante telle que la liste
   * de retour soit triée par distance décroissante *)
  let rec inserer (x': vector) (l: vector list): vector list =
    match l with
    | [] -> [x']
    | v::q ->
        if distance v input <= distance x' input then
          x'::v::q
        else
          v::(inserer x' q)
  in
  (* Renvoie l privée de ses p premiers éléments (renvoie une liste vide
   * si l possède moins de p éléments) *)
  let rec sans_les_p_premiers (l: 'a list) (p: int): 'a list =
    if p = 0 then l
    else
    match l with
    | [] -> []
    | _::q -> sans_les_p_premiers q (p-1)
  in
  (* Comme merge, mais sans x *)
  let rec merge_aux (l1': vector list) (r1': int) (l2': vector list)
      (r2': int) =
    match (l1', l2') with
    | [], [] -> 0, []
    | _, [] ->
        if r1' <= k then
          r1', l1'
        else
          k, sans_les_p_premiers l1' (r1'-k)
    | [], _ ->
        if r2' <= k then
          r2', l2'
        else
          k, sans_les_p_premiers l2' (r2'-k)
    | x1::q1, x2::q2 ->
        let d1 = distance x1 input in
        let d2 = distance x2 input in
        if r1' + r2' <= k then
          if d1 <= d2 then
            let r, m = merge_aux l1' r1' q2 (r2'-1) in
            r+1, x2::m
          else
            let r, m = merge_aux q1 (r1'-1) l2' r2' in
            r+1, x1::m
        else
          if d1 <= d2 then
            merge_aux l1' r1' q2 (r2'-1)
          else
            merge_aux q1 (r1'-1) l2' r2'
  in
  let r, m = merge_aux (inserer x l1) (r1+1) l2 r2 in
  assert (r = List.length m);
  r, m


(* Renvoie les k plus proches voisins de input dans l’arbre p-dimentionnel t.
 * Renvoie une liste de voisins ainsi que la taille réelle r de la liste (r ⩽ k)
 * La liste renvoyée est triée par distance décroissante. *)
let rec knn (k: int) (input: vector) (t: kd_tree) : (int * vector list) =
  match t with
  | Vide -> 0, []
  | Node(i, x, ag, ad) ->
    let proche, loin =
      if input.(i) < x.(i) then
        ag, ad
      else
        ad, ag
    in
    let r_proche, nn_proche = knn k input proche in
    (* Si la liste renvoyée est de taille inférieure à k, ou que le vecteur le
     * plus loin qui a été trouvé est plus proche de la « ligne » médianne qu’il
     * n’est proche de input, alors on regarde aussi la composante « loin » *)
    let regarder_dans_loin = (
      r_proche < k ||
      match nn_proche with
      | v_loin::_ when abs_float (v_loin.(i) -. x.(i)) <= distance v_loin input
          -> true
      | _ -> false
    ) in
    if regarder_dans_loin then
      let r_loin, nn_loin = knn k input loin in
      merge nn_proche r_proche nn_loin r_loin x k input
    else
      merge nn_proche r_proche [] 0 x k input


let print_list (l: 'a list) (print_'a: 'a -> unit) =
  print_string "[";
  let rec print_list_aux (l': 'a list) =
    match l' with
    | [] -> ()
    | x::[] -> print_'a x
    | x::q -> print_'a x; print_string ", "; print_list_aux q
  in
  print_list_aux l;
  print_endline "]"


let main_exemple () =
  () |> Unix.time |> int_of_float |> Random.init;
  let nb_points = 50 in
  let _t = genere_jeu_donnes nb_points in
  let kd_tree = creer_arbre_kd _t in
  let input = [|Random.float 1.; Random.float 1.|] in
  let _, _knn = knn 10 input kd_tree in
  Graphics.open_graph " 1000x1000";
  draw_kd_tree_knn kd_tree _knn (Some input);
  print_endline "Appuyez sur n’importe quelle touche pour quitter.";
  let _ = Graphics.wait_next_event [Graphics.Key_pressed] in ()


let () = main_exemple ()

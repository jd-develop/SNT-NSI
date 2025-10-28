type vector = float array

type kd_tree =
  | Vide
  | Node of int * vector * kd_tree * kd_tree


(* GÉNÉRATION JEU TEST *)
let genere_jeu_donnes (n: int) : vector array =
  Array.init n (fun _ -> Array.init 2 (fun _ -> Random.float 1.))

(* OUTILS GRAPHIQUES *)

let yellow = Graphics.rgb 210 160 4
let cx = 1000
let cy = 1000
let to_x pt = (pt *. (float_of_int cx)) |> int_of_float
let to_y pt = (pt *. (float_of_int cy)) |> int_of_float

let rec draw_kd_tree_aux (t: kd_tree) swx swy nex ney =
  match t with
  | Vide -> ()
  | Node(dim, v_sep, g, d) ->
    begin
      let dx, dy = to_x v_sep.(0), to_y v_sep.(1) in
      if dim = 0 then
        begin
          Graphics.set_color Graphics.black;
          Graphics.moveto dx swy; Graphics.lineto dx ney;
          Graphics.set_color yellow;
          Graphics.fill_circle dx dy 5;
          draw_kd_tree_aux g swx swy dx ney;
          draw_kd_tree_aux d dx swy nex ney;
        end
      else
        begin
          Graphics.set_color Graphics.black;
          Graphics.moveto swx dy; Graphics.lineto nex dy;
          Graphics.set_color yellow;
          Graphics.fill_circle dx dy 5;
          draw_kd_tree_aux g swx swy nex dy;
          draw_kd_tree_aux d swx dy nex ney;
        end;
    end


let draw_kd_tree (t: kd_tree) =
  (* Hyp : fenêtre graphique de taille cx * cy ouverte
   * dessine l'arbre t *)
  draw_kd_tree_aux t 0 0 cx cy


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
    (* Je ne vois pas l’utilité d’étiquetter les paramètres ET les arguments
     * pour une fonction aussi bateau que int_in_range… Mais bon, ocamlc me
     * sortait un warning. *)
    let p = Random.int_in_range ~min:d ~max:f in
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


let main_exemple () =
  () |> Unix.time |> int_of_float |> Random.init;
  let nb_points = 50 in
  let _t = genere_jeu_donnes nb_points in
  let kd_tree = creer_arbre_kd _t in
  Graphics.open_graph " 1000x1000";
  draw_kd_tree kd_tree;
  Graphics.loop_at_exit [] (fun _ -> ())


let () = main_exemple ()

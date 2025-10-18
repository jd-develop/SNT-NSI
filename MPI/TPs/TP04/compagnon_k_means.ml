(*-----------------------------------*)
(*    OPERATIONS SUR DES TABLEAUX    *)
(*-----------------------------------*)

let array_map2 (f: 'a -> 'b -> 'c) (a: 'a array) (b: 'b array): 'c array =
  (* Hyp : a et b sont de même taille n *)
  (* calcule le tableau des f(a(i),b(i)) pour i de 0 à n-1 *)
  let na = Array.length a in
  let nb = Array.length b in
  if na <> nb
    then raise (Invalid_argument "pas même taille")
  else if na = 0
    then [||]
  else
    let rep = Array.make na (f a.(0) b.(0)) in
    for i = 1 to (na-1) do
      rep.(i) <- f (a.(i)) (b.(i))
    done;
    rep

(* Mélange de Knuth du tableau a *)
let knuth_shuffle (a:'a array) =
  let n = Array.length a in
  let a = Array.copy a in
  for i = n - 1 downto 1 do
    let k = Random.int (i+1) in
    let x = a.(k) in
    a.(k) <- a.(i);
    a.(i) <- x
  done;
  a

(*-----------------------------------*)
(*     DIVERSES FONCTIONS UTILES     *)
(*-----------------------------------*)

(* Module de manipulation de vecteurs *)
module Vector = struct
  type t = float array
  let null (n: int) = Array.make n 0.
  let ( + ) (x: t) (y: t) =
    array_map2 ( +. ) x y
  let ( * ) (lam: float) (x: t) =
    Array.map (fun y -> lam *. y) x
  let ( - ) (x: t) (y: t) =
    array_map2 ( -. ) x y
  let sq_norm (x: t) =
    Array.fold_left (fun acc x -> acc +. x *. x) 0. x
  let norm (x: t) = (sq_norm x) |> sqrt
  let dist x y = norm (x - y)
end
type data = Vector.t array

let list_init (nb_elem: int) (f: int -> 'a): 'a list =
  (* calcule la liste f(0) f(1) f(2) ... f(nb_elem-1) *)
  let rec aux (i: int) (l: 'a list): 'a list =
    if i < nb_elem then aux (i+1) ((f i) :: l)
    else List.rev l
  in aux 0 []



(*-----------------------------------*)
(*      POUR GÉRER L'AFFICHAGE       *)
(*-----------------------------------*)

(* association d'une couleur à chaque entier *)
let color_table = Hashtbl.create 12
let get_color (i: int) =
  match i with
  | -1 -> Graphics.black
  | 2 -> Graphics.rgb 109 129 98
  | 1 -> Graphics.rgb 105 105 0
  | 0 -> Graphics.rgb 168 27 3
  | 3 -> Graphics.rgb 210 160 4
  | 4 -> Graphics.rgb 217 203 162
  | _ ->
    if Hashtbl.mem color_table i then Hashtbl.find color_table i
    else
      let c = Graphics.rgb (Random.int 255) (Random.int 255) (Random.int 255) in
      let () = Hashtbl.add color_table i c in
      c



(* Constantes pour graphique *)
let cx = 1000
let cy = 1000
let to_x pt = (pt *. (float_of_int cx)) |> int_of_float
let to_y pt = (pt *. (float_of_int cy)) |> int_of_float

(* Dessine un jeu de données *)
let draw_data (d: data): unit =
  Array.iteri (fun i v ->
      let x = to_x v.(0) in
      let y = to_y v.(1) in
      Graphics.set_color Graphics.black ;
      Graphics.fill_circle x y 3
    ) d

(* Dessine une partition. La partition est représentée par un tableau associant à chaque indice de donnée
   son numéro de groupe *)
let draw_clustering (d: data) (cl: int array): unit =
  Array.iteri (fun i v ->
      let c = get_color cl.(i) in
      let x = to_x v.(0) in
      let y = to_y v.(1) in
      Graphics.set_color c ;
      Graphics.fill_circle x y 3
    ) d

(* Dessine une partition. La partition est représenté pare un tableau associant à chaque indice de donnée
   son numéro de groupe. Les "centres" de chaque groupe sont indiqués au moyen d'un tableau centers. *)
let draw_clustering_w_centers (ce: data) (d: data) (cl: int array): unit =
  Array.iteri (fun i v ->
      let c = get_color cl.(i) in
      let x = to_x v.(0) in
      let y = to_y v.(1) in
      Graphics.set_color c ;
      Graphics.fill_circle x y 3
    ) d;
  Array.iteri (fun i v ->
      let c = get_color i in
      let x = to_x v.(0) in
      let y = to_y v.(1) in
      Graphics.set_color Graphics.black;
      Graphics.fill_rect (x-1) (y-1) 12 12;
      Graphics.set_color c ;
      Graphics.fill_rect x y 10 10;
    ) ce


(*-----------------------------------*)
(*      GÉNERATION DES DONNÉES       *)
(*-----------------------------------*)
 (* Constante pi *)
let pi = 4. *. atan 1.

(* variable aléatoire de loi exponentielle de paramètre lam *)
let expo (lam: float) : float =
  (* 1 - exp(-lam x) *)
  let y = Random.float 1. in
  (log (1. -. y)) /. (-. lam)


(* Génère un jeu de nb_elem données réparties en nb_cluster groupes d'"étalement" dist *)
let gen_data (nb_elem: int) (nb_cluster: int) (dist: float) : data =
  let cluster_centers_dist = Array.init nb_cluster (fun _ -> (Array.init 2 (fun _ -> 0.1 +. Random.float 0.8), (Random.float dist))) in
  list_init nb_elem (fun _ ->
      let i = Random.int nb_cluster in
      let c, r = cluster_centers_dist.(i) in
      let theta = 2. *. pi *. (Random.float 1.) in
      let dist = expo (1./.dist) in
      let ecart = [|dist *. cos (theta); dist *. sin (theta)|] in
      [Vector.( c + ecart )]
    )
  |> List.flatten
  |> Array.of_list
  |> knuth_shuffle

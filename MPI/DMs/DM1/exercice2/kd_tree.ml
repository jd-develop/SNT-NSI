type vector = float array

type kd_tree =
  | Vide
  | Node  of int * vector * kd_tree * kd_tree


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


let main_exemple () =
  let nb_points = 50 in
  let _t = genere_jeu_donnes nb_points in
  let kd_tree = Vide in         (* TODO : remplacer ici par votre fonction de génération d'un arbre k dimensionel *)
  Graphics.open_graph " 1000x1000";
  draw_kd_tree kd_tree;
  Graphics.loop_at_exit [] (fun _ -> ())


let () = main_exemple ()

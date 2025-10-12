
(* Renvoie i dans l tel que mu.(i) soit minimal *)
let find_min (l: int list) (mu: Floatb.t array) : int =
  let rec find_min_tr (l: int list) (min_courant: Floatb.t) (i_min: int) : int =
    match l with
    | [] -> i_min
    | i::q ->
      if Floatb.inf mu.(i) min_courant then
        find_min_tr q mu.(i) i
      else
        find_min_tr q min_courant i_min
  in
  if l = [] then
    failwith "find_min: La liste doit contenir au moins un élément"
  else
    find_min_tr l Floatb.Infini (-1)


exception FinishFound of Floatb.t


let (+..) = Floatb.add
let (<..) = Floatb.inf


(* Renvoie la distance entre start et finish dans w *)
let dijkstra (w: world) (start: cell) (finish: cell) (graphics: bool) : Floatb.t =

  let start' = lin w start in
  let finish' = lin w finish in
  let mu = Array.make (w.w*w.h) Floatb.Infini in
  let pi: cell_l option array = Array.make (w.w*w.h) None in
  mu.(start') <- Floatb.F 0.;
  pi.(start') <- Some start';
  let todo = ref [start'] in
  let fini = ref [] in

  let relax (u: int) (v: int) (c: float) : unit =
    if mu.(u) +.. Floatb.F c <.. mu.(v) then begin
      mu.(v) <- mu.(u) +.. Floatb.F c;
      pi.(v) <- Some u;
      todo := v::!todo
    end
  in

  try begin
    while !todo <> [] do
      let u = find_min !todo mu in
      if u = finish' then
        raise (FinishFound mu.(u))
      else begin
        List.iter
          (fun (v, c) -> let v' = lin w v in relax u v' c)
          (voisin w (delin w u));
        todo := List.filter (fun x -> x <> u) !todo;
        fini := u::!fini
      end
    done;
    Floatb.Infini
  end
  with
  | FinishFound f ->
    if graphics then begin
      Graphics.open_graph " 600x600";
      draw_world (Some {
        fini = !fini; todo = !todo; mu = mu; pi = pi; src = start; obj = finish
      }) w;
      let _ = Graphics.wait_next_event [Key_pressed] in
      Graphics.close_graph();
    end;
    f


(* Proposition d’heuristique : distance à vol d’oiseau (distance
   cartésienne) *)
(* Calcule et renvoie la distance euclidienne entre 1 et 2 *)
let distance_euclidienne ((x1, y1): cell) ((x2, y2): cell) : float =
  (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) |> float_of_int |> sqrt


(* Renvoie la distance entre start et finish dans w *)
let a_etoile
    (w: world)
    (start: cell)
    (finish: cell)
    (h: cell -> cell -> float)
    (graphics: bool) : Floatb.t =

  let start' = lin w start in
  let finish' = lin w finish in
  let mu = Array.make (w.w*w.h) Floatb.Infini in
  let eta = Array.make (w.w*w.h) Floatb.Infini in
  let pi: cell_l option array = Array.make (w.w*w.h) None in
  mu.(start') <- Floatb.F 0.;
  eta.(start') <- Floatb.F (h start finish);
  pi.(start') <- Some start';
  let todo = ref [start'] in
  let fini = ref [] in

  let relax (u: int) (v: int) (c: float) : unit =
    if mu.(u) +.. Floatb.F c <.. mu.(v) then begin
      mu.(v) <- mu.(u) +.. Floatb.F c;
      eta.(v) <- mu.(v) +.. Floatb.F (h (delin w v) finish);
      pi.(v) <- Some u;
      todo := v::!todo
    end
  in

  try begin
    while !todo <> [] do
      let u = find_min !todo eta in
      if u = finish' then
        raise (FinishFound mu.(u))
      else begin
        List.iter
          (fun (v, c) -> let v' = lin w v in relax u v' c)
          (voisin w (delin w u));
        todo := List.filter (fun x -> x <> u) !todo;
        fini := u::!fini
      end
    done;
    Floatb.Infini
  end
  with
  | FinishFound f ->
    if graphics then begin
      Graphics.open_graph " 600x600";
      draw_world (Some {
        fini = !fini; todo = !todo; mu = mu; pi = pi; src = start; obj = finish
      }) w;
      let _ = Graphics.wait_next_event [Key_pressed] in
      Graphics.close_graph();
    end;
    f



(* Deuxième heuristique : calcule une distance en faisant d'abord des
 * mouvements en diagonale puis des mouvements horizontaux ou verticaux *)
let distance_mieux ((x1, y1): cell) ((x2, y2): cell): float =
  let diff_x = abs (x2-x1) in
  let diff_y = abs (y2-y1) in
  let diff_diago = min diff_x diff_y in
  let diff_horiz_vert = max diff_x diff_y - diff_diago in
  sqrt2 *. float_of_int diff_diago +. float_of_int diff_horiz_vert


(* Distance de Manhattan *)
let distance_de_manhattan ((x1, y1): cell) ((x2, y2): cell) : float =
  float_of_int (abs (x2-x1) + abs (y2-y1))

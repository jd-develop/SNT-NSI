
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


let (+..) (x: Floatb.t) (y: Floatb.t) =
  Floatb.add x y


let (<..) (x: Floatb.t) (y: Floatb.t) =
  Floatb.inf x y


(* Renvoie la distance entre start et finish dans w *)
let dijkstra (w: world) (start: cell) (finish: cell) : Floatb.t =
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
      end;
      (*draw_world (Some {
        fini = !fini; todo = !todo; mu = mu; pi = pi; src = start; obj = finish
      }) w;
      let _ = Graphics.wait_next_event [Key_pressed] in ();*)
    done;
    Floatb.Infini
  end
  with
  | FinishFound f -> f


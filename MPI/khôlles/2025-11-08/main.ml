
type graphe = int list array


let g0 = [|
  [1; 3];
  [0; 4];
  [3; 5];
  [0; 2; 5];
  [1];
  [2; 3];
|]

let g1 = [|
  [2; 4];
  [3; 4];
  [0];
  [1];
  [0; 1];
|]

(* Renvoie true si g est biparti, false sinon. Hypothèse : le graphe est
 * connexe et non-orienté *)
let biparti (g: graphe) : bool =
  let n = Array.length g in
  let visites = Array.make n false in
  let couleurs = Array.make n (-1) in
  let res = ref true in

  let rec explore_depuis (coul: int) (ident: int) (s: int) : unit =
    if visites.(s) then
      ()
    else begin
      visites.(s) <- true;
      couleurs.(s) <- coul;
      List.iter (
        fun u ->
          if couleurs.(u) = coul then
            res := false
          else
            explore_depuis (1-coul) (ident+1) u
      ) g.(s)
    end
  in
  explore_depuis 0 0 0;
  !res


let test_biparti : unit =
  assert (not (biparti g0));
  assert (biparti g1)


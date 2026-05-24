module type Puzzle = sig
  type t
  val canonical : t -> string
  val is_goal : t -> bool
  val next_positions : t -> t list
  val init : t
end

module JugPuzzle : Puzzle = struct
  type t = int * int * int

  let capacity : t = (8, 5, 3)
  let init : t = (8, 0, 0)
  let goal : t = (4, 4, 0)

  let canonical ((a, b, c): t) : string =
    (
      "("^
      string_of_int a ^
      ", "^
      string_of_int b ^
      ", "^
      string_of_int c ^
      ")"
    )

  let is_goal (state: t) : bool =
    state = goal

  let next_positions (state: t) : t list =
    let (a, b, c) = state in
    let (ma, mb, mc) = capacity in
    (* On enlève les états où on n'a rien changé avec un List.filter *)
    List.filter (fun x -> x <> state) [
      (* on verse le contenu de a dans b *)
      (a - min a (mb-b), b + min a (mb-b), c);
      (* on verse le contenu de a dans c *)
      (a - min a (mc-c), b, c + min a (mc-c));
      (* on verse le contenu de b dans a *)
      (a + min b (ma-a), b - min b (ma-a), c);
      (* on verse le contenu de b dans c *)
      (a, b - min b (mc-c), c + min b (mc-c));
      (* on verse le contenu de c dans a *)
      (a + min c (ma-a), b, c - min c (ma-a));
      (* on verse le contenu de c dans b *)
      (a, b + min c (mb-b), c - min c (mb-b));
    ] 

  let test_next_positions : unit =
    assert (next_positions (8, 0, 0) = [(3, 5, 0); (5, 0, 3)]);
    assert (next_positions (3, 5, 0) = [(0, 5, 3); (8, 0, 0); (3, 2, 3)]);
    assert (next_positions (5, 0, 3) = [(0, 5, 3); (8, 0, 0); (5, 3, 0)]);
    assert (next_positions (3, 2, 3) = [(0, 5, 3); (5, 0, 3); (6, 2, 0); (3, 5, 0)]);
    print_endline "ok next_positions"
end

module NQueens : Puzzle = struct
  type t = int list

  let init = []
  let n = 8

  let canonical (echiquier: t) : string =
    "["^(String.concat "; " (List.map string_of_int echiquier))^"]"

  let to_string (echiquier: t) : string =
    (* Renvoie une chaîne | | ... |X| ... | | où X est à l'indice i *)
    let ligne_to_string (i: int) : string =
      let res = ref "|" in
      for j = 0 to n-1 do
        if j = i then
          res := !res ^ "X|"
        else
          res := !res ^ " |"
      done;
      !res^"\n"
    in
    (* Construit un séparateur de la forme +-+-+-+-+-+-+... *)
    let separateur () : string =
      let res = ref "+" in
      for j = 0 to n-1 do
        res := !res ^ "-+"
      done;
      !res^"\n"
    in
    let lignes = List.map ligne_to_string echiquier in
    let sep = separateur () in
    sep^(String.concat sep lignes)^sep


  let is_goal (echiquier: t) : bool =
    List.length echiquier = n

  (* Pour un échiquier de i lignes, renvoie true si l'on peut placer
   * une reine en case (i, qi), et false sinon *)
  let no_conflicts (echiquier: t) (qi: int) =
    let i = List.length echiquier in
    (* Vérifie s'il n'y a pas déjà une reine sur la colonne qi *)
    let colonne_libre = List.for_all (fun q -> q <> qi) echiquier in
    (* Vérifie s'il n'y a pas déjà une reine sur la diagonale de
     * (i, qi) *)
    let diagonale_libre =
      echiquier
      |> List.mapi ( fun j qj -> qj <> qi-(i-j) && qj <> qi+(i-j) )
      |> List.for_all ( fun x -> x)
    in
    colonne_libre && diagonale_libre


  (* Renvoie les positions valides à partir d'un état de l'échiquier *)
  let next_positions (echiquier: t): t list =
    List.init n (fun i -> i)
    |> List.filter (no_conflicts echiquier)
    |> List.map (fun i -> List.rev (i::(List.rev echiquier)))

  let test_to_string () : unit =
    print_endline (to_string [3; 1; 6; 4; 2; 7; 0; 2]);
    print_endline (to_string [3; 1; 6]);
    print_endline "ok to_string"

  let test_no_conflicts : unit =
    let echiquier = [3; 1; 6] in
    assert (no_conflicts echiquier 4);
    assert (not (no_conflicts echiquier 0));  (* diagonale *)
    assert (not (no_conflicts echiquier 5));  (* diagonale *)
    assert (not (no_conflicts echiquier 7));  (* diagonale *)
    assert (not (no_conflicts echiquier 1));  (* colonne *)
    assert (not (no_conflicts echiquier 3));  (* colonne et diagonale *)
    assert (not (no_conflicts echiquier 6));  (* colonne et diagonale *)
    print_endline "ok no_conflicts"

  let test_next_positions : unit =
    assert (next_positions [] = [[0]; [1]; [2]; [3]; [4]; [5]; [6]; [7]]);
    assert (next_positions [0] = [[0; 2]; [0; 3]; [0; 4]; [0; 5]; [0; 6]; [0; 7]]);
    assert (next_positions [1; 3] = [[1; 3; 0]; [1; 3; 5]; [1; 3; 6]; [1; 3; 7]]);
    print_endline "ok next_positions"
end

module type Structure = sig
  type 'a t
  val create : unit -> 'a t
  val push : 'a -> 'a t -> unit
  val pop : 'a t -> 'a
  val is_empty : 'a t -> bool
end 

module Solver =
  functor (P: Puzzle) -> struct
    type hashtbl_type = (P.t, P.t option) Hashtbl.t

    let reconstruire (trail: hashtbl_type) (goal: P.t) : P.t list =
      let res = ref [] in
      let etat_courant = ref (Some goal) in
      while not (!etat_courant = None) do
        res := Option.get !etat_courant :: !res;
        etat_courant := Hashtbl.find trail (Option.get !etat_courant)
      done;
      !res

    let solve (etat_init: P.t) : P.t list =
      let file = Queue.create () in
      let trail = Hashtbl.create 8 in
      Queue.push etat_init file;
      Hashtbl.add trail etat_init None;

      let found_goal = ref false in
      let goal = ref None in

      while not (Queue.is_empty file || !found_goal) do
        let etat = Queue.pop file in
        if P.is_goal etat then begin
          found_goal := true;
          goal := Some etat 
        end else
          let suivants = P.next_positions etat in
          List.iter (
            fun etat' ->
              if Hashtbl.mem trail etat' then
                ()
              else begin
                Hashtbl.add trail etat' (Some etat);
                Queue.push etat' file
              end
          ) suivants
      done;
      reconstruire trail (Option.get !goal)

    end


(*
module JugPuzzleSolver = struct

  type hashtbl_type = (JugPuzzle.t, JugPuzzle.t option) Hashtbl.t

  (* Renconstruit le chemin menant de l'état initial à l'état final
   * à partir de la table de hachage de parents `trail` *)
  let reconstruire (trail: hashtbl_type) : JugPuzzle.t list =
    let res = ref [] in
    let etat_courant = ref (Some JugPuzzle.goal) in
    while not (!etat_courant = None) do
      res := Option.get !etat_courant :: !res;
      etat_courant := Hashtbl.find trail (Option.get !etat_courant)
    done;
    !res

  let solve (etat_init: JugPuzzle.t) : JugPuzzle.t list =
    let file: JugPuzzle.t Queue.t = Queue.create () in
    let trail: hashtbl_type = Hashtbl.create 8 in
    Queue.add etat_init file;
    Hashtbl.add trail etat_init None;

    while not (Queue.is_empty file) do
      let etat = Queue.pop file in
      let suivants = JugPuzzle.next_positions etat in
      List.iter (
        fun (etat': JugPuzzle.t) ->
          if Hashtbl.mem trail etat' then
            ()
          else begin
            Hashtbl.add trail etat' (Some etat);
            Queue.add etat' file
          end
      ) suivants
    done;
    reconstruire trail

  let solve2 (etat_init: JugPuzzle.t) : JugPuzzle.t list =
    let pile: JugPuzzle.t Stack.t = Stack.create () in
    let trail: hashtbl_type = Hashtbl.create 8 in
    Stack.push etat_init pile;
    Hashtbl.add trail etat_init None;

    while not (Stack.is_empty pile) do
      let etat = Stack.pop pile in
      let suivants = JugPuzzle.next_positions etat in
      List.iter (
        fun (etat': JugPuzzle.t) ->
          if Hashtbl.mem trail etat' then
            ()
          else begin
            Hashtbl.add trail etat' (Some etat);
            Stack.push etat' pile
          end
      ) suivants
    done;
    reconstruire trail

end

let test_solve : unit =
  JugPuzzleSolver.(
    assert (solve (8, 0, 0) = [
      (8, 0, 0); (3, 5, 0); (3, 2, 3); (6, 2, 0); (6, 0, 2); (1, 5, 2); (1, 4, 3); (4, 4, 0)
    ]);
    assert (solve (4, 4, 0) = [(4, 4, 0)]);
    assert (solve (4, 1, 3) = [(4, 1, 3); (4, 4, 0)])
  );
  print_endline "ok solve"


let test_solve : unit =
  JugPuzzleSolver.(
    assert (solve2 (8, 0, 0) = [
      (8, 0, 0); (5, 0, 3); (5, 3, 0); (2, 3, 3); (2, 5, 1); (7, 0, 1); (7, 1, 0); (4, 1, 3);
      (4, 4, 0)
    ]);
    assert (solve2 (4, 4, 0) = [(4, 4, 0)]);
    assert (solve2 (4, 1, 3) = [(4, 1, 3); (4, 4, 0)])
  );
  print_endline "ok solve2"




module NQueenSolver = struct

  type hashtbl_type = (NQueens.t, NQueens.t option) Hashtbl.t

  (* Renconstruit le chemin menant de l'état initial à l'état final `goal`
   * à partir de la table de hachage de parents `trail` *)
  let reconstruire (trail: hashtbl_type) (goal: NQueens.t) : NQueens.t list =
    let res = ref [] in
    let etat_courant = ref (Some goal) in
    while not (!etat_courant = None) do
      res := Option.get !etat_courant :: !res;
      etat_courant := Hashtbl.find trail (Option.get !etat_courant)
    done;
    !res

  let solve (etat_init: NQueens.t) (largeur: bool) : NQueens.t list =
    let file: NQueens.t Queue.t = Queue.create () in
    let trail: hashtbl_type = Hashtbl.create 8 in
    Queue.add etat_init file;
    Hashtbl.add trail etat_init None;

    let found_goal = ref false in
    let goal = ref None in

    while not (Queue.is_empty file || !found_goal) do
      let etat = Queue.pop file in
      if NQueens.is_goal etat then begin
        found_goal := true;
        goal := Some etat 
      end else
        let suivants = NQueens.next_positions etat in
        List.iter (
          fun (etat': NQueens.t) ->
            if Hashtbl.mem trail etat' then
              ()
            else begin
              Hashtbl.add trail etat' (Some etat);
              Queue.push etat' file
            end
        ) suivants
    done;
    reconstruire trail (Option.get !goal)

  let solve2 (etat_init: NQueens.t) : NQueens.t list =
    let pile: NQueens.t Stack.t = Stack.create () in
    let trail: hashtbl_type = Hashtbl.create 8 in
    Stack.push etat_init pile;
    Hashtbl.add trail etat_init None;

    let found_goal = ref false in
    let goal = ref None in

    while not (Stack.is_empty pile || !found_goal) do
      let etat = Stack.pop pile in
      if NQueens.is_goal etat then begin
        found_goal := true;
        goal := Some etat 
      end else
        let suivants = NQueens.next_positions etat in
        List.iter (
          fun (etat': NQueens.t) ->
            if Hashtbl.mem trail etat' then
              ()
            else begin
              Hashtbl.add trail etat' (Some etat);
              Stack.push etat' pile
            end
        ) suivants
    done;
    reconstruire trail (Option.get !goal)

end



let () = test_to_string ()
*)

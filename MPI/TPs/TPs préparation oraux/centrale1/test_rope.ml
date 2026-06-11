
(* `read file_name nb_lines)` lit les `nb_lines` premières lignes
   d'un fichier (si elles existent) dans une corde. *)
let read file_name nb_lines =
  let fp = open_in file_name in
  let rec add_lines nb c =
    try
      if nb <= 0 then raise End_of_file;
      let line = input_line fp in
      add_lines (nb - 1) (Rope.cat c (Rope.of_string (line ^ "\n")))
    with
      End_of_file -> close_in fp; c
  in
  add_lines nb_lines Rope.empty

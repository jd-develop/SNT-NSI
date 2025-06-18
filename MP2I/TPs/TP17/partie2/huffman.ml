
type huffman =
  | Leaf of int * char
  | Node of int * huffman * huffman


(* Renvoie la fréquence totale de h *)
let rec freq (h: huffman) : int =
  match h with
  | Leaf (i, _)
  | Node (i, _, _) -> i


(* Renvoie l’arbre contenant h1 et h2 comme sous-arbres *)
let fusion (h1: huffman) (h2: huffman) : huffman =
  Node(freq h1 + freq h2, h1, h2)


(* Convertit la chaîne s en liste de caractères *)
(* O(n) *)
let list_of_string (s: string) : char list =
  (* Idem mais démarre de l’indice i et renvoie la liste dans le sens inverse *)
  let rec list_of_string_starting_at_index (i: int) (s: string) =
    if i < 0 then []
    else (s.[i])::(list_of_string_starting_at_index (i-1) s)
  in
  List.rev (list_of_string_starting_at_index (String.length s - 1) s)


(*
 * Renvoie un dictionnaire contenant comme clefs les caractères apparaîssant
 * dans s, et comme valeurs la fréquence du caractère (i.e. le nombre de fois
 * qu’il apparaît dans s)
 *)
(* O(n) *)
(* TR *)
let count_freqs (s: string) : (char, int) Hashtbl.t =
  (* Idem mais en mettant à jour le dictionnaire t au lieu d’un créer un *)
  let rec count_freqs_accu (s: char list) (t: (char, int) Hashtbl.t) : (char, int) Hashtbl.t =
    match s with
    | [] -> t
    | c::q -> if Hashtbl.mem t c then
                Hashtbl.replace t c (Hashtbl.find t c + 1)
              else
                Hashtbl.replace t c 1;
              count_freqs_accu q t
    in
    count_freqs_accu (list_of_string s) (Hashtbl.create 16)


(* Construit la liste initiale des feulles de l’algo de Huffman *)
(* O(n) *)
let huffman_leaves (s: string) : huffman list =
  let freqs = count_freqs s in
  Hashtbl.fold (fun clef valeur res -> Leaf(valeur, clef)::res) freqs []


(* À partir de deux listes h1 et h2 triées par ordre croissant de fréquence,
 * construit une liste contenant les éléments de h1 et h2 par ordre croissant
 * de fréquence *)
let rec merge (h1: huffman list) (h2: huffman list) : huffman list =
  match (h1, h2) with
  | [], l
  | l, [] -> l
  | x1::q1, x2::q2 when freq x1 < freq x2 -> x1::(merge q1 h2)
  | x1::q1, x2::q2                        -> x2::(merge h1 q2)


(* Sépare une liste l en deux listes (l’ordre est conservé mais les éléments
 * alternent entre les deux listes) *)
let rec split (l: 'a list) : 'a list * 'a list =
  match l with
  | []  -> ([], [])
  | [x] -> ([x], [])
  | x::y::q -> let q1, q2 = split q in
               (x::q1, y::q2)


(* Trie h dans l’ordre croissant de fréquence *)
(* O(n log n) *)
let rec merge_sort (h: huffman list) : huffman list =
  match h with
  | [] -> []
  | [x] -> [x]
  | _ -> let h1, h2 = split h in
         let h1', h2' = merge_sort h1, merge_sort h2 in
         merge h1' h2'

(* Insère h au bon endroit dans hl triée par ordre croissant de fréquence *)
(* O(n) *)
(* TR *)
let insert_huffman (h: huffman) (hl: huffman list) : huffman list =
  (* Idem mais ajoute List.rev accu au début *)
  let rec insert_huffman_accu (h: huffman) (hl: huffman list) (accu: huffman list) : huffman list =
    match hl with
    | [] -> (List.rev (h::accu))
    | h'::q -> if freq h' < freq h then insert_huffman_accu h q (h'::accu)
               else (List.rev accu) @ (h::hl)
  in insert_huffman_accu h hl []


(*
 * Renvoie l’arbre de Huffman contenant tous les sous-arbres de hl (hl triée
 * par ordre croissant de fréquence et non vide)
 *)
(* O(n^3) (avec des tas binaires : O(n^2)) *)
(* TR *)
let rec fusion_huffman (hl: huffman list) : huffman =
  match hl with
  | [] -> failwith "hl ne doit pas être vide"
  | [h] -> h
  | h1::h2::q -> let h' = fusion h1 h2 in
                 let q' = insert_huffman h' q in
                 fusion_huffman q'


(* Construit l’arbre de Huffman du texte s, supposé non vide *)
(* O(n^3 + n + n log n) (O(n^2 + n + n log n) avec des tas binaires) *)
let huffman_tree (s: string) : huffman =
  assert (String.length s <> 0);
  fusion_huffman (merge_sort (huffman_leaves s))

(* Construit le dictionnaire qui à chaque caractère associe son chemin dans
 * l’arbre de huffman hf *)
let construire_table (h: huffman) : (char, bool list) Hashtbl.t =
  let tbl = Hashtbl.create 16 in
  (* Ajoute à tbl les associations truc@(List.rev l) pour truc chemin valide
   * dans h *)
  let rec construire_table_chemin (h: huffman) (l: bool list) : unit =
    match h with
    | Leaf(_, c) -> Hashtbl.replace tbl c (List.rev l)
    | Node(_, h1, h2) ->
        construire_table_chemin h1 (false::l);
        construire_table_chemin h2 (true::l)
    in
    construire_table_chemin h [];
    tbl


(* Affiche une liste de booléens sous forme de bits *)
let rec print_bool_list (l: bool list) : unit =
  match l with
  | [] -> ()
  | x::q -> if x then print_char '1' else print_char '0';
            print_bool_list q

(* Affiche la table construite par construire_table *)
let print_table_huffman (tbl: (char, bool list) Hashtbl.t) : unit =
  let _ = Hashtbl.fold (
    fun clef valeur _ ->
      print_char clef;
      print_char ' ';
      print_bool_list valeur;
      print_newline ();
      []
  ) tbl []
  in ()


(* Renvoie l’encodage de huffman de s (supposée non vide), sous forme de
 * l’encodage à proprement parler et de l’arbre *)
let compression_huffman (s: string) : (bool list * huffman) =
  (* deja_fait est dans l’ordre inverse *)
  let rec compression_huffman_accu (s: char list) (h: huffman) (tbl: (char, bool list) Hashtbl.t) (deja_fait : bool list) : bool list =
    match s with
    | [] -> List.rev deja_fait
    | c::q -> compression_huffman_accu q h tbl ((List.rev (Hashtbl.find tbl c))@deja_fait)
  in
  let h = huffman_tree s in
  let tbl = construire_table h in
  (compression_huffman_accu (list_of_string s) h tbl [], h)


(* Lit la chaîne codée chemin dans l’arbre h, renvoie le caractère lu
 * et la liste restante. *)
let rec read_path (h: huffman) (chemin: bool list) : char * bool list =
  match h, chemin with
  | Leaf(_, c), _ -> c, chemin
  | Node(_, _, _), [] -> failwith "Codage invalide"
  | Node(_, h1, _), false::q -> read_path h1 q
  | Node(_, _, h2), true::q  -> read_path h2 q


(* Décode l avec l’arbre de huffman h, et renvoie le texte construit *)
let decompression_huffman (l: bool list) (h: huffman) : string =
  let rec decompression_huffman_accu (l: bool list) (h: huffman) (deja_construit: string) : string =
    match l with
    | [] -> deja_construit
    | _  -> let c, l' = read_path h l in
            decompression_huffman_accu l' h (deja_construit ^ String.make 1 c)
  in
  decompression_huffman_accu l h ""


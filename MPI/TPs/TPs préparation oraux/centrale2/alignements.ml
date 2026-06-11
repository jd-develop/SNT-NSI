type dir = Gauche | Diag | Haut | Origine
type case = {score : int; d : dir}


let blosum =
[|[|4; -1; -2; -2;  0; -1; -1;  0; -2; -1; -1; -1; -1; -2; -1;  1;  0; -3; -2;  0|];
[|-1;  5;  0; -2; -3;  1;  0; -2;  0; -3; -2;  2; -1; -3; -2; -1; -1; -3; -2; -3|];
[|-2;  0;  6;  1; -3;  0;  0;  0;  1; -3; -3;  0; -2; -3; -2;  1;  0; -4; -2; -3|];
[|-2; -2;  1;  6; -3;  0;  2; -1; -1; -3; -4; -1; -3; -3; -1;  0; -1; -4; -3; -3|];
[| 0; -3; -3; -3;  9; -3; -4; -3; -3; -1; -1; -3; -1; -2; -3; -1; -1; -2; -2; -1|];
[|-1;  1;  0;  0; -3;  5;  2; -2;  0; -3; -2;  1;  0; -3; -1;  0; -1; -2; -1; -2|];
[|-1;  0;  0;  2; -4;  2;  5; -2;  0; -3; -3;  1; -2; -3; -1;  0; -1; -3; -2; -2|];
[| 0; -2;  0; -1; -3; -2; -2;  6; -2; -4; -4; -2; -3; -3; -2;  0; -2; -2; -3; -3|];
[|-2;  0;  1; -1; -3;  0;  0; -2;  8; -3; -3; -1; -2; -1; -2; -1; -2; -2;  2; -3|];
[|-1; -3; -3; -3; -1; -3; -3; -4; -3;  4;  2; -3;  1;  0; -3; -2; -1; -3; -1;  3|];
[|-1; -2; -3; -4; -1; -2; -3; -4; -3;  2;  4; -2;  2;  0; -3; -2; -1; -2; -1;  1|];
[|-1;  2;  0; -1; -3;  1;  1; -2; -1; -3; -2;  5; -1; -3; -1;  0; -1; -3; -2; -2|];
[|-1; -1; -2; -3; -1;  0; -2; -3; -2;  1;  2; -1;  5;  0; -2; -1; -1; -1; -1;  1|];
[|-2; -3; -3; -3; -2; -3; -3; -3; -1;  0;  0; -3;  0;  6; -4; -2; -2;  1;  3; -1|];
[|-1; -2; -2; -1; -3; -1; -1; -2; -2; -3; -3; -1; -2; -4;  7; -1; -1; -4; -3; -2|];
[| 1; -1;  1;  0; -1;  0;  0;  0; -1; -2; -2;  0; -1; -2; -1;  4;  1; -3; -2; -2|];
[| 0; -1;  0; -1; -1; -1; -1; -2; -2; -1; -1; -1; -1; -2; -1;  1;  5; -2; -2;  0|];
[|-3; -3; -4; -4; -2; -2; -3; -2; -2; -3; -2; -3; -1;  1; -4; -3; -2; 11;  2; -3|];
[|-2; -2; -2; -3; -2; -1; -2; -3;  2; -1; -1; -2; -1;  3; -3; -2; -2;  2;  7; -1|];
[| 0; -3; -3; -3; -1; -2; -2; -3; -3;  3;  1; -2;  1; -1; -2; -2;  0; -3; -1;  4|]|]

let alphabet = [|'A'; 'R'; 'N'; 'D'; 'C'; 'Q'; 'E'; 'G'; 'H'; 'I'; 'L'; 'K'; 'M'; 'F'; 'P'; 'S'; 'T'; 'W'; 'Y'; 'V'|]

let to_ind (c : char) : int =
  let i = ref 0 in
  while alphabet.(!i) != c do
    i := !i + 1;
  done;
  !i


type dendro = Noeud of dendro * dendro | Feuille of string

let rec print_dendro (d : dendro) (accu : string) =
  (* Affiche un dendrogramme *)
  match d with
  | Feuille s -> Printf.printf "%s%s\n" accu s
  | Noeud (d1, d2) ->
    Printf.printf "%s-----\n" accu;
    print_dendro d1 (accu ^ "|  ");
    print_dendro d2 (accu ^ "|  ");
    Printf.printf "%s-----\n" accu



let insuline_humain = "MALWMRLLPLLALLALWGPDPAAAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGGGPGAGSLQPLALEGSLQKRGIVEQCCTSICSLYQLENYCN"
let insuline_chien = "MALWMRLLPLLALLALWAPAPTRAFVNQHLCGSHLVEALYLVCGERGFFYTPKARREVEDLQVRDVELAGAPGEGGLQPLALEGALQKRGIVEQCCTSICSLYQLENYCN"
let insuline_poisson = "MAVWIQAGALLFLLAVSSVNANAGAPQHLCGSHLVDALYLVCGPTGFFYNPKRDVDPPLGFLPPKSAQETEVADFAFKDHAEVIRKRGIVEQCCHKPCSIFELQNYCN"
let insuline_poule = "MALWIRSLPLLALLVFSGPGTSYAAANQHLCGSHLVEALYLVCGERGFFYSPKARRDVEQPLVSSPLRGEAGVLPFQQEEYEKVKRGIVEQCCHNTCSLYQLENYCN"


(* Insulines provenant d'espèces inconnues *)
let insuline_X1 = "MALWMRLLPLLVLLALWGPDPASAFVNQHLCGSHLVEALYLVCGERGFFYTPKTRREAEDLQVGQVELGGGPGAGSLQPLALEGSLQKRGIVEQCCTSICSLYQLENYCN"
let insuline_X2 = "MAALWLQSVSLLVLMLVSWSGSQAVLPPQHLCGAHLVDALYLVCGERGFFYTPKRDVDPLLGFLPAKSGGAAAGGENEVAEFAFKDQMEMMVKRGIVEQCCHKPCNIFDLQNYCN"
let insuline_X3 = "MALWTRLVPLLALLALWAPAPAHAFVNQHLCGSHLVEALYLVCGERGFFYTPKARREVEGPQVGALELAGGPGAGGLEGPPQKRGIVEQCCAGVCSLYQLENYCN"


(* Code *)
let blosum_get (a: char) (b: char) : int =
  blosum.(to_ind a).(to_ind b)

let needleman_wunsch (u: string) (v: string) : case array array =
  let n = String.length u in
  let m = String.length v in
  let res = Array.init (n+1) (fun _ -> Array.make (m+1) {score=0; d=Origine}) in
  for i = 1 to n do
    res.(i).(0) <- {score=(-3)*i; d=Haut}
  done;
  for j = 1 to m do
    res.(0).(j) <- {score=(-3)*j; d=Gauche}
  done;
  for i = 1 to n do
    for j = 1 to m do
      let diag = res.(i-1).(j-1).score + blosum_get u.[i-1] v.[j-1] in
      let gauche = res.(i).(j-1).score - 3 in
      let haut = res.(i-1).(j).score - 3 in
      if diag >= gauche && diag >= haut then
        res.(i).(j) <- {score=diag; d=Diag}
      else if gauche >= haut then
        res.(i).(j) <- {score=gauche; d=Gauche}
      else
        res.(i).(j) <- {score=haut; d=Haut}
    done
  done;
  res


let score (t: case array array) : int =
  let n = Array.length t in
  let m = Array.length t.(n-1) in
  t.(n-1).(m-1).score

let affiche_alignement (t: case array array) (u: string) (v: string) : unit =
  let n = Array.length t in
  let m = Array.length t.(n-1) in
  (* Construit deux listes de caractères de u et v ou - dans l'ordre origine->fin *)
  let rec liste_cases
      (i: int) (j: int) (uacc: char list) (vacc: char list) : char list * char list =
    match t.(i).(j).d with
      | Origine -> uacc, vacc
      | Haut -> liste_cases (i-1) j (u.[i-1]::uacc) ('-'::vacc)
      | Gauche -> liste_cases i (j-1) ('-'::uacc) (v.[j-1]::vacc)
      | Diag -> liste_cases (i-1) (j-1) (u.[i-1]::uacc) (v.[j-1]::vacc)
  in
  let uchars, vchars = liste_cases (n-1) (m-1) [] [] in
  List.iter print_char uchars;
  print_newline ();
  List.iter print_char vchars;
  print_newline ()


let parse_fichier (filename: string) : string array * string array =
  let fp = open_in filename in
  let n = int_of_string (input_line fp) in
  let noms = Array.make n "" in
  let seqs = Array.make n "" in
  for i = 0 to n-1 do
    noms.(i) <- input_line fp;
    seqs.(i) <- input_line fp;
  done;
  close_in fp;
  noms, seqs

(* Insère un élément dans une liste triée dans l'ordre décroissant *)
let rec insere_liste (l: 'a list) (e: 'a): 'a list =
  match l with
  | [] -> [e]
  | x::q when e >= x -> e::x::q
  | x::q -> x::(insere_liste q e)

let compare_toutes_sequences (seqs: string array) : (int * int * int) list =
  let n = Array.length seqs in
  let res = ref [] in
  for i = 0 to n-1 do
    for j = i+1 to n-1 do
      res := insere_liste !res (score (needleman_wunsch seqs.(i) seqs.(j)), i, j)
    done
  done;
  !res


(* Union-find *)
type uf = {
  rangs: int array;
  parents: int array
}



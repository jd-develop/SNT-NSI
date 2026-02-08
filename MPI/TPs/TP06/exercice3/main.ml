
(* Question 1
 *
 * On fait deux fils d’exécutions qui auront pour but de chercher le maximum sur
 * deux moitiés de tableau, ces deux fils d’exécution crééront à leur tour
 * deux fils d’exécution, etc. On renvoie ensuite le maximum des résultats des
 * deux fils.
 * C’est bien en Theta(log(n)) : l’équation de complexité s’écrit
 * C(n) = 2C(n/2) + Theta(1), qui se résoud bien en Theta(log(n))
 *)

type espace_recherche = {
  tab: int array;
  g: int;
  d: int;
  mutable ret: int;
}

let rec recherche_max_thread (args: espace_recherche) : unit =
  if args.g = args.d then
    args.ret <- args.tab.(args.g)
  else begin
    let milieu = (args.g+args.d)/2 in
    let args1 = {
      tab = args.tab;
      g = args.g;
      d = milieu;
      ret = -1
    } in
    let args2 = {
      tab = args.tab;
      g = milieu+1;
      d = args.d;
      ret = -1
    } in
    let pa = Thread.create recherche_max_thread args1 in
    let pb = Thread.create recherche_max_thread args2 in
    Thread.join pa;
    Thread.join pb;
    args.ret <- max (args1.ret) (args2.ret)
  end

let recherche_max (tab: int array) : int =
  let n = Array.length tab in
  if n = 0 then
    failwith "Tableau vide !"
  else begin
    let args = {
      tab;
      g = 0;
      d = n-1;
      ret = -1
    } in
    print_endline "Je commence…";
    recherche_max_thread args;
    print_endline "J’ai fini !";
    args.ret
  end


let recherche_max_classique (tab: int array) : int =
  let n = Array.length tab in
  if n = 0 then
    failwith "Tableau vide !"
  else
    Array.fold_left max (tab.(0)) tab

let test_recherche_max : unit =
  Random.self_init ();  (* prend la graine de génération dans /dev/urandom *)
  (* On ne fait qu’un seul tableau parce que recherche_max est très lent *)
  let a = Array.init 10000 (fun _ -> Random.int 1000) in
  assert (recherche_max a = recherche_max_classique a)


(* Pour n’utiliser qu’au plus n fils d’exécution, on peut ne créer qu’un seul
 * fil d’exécution récursif à chaque appel, s’occupant de la première moitié
 * du tableau, et nous-même s’occuper de la seconde moitié *)

let rec recherche_max_thread_meilleur (args: espace_recherche) : unit =
  let g = ref args.g in
  let threads = ref [] in
  let args_list = ref [] in
  while !g <> args.d do
    let milieu = (!g+args.d)/2 in
    let args1 = {
      tab = args.tab;
      g = !g;
      d = milieu;
      ret = -1
    } in
    g := milieu+1;
    threads := (Thread.create recherche_max_thread_meilleur args1)::!threads;
    args_list := args1::!args_list
  done;
  List.iter Thread.join !threads;
  (* On fait le maximum entre tous les max calculés par les threads et le
   * nôtre *)
  args.ret <- List.fold_left max (args.tab.(args.d))
                             (List.map (fun x -> x.ret) !args_list)


let recherche_max_meilleur (tab: int array) : int =
  let n = Array.length tab in
  if n = 0 then
    failwith "Tableau vide !"
  else begin
    let args = {
      tab;
      g = 0;
      d = n-1;
      ret = -1
    } in
    print_endline "Je commence…";
    recherche_max_thread_meilleur args;
    print_endline "J’ai fini !";
    args.ret
  end


let test_recherche_max_meilleeur : unit =
  (* Ça reste lent mais c’est deux fois moins lent (sur ma machine) que le
   * précédent sur un tableau de taille 10000 *)
  let a = Array.init 10000 (fun _ -> Random.int 1000) in
  assert (recherche_max_meilleur a = recherche_max_classique a)


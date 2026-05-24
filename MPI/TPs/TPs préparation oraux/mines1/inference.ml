(* Implémentation de dictionnaire *)
type ('a, 'b) dict =
 | Vide
 | Noeud of 'a * 'b * ('a, 'b) dict * ('a, 'b) dict

(* Crée et renvoie un dictionnaire vide *)
let dict_vide () : ('a, 'b) dict =
  Vide

exception CleIntrouvable

(* Renvoie la valeur associée à `cle` dans le dictionnaire `dico`, ou lève
 * CleIntrouvable si la clé n’est pas dans le dictionnaire *)
let rec assoc (dico : ('a, 'b) dict) (cle: 'a) : 'b =
  match dico with
  | Vide -> raise CleIntrouvable
  | Noeud (etiquette, valeur, gauche, droite) ->
    if etiquette = cle then
      valeur
    else if cle < etiquette then
      assoc gauche cle
    else
      assoc droite cle

exception ExisteDeja

(* Insère une clé et une valeur dans le dictionnaire `dico` puis renvoie le
 * dictionnaire ainsi modifié. Lève ExisteDeja si jamais la clé est déjà
 * présente dans le dictionnaire *)
let rec insere (dico: ('a, 'b) dict) (cle: 'a) (valeur: 'b) : ('a, 'b) dict =
  match dico with
  | Vide -> Noeud (cle, valeur, Vide, Vide)
  | Noeud (etiquette, val_courante, gauche, droite) ->
    if etiquette = cle then
      raise ExisteDeja
    else if cle < etiquette then
      Noeud (etiquette, val_courante, insere gauche cle valeur, droite)
    else
      Noeud (etiquette, val_courante, gauche, insere droite cle valeur)

(* Applique f à toutes les valeurs de dict *)
let rec dict_map (dico: ('a, 'b) dict) (f: 'b -> 'c) : ('a, 'c) dict =
  match dico with
  | Vide -> Vide
  | Noeud (etiquette, valeur, gauche, droite) ->
    Noeud (etiquette, f valeur, dict_map gauche f, dict_map droite f)

let test_dico : unit =
  let dico1 = dict_vide () in
  let dico2 =
    insere (insere (insere (insere dico1 "c" 15) "a" 3) "d" (-1)) "b" (6) in
  assert (dico2 =
      Noeud(
        "c", 15,
        Noeud(
          "a", 3,
          Vide,
          Noeud("b", 6, Vide, Vide)
        ),
        Noeud("d", (-1), Vide, Vide)
     ));
  try (let _ = insere dico2 "b" 12 in assert false) with
  | ExisteDeja -> ();
  assert (assoc dico2 "a" = 3);
  assert (assoc dico2 "b" = 6);
  assert (assoc dico2 "c" = 15);
  assert (assoc dico2 "d" = -1);
  try (let _ = assoc dico2 "e" in assert false) with
  | CleIntrouvable -> ();
  print_endline "ok dictionnaires"

(* Inférence avec annotation de paramètre *)

type typ1 =
  | Int  (* type de base des entiers *)
  | Arrow of typ1 * typ1  (* t1 -> t2 *)
  | Product of typ1 * typ1  (* t1 * t2 *)

type expression1 =
  | Var of string
  | Const of int
  | Op of string  (* opérateur prenant un couple d'entiers et renvoyant un
                   * entier *)
  | Fun of string * typ1 * expression1  (* fun (x : t) -> e *)
  | App of expression1 * expression1  (* e1 e2 *)
  | Couple of expression1 * expression1  (* e1, e2 *)
  | Let of string * expression1 * expression1  (* let x = e1 in e2 *)

let rec print_typ1 (type_: typ1) : unit =
  match type_ with
  | Int -> print_string "int"
  | Arrow (a, b) ->
    begin
      print_string "(";
      print_typ1 a;
      print_string " -> ";
      print_typ1 b;
      print_string ")"
    end
  | Product (a, b) ->
    begin
      print_string "(";
      print_typ1 a;
      print_string ", ";
      print_typ1 b;
      print_string ")"
    end

let rec print_expression1 (expr': expression1) : unit =
  match expr' with
  | Var x -> print_string x
  | Const i -> print_int i
  | Op op -> print_string op
  | Fun (x, t, e) ->
    begin
      print_string "fun ";
      print_string x;
      print_string " : ";
      print_typ1 t;
      print_string " -> ";
      print_expression1 e
    end
  | App (e1, e2) ->
    begin
      print_string "(";
      print_expression1 e1;
      print_string ") (";
      print_expression1 e2;
      print_string ")"
    end
  | Couple (e1, e2) ->
    begin
      print_string "(";
      print_expression1 e1;
      print_string ", ";
      print_expression1 e2;
      print_string ")"
    end
  | Let (x, e1, e2) ->
    begin
      print_string ("let "^x^" = ");
      print_expression1 e1;
      print_string " in ";
      print_expression1 e2
    end


exception NonTypable

(* Renvoie le type de e, ou lève NonTypable si e n'est pas typable *)
let rec typ_expr (e: expression1) : typ1 =
  let rec typ_expr_gamma (e': expression1) (gamma: (string, typ1) dict) : typ1 =
    match e' with
    | Var x -> assoc gamma x
    | Const _ -> Int
    | Op _ -> Arrow (Product (Int, Int), Int)
    | Fun (x, typ_arg, e1) ->
      let gamma' = insere gamma x typ_arg in
      Arrow (typ_arg, typ_expr_gamma e1 gamma')
    | App (e1, e2) ->
      let typ_e1 = typ_expr_gamma e1 gamma in
      begin match typ_e1 with
        | Arrow (typ_arg, typ_retour) ->
          let typ_e2 = typ_expr_gamma e2 gamma in
          if typ_arg = typ_e2 then
            typ_retour
          else
            raise NonTypable
        | _ -> raise NonTypable
      end
    | Couple (e1, e2) ->
        Product (typ_expr_gamma e1 gamma, typ_expr_gamma e2 gamma)
    | Let (x, e1, e2) ->
      let typ_x = typ_expr_gamma e1 gamma in
      let gamma' = insere gamma x typ_x in
      typ_expr_gamma e2 gamma'
 in
 typ_expr_gamma e (dict_vide ())

(* tests *)

let test1 e =
  print_expression1 e;
  print_newline ();
  begin
  try
  print_typ1 (typ_expr e);
  with _ -> print_string "terme non typable"
  end;
  print_newline ();;

let e = Let ("f",
Fun ("x", Int, App (Op "+", Couple (Var "x", Const 1))),
App (Var "f", Const 2))
in test1 e;;
print_newline ();
(* type attendu : int *)

let e = Fun( "f", Arrow(Int, Int) ,
Fun ("g", Arrow(Int, Int),
Fun("x" , Int,
App (Var "f" , App(Var "g", Var "x")))))
in
test1 e;;
print_newline ();
(* type attendu : (int -> int) -> (int -> int) -> int -> int *)

let e = Fun("x", Int , App(Var "x", Var "x"))
in
test1 e;;
print_newline ();
(* non typable *)

let e = App (Fun("x", Int, Var "x"),
App(Fun("x", Product(Int, Int),App(Op "+", Var "x")), Couple(Const 1, Const 2)))
in test1 e;;
print_newline ();
(* int *)


(* Inférence sans annotation *)

type typ2 =
  | Int
  | Arrow of typ2 * typ2
  | Product of typ2 * typ2
  | Tvar of int

type expression2 =
  | Var of string
  | Const of int
  | Op of string
  | Fun of string * expression2
  | App of expression2 * expression2
  | Couple of expression2 * expression2
  | Let of string * expression2 * expression2


let rec print_typ2 (type_: typ2) : unit =
  match type_ with
  | Int -> print_string "int"
  | Arrow (a, b) ->
    begin
      print_string "(";
      print_typ2 a;
      print_string " -> ";
      print_typ2 b;
      print_string ")"
    end
  | Product (a, b) ->
    begin
      print_string "(";
      print_typ2 a;
      print_string ", ";
      print_typ2 b;
      print_string ")"
    end
  | Tvar i -> print_int i

let rec print_expression2 (expr': expression2) : unit =
  match expr' with
  | Var x -> print_string x
  | Const i -> print_int i
  | Op op -> print_string op
  | Fun (x, e) ->
    begin
      print_string ("fun "^x^" -> ");
      print_expression2 e
    end
  | App (e1, e2) ->
    begin
      print_string "(";
      print_expression2 e1;
      print_string ") (";
      print_expression2 e2;
      print_string ")"
    end
  | Couple (e1, e2) ->
    begin
      print_string "(";
      print_expression2 e1;
      print_string ", ";
      print_expression2 e2;
      print_string ")"
    end
  | Let (x, e1, e2) ->
    begin
      print_string ("let "^x^" = ");
      print_expression2 e1;
      print_string " in ";
      print_expression2 e2
    end

let rec appliquer (subst: (int, typ2) dict) (typ: typ2) : typ2 =
  match typ with
  | Int -> Int
  | Arrow (t1, t2) -> Arrow (appliquer subst t1, appliquer subst t2)
  | Product (t1, t2) -> Product (appliquer subst t1, appliquer subst t2)
  | Tvar i ->
    begin try (assoc subst i) with
    | CleIntrouvable -> Tvar i
    end

let test_appliquer : unit =
  let dico = insere (dict_vide ()) 1 (Arrow (Int, Int)) in
  assert (
    appliquer dico (Product (Arrow (Tvar 1, Tvar 1), Arrow (Tvar 2, Tvar 2))) =
    Product (Arrow (Arrow (Int, Int), Arrow (Int, Int)), Arrow (Tvar 2, Tvar 2))
  );
  print_endline "ok appliquer"


(* renvoie true si Tvar i apparaît dans t, false sinon *)
let rec est_libre (i: int) (t: typ2) : bool =
  match t with
  | Int -> false
  | Arrow (t1, t2)
  | Product (t1, t2) -> est_libre i t1 || est_libre i t2
  | Tvar j -> i = j


exception UnificationImpossible

let rec unification (subst: (int, typ2) dict) (ta: typ2) (tb: typ2) :
    (int, typ2) dict =
  let ta', tb' = appliquer subst ta, appliquer subst tb in
  if ta' = tb' then
    subst
  else match ta', tb' with
  | (Arrow(t1, t1'), Arrow(t2, t2'))
  | (Product(t1, t1'), Product(t2, t2')) ->
    let subst' = unification subst t1 t2 in
    unification subst' (appliquer subst' t1') (appliquer subst' t2')
  | (Tvar i, t) | (t, Tvar i) ->
    if est_libre i t then begin
      raise UnificationImpossible
    end else
      (* substutuer i par t partout où i apparaît dans la substitution et lui
       * ajouter i->t *)
      let subst_temporaire = insere (dict_vide ()) i t in
      let nouvelle_subst = dict_map subst (appliquer subst_temporaire) in
      insere nouvelle_subst i t
  | _ -> raise UnificationImpossible

(*tests unification *)

let test_unif t1 t2 =
  print_string "t1 : ";
  print_typ2 t1;
  print_newline ();
  print_string "t2 : ";
  print_typ2 t2;
  print_newline ();
  begin
  try
  let s = unification (dict_vide ()) t1 t2 in
  print_string "unification : ";
  print_typ2 (appliquer s t1);
  with _ -> print_string "types non unifiables"
  end;
  print_newline ();;

let t1 = Arrow(Tvar 0 , Int) in
let t2 = Arrow(Tvar 1 , Tvar 2) in
test_unif t1 t2;;
(* 1 -> int *)

let t1 = Arrow(Tvar 0 , Int) in
let t2 = Product(Tvar 1 , Tvar 2) in
test_unif t1 t2;;
(* échec *)

let t1 = Arrow(Product(Tvar 0, Tvar 1) , Int) in
let t2 = Arrow(Product(Int, Int)  , Tvar 3) in
test_unif t1 t2;;
(* (int * int) -> int *)

let t1 = Arrow(Tvar 0, Tvar 0) in
let t2 = Arrow(Int, Tvar 1) in
test_unif t1 t2;;
(* int -> int *)

let t1 = Arrow(Tvar 0, Tvar 0) in
let t2 = Arrow(Int, Product(Int, Int)) in
test_unif t1 t2;;
(* échec *)

print_newline ();;


let w (e: expression2) : typ2 =
  (* Inférence de type avec mémorisation du nombre actuel pour la prochaine
   * variable de type, en se souvenant du type des variables et de la
   * substitution *)
  let rec w_subst (e': expression2) (tvar_number: int)
      (typ_vars: (string, typ2) dict) (subst: (int, typ2) dict) :
      typ2 * int * (string, typ2) dict * (int, typ2) dict =
    match e' with
    | Var x -> appliquer subst (assoc typ_vars x), tvar_number, typ_vars, subst
    | Const _ -> Int, tvar_number, typ_vars, subst
    | Op _ -> Arrow (Product (Int, Int), Int), tvar_number, typ_vars, subst
    | Fun (parameter, body) ->
        let typ_body, new_num, new_vars, new_subst =
          w_subst body (tvar_number+1)
          (insere typ_vars parameter (Tvar tvar_number)) subst
        in
        appliquer new_subst (Arrow (Tvar tvar_number, typ_body)), new_num,
          new_vars, new_subst
    | App (e1, e2) ->
        let typ_e1, new_num, new_vars, new_subst =
          w_subst e1 tvar_number typ_vars subst in
        let typ_e2, new_num', new_vars', new_subst' =
          w_subst e2 new_num new_vars new_subst in
        let typ_out = Tvar (new_num') in
        let new_subst'' =
          unification new_subst' typ_e1 (Arrow(typ_e2, typ_out)) in
        appliquer new_subst'' typ_out, new_num'+1, new_vars', new_subst''
    | Couple (e1, e2) ->
        let typ_e1, new_num, new_vars, new_subst =
          w_subst e1 tvar_number typ_vars subst in
        let typ_e2, new_num', new_vars', new_subst' =
          w_subst e2 new_num new_vars new_subst in
        Product(typ_e1, typ_e2), new_num', new_vars', new_subst'
    | Let _ -> raise (Invalid_argument "On ne s’autorise pas aux let")
  in
  let typ, _, _, _ = w_subst e 0 (dict_vide ()) (dict_vide ()) in
  typ


(* Tests W *)

let test2 e =
  print_expression2 e;
  print_newline ();
  begin
  try
  print_typ2 (w e);
  with _ -> print_string "terme non typable"
  end;
  print_newline ();;

let e = Fun("x", App (Var "x", Const 2)) in
test2 e;;
(* (int -> 1) -> 1 *)


let e = Fun("x", App (Op "+", Couple(Var "x", Var "x")))in
test2 e;;
(* int -> int *)

let e = Fun( "f", Fun ("g", Fun("x" , App (Var "f" , App(Var "g", Var "x")) ) ))in
test2 e;;
(* (3 -> 4) -> ((2 -> 3) -> (2 -> 4)) *)

let e =  (App (Fun ("f", App (Op "+", App (Var "f", Const 1))),
Fun ("x", Var "x")))in
test2 e;;
(* échec *)

let e =(Fun ("x", Couple (App (Var "x", Const 1),
App (Var "x", Couple (Const 1, Const 2)))))in
test2 e;;
(* échec *)

(* Inférence avec polymorphisme *)

(* Tests avec polymorphisme *)

(*
let test2 e =
  print_expression2 e;
  print_newline ();
  begin
  try
  print_typ2 (w e);
  with _ -> print_string "terme non typable"
  end;
  print_newline ();;

let e = (Let ("f",
Fun ("x", App (Op "+", Couple (Var "x", Const 1))),
App (Var "f", Const 2)))in
test2 e;;
(* int *)

let id = Fun ("x", Var "x");;

let e = (Let ("f",
id , App(Var "f", Var "f"))) in
test2 e;;
(* 2 -> 2 *)

let e = Let("f", Fun ("x", Var "x"), Couple(App (Var "f",id), App (Var "f", Const 2)))in
test2 e;;
(* (4 -> 4) * int *)

let e = Let("f", Fun ("x", Var "x"), Couple(App (Var "f", Const 2), App (Var "f",id)))in
test2 e;;
(* int * (2 -> 2) *)

let e = Let("f", Fun ("x", Var "x"), Couple(App (Var "f", Const 2), App (Var "f", Fun("x", Const 2) )))in
test2 e;;
(* int * (2 -> int) *)

let e = (Let ("id", Fun ("x", Var "x"),
Couple (App (Var "id", Const 1),
App (Var "id", Couple (Const 1, Const 2)))))in
test2 e;;
(* int * (int * int) *)

let e =  (Fun ("f", Fun ("x", Let ("y", App (Var "f", Var "x"), Var "y"))))in
test2 e;;
(* (1 -> 2) -> (1 -> 2) *)

let e =  (Fun ("x",
Let ("z", Var "x",
Couple (App (Var "z", Const 1),
App (Var "z", Couple (Const 1, Const 2)))))) in
test2 e;;
(* echec *)

let e = Let ("distr_pair",
Fun ("f", Couple (App (Var "f", Const 1),
App (Var "f", Couple (Const 1, Const 2)))),
App (Var "distr_pair", (Fun ("x", Var "x")))) in
test2 e;;
(* echec *)
*)

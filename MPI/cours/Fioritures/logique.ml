type formule =
  | Top
  | Bot
  | Var of string
  | Not of formule
  | Or of formule * formule
  | And of formule * formule
  | Implies of formule * formule
  | Equiv of formule * formule


(* Évalue f sur les variables v. Une variable dans la liste est
 * considérée comme vraie, une variable pas dans la liste est considérée comme
 * false *)
let rec eval (f: formule) (v: string list) : bool =
  match f with
  | Top -> true
  | Bot -> false
  | Var s -> List.mem s v
  | Not f -> not (eval f v)
  | Or(f1, f2) -> eval f1 v || eval f2 v
  | And(f1, f2) -> eval f1 v && eval f2 v
  | Implies(f1, f2) -> not (eval f1 v) || eval f2 v
  | Equiv(f1, f2) -> ((eval f1 v) && (eval f2 v)) || not ((eval f1 v) || (eval f2 v))

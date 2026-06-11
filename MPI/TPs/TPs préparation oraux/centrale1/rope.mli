
(* Type corde pour représenter une chaîne de caractères *)
type rope

(* `length c` renvoie la longueur de la chaîne de caractères
   représentée par la corde `c` *)
val length : rope -> int

(* La corde vide. *)
val empty : rope

(* `of_string s` renvoie une corde qui représente la chaîne de
   caractères `s` *)
val of_string : string -> rope

(* `to_string c` renvoie la chaîne de caractères représentée par la
   corde `c` *)
val to_string : rope -> string

(* `make n x` est une corde représentant la chaîne de caractères
   constituée de `n` fois le caractère `x` *)
val make : int -> char -> rope

(* `cat c1 c2` est une corde représentant la concaténation des
   chaînes de caractères représentées par `c1` et `c2` *)
val cat : rope -> rope -> rope

(* `get c i` est le caractère en indice `i` de la chaîne de caractères
   représentée par la corde `c`. Lève l'exception `Invalid_argument`
   si `i` n'est pas un indice valable. *)
val get : rope -> int -> char

(* `sub c pos len` est une corde représentant la sous-chaîne de
   caractères commençant à l'indice `pos` de longueur `len` de la
   chaîne de caractère représentée par la corde `c`. Lève l'exception
   `Invalid_argument` si `pos` et `len` ne désignent pas une
   sous-chaîne valide. *)
val sub : rope -> int -> int -> rope

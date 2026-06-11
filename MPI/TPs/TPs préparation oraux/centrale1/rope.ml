type rope =
  | Base of string * int * int
  | Concat of rope * rope * int

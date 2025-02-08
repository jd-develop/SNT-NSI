type boisson =
    | Eau
    | Jus of string
    (* Soda tarnais (visca l’Occitània !) *)
    | BaplaCola of bool (* true pour light *)
    | Cocktail of boisson * boisson * float


(* Calcule le prix au litre de la boisson b *)
let rec prix_boisson (b: boisson) : float = match b with
    | Eau -> 0.
    | Jus j -> if j = "ramboutan" then 5.3 else 3.
    | BaplaCola _ -> 1.
    | Cocktail (b1, b2, p) -> p*.(prix_boisson b1) +. (1.-.p)*.(prix_boisson b2)


(*
 * Créée un cocktail contenant chacune des boissons de la liste l, avec des
 * proportions de 1/2, 1/4, 1/8, etc.
 *)
let rec shaker (l: boisson list) : boisson = match l with
    | [] -> failwith "Aucune boisson fournie"
    | x::[] -> x
    | x::q -> Cocktail (x, shaker q, 0.5)


(* Renvoie le nom de la boisson de base b (b n’est donc pas un cocktail) *)
let rec string_of_boisson (b: boisson) : string = match b with
    | Cocktail _ ->
        failwith "Impossible de convertir un cocktail en chaîne de caractères"
    | Eau -> "Eau"
    | Jus type_jus -> (match type_jus.[0] with
        | 'a' | 'e' | 'i' | 'o' | 'u' | 'y'
            -> "Jus d'"^type_jus
        | _ -> "Jus de "^type_jus)
    | BaplaCola light -> "Bapla Cola" ^ if light then " light" else ""

(* Renvoie la liste des éléments du cokctail c avec leur proportion totale dans
 * le cocktail, le tout multiplié par le coefficient a
 *)
let rec ingredrients_fraction (c: boisson) (a: float) : (boisson*float) list =
    match c with
    | Cocktail (b1, b2, p) ->
        (b1, p*.a)::(ingredrients_fraction b2 ((1.-.p)*.a))
    | _ -> [(c, a)]

(* Renvoie la liste des éléments du cocktail c avec leur proportion totale dans
 * le cocktail
 *)
let ingredrients (c: boisson) : (boisson*float) list =
    ingredrients_fraction c 1.

(* Renvoie une liste contenant des couples ayant pour premiers éléments tous les
 * premiers éléments des couples de la liste l, mais dont les deuxièmes éléments
 * sont à chaque fois la somme de tous les deuxièmes éléments des couples
 * de la liste l (regroupés par premiers éléments)
 *)
let rec agreg_sum (l: ('a*float) list) : ('a * float) list = match l with
    | [] -> []
    | x::[] -> x::[]
    | x::y::q -> let x1, x2 = x in let y1, y2 = y in
        if x1 = y1 then (x1, x2+.y2)::(agreg_sum q)
        else x::(agreg_sum (y::q))


(* Affiche la liste des différentes boissons de la liste l, dans laquelle les
 * proportions sont données par rapport à 1L.
 *)
let rec affiche_liste_ingredients (l: (boisson*float) list) : unit =
    match l with
    | [] -> ()
    | x::q -> let b, p = x in
        print_int (int_of_float (p *. 1000.));
        print_string " mL ";
        print_string (string_of_boisson b);
        print_newline ();
        affiche_liste_ingredients q


(* Affiche la liste des différents ingrédients de la boisson b, en assumant
 * qu’au total, on a 1L de boisson.
 *)
let recette (b: boisson) : unit =
    let liste_ingredients = (ingredrients b) in
    let ingredients_tries = List.sort compare liste_ingredients in
    let ingredients_agreg = agreg_sum ingredients_tries in
    print_endline "Recette pour 1L :";
    affiche_liste_ingredients ingredients_agreg


let test () =
    assert(prix_boisson Eau = 0.);
    assert(prix_boisson (Jus "orange") = 3.);
    assert(prix_boisson (Jus "pomme") = 3.);
    assert(prix_boisson (Jus "raisin") = 3.);
    assert(prix_boisson (Jus "violette de Toulouse") = 3.);
    assert(prix_boisson (Jus "ramboutan") = 5.3);
    assert(prix_boisson (BaplaCola true) = 1.);
    assert(prix_boisson (BaplaCola false) = 1.);

    assert(prix_boisson (Cocktail (Eau, BaplaCola true, 0.2)) = 0.8);
    assert(prix_boisson (Cocktail (Eau, BaplaCola false, 0.2)) = 0.8);
    assert(
        prix_boisson (Cocktail (Jus "ramboutan", BaplaCola false, 0.2)) = 1.86
    );

    assert (shaker [Jus "ananas"; Eau; BaplaCola true; Jus "pomme"] =
        Cocktail (Jus "ananas", (
            Cocktail (Eau, (
                Cocktail (BaplaCola true, Jus "pomme", 0.5)
            ), 0.5)
        ), 0.5)
    );

    assert (string_of_boisson Eau = "Eau");
    assert (string_of_boisson (Jus "orange") = "Jus d'orange");
    assert (string_of_boisson (Jus "pomme") = "Jus de pomme");
    assert (string_of_boisson (Jus "raisin") = "Jus de raisin");
    assert (string_of_boisson (Jus "ramboutan") = "Jus de ramboutan");
    assert (string_of_boisson (Jus "violette de Toulouse") =
        "Jus de violette de Toulouse"
    );
    assert (string_of_boisson (BaplaCola true) = "Bapla Cola light");
    assert (string_of_boisson (BaplaCola false) = "Bapla Cola");

    assert (
        ingredrients_fraction (
            Cocktail (Eau,
                Cocktail (BaplaCola true, Jus "pomme", 0.4),
                0.5
            )
        ) 0.7 = [
            (Eau, 0.35);
            (BaplaCola true, 0.4*.0.5*.0.7);
            (Jus "pomme", 0.21)
        ]
    );

    assert (
        ingredrients (
            Cocktail (Eau,
                Cocktail (BaplaCola true, Jus "pomme", 0.4),
                0.5
            )
        ) = [
            (Eau, 0.5);
            (BaplaCola true, 0.2);
            (Jus "pomme", 0.3)
        ]
    );

    assert (
        ingredrients (Cocktail (Eau, Eau, 0.5)) = [(Eau, 0.5); (Eau, 0.5)]
    );

    assert (
        agreg_sum [
            ("chocolatine", 0.1); ("chocolatine", 0.3);
            ("lorem ipsum", 0.4); ("lorem ipsum", 0.2)
        ] = [
            ("chocolatine", 0.4);
            ("lorem ipsum", 0.4 +. 0.2) (* je déteste les flottants *)
        ]
    );

    recette (Cocktail (
        Eau, Cocktail (
            Jus "raisin", Cocktail (
                BaplaCola false, Jus "orange",
                30. /. 55.
            ), 40. /. 95.
        ), 0.05
    )); (* tout va bien si ce n’est les arrondis douteux… *)

    print_endline "Tous les tests de l’exercice 5 ont réussi."

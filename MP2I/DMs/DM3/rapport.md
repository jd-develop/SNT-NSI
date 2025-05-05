# Rapport
## Satsolver
**Q1:** Le premier argument est l'appelle du programme: ./satsolver.
Sans deuxième argument: Fatal error: exception Invalid_argument("index out of bounds")

**Q10:** Soit n la taille de l'arbre syntaxique de f. (les noueuds sont les éléments de bases: Not, Or, And, Var, Top, Bot).
Ainsi, on se ramène à un problème de parcours d'arbre binaires avec une étape de traitement (union) en $\Theta(n)$.
Or on sait que le pire cas pour un parcours en hauteur est le peigne.
De plus, dans le pire cas toutes les feuilles sont des variables différentes. Et le nombre de feuilles est forcément inférieure aux nombres
de noeuds et dans le pire cas: peigne, il y a $E(\frac {n+1}2) = \Theta(n)$ feuilles. 
Pour un tel arbre, l'équation de complexitée s'écrit: $C(n) = C(n-1) + \Theta(n)$.
Donc $C(n) = \Theta(n^2)$. Pour optimiser, on peut implémenter var_list avec un ARN ou un AVL.

**Q19:**  Une famille en $\Theta(n^2)$ est un peigne avec que des Or et où les feuilles sont des 
variables sauf la dernière qui est un Top. i.e "X1 | X2 | ... | Xn | T". Car simpl_step vas parcourir
tout l'arbre pour faire qu'une seul simplification à chaque fois.

**Q25:** On peut remplacer la variable la plus fréquente dans la formule. Ainsi, la formule aurra plus de chance de ce simplifier.
Malheureusement, choisir la variable de cette façon est couteux ... (Implémenté en O(nlog(k)) avec n la taille de la formule et k le nombre
de variable)
De plus, si la formule est sous FNC, il n'y a qu'a choisir Top ou Bot en fonction de nombres de clauses satisfaites pour ce choix.
Sinon, l'impacte du choix est difficile à prévoir.

**Q31:** La formule générée par au_plus_une est sous FNC si et seulement si les formules en entrée sont des littéraux. 
De plus, si on considère que la taille de la formule généré comme la taille de son arbre syntaxique où les feuilles sont
les formules atomique en entré, alors sa taille est: 3n(n-1) - 1. Avec n le nombre de formules en entrée.

**Bonus ++** Nous avons implémenté la stratégie de la questions 25 pour la formule FNC. De plus, nous l'avons améliorée. En effet, sous FNC on remarque que si 
un littéral n'apparait que sous une forme (positive / négative), alors on peut la substitué dans la formule sans créer de clause vide. Ainsi, il n'y a pas besoins
de tester l'autres valuations possibles. De plus, les littéraux des clauses unitaires doivent être nécessairement satisfait pour que la formule soit satisfiable. Ainsi, 
on commencera par substituer ceux ci. En pratique cette implémentation semble être assez rapide.
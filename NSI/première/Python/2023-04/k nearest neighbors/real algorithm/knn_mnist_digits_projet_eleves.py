# coding:utf-8
from typing import List, Tuple, Dict, TextIO
from math import sqrt
import matplotlib.pyplot as plt

# Utiliser la commande cd pour se placer dans le répertoire contenant les fichiers digits.csv et digit5.csv

digits_filepath = "digits.csv"
digit5_filepath = "digit5.csv"


def load_digit(digits_file: TextIO):
    """
    Convertit une ligne du fichier digits.csv, en un dictionnaire digit de clés :
                'X' dont la valeur X (de type List[int]) est la liste de 64 pixels de l'image
                'Y' dont la valeur Y (de type str) est le chiffre correspondant
    Paramètre :
        `digits_file`, référence à l'objet fichier texte (de type TextIO) associé au fichier csv
    Retourne le dictionnaire digit
    Par effet de bord, cette fonction modifie la position du curseur de position dans le fichier digits_file.
    """

    # Lecture de la ligne des données : 64 pixels + label, dans une chaine data, de longueur data_len
    data = digits_file.readline()

    # Longueur de la chaîne data
    data_len = len(data)

    # Le label Y est le dernier ou l'avant-dernier (si `\n` en fin) caractère de la chaîne data.
    if data[-1] == '\n':
        y = data[-2]
    else:
        y = data[-1]

    # Construction de la liste X des 64 pixels de type int à partir du contenu de la chaîne data
    x = []
    # Le pixel courant est initialement vide
    pixel = ''
    # Boucle de parcours des caractères de la chaîne data
    for i in range(data_len - 1):
        # Le caractère courant est la virgule de séparation ','
        if data[i] == ',':
            # Ajoute à la liste X la chaîne pixel précédent le caractère de séparation
            x.append(int(pixel))
            # Réinitialise la chaîne pixel à vide
            pixel = ''
        else:
            # Constitue la chaîne de caractères du pixel courant par concaténation des chiffres successifs
            pixel = pixel + data[i]

    # Enregistrement des 64 pixels et du label dans un dictionnaire digit de clés 'X' et 'Y'
    digit_ = {'X': x, 'Y': y}

    return digit_


# Test unitaire
digit5_pixels = [0, 0, 9, 12, 12, 13, 7, 0, 0, 0, 15, 5, 5, 4, 2, 0, 0, 4, 15, 10, 4, 0, 0, 0, 0, 2, 11, 11, 15, 11, 0,
                 0, 0, 0, 0, 0, 0, 10, 5, 0, 0, 0, 0, 0, 0, 7, 7, 0, 0, 5, 11, 4, 5, 14, 1, 0, 0, 0, 9, 16, 13, 3, 0, 0]
digit5_file = open(digit5_filepath, 'r')
digit = load_digit(digit5_file)
assert digit['Y'] == '5', "Erreur donnée label"
assert digit['X'] == digit5_pixels, "Erreur données pixels"
print('Test "load_digit" réussi')


def load_digits(digits_filepath_):
    """
    Charge l'ensemble des données depuis le fichier csv.
    Paramètre : chemin d'accès au fichier csv (de type str)
    Retourne deux listes de dictionnaires :
        `digits_training`, constitué de 1500 dictionnaires digit codant les données d'apprentissage.
        `digits_testing`, constitué de 200 dictionnaires digit codant les données de test.
    """
    # Ouverture du fichier texte des données en mode lecture
    digits_file = open(digits_filepath_, 'r')

    # Construction de la liste de dictionnaires des données d'apprentissage
    digits_training_ = []
    for i in range(1500):
        # Conversion d'une ligne en dictionnaire digit.
        digit_ = load_digit(digits_file)
        # Ajout du dictionnaire à la liste digits_training.
        digits_training_.append(digit_)

    # Construction de la liste de dictionnaires des données de test
    digits_testing_ = []
    for i in range(200):
        # Conversion d'une ligne en dictionnaire digit.
        digit_ = load_digit(digits_file)
        # Ajout du dictionnaire à la liste digits_testing.
        digits_testing_.append(digit_)
    # Fermeture du fichier de données
    digits_file.close()

    return digits_training_, digits_testing_


def show_digit(pixels: List[List[int]], n: int) -> None:
    """
    Affiche dans une fenêtre, l'image carrée de taille de nxn pixels en 16 niveaux de gris.
    Paramètres :
        `pixels` (de type List[int]), la liste des nxn pixels
        `n` (de type int), le nombre de lignes (et de colonnes) de la matrice carrée
    """

    # image est un tableau de nxn pixels construit à partie de la liste pixels de longueur nxn
    image = [[pixels[j + 8 * i] for j in range(n)] for i in range(n)]

    # Utilisation de la bibliothèque pyplot pour afficher l'image dans une fenêtre
    plt.gray()
    plt.matshow(image)
    plt.show()


def knn(digit_, digits_training_, k: int) -> List[Tuple[float, int]]:
    """
    Détermine la liste des k plus proches voisins.
    Paramètres :
        X (de type List[int]), l'image à classer
        digits_training (de type Dict(str, List[int]), la base d'entrainement
        k (de type int), le nombre de plus proches voisins
    Retourne un tableau neighbors (de type List[(Float, Int)]) de tuples (d, label)
    """
    assert k <= len(digits_training_), "k cannot be greater than training set size"

    # Tableau des couples (d, label) pour chaque comparaison de la donnée à classer avec celles d'apprentissage
    neighbors = []

    # Calcul des distances entre la donnée digit à classer et chaque
    for digit_training in digits_training_:
        d = distance(digit_['X'], digit_training['X'])
        neighbor = (d, digit_training['Y'])
        neighbors.append(neighbor)

    # Tri selon les distances croissantes
    tri_neighbors(neighbors)
    # neighbors.sort(key=lambda tup: tup[0])
    # k_neighbors = neighbors[:k]

    k_neighbors_ = [neighbors[i] for i in range(k)]

    return k_neighbors_


def insert_tuple(t: List[Tuple[float, str]], i: int, v: Tuple[float, str]) -> None:
    """
    Insère la valeur v au rang i, dans le tableau t.
    Paramètres :
        `t` est un tableau (de type List[Tuple[float, str]]) dont les éléments sont des tuples (distance, label).
        `i` (de type int) est le rang ou la valeur v est insérée.
        `v` (de type Tuple[float, str]) est le tuple (distance, label) à insérer.
    Pas de valeur de retour, le paramètre `t` est modifié par effet de bord.
    """
    j = i
    while j > 0 and t[j - 1][0] > v[0]:
        t[j] = t[j - 1]
        j = j - 1
    t[j] = v


def tri_neighbors(neighbors: List[Tuple[float, str]]) -> None:
    """
    Tri la liste des tuples (distance, label) par ordre croissant des distances.
    Paramètre :
        neighbors (de type List[Tuple[float, str]]) est la liste à trier.
    Pas de valeur de retour, le paramètre neighbors est modifié par effet de bord.
    """
    for i in range(1, len(neighbors)):
        insert_tuple(neighbors, i, neighbors[i])


def distance(x1: List[int], x2: List[int]) -> float:
    """
    Calcule la distance euclidienne entre les entrées X1 = [x11, x12, x13, ..., x1p]
    et  X2 = [x21, x22, x23, ..., x2p] de même taille p
    """
    assert len(x1) == len(x2), "données de dimensions différentes"
    distance_ = 0
    for i in range(len(x1)):
        distance_ += (x1[i] - x2[i]) ** 2
    distance_ = sqrt(distance_)
    return distance_


def majority(labels: List[str]) -> str:
    """
    Détermine la classe majoritaire (la première si égalité) de la liste labels.
    Paramètre :
        `labels`, liste de labels (de type List[str])
    Retourne la classe majoritaire (de type str)
    """
    assert labels != [], "Liste vide"

    # Les occurrences des labels sont enregistrées dans le dictionnaire classifier
    # les clés sont les labels, les valeurs sont leurs occurrences
    classifier: Dict[str, int] = {}

    for label in labels:
        if label in classifier.keys():
            classifier[label] += 1
        else:
            classifier[label] = 1

    max_ = 0
    for label in classifier:
        if classifier[label] > max_:
            max_ = classifier[label]
            maj = label

    return maj


def predict(k_neighbors_: List[Tuple[float, str]]) -> str:
    """
    Prédit le label majoritaire du tableau de tuples (distance, label) des k plus proches voisins.
    Paramètre :
        `k_neighbors` (de type List[Tuple[float, str]]), le tableau des k plus proches voisins.
    Retourne le label (de type str) majoritaire.
    """
    knn_labels = [k_neighbor[1] for k_neighbor in k_neighbors_]
    # prediction = max(set(k_neighbors_labels), key=k_neighbors_labels.count)
    prediction_ = majority(knn_labels)
    return prediction_


def score(digits_training_: List, digits_testing_: List) -> float:
    nb_total = len(digits_testing_)
    nb_match = 0
    for digit_test_ in digits_testing_:
        label = digit_test_['Y']
        prediction_ = predict(knn(digit_test_, digits_training_, 5))
        if label == prediction_:
            nb_match += 1
    return nb_match / nb_total


digits_training, digits_testing = load_digits(digits_filepath)
digit_test = digits_testing[16]
# digit_test = {"X": (0, 0, 0, 0, 10, 5, 0, 0,
#                     0, 0, 0, 10, 10, 7, 0, 0,
#                     0, 4, 9, 10, 7, 7, 0, 0,
#                     0, 1, 4, 0, 10, 10, 0, 0,
#                     0, 0, 0, 0, 8, 8, 0, 5,
#                     0, 0, 0, 0, 8, 8, 10, 10,
#                     0, 0, 0, 0, 8, 11, 10, 0,
#                     0, 0, 10, 11, 8, 0, 0, 0), "Y": '1'}

show_digit(digit_test['X'], 8)

k_neighbors = knn(digit_test, digits_training, 5)
prediction = predict(k_neighbors)

print("Score : ", score(digits_training, digits_testing))
print("Prediction : ", prediction)

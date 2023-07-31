# coding:utf-8

# Adapted from course assignments of "Applied machine learning with python"
# on coursera by university of michigan.

# import numpy as np
import matplotlib.pyplot as plt
# pandas est une bibliothèque Python de codage et d'analyse de données
import pandas as pd
# scikit-learn est une bibliothèque Python de machine learning
from sklearn.model_selection import train_test_split
# from mpl_toolkits.mplot3d import Axes3D
from sklearn.neighbors import KNeighborsClassifier


# Lecture et codage en DataFrame des données de 59 fruits du fichier csv
fruits = pd.read_csv('knn_fruits.csv')

# Extraction des vecteurs de données X et des labels (étiquettes) Y correspondants
X = fruits[['masse', 'largeur', 'hauteur']]
Y = fruits['label']

# Répartition des données du fichier : 75% - 25% pour training/testing
# 44 données d'apprentissage et 15 données de test
X_train, X_test, Y_train, Y_test = train_test_split(X, Y, random_state=0)


# Création d'un modèle de classification par l'algorithme des k plus proches voisins
# Changer le paramètre n_neighbors correspondant à k pour observer des modifications du score (en %) de classifications
# correctes
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, Y_train)
print("\nScore de classification avec les données tests :", knn.score(X_test, Y_test))

# Exemple 1 de classification d'un fruit de masse 20g,
# de largeur 4.3 cm et de hauteur 5.5 cm.
fruit_masse = 20
fruit_largeur = 4.3
fruit_hauteur = 5.5
fruit_prediction = knn.predict([[fruit_masse, fruit_largeur, fruit_hauteur]])
print("Fruit 1 :", fruit_prediction[0])

# Exemple 2 de classification d'un fruit de masse 100g,
# de largeur 6.4 cm et de hauteur 8.5 cm.
fruit_masse = 200
fruit_largeur = 8.1
fruit_hauteur = 7.2
fruit_prediction = knn.predict([[fruit_masse, fruit_largeur, fruit_hauteur]])
print("Fruit 2 :", fruit_prediction[0])

# Peser et mesurer un fruit de variété classique (pomme, orange, citron ou mandarine)
# pour vérifier la prédiction donnée par l'algorithme :
mon_fruit_masse = 170
mon_fruit_largeur = 6
mon_fruit_hauteur = 8
mon_fruit_prediction = knn.predict([[mon_fruit_masse, mon_fruit_largeur, mon_fruit_hauteur]])
print("Mon fruit :", mon_fruit_prediction[0])


# Nuage de points représentant les 59 fruits étiquetés + le fruit à classer (en bleu)
colors_palette = {'pomme': "green", 'orange': "red", 'citron': "yellow", 'mandarine': "orange"}
colors = [colors_palette[c] for c in Y_train]
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(X_train['masse'], X_train['largeur'], X_train['hauteur'], c=colors, marker='o', s=100)
ax.scatter([mon_fruit_masse], [mon_fruit_largeur], [mon_fruit_hauteur], c='blue', marker='o', s=100)
ax.set_xlabel('masse')
ax.set_ylabel('largeur')
ax.set_zlabel('hauteur')
plt.show()

import csv

# question 1

# countries = [
#     {'code':'AD', 'name':'Andorra', 'capital':'Andorra la Vella', 'demonym':'Andorrans', 'area':'468',
#      'population':'77265', 'language':'Catalana'},
#     {'code':'AE', 'name':'United Arab Emirates', 'capital':'Abu Dhabi', 'demonym':'Emirians', 'area':'83600',
#      'population':'9890402', 'language':'Arabic'},
# ]

# question 2
with open("./countries.csv", encoding='UTF-8') as fichier_pays:
    # traitement des données
    countries = list(csv.DictReader(fichier_pays))

with open("./currencies.csv", encoding='UTF-8') as fichier_monnaies:
    # traitement des données
    currencies = list(csv.DictReader(fichier_monnaies))

print(currencies[4]["currency"])  # East Caribbean Dollar
print(countries[41]['name'])  # Congo
print(currencies[4]["code"])
print(countries[4]["code"])


# question 3
def schema(table: list[dict]) -> list[str]:
    """
    La fonction schema retourne le schéma (liste des noms d'attributs) de la table de données.
    Paramètre :
        * table est une liste de dictionnaires représentant les lignes de données
    Retour :
        * la liste des clés d'un dictionnaire de table
    """
    attributs = [k for k in table[0].keys()]
    return attributs


print(schema(countries))
# test fonction schema
assert schema(countries) == ['code', 'name', 'capital', 'demonym', 'area', 'population', 'language'], \
    'Erreur test fonction schema'


# question 4
def insert(table: list[dict], ligne: dict):
    """
    La fonction insert insère une nouvelle ligne dans la table de données.
    Paramètres :
        * table est une liste de dictionnaires représentant les lignes de données
        * ligne est le dictionnaire représentant la ligne de données à insérer
    Retour :
        * pas de retour
    """
    if ligne not in table:
        table.append(ligne)
    else:
        print(f"Insertion de {ligne} impossible")


# Tests fonction insert
zimbabwe = {'code': 'ZW', 'name': 'Zimbabwe', 'capital': 'Harare', 'demonym': 'Zimbabweans', 'area': '390757',
            'population': '14862924', 'language': 'English'}

andorre = {'code': 'AD', 'name': 'Andorra', 'capital': 'Andorra la Vella', 'demonym': 'Andorrans', 'area': '468',
           'population': '77265', 'language': 'Catalana'}

moon = {'code': 'LN', 'name': 'Moon', 'capital': 'None', 'demonym': 'Selenites', 'area': '38000000', 'population': '0',
        'language': 'Selenit'}

insert(countries, zimbabwe)
insert(countries, andorre)
insert(countries, moon)
assert zimbabwe in countries, 'Erreur test fonction insert'
assert andorre in countries
assert moon in countries


# Question 5
def delete(table, id_, value):
    """
    La fonction delete supprime la ligne ayant la valeur "value" pour l'attribut "id_".
    Paramètres :
        * table est une liste de dictionnaires représentant les lignes de données
        * id_ est le nom de la clé identifiant la ligne à supprimer
        * value est la valeur associée à la clé id_ identifiant la ligne à supprimer
    Retour :
        * pas de retour
    """
    for line in table:
        if line[id_] == value:
            table.remove(line)
            break


# Test fonction delete
delete(countries, 'code', 'LN')
assert moon not in countries, 'Erreur test fonction delete'


# Question 6
def update(table, id_, id_value, attribute, value):
    """
    La fonction update actualise par "value" la valeur d'attribut "attribute" dans la ligne identifiée par la valeur
    "id_value" pour l'attribut "id_".
    Paramètres :
        * table est une liste de dictionnaires représentant les lignes de données
        * id_ est le nom de la clé identifiant la ligne à modifier
        * id_value est la valeur associée à la clé id_ pour identifier la ligne à modifier
        * attribute est le nom de l'attribut à modifier
        * value est la nouvelle valeur de cet attribut
    Retour :
        * pas de retour
    """
    for line in table:
        if line[id_] == id_value:
            line[attribute] = value
            break


# Test fonction update
france_with_toulouse_as_capital = {'code': 'FR', 'name': 'France', 'capital': 'Toulouse', 'demonym': 'French',
                                   'area': '643801', 'population': '65273511', 'language': 'French'}
update(countries, 'code', 'FR', 'capital', 'Toulouse')
assert france_with_toulouse_as_capital in countries, 'Erreur test fonction update'
france = {'code': 'FR', 'name': 'France', 'capital': 'Paris', 'demonym': 'French', 'area': '643801',
          'population': '65273511', 'language': 'French'}
update(countries, 'code', 'FR', 'capital', 'Paris')
assert france in countries, 'Erreur test fonction update'


# question 7
def selection(table, condition):
    """
    La fonction selection retourne la liste les lignes de la table vérifiant la condition donnée.
    Paramètres :
        * table est une liste de dictionnaires représentant les lignes de données
        * condition est la chaîne de caractère correspondant à la condition de sélection des lignes
    Retour :
        * retourne la liste des dictionnaires représentant les lignes sélectionnées
    """
    selection_lignes = []
    for line in table:
        print("pop", line["population"])
        print("area", line["area"])
        if eval(condition):
            selection_lignes.append(line)
    return selection_lignes


francophone = "line['language'] == 'French'"
peuple = "int(line['population']) > 10**8"
dense = "float(line['population'])/float(line['area']) > 50"

# Tests fonction selection
pays_francophones = selection(countries, francophone)
pays_peuples = selection(countries, peuple)
pays_denses = selection(countries, dense)
assert len(pays_francophones) == 36, 'Erreur test francophone fonction selection'
assert len(pays_peuples) == 14, 'Erreur test peuple fonction selection'
assert len(pays_denses) == 161, 'Erreur test dense fonction selection'


# question 8
def projection(table: list[dir], attributes: list[str]):
    """
    La fonction projection retourne la liste des lignes de la table en ne conservant que les colonnes précisées dans la
      liste attributes
    Paramètres :
        * table est une liste de dictionnaires représentant les lignes de données
        * attributes est la liste des attributs de caractère correspondante à la condition de sélection des lignes
    Retour :
        * retourne la liste des lignes dictionnaires avec les valeurs des colonnes sélectionnées
    """
    projection_lignes = []
    for line in table:
        newline = dict()
        for attribute in attributes:
            newline[attribute] = line[attribute]
        projection_lignes.append(newline)
    return projection_lignes


# Tests fonction projection
liste_codes_pays = projection(countries, ['code', 'name'])

assert liste_codes_pays[0] == {'code': 'AD', 'name': 'Andorra'}, 'Erreur test1 fonction projection'
assert liste_codes_pays[-1] == {'code': 'ZW', 'name': 'Zimbabwe'}, 'Erreur test2 fonction projection'


# question 9
def jointure(table1, table2, id_):
    """
    La fonction projection retourne la liste des lignes de la table en ne conservant que les lignes dont la valeur
      d'identifiant id_ est similaire
    Paramètres :
        * table1 est une liste de dictionnaires représentant la première table
        * table2 est une liste de dictionnaires représentant la deuxième table
        * id_ est la chaîne de caractère correspondant à l'attribut clé commun aux deux tables
    Retour :
        * retourne la table constituée des lignes de table1 avec les attributs supplémentaires de table2
    """
    new_table = []
    for line1 in table1:
        for line2 in table2:
            if line1[id_] == line2[id_]:
                newline = line1
                for k in line2:
                    if k not in newline.keys():
                        newline[k] = line2[k]
                new_table.append(newline)
    return new_table


# Tests fonction jointure
table_complete = jointure(countries, currencies, 'code')
assert table_complete[0] == {'code': 'AD', 'name': 'Andorra', 'capital': 'Andorra la Vella', 'demonym': 'Andorrans',
                             'area': '468', 'population': '77265', 'language': 'Catalana',
                             'currency': 'Euro'}, 'Erreur test1 fonction jointure'
assert table_complete[-1] == {'code': 'ZW', 'name': 'Zimbabwe', 'capital': 'Harare', 'demonym': 'Zimbabweans',
                              'area': '390757', 'population': '14862924', 'language': 'English',
                              'currency': 'Zimbabwe Dollar'}, 'Erreur test2 fonction jointure'

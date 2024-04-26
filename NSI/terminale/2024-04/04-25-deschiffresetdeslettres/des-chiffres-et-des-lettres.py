#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
from translatiton_table import anagramme
from frequencies import FREQUENCIES
import random

print("Reading file…")
with open("liste_mots_francais.txt", "r+", encoding="utf-8") as _liste_mots_filep:
    _liste_mots_liste = _liste_mots_filep.readlines()

print("Creating word list…")
LISTE_MOTS = [w.replace("\n", "") for w in _liste_mots_liste]
print("Creating normalsed word list…")
LISTE_MOTS_NORMALISÉS = [anagramme(w) for w in LISTE_MOTS]
print("Done.")


def combinaisons_moins_n_lettres(text: str, n: int) -> list[str]:
    if n == 0:
        return [text]
    if n == 1:
        return list(set([text[:i] + text[i+1:] for i in range(len(text))]))
    combinaisons_precedentes = combinaisons_moins_n_lettres(text, n-1)
    résultat: list[str] = []
    for c in combinaisons_precedentes:
        résultat.extend([c[:i] + c[i+1:] for i in range(len(c))])
    return list(set(résultat))  # remove duplicates


def créer_tirage(nb_voyelles: int, nb_consonnes: int):
    tirage = ""
    voyelles = list("AEIOUY")
    consonnes = list("BCDFGHJKLMNPQRSTVWXZ")
    assert len(voyelles) + len(consonnes) == 26
    poids_voyelles = [FREQUENCIES[letter] for letter in voyelles]
    poids_consonnes = [FREQUENCIES[letter] for letter in consonnes]

    tirage += "".join(random.choices(voyelles, weights=poids_voyelles, k=nb_voyelles))
    tirage += "".join(random.choices(consonnes, weights=poids_consonnes, k=nb_consonnes))

    return tirage


def trouve_mot_le_plus_long(tirage: str, verbose: bool = False, print_every: int = 1) -> str | None:
    tirage_normalisé = anagramme(tirage)
    compteur = 1
    if verbose: print(compteur, tirage_normalisé)

    if len(tirage_normalisé) == 0:
        return None
    if tirage_normalisé in LISTE_MOTS_NORMALISÉS:
        return LISTE_MOTS[LISTE_MOTS_NORMALISÉS.index(tirage_normalisé)]
    if len(tirage_normalisé) == 1:
        return None
    
    len_tirage = len(tirage_normalisé)

    for i in range(1, len_tirage+1):
        for combination in combinaisons_moins_n_lettres(tirage_normalisé, i):
            compteur += 1
            if verbose and compteur%print_every == 0:
                print(compteur, combination)
            if combination in LISTE_MOTS_NORMALISÉS:
                if verbose and print_every != 1:
                    print(compteur)
                return LISTE_MOTS[LISTE_MOTS_NORMALISÉS.index(combination)]
    if verbose and print_every != 1:
        print(compteur)
    return None


def test():
    assert trouve_mot_le_plus_long("nticonstitutionenllementja") == "anticonstitutionnellement"
    assert trouve_mot_le_plus_long("iiqmrsllie") == "milliers"


# from what I tested:
# (word to find: anticonstitutionnellement, so these number do vary depending on your word)
# 30 letters: >30s
# 29 letters: ~7s
# 28 letters: ~3s
# 27 letters: ~2s
# 26 letters: ~1s

# print(trouve_mot_le_plus_long(créer_tirage(4, 6), True))


def le_compte_est_bon(but: int, disponible: list[int], résultat: str = "") -> tuple[bool, str]:
    """Le compte est bon"""
    if len(disponible) == 1:
        if disponible[0] == but:
            return True, résultat
        return False, ""
    for i in range(len(disponible)):
        for j in range(len(disponible)-1):
            a = disponible[i]
            nouveau_disponible = disponible[:i] + disponible[i+1:]
            b = nouveau_disponible[j]
            nouveau_disponible = nouveau_disponible[:j] + nouveau_disponible[j+1:]
            a_tester = [(a+b, f"{a}+{b}={a+b}"), (a*b, f"{a}*{b}={a*b}")]
            if a > b:
                a_tester.append((a-b, f"{a}-{b}={a-b}"))
            if a%b == 0:
                a_tester.append((int(a/b), f"{a}:{b}={int(a/b)}"))
            for value, nouveau_résultat in a_tester:
                dispo = nouveau_disponible.copy()
                dispo.append(value)
                nouveau_compte, newnew_résultat = le_compte_est_bon(but, dispo, résultat+"\n"+nouveau_résultat)
                if nouveau_compte:
                    return True, newnew_résultat
    return False, ""

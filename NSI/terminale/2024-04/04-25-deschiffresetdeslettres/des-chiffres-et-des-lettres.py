#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
from translatiton_table import remove_diacritics
# from frequencies import count_frequencies

print("Reading file…")
with open("liste_mots_francais.txt", "r+", encoding="utf-8") as _liste_mots_filep:
    _liste_mots_liste = _liste_mots_filep.readlines()

print("Creating word list…")
LISTE_MOTS = [w.replace("\n", "") for w in _liste_mots_liste]
print("Creating normalsed word list…")
LISTE_MOTS_NORMALISÉS = [remove_diacritics(w) for w in LISTE_MOTS]
print("Done.")


def combinaisons_moins_n_lettres(text: str, n: int) -> list[str]:
    if n == 0:
        return [text]
    if n == 1:
        return [text[:i] + text[i+1:] for i in range(len(text))]
    combinaisons_precedentes = combinaisons_moins_n_lettres(text, n-1)
    résultat: list[str] = []
    for c in combinaisons_precedentes:
        résultat.extend([c[:i] + c[i+1:] for i in range(len(c))])
    return list(set(résultat))  # remove duplicates

# pprint(count_frequencies(LISTE_MOTS, True))


def trouve_mot_le_plus_long(tirage: str, verbose: bool = False) -> str | None:
    tirage_normalisé = remove_diacritics(tirage)
    if len(tirage_normalisé) == 0:
        return None
    if tirage_normalisé in LISTE_MOTS_NORMALISÉS:
        return LISTE_MOTS[LISTE_MOTS_NORMALISÉS.index(tirage_normalisé)]
    if len(tirage_normalisé) == 1:
        return None
    
    len_tirage = len(tirage_normalisé)

    for i in range(1, len_tirage+1):
        for combination in combinaisons_moins_n_lettres(tirage_normalisé, i):
            if verbose: print(combination)
            if combination in LISTE_MOTS_NORMALISÉS:
                return LISTE_MOTS[LISTE_MOTS_NORMALISÉS.index(combination)]    
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

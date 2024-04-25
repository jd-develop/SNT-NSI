#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
from translatiton_table import remove_diacritics
from frequencies import count_frequencies
from pprint import pprint
import functools


with open("liste_mots_francais.txt", "r+", encoding="utf-8") as _liste_mots_filep:
    _liste_mots_liste = _liste_mots_filep.readlines()

LISTE_MOTS = [w.replace("\n", "") for w in _liste_mots_liste]
LISTE_MOTS_NORMALISÉS = [remove_diacritics(w) for w in LISTE_MOTS]

pprint(count_frequencies(LISTE_MOTS, True))


# @functools.cache
def trouve_mot_le_plus_long(tirage: str, longueur_mot_plus_long_déjà_trouvé: int = 0) -> str | None:
    tirage_normalisé = remove_diacritics(tirage)
    if len(tirage_normalisé) == 0:
        return None
    if tirage_normalisé in LISTE_MOTS_NORMALISÉS:
        return LISTE_MOTS[LISTE_MOTS_NORMALISÉS.index(tirage_normalisé)]
    résultats: list[str] = []
    if len(tirage_normalisé) == 1:
        return None

    if len(tirage_normalisé) < longueur_mot_plus_long_déjà_trouvé:
        return None
    if len(tirage_normalisé)-1 < longueur_mot_plus_long_déjà_trouvé:
        return None

    for i in range(len(tirage_normalisé)):
        nouveau_tirage = tirage_normalisé[:i] + tirage_normalisé[i+1:]
        print(nouveau_tirage)
        if len(résultats) != 0:
            long_mot_plus_long = max(len(résultats[-1]), longueur_mot_plus_long_déjà_trouvé)
        else:
            long_mot_plus_long = longueur_mot_plus_long_déjà_trouvé
        résultat = trouve_mot_le_plus_long(nouveau_tirage, long_mot_plus_long)
        if résultat is None:
            continue
        if len(résultat) < longueur_mot_plus_long_déjà_trouvé:
            continue
        if len(résultat) == len(nouveau_tirage):
            return résultat
        résultats.append(résultat)
    
    if len(résultats) == 0:
        return None
    résultats.sort(key=len)
    return résultats[-1]

# print(trouve_mot_le_plus_long("abcdef"))
# print(trouve_mot_le_plus_long("anticonstitutionenllementjlbdpdrsautriel"))
print(trouve_mot_le_plus_long("iiqmrsllie"))

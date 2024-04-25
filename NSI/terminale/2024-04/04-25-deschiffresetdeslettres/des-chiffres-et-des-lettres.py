#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
from translatiton_table import remove_diacritics
# from frequencies import count_frequencies
# from pprint import pprint
import itertools


with open("liste_mots_francais.txt", "r+", encoding="utf-8") as _liste_mots_filep:
    _liste_mots_liste = _liste_mots_filep.readlines()

LISTE_MOTS = [w.replace("\n", "") for w in _liste_mots_liste]
LISTE_MOTS_NORMALISÉS = [remove_diacritics(w) for w in LISTE_MOTS]
LISTE_TUPLES_NORMALISÉS = [tuple(w) for w in LISTE_MOTS_NORMALISÉS]

# pprint(count_frequencies(LISTE_MOTS, True))


def trouve_mot_le_plus_long(tirage: str) -> str | None:
    tirage_normalisé = remove_diacritics(tirage)
    if len(tirage_normalisé) == 0:
        return None
    if tirage_normalisé in LISTE_MOTS_NORMALISÉS:
        return LISTE_MOTS[LISTE_MOTS_NORMALISÉS.index(tirage_normalisé)]
    if len(tirage_normalisé) == 1:
        return None
    
    len_tirage = len(tirage_normalisé)

    for i in range(len_tirage, -1, -1):
        for combination in itertools.combinations(tirage_normalisé, i):
            print(combination)
            if combination in LISTE_TUPLES_NORMALISÉS:
                return LISTE_MOTS[LISTE_TUPLES_NORMALISÉS.index(combination)]    
    return None

# print(trouve_mot_le_plus_long("abcdef"))
# print(trouve_mot_le_plus_long("anticonstitutionenllementj"))
# print(trouve_mot_le_plus_long("iiqmrsllie"))

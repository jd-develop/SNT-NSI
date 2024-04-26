#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
from translatiton_table import anagramme


def count_frequencies(word_list: list[str], should_remove_diacritics: bool = False):
    """Returns the frequency of each letter"""

    occurences: dict[str, int] = dict()

    for word in word_list:
        if should_remove_diacritics:
            word = anagramme(word)
        for c in word:
            occurences[c] = occurences.get(c, 0) + 1
    
    # pprint(occurences)

    # sum_occurences = sum(occurences.values())
    # frequencies = {c: occurences[c]/sum_occurences for c in occurences}
    # return frequencies
    return occurences


FREQUENCIES = {
    'A': 327202,
    'B': 47063,
    'C': 115523,
    'D': 79908,
    'E': 503493,
    'F': 45267,
    'G': 53782,
    'H': 39179,
    'I': 319657,
    'J': 5942,
    'K': 1699,
    'L': 135702,
    'M': 86047,
    'N': 250539,
    'O': 199228,
    'P': 79988,
    'Q': 17059,
    'R': 293142,
    'S': 347779,
    'T': 232533,
    'U': 122586,
    'V': 32321,
    'W': 547,
    'X': 8584,
    'Y': 11536,
    'Z': 35603
}

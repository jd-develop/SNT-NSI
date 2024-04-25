#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
from translatiton_table import remove_diacritics


def count_frequencies(word_list: list[str], should_remove_diacritics: bool = False):
    """Returns the frequency of each letter"""

    occurences: dict[str, int] = dict()

    for word in word_list:
        if should_remove_diacritics:
            word = remove_diacritics(word)
        for c in word:
            occurences[c] = occurences.get(c, 0) + 1
    
    # pprint(occurences)

    sum_occurences = sum(occurences.values())
    frequencies = {c: occurences[c]/sum_occurences for c in occurences}
    return frequencies

#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

_DIACRITICS_DICT: dict[str, str] = {
    "â": "a",
    "à": "a",
    "á": "a",
    "ä": "a",
    "æ": "ae",
    "ç": "c",
    "è": "e",
    "é": "e",
    "ê": "e",
    "ë": "e",
    "î": "i",
    "ï": "i",
    "ô": "o",
    "ö": "o",
    "œ": "oe",
    "ù": "u",
    "û": "u",
    "ü": "u",
    "ÿ": "y"
}
_TRANSLATION_TABLE = str.maketrans(_DIACRITICS_DICT)


def remove_diacritics(text: str, print_translated_not_sorted: bool = False):
    text = text.lower().replace("\n", "").replace("-", "")
    text = text.translate(_TRANSLATION_TABLE)
    if print_translated_not_sorted:
        print(text)
    return "".join(sorted(text.upper()))


assert remove_diacritics("âàáäçæœ") == "AAAAACEEO"
assert remove_diacritics(
    "Dès Noël, où un zéphir haï me vêt de glaçons würmiens, je dîne d’exquis rôtis de bœuf au kir, à l’aÿ d’âge mûr, &cætera."
) == "".join(sorted("DES NOEL, OU UN ZEPHIR HAI ME VET DE GLACONS WURMIENS, JE DINE D’EXQUIS ROTIS DE BOEUF AU KIR, A L’AY D’AGE MUR, &CAETERA."))

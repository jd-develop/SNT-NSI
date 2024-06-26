#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# Des Chiffres Et Des Lettres
# Under GNU GPL v3.0
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

_DIACRITICS_DICT: dict[str, str] = {
    "Â": "A",
    "À": "A",
    "Á": "A",
    "Ä": "A",
    "Æ": "AE",
    "Ç": "C",
    "È": "E",
    "É": "E",
    "Ê": "E",
    "Ë": "E",
    "Î": "I",
    "Ï": "I",
    "Ô": "O",
    "Ö": "O",
    "Œ": "OE",
    "Ù": "U",
    "Û": "U",
    "Ü": "U",
    "Ÿ": "Y",
    "-": "",
    ",": "",
    " ": "",
    "\n": "",
    "\t": "",
    ";": "",
    "’": "",
    "'": "",
    ":": "",
    ".": "",
    "&": "ET"
}
_TRANSLATION_TABLE = str.maketrans(_DIACRITICS_DICT)


def anagramme(text: str):
    text = text.upper().translate(_TRANSLATION_TABLE)
    return "".join(sorted(text))


assert anagramme("âàáäçæœ") == "AAAAACEEO"
assert anagramme(
    "Dès Noël, où un zéphir haï me vêt de glaçons würmiens, je dîne d’exquis rôtis de bœuf au kir, à l’aÿ d’âge mûr, &cætera."
) == "".join(sorted("DESNOELOUUNZEPHIRHAIMEVETDEGLACONSWURMIENSJEDINEDEXQUISROTISDEBOEUFAUKIRALAYDAGEMURETCAETERA"))

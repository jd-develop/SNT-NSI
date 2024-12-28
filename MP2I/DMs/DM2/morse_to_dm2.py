#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import sys

ALPHABET_MORSE_INTERNATIONAL = {
    "A": ".-",
    "B": "-...",
    "C": "-.-.",
    "D": "-..",
    "E": ".",
    "F": "..-.",
    "G": "--.",
    "H": "....",
    "I": "..",
    "J": ".---",
    "K": "-.-",
    "L": ".-..",
    "M": "--",
    "N": "-.",
    "O": "---",
    "P": ".--.",
    "Q": "--.-",
    "R": ".-.",
    "S": "...",
    "T": "-",
    "U": "..-",
    "V": "...-",
    "W": ".--",
    "X": "-..-",
    "Y": "-.--",
    "Z": "--..",
    "0": "-----",
    "1": ".----",
    "2": "..---",
    "3": "...--",
    "4": "....-",
    "5": ".....",
    "6": "-....",
    "7": "--...",
    "8": "---..",
    "9": "----.",
    ".": ".-.-.-",
    "&": ".-...",
    "'": ".----.",
    "’": ".----.",
    "@": ".--.-.",
    ")": "-.--.-",
    "(": "-.--.",
    ":": "---...",
    ",": "--..--",
    "=": "-...-",
    "-": "-....-",
    "×": "-..-",
    "+": ".-.-.",
    "\"": ".-..-.",
    "?": "..--..",
    "/": "-..-."
}
DUREE_POINT = 0.06

def main():
    if len(sys.argv) != 2:
        print("Merci de donner un argument : le fichier de sortie")
        return

    phrase = input("Phrase à coder en morse : ")
    phrase = phrase.upper().replace("%", "0/0")  # en morse, % est codé par 0/0…

    notes: list[tuple[int, int]] = []  # (0|1, durée par rapport à la durée d’un point)
    for c in phrase:
        if c in ALPHABET_MORSE_INTERNATIONAL:
            for note in ALPHABET_MORSE_INTERNATIONAL[c]:
                duree = 1 if note == "." else 3
                notes.append((1, duree))
                notes.append((0, 1))
            notes[-1] = (0, 3)
        else:
            notes.append((0, 7))

    notes.append((0, 10))

    with open(sys.argv[1], "w") as fp:
        fp.write(f"1\n1\n\n{len(notes)} sine\n")
        for amplitude, durée in notes:
            fp.write(f"0 {durée*DUREE_POINT} {amplitude}\n")


if __name__ == "__main__":
    main()

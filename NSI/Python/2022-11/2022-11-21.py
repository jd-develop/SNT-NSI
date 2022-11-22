def remove_space(chaine):
    return chaine.replace(" ", "")


def remove_space2(chaine):
    res = ""
    for c in chaine:
        if c != " ":
            res += c
    return res


# the space between "bonan" and "tagon" is a non-breakable space (espace insécable)
assert remove_space("b o n a n t a g o n") == "bonan tagon"
assert remove_space2("b o n a n t a g o n") == "bonan tagon"


# chr(0x41) == 'A'
alphabet = []
for i in range(26):
    alphabet.append(chr(0x41 + i))
print(alphabet)

alphabet_lower = []
for i in range(26):
    alphabet_lower.append(chr(0x61 + i))
print(alphabet_lower)

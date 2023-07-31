#!/usr/bin/env python3
# coding:utf-8

def dec2bin(dec: int):
    """Même chose que la fonction bin pré-intégrée.
    Multiplications successives par 2, le reste est le bit de droite et le quotient est redivisé par 2."""
    r = dec % 2
    q = dec // 2
    output = str(r)
    while q != 0:
        r = q % 2
        q = q // 2
        output = str(r) + output
    return '0b' + output


print(dec2bin(179))
assert dec2bin(10) == bin(10)
assert dec2bin(34) == bin(34)
assert dec2bin(13) == bin(13)
assert dec2bin(2) == bin(2)
assert dec2bin(140) == bin(140)

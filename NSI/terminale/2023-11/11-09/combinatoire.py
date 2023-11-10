#!/usr/bin/env python3
# -*- coding:utf-8 -*-
def comb(k: int, n: int) -> int:
    """Divise k trucs parmi n"""
    numerator = 1
    for i in range(k):
        numerator *= n-i
    denominator = 1
    for i in range(k):
        denominator *= k-i
    return numerator // denominator


print(comb(13, 52) * comb(13, 39) * comb(13, 26) * comb(13, 13))

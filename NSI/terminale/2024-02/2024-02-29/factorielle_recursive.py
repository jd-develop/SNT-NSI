#!/usr/bin/env python3
# -*- coding=utf-8 -*-

# This document is licensed under the GNU-GPL v3 or later.
from math import factorial


def factorielle_récursive(n: int) -> int:
    if n < 0:
        raise ValueError("Please provide a number greater than 0")
    if n == 0 or n == 1:
        return 1
    return n*factorielle_récursive(n-1)


for i in range(100):
    assert factorielle_récursive(i) == factorial(i)

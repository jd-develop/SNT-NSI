#!/usr/bin/env python3
# -*- coding:utf-8 -*-

def estMultiple(a, b):
    return b != 0 and a % b == 0


print(estMultiple(10, 5))
print(estMultiple(301, 2))
print(estMultiple(7, 0))

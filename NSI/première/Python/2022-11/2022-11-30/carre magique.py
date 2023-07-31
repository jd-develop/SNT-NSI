#!/usr/bin/env python3
# coding:utf-8

carreMagique = [[2, 9, 4],
                [7, 5, '?'],
                [6, '?', 8]]

carreMagique[1][2] = 3
carreMagique[2][1] = 1

print(sum(carreMagique[0]))
print(sum(carreMagique[1]))
print(sum(carreMagique[2]))

print(carreMagique[0][0] + carreMagique[1][0] + carreMagique[2][0])
print(carreMagique[0][1] + carreMagique[1][1] + carreMagique[2][1])
print(carreMagique[0][2] + carreMagique[1][2] + carreMagique[2][2])

print(carreMagique[0][0] + carreMagique[1][1] + carreMagique[2][2])
print(carreMagique[2][0] + carreMagique[1][1] + carreMagique[0][2])

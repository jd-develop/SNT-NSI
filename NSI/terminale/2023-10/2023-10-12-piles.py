#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import math


class Stack:
    """Une pile avec ses 5 méthodes"""
    def __init__(self):
        self.stack: list = list()

    def is_empty(self):
        return len(self.stack) == 0

    def push(self, value):
        self.stack.append(value)

    def read(self):
        return self.stack[-1]

    def pop(self):
        return self.stack.pop()


def copy_stack(stack: Stack):
    temporary = Stack()
    copy = Stack()

    while not stack.is_empty():
        temporary.push(stack.pop())

    while not temporary.is_empty():
        element = temporary.pop()
        copy.push(element)
        stack.push(element)

    return copy


s = Stack()
s.push(math)
s.push(1)
c = copy_stack(s)
assert c.stack == s.stack
assert c.pop() == 1
assert c.pop().pi == math.pi


def destructive_print(stack):
    while not stack.is_empty():
        print(stack.pop())


def print_stack(stack):
    copy = copy_stack(stack)
    destructive_print(copy)


s = Stack()
for i in range(10):
    s.push(i)

print_stack(s)
assert s.stack == list(i for i in range(10))
print()
destructive_print(s)
assert s.stack == list()

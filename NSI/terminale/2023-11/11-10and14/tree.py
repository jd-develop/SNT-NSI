#!/usr/bin/env python3
# -*- coding:utf-8 -*-


class Node:
    def __init__(self, value):
        self.value = value
        self.left: Node | None = None
        self.right: Node | None = None

    def __str__(self):
        return f"({self.left}, {self.value}, {self.right})"

    def add(self, value):
        if value == self.value:
            return
        if isinstance(value, str) and isinstance(self.value, str):
            if len(value) == 0:
                return
            greater = value.lower() > self.value.lower()
        else:
            greater = value > self.value
        if greater:
            if self.right is None:
                self.right = Node(value)
            else:
                self.right.add(value)
        else:
            if self.left is None:
                self.left = Node(value)
            else:
                self.left.add(value)

    def add_all(self, *args):
        for arg in args:
            self.add(arg)

    def __contains__(self, item):
        if self.value == item:
            return True

        if isinstance(item, str) and isinstance(self.value, str):
            greater = ord(item[0].lower()) > ord(self.value[0].lower())
        else:
            greater = item > self.value

        if greater:
            return self.right is not None and item in self.right
        else:
            return self.left is not None and item in self.left

    def infix_path(self):
        if self.left is None:
            left_path = ()
        else:
            left_path = self.left.infix_path()
        if self.right is None:
            right_path = ()
        else:
            right_path = self.right.infix_path()
        return left_path + (self.value,) + right_path

    def prefix_path(self):
        if self.left is None:
            left_path = ()
        else:
            left_path = self.left.prefix_path()
        if self.right is None:
            right_path = ()
        else:
            right_path = self.right.prefix_path()
        return (self.value,) + left_path + right_path

    def postfix_path(self):
        if self.left is None:
            left_path = ()
        else:
            left_path = self.left.postfix_path()
        if self.right is None:
            right_path = ()
        else:
            right_path = self.right.postfix_path()
        return left_path + right_path + (self.value,)

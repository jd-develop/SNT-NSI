#!/urs/bin/env python3
# coding:utf-8
import random


class Card:
    COLOUR_NAME = ("trèfle", "carreau", "cœur", "pique")
    CARD_NAME = (2, 3, 4, 5, 6, 7, 8, 9, 10, "Valet", "Dame", "Roi", "As")

    def __init__(self, colour: int, value: int, next=None):
        assert colour in range(4), "0 = trèfle, 1 = carreau, 2 = cœur, 3 = pique."
        self.colour: int = colour
        assert value in range(13), "0 = 2, 1 = 3, ..., 9 = valet, 10 = dame, 11 = roi, 12 = as."
        self.value: int = value
        self.next = next

    def __str__(self):
        return f"{self.CARD_NAME[self.value]} de {self.COLOUR_NAME[self.colour]}"

    def __repr__(self):
        return str(self)

    def __eq__(self, other):
        """Renvoie si les cartes ont la même VALEUR (roi de pique = roi de trèfle par exemple)"""
        if not isinstance(other, Card):
            return False
        return self.value == other.value

    def __lt__(self, other):
        """Compare uniquement les VALEURS des cartes"""
        if not isinstance(other, Card):
            return False
        return self.value < other.value

    def __gt__(self, other):
        """Compare uniquement les VALEURS des cartes"""
        if not isinstance(other, Card):
            return False
        return self.value > other.value

    def __ge__(self, other):
        """Compare uniquement les VALEURS des cartes"""
        if not isinstance(other, Card):
            return False
        return self.value >= other.value

    def __le__(self, other):
        """Compare uniquement les VALEURS des cartes"""
        if not isinstance(other, Card):
            return False
        return self.value <= other.value

    def __ne__(self, other):
        """Compare uniquement les VALEURS des cartes"""
        if not isinstance(other, Card):
            return False
        return self.value != other.value


class Stack:
    """Une pile"""
    def __init__(self):
        self.top = None

    def __str__(self):
        if self.top is None:
            return 'Pile vide'
        card = self.top
        result = ""
        while card is not None:
            result += " → " + str(card)
            card = card.next
        return result

    def __repr__(self):
        return str(self)

    def __len__(self):
        length = 0
        card = self.top
        while card is not None:
            length += 1
            card = card.next
        return length

    def is_empty(self):
        return self.top is None

    def push(self, card):
        card.next = self.top
        self.top = card

    def pop(self):
        assert not self.is_empty(), "la pile est vide."
        top = self.top
        self.top = top.next
        top.next = None
        return top

    def read(self):
        """Renvoie le haut de la pile"""
        if self.is_empty():
            return None
        return self.top


class Queue:
    def __init__(self):
        self.head = None
        self.tail = None
        self._len = 0

    def __str__(self):
        if self.head is None:
            return 'File vide'
        card = self.head
        result = ""
        while card is not None:
            result += ' ← ' + str(card)
            card = card.next
        return result + ' ← '

    def __repr__(self):
        return str(self)

    def is_empty(self):
        return self.head is None and self.tail is None

    def push(self, value):
        if self.is_empty():
            self.head = self.tail = value
        else:
            if self.head.next is None:
                self.head.next = self.tail
            self.tail.next = value
            self.tail = value
        self._len += 1

    def pop(self):
        former_head = self.head
        self.head = self.head.next
        if self.head is None:
            self.tail = None
        self._len -= 1
        return former_head

    def read(self):
        if self.is_empty():
            return None
        return self.head

    def empty(self):
        self.head = self.tail = None
        self._len = 0

    def __len__(self):
        return self._len


def create_shuffle_and_distribute_game():
    """Renvoie le tuple joueur1, joueur2"""
    game = [Card(colour, value) for colour in range(4) for value in range(13)]
    assert len(game) == 52
    random.shuffle(game)

    p1 = Queue()
    p2 = Queue()
    for i, card in enumerate(game):
        if i % 2 == 0:
            p1.push(card)
        else:
            p2.push(card)

    return p1, p2


if __name__ == '__main__':
    player1, player2 = create_shuffle_and_distribute_game()

#!/urs/bin/env python3
from main import *


def test_file(file: Queue):
    assert file.is_empty()
    assert len(file) == 0

    file.push(Card(1, 1))
    assert len(file) == 1
    assert file.read() == Card(2, 1)
    assert not file.is_empty()

    file.push(Card(2, 1))
    assert len(file) == 2
    assert file.read() == Card(3, 1)

    assert file.pop() == Card(2, 1)
    assert len(file) == 1
    assert file.read() == Card(2, 1)
    assert file.pop() == Card(0, 1)
    assert len(file) == 0

    assert file.is_empty()

    for i in range(10):
        file.push(Card(1, i))

    assert len(file) == 10
    assert file.read() == Card(1, 0)

    file.empty()
    assert file.is_empty()
    assert file.read() is None
    assert file._len == 0


test_file(Queue())

assert Card(1, 9) <= Card(2, 11)
assert Card(1, 9) != Card(2, 12)
assert Card(1, 9) <= Card(2, 9)
assert Card(1, 9) == Card(2, 9)

print("test Pile")
pp = Stack()
for i in [Card(1, 1), Card(1, 2), Card(1, 3), 0, 0, Card(1, 4), 0, 0, Card(1, 5), 0]:
    if i == 0:
        print(f"dépile {pp.pop()} ==> {str(pp)} (len: {len(pp)})")
    else:
        pp.push(i)
        print(f"empile {i} ==> {str(pp)} (len: {len(pp)})")

print("test File")
ff = Queue()
for i in [Card(1, 1), Card(1, 2), Card(1, 3), 0, 0, Card(1, 4), 0, 0, Card(1, 5), 0]:
    if i == 0:
        print(f"défile {ff.pop()} ==> {str(ff)} (len: {len(ff)})")
    else:
        ff.push(i)
        print(f"enfile {i} ==> {str(ff)} (len: {len(ff)})")

p1, p2 = create_shuffle_and_distribute_game()
assert len(p1) + len(p2) == 52


print("test boucle de jeu")
p1 = Queue()
for card in [8, 11, 11, 1, 4, 8, 10, 9, 5, 7, 4, 13, 3, 6, 12, 1, 9, 1, 9, 12, 2, 2, 8, 10, 2, 11]:
    card_to_push = card-2
    if card_to_push == -1:
        card_to_push = 12
    p1.push(Card(1, card_to_push))
p2 = Queue()
for card in [3, 5, 6, 10, 6, 5, 13, 7, 10, 12, 13, 4, 1, 7, 3, 2, 11, 4, 3, 12, 13, 6, 9, 5, 7, 8]:
    card_to_push = card - 2
    if card_to_push == -1:
        card_to_push = 12
    p2.push(Card(1, card_to_push))

result = main_loop(p1, p2, False)
assert result[0].is_empty()
assert len(result[1]) == 52
assert result[1].read() == Card(1, 0)

p1 = Queue()
p1.push(Card(1, 1))
p2 = Queue()
p2.push(Card(1, 1))

result = main_loop(p1, p2, False)
assert result[0].is_empty()
assert result[1].is_empty()

print("test boucle de jeu réussi")

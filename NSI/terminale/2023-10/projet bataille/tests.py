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

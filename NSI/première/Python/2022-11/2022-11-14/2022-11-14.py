def ascii_(str_):
    for char in str_:
        print(hex(ord(char)), end=' ')
    print()


ascii_("SALUT")


def occurrences1(str_, char_):
    if char_ not in str_:
        return 0
    counter = 0
    for char in str_:
        if char == char_:
            counter += 1

    return counter


def occurrences2(str_, char_):
    if char_ not in str_:
        return 0
    counter = 0
    for i in range(len(str_)):
        if str_[i] == char_:
            counter += 1

    return counter


def indice_occurrence1(str_, char_):
    if char_ not in str_:
        return None
    for index, char in enumerate(str_):
        if char == char_:
            return index


def indice_occurrence2(str_, char_):
    if char_ not in str_:
        return None
    for i in range(len(str_)):
        if str_[i] == char_:
            return i


def indice_occurrence3(str_, char_):
    if char_ not in str_:
        return None
    i = 0
    char = str_[i]
    while char != char_:
        i += 1
        char = str_[i]
    return i


print(occurrences1("llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch", 'l'))
print(occurrences2("llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch", 'l'))

print(indice_occurrence1("llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch", 'p'))
print(indice_occurrence2("llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch", 'p'))
print(indice_occurrence3("llanfairpwllgwyngyllgogerychwyrndrobwllllantysiliogogogoch", 'p'))

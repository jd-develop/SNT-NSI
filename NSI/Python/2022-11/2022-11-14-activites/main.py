#!/usr/bin/env python3
# codding:utf-8

def frequences(sequence: str):
    sequence = sequence.upper()
    nb_total = 0
    nb = {
        "A": 0,
        "C": 0,
        "G": 0,
        "T": 0,
    }
    for b in sequence:
        assert b in nb.keys(), f"{b} n'est pas une base valide."
        nb[b] += 1
        nb_total += 1
    return nb_total, nb


def frequences2(sequence: str):
    sequence = sequence.upper()
    nb_total = 0
    nb = {
        "A": 0,
        "C": 0,
        "G": 0,
        "T": 0,
    }
    for i in range(len(sequence)):
        b = sequence[i]
        assert b in nb.keys(), f"{b} n'est pas une base valide."
        nb[b] += 1
        nb_total += 1
    return nb_total, nb


gene = 'ATGCGTACTGGTAATGCAAACTAA'
print(frequences(gene))
print(frequences2(gene))


def transcription(sequence: str): return sequence.upper().replace('T', 'U')


def transcription1(sequence: str):
    arn = ""
    sequence = sequence.upper()
    for i in range(len(sequence)):
        if sequence[i] == 'T':
            arn += 'U'
        else:
            arn += sequence[i]
    return arn


gene = "ATGCGTACTGGTAATGCAAACTAA"
print(transcription(gene))
print(transcription1(gene))

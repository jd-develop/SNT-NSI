#!/usr/bin/env python3
# codding:utf-8

def frequences(sequence: str):
    sequence = sequence.upper()
    nb = {
        "A": 0,
        "C": 0,
        "G": 0,
        "T": 0,
    }
    for b in sequence:
        assert b in nb.keys(), f"{b} n'est pas une base valide."
        nb[b] += 1
    for b in nb.keys():
        nb[b] /= len(sequence)
    return nb


def frequences2(sequence: str):
    sequence = sequence.upper()
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
    for b in nb.keys():
        nb[b] /= len(sequence)
    return nb


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


def rechercheGene(sequence):
    n = len(sequence)
    i = 0
    while i < n-3:
        if sequence[i] == 'A' and sequence[i + 1] == 'T' and sequence[i + 2] == 'G':
            return i
        i += 1
    return -1


seq = 'TCACAGTAATAGGAGGCGTAAAATGCGTACTGGTAATGCAAACTAATGGAAAAATATAAA'
print(rechercheGene(seq))


def recherche(gene_, sequence): return gene_ in sequence


def recherche2(gene_, sequence):
    n = len(sequence)
    g = len(gene_)
    i = 0
    trouve = False
    while i < n and not trouve:
        j = 0
        while j < g and gene_[j] == sequence[i + j]:
            j += 1
        if j == g:
            trouve = True
        i += 1
    return trouve


print(recherche("AATC", "GTACAAATCTTGCC"))
print(recherche("AATC", "GTACAAATGTTGCC"))
print(recherche2("AATC", "GTACAAATCTTGCC"))
print(recherche2("AATC", "GTACAAATGTTGCC"))

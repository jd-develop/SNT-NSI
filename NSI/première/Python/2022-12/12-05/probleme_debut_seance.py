tableau = []
for i in range(3):
    tableau.append([])
    for j in range(3):
        tableau[i].append(3*i + j + 1)

print(tableau)

print([[3*i + j + 1 for j in range(3)] for i in range(3)])

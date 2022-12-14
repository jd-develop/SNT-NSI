from random import randint

global n, p
cellSize = 15
global currentGrid
global tempGrid
alive = 1
dead = 0
pause = False

def setup():
    global n, p
    # fenêtre d'affichage pour les motifs de test
    # size(600, 500) 
    # plein écran pour la version définitive 
    fullScreen() 
    background(0) # fond noir
    frameRate(20)
    
    # Calcul du nombre de lignes n et du nombre de colonnes p
    n = int(width/cellSize)
    p = int(height/cellSize)
    
    # Initialisation des grilles courante et temporaire
    initGrids()
    # Affichage initial de la grille
    displayGrid()
    
    
def draw():
    # Actualiser la grille
    updateGrids()
    # Afficher la grille
    displayGrid()


def mousePressed():
    # Réinitialise la grille
    initGrids()
    
def keyPressed():
    # Appuyer sur la touche espace suspend ou reprend l'exécution
    global pause
    if key == ' ':
        pause = not pause
    if pause:
        noLoop()
    else:
        loop()
            

def initGrids():
    '''
    La fonction initGrids initialise les grilles courante currentGrid et temporaire tempGrid.
    Les grilles sont codées par des listes de colonnes, par cohérence avec l'abscisse x en colonne et l'ordonnée y en ligne
    '''
    
    global currentGrid, tempGrid
    
    # Grilles avec motifs de test
    blinker = [[0, 0, 0, 0, 0],
               [0, 0, 0, 0, 0],
               [0, 1, 1, 1, 0],
               [0, 0, 0, 0, 0],
               [0, 0, 0, 0, 0]]
    
    tub = [[0, 0, 0, 0, 0],
           [0, 0, 1, 0, 0],
           [0, 1, 0, 1, 0],
           [0, 0, 1, 0, 0],
           [0, 0, 0, 0, 0]]

    ship = [[0, 0, 0, 0, 0],
            [0, 1, 1, 0, 0],
            [0, 1, 0, 1, 0],
            [0, 0, 1, 1, 0],
            [0, 0, 0, 0, 0]]
    
    glider = [[0, 0, 0, 0, 0],
              [0, 0, 0, 1, 0],
              [0, 1, 0, 1, 0],
              [0, 0, 1, 1, 0],
              [0, 0, 0, 0, 0]]
    
    glider_gun = [[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0],
                  [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]
    
    the_4812_diamond = [[0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0],
                        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                        [0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
                        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                        [0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0],
                        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
                        [0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0]]
    
    chosen_grid = glider_gun
    
    chosen_grid2 = [[0 for y in range(p)] for x in range(n)]
    for i, line_ in enumerate(chosen_grid):
        for j, cell_ in enumerate(line_):
            chosen_grid2[i+int(n/2)-int(len(chosen_grid)/2)][j+int(p/2)-int(len(line_)/2)] = cell_
    
    # Choix de la grille initiale
    
    # Grille aléatoire finale ou adaptation d'une autre grille
    # currentGrid = [[randint(1,12)//12 for y in range(p)] for x in range(n)] # cas général avec l'affichage fullScreen()
    currentGrid = chosen_grid2
    
    # test clignotant
    # currentGrid = blinker 
    # test tube
    # currentGrid = tub 
    # test navire
    # currentGrid = ship 
    # test planeur
    # currentGrid = glider 
    
    # initialise la grille temporaire avec des zéros
    tempGrid = [[0 for y in range(p)] for x in range(n)]
    
    
def displayGrid():
    '''
    Affiche chaque cellule (x;y), sous la forme d'un rectangle 
    '''
    for x in range(n):
        for y in range(p):
            # Si la cellule est vivante, colorier en bleu
            if currentGrid[x][y] == alive:
                fill(255)
            # Sinon la cellule est morte, colorier en noir
            elif currentGrid[x][y] == dead:
                fill(0)
            # Tracer la cellule carrée de taille cellSize et de cordonnées (x*cellSize; y*cellSize)
            square(x*cellSize, y*cellSize, cellSize)
    
            
def updateGrids():
    '''
    Actualise la grille en :
        - parcourant toutes les cellules de la grille
        - calculant le nombre de voisins vivants de la cellule en cours
        - appliquant alors les règles de transition pour actualiser la cellule en cours
    '''
    global currentGrid
    global tempGrid
    
    # Boucles de parcours de la grille courante, par colonne x, puis par ligne y
    
    for x in range(n):
        for y in range(p):
            # nombre de voisins vivants de la cellule (x;y)
            neighbors = aliveNeighbors(currentGrid, x, y)
            # état de la cellule (x;y)
            state = currentGrid[x][y]
            # Actualisation de la cellule (x;y)
            if state == dead and neighbors == 3: # birth
                tempGrid[x][y] = alive
            elif state == alive and neighbors < 2: # isolation
                tempGrid[x][y] = dead
            elif state == alive and neighbors > 3: # overpopulated
                tempGrid[x][y] = dead
            else: # stable           
                tempGrid[x][y] = currentGrid[x][y]
    
    # boucles de recopie des valeurs de tempGrid dans  currentGrid   
    for x in range(n):
        for y in range(p):
            currentGrid[x][y] = tempGrid[x][y]
    
            

def aliveNeighbors(current_grid, x, y):
    '''
    Calcule et retourne le nombre de voisins vivants de la cellule de coordonnées (x;y).
    Doit tenir compte du voisinage
    '''

    nb = 0
    for i in range(-1,2,1):
        for j in range(-1,2,1):
            nb += current_grid[(x+i+n)%n][(y+j+p)%p]

    nb -= current_grid[x][y]
    return nb
    

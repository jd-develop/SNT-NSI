from random import randint

CHOSEN_GRID = "glider_gun"

global n, p
cellSize = 15
global currentGrid
global tempGrid
alive = 1
dead = 0
pause = True
gen = 0
frame_rate = 20


def setup():
    global n, p
    # fenêtre d'affichage pour les motifs de test
    # size(600, 500) 
    # plein écran pour la version définitive 
    fullScreen() 
    background(0) # fond noir
    frameRate(frame_rate)
    
    # Calcul du nombre de lignes n et du nombre de colonnes p
    n = int(width/cellSize)
    p = int(height/cellSize)
    
    # Initialisation des grilles courante et temporaire
    initGrids("empty")
    # Affichage initial de la grille
    displayGrid()
    
    textSize(20)
    fill(255)
    text("gen: " + str(gen), 0, 20)
    fill(0)
    
    
def draw():
    if not pause:
        # Actualiser la grille
        updateGrids()
        # Afficher la grille
        displayGrid()
        
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)


def mousePressed():
    if mouseButton == LEFT: 
        # Réinitialise la grille
        initGrids()
        # Afficher la grille
        displayGrid()
        
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    else:
        global currentGrid
        # changer l'état d'une cellule
        cell_x = int(mouseX/cellSize)
        cell_y = int(mouseY/cellSize)
        
        try:
            if currentGrid[cell_x][cell_y] == alive:
                currentGrid[cell_x][cell_y] = dead
            else:
                currentGrid[cell_x][cell_y] = alive
            # Afficher la grille
            displayGrid()
            fill(255)
            text("gen: " + str(gen), 0, 20)
            fill(0)
        except IndexError:
            pass
    

def keyPressed():
    global frame_rate
    # Appuyer sur la touche espace suspend ou reprend l'exécution
    global pause
    if key == ' ':
        pause = not pause
    elif keyCode == RIGHT and pause:
        # Actualiser la grille
        updateGrids()
        # Afficher la grille
        displayGrid()
        
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif keyCode == UP:
        frame_rate += 5
        frameRate(frame_rate)
    elif keyCode == DOWN:
        frame_rate -= 5
        if frame_rate < 5:
            frame_rate = 5
        frameRate(frame_rate)
    elif key == 'r':
        initGrids("random")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 'b':
        initGrids("blinker")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 't':
        initGrids("tub")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 's':
        initGrids("ship")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 'g':
        initGrids("glider")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 'u':
        initGrids("glider_gun")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 'd':
        initGrids("the_4812_diamond")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == 'e':
        initGrids("random_more")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    elif key == "p":
        initGrids("space_ship")
        displayGrid()
        fill(255)
        text("gen: " + str(gen), 0, 20)
        fill(0)
    

def initGrids(which_grid="empty"):
    '''
    La fonction initGrids initialise les grilles courante currentGrid et temporaire tempGrid.
    Les grilles sont codées par des listes de colonnes, par cohérence avec l'abscisse x en colonne et l'ordonnée y en ligne
    '''
    
    global currentGrid, tempGrid, gen
    
    # Grilles avec motifs de test
    empty = [[0]]
    
    blinker = [[1, 1, 1]]
    
    tub = [[0, 1, 0],
           [1, 0, 1],
           [0, 1, 0]]

    ship = [[1, 1, 0],
            [1, 0, 1],
            [0, 1, 1]]
    
    glider = [[0, 0, 1],
              [1, 0, 1],
              [0, 1, 1]]
    
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
    
    space_ship = [[0, 1, 1, 1, 1, 1, 1],
                  [1, 0, 0, 0, 0, 0, 1],
                  [0, 0, 0, 0, 0, 0, 1],
                  [1, 0, 0, 0, 0, 1, 0],
                  [0, 0, 1, 1, 0, 0, 0]]
    
    adapt_to_screen = True
    if which_grid == "blinker":
        chosen_grid = blinker
    elif which_grid == "tub":
        chosen_grid = tub
    elif which_grid == "ship":
        chosen_grid = ship
    elif which_grid == "glider":
        chosen_grid = glider
    elif which_grid == "glider_gun":
        chosen_grid = glider_gun
    elif which_grid == "the_4812_diamond":
        chosen_grid = the_4812_diamond
    elif which_grid == "empty":
        chosen_grid = empty
    elif which_grid == "space_ship":
        chosen_grid = space_ship
    elif which_grid == "random_more":
        currentGrid = [[randint(1, 5)//5 for y in range(p)] for x in range(n)]
        adapt_to_screen = False
    else:
        currentGrid = [[randint(1, 12)//12 for y in range(p)] for x in range(n)]
        adapt_to_screen = False
    
    if adapt_to_screen:
        chosen_grid2 = [[0 for y in range(p)] for x in range(n)]
        for i, line_ in enumerate(chosen_grid):
            for j, cell_ in enumerate(line_):
                chosen_grid2[j+int(n/2)-int(len(line_)/2)][i+int(p/2)-int(len(chosen_grid)/2)] = cell_
        currentGrid = chosen_grid2
    
    # initialise la grille temporaire avec des zéros
    tempGrid = [[0 for y in range(p)] for x in range(n)]
    gen = 0
    
    
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
    global tempGrid, gen
    
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
    gen += 1
    
    
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
    

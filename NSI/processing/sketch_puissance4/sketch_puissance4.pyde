# Puissance 4
player = 1
fin = False
winner = 0
grille = [[0] * 7 for _ in range(6)]

def setup():
    background(0)
    size(700, 640)
    fill(0)
    stroke(255)
    textSize(40)
    
    for i in range(6):
        for j in range(7):
            rect(j*100, 40 + i*100, (j+1)*100, 140 + i*100)
    
    fill(255)
    
    
def draw():
    global player, fin, grille, winner
    # dessine la zone de texte
    fill(255)
    stroke(255)
    rect(0, 0, 700, 40)
    # écrit le texte
    fill(0)
    if not fin:
        text("Joueur " + str(player), 0, 30)
            
        if mousePressed:
            if 0 <= mouseX <= 700 and 40 <= mouseY <= 640:
                jouer(player)
                delay(200)
                
        if gagne(1):
            fin = True
            winner = 1
            delay(100)
        elif gagne(2):
            fin = True
            winner = 2
            delay(100)
        elif grille_pleine():
            fin = True
            winner = 0
            delay(100)
    else:
        if winner == 1:
            text("Bravo joueur 1 !", 0, 30)
        elif winner == 2:
            text("Bravo joueur 2 !", 0, 30)
        else:
            text("Partie nulle.", 0, 30)
        
        if mousePressed:
            clear()
            
            background(0)
            fill(0)
            stroke(255)
            textSize(40)
            
            for i in range(6):
                for j in range(7):
                    rect(j*100, 40 + i*100, (j+1)*100, 140 + i*100)
    
            fill(255)
            
            grille = [[0] * 7 for _ in range(6)]
            fin = False
            delay(100)            
          
    for i, ligne in enumerate(grille):
        for j, colonne in enumerate(ligne):
            if grille[i][j] == 1:
                fill(255, 255, 0)
                stroke(255, 255, 0)
                circle(j*100 + 50, i*100 + 90, 95)
            elif grille[i][j] == 2:
                fill(255, 0, 0)
                stroke(255, 0, 0)
                circle(j*100 + 50, i*100 + 90, 95)
            
def jouer(joueur):
    global grille, player
    for j in range(7):
        if j*100 <= mouseX <= (j+1)*100:  # colonne
            for ligne_ in range(5, -1, -1):
                if grille[ligne_][j] == 0:
                    grille[ligne_][j] = joueur
                    if player == 2:
                        player = 1
                    else:
                        player = 2
                    return
            
def gagne(joueur):
    return diagonale(joueur) or colonne(joueur) or ligne(joueur)

def diagonale(joueur):
    for i, line_ in enumerate(grille):
        for j, piece in enumerate(grille):
            try:
                if grille[i][j] * grille[i+1][j+1] * grille[i+2][j+2] * grille[i+3][j+3] == joueur**4:
                    return True
            except:
                pass
            try:
                if grille[i][j] * grille[i+1][j-1] * grille[i+2][j-2] * grille[i+3][j-3] == joueur**4:
                    return True
            except:
                pass
            try:
                if grille[i][j] * grille[i-1][j+1] * grille[i-2][j+2] * grille[i-3][j+3] == joueur**4:
                    return True
            except:
                pass
            try:
                if grille[i][j] * grille[i-1][j-1] * grille[i-2][j-2] * grille[i-3][j-3] == joueur**4:
                    return True
            except:
                pass
    return False

def ligne(joueur):
    for i, line_ in enumerate(grille):
        for j, piece in enumerate(grille):
            try:
                if grille[i][j] * grille[i][j+1] * grille[i][j+2] * grille[i][j+3] == joueur**4:
                    return True
            except:
                pass
    return False

def colonne(joueur):
    for i, line_ in enumerate(grille):
        for j, piece in enumerate(grille):
            try:
                if grille[i][j] * grille[i+1][j] * grille[i+2][j] * grille[i+3][j] == joueur**4:
                    return True
            except:
                pass
    return False

def grille_pleine():
    for ligne in grille:
        for colonne in ligne:
            if colonne == 0:
                return False
    return True        

    

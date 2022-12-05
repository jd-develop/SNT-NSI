# Morpion (Tic-tac-toe)
player = 1
fin = False
winner = 0
grille = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]

def setup():
    background(0)
    size(300, 340)
    fill(0)
    stroke(255)
    textSize(40)
    
    rect(0, 40, 100, 140)
    rect(100, 40, 200, 140)
    rect(200, 40, 300, 140)
    
    rect(0, 140, 100, 240)
    rect(100, 140, 200, 240)
    rect(200, 140, 300, 240)
    
    rect(0, 240, 100, 340)
    rect(100, 240, 200, 340)
    rect(200, 240, 300, 340)
    
    fill(255)
    
    
def draw():
    global player, fin, grille, winner
    # dessine la zone de texte
    fill(255)
    stroke(255)
    rect(0, 0, 300, 40)
    # écrit le texte
    fill(0)
    if not fin:
        text("Joueur " + str(player), 0, 30)
            
        if mousePressed:
            if 0 <= mouseX <= 300 and 40 <= mouseY <= 340:
                jouer(player)
                
        if gagne(1):
            fin = True
            winner = 1
            
        if gagne(2):
            fin = True
            winner = 2
            
        if grille_pleine():
            fin = True
            winner = 0
    else:
        if winner == 1:
            text("Bravo joueur 1 !", 0, 30)
        elif winner == 2:
            text("Bravo joueur 2 !", 0, 30)
        else:
            text("Partie nulle.", 0, 30)       
            
            
    for i, ligne in enumerate(grille):
        for j, colonne in enumerate(grille):
            if grille[i][j] == 1:
                line((j+1)*100, i*100 + 40, j*100, (i+1)*100 + 40)
                line(j*100, i*100 + 40, (j+1)*100, (i+1)*100 + 40) 
            elif grille[i][j] == 2:
                circle(j*100 + 50, i*100 + 90, 95)
            
def jouer(joueur):
    global grille, player
    if 40 <= mouseY <= 140:  # première ligne
        if 0 <= mouseX <= 100:  # première colonne
            if grille[0][0] == 0:
                grille[0][0] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
        elif 100 <= mouseX <= 200:  # deuxième colonne
            if grille[0][1] == 0:
                grille[0][1] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
        elif 200 <= mouseX <= 300:  # troisième colonne
            if grille[0][2] == 0:
                grille[0][2] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
    elif 140 <= mouseY <= 240:  # deuxième ligne
        if 0 <= mouseX <= 100:  # première colonne
            if grille[1][0] == 0:
                grille[1][0] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
        elif 100 <= mouseX <= 200:  # deuxième colonne
            if grille[1][1] == 0:
                grille[1][1] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
        elif 200 <= mouseX <= 300:  # troisième colonne
            if grille[1][2] == 0:
                grille[1][2] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
    elif 240 <= mouseY <= 340:  # troisième ligne
        if 0 <= mouseX <= 100:  # première colonne
            if grille[2][0] == 0:
                grille[2][0] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
        elif 100 <= mouseX <= 200:  # deuxième colonne
            if grille[2][1] == 0:
                grille[2][1] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
        elif 200 <= mouseX <= 300:  # troisième colonne
            if grille[2][2] == 0:
                grille[2][2] = joueur
                if player == 2:
                    player = 1
                else:
                    player = 2
                
def gagne(joueur):
    return diagonale(joueur) or ligne(joueur) or colonne(joueur)


def diagonale(joueur):
    return (grille[0][0] * grille[1][1] * grille[2][2] == joueur ** 3) or (grille[2][0] * grille[1][1] * grille[0][2] == joueur ** 3)

def ligne(joueur):
    return (grille[0][0] * grille[0][1] * grille[0][2] == joueur ** 3) or (grille[1][0] * grille[1][2] * grille[1][1] == joueur ** 3) or (grille[2][0] * grille[2][1] * grille[2][2] == joueur ** 3) 

def colonne(joueur):
    return (grille[0][0] * grille[1][0] * grille[2][0] == joueur ** 3) or (grille[0][1] * grille[1][1] * grille[2][1] == joueur ** 3) or (grille[0][2] * grille[1][2] * grille[2][2] == joueur ** 3)

def grille_pleine():
    for ligne in grille:
        for colonne in ligne:
            if colonne == 0:
                return False
    return True        

    

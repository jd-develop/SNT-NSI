# pong
# joueur de droite : touches haut et bas
# joueur de gauche : touches Z et S

import math
from random import random, randint

# définition de la position du paddle de gauche
leftPaddleX = 40
leftPaddleY = 0

# sera défini dans setup()
rightPaddleX = rightPaddleY = 0

# gère la valeur qui doit être ajouté au Y des paddles à chaque tick
leftPaddleMove = rightPaddleMove = 0

# vitesse des raquettes
dy = 7

# pour les bots: si la balle n'est pas dans le camp ou qu'on vient de la toucher, on ne bouge plus les raquettes (à peu près comme un joueur humain)
do_not_move_paddles = False

paddleHeight = 150

# balle
ballR = 30
ballX, ballY = 0, 0
ballDX = ballDY = 5
ballDX *= (-1)**randint(0, 1)
ballDY *= (-1)**randint(0, 1)

# score
player_left_score = 0
player_right_score = 0

# mode
# si botMode est à True, le mode est Ordinateur contre Ordinateur
# si playerVersusBot est à True, le mode est Joueur contre Ordinateur
# si aucun des deux est à True, le mode est Joueur contre Joueur
botMode = False
playerVersusBot = False

inMenu = True
start = False


def setup():
    global leftPaddleY, rightPaddleY, rightPaddleX, ballX, ballY
    
    fullScreen()
    # size(600, 600)
    background(0)
    
    # on change le Y de la raquette gauche pour sa valeur par défaut (milieu de l'écran)
    leftPaddleY = math.ceil((height / 2) - (paddleHeight / 2))
    
    # on met la raquette droite au milieu de l'écran en Y et à droite en X
    rightPaddleY = math.ceil((height / 2) - (paddleHeight / 2))
    rightPaddleX = width - 60
    
    # on met la balle au centre
    ballX, ballY = math.ceil(width/2), math.ceil(height/2)
    
    # on change les paramètres par défaut
    textSize(50)
    textAlign(CENTER)
    strokeWeight(1)
    
    
def draw():
    global rightPaddleY, leftPaddleY, ballX, ballY, ballDX, ballDY, start, player_left_score, player_right_score, leftPaddleMove, rightPaddleMove, botMode, playerVersusBot, inMenu
    background(0)
    
    if inMenu:  # dans le menu principal
        # titre "PONG"
        fill(255)
        stroke(0);strokeWeight(1)
        textSize(100)
        text("PONG", width/2, 150)
        textSize(50)
        
        # 3 boutons: joueur contre joueur, joueur contre ordinateur, ordinateur contre ordinateur
        # bouton joueur contre joueur
        firstButtonY = (height/2)-(height/5)
        if (width/2)-300 <= mouseX <= (width/2)+300 and firstButtonY <= mouseY <= firstButtonY+100:  # hover
            fill(0)
            stroke(255);strokeWeight(5)
            rect((width/2)-300, firstButtonY, 600, 100)
            stroke(0);strokeWeight(1)
            fill(255)
            text("Player vs. Player", (width/2), firstButtonY+65)
        else:
            fill(255)
            rect((width/2)-300, firstButtonY, 600, 100)
            fill(0)
            text("Player vs. Player", (width/2), firstButtonY+65)
        
        # bouton joueur contre ordinateur
        secondButtonY = (height/2)
        if (width/2)-300 <= mouseX <= (width/2)+300 and secondButtonY <= mouseY <= secondButtonY+100:  # hover
            fill(0)
            stroke(255);strokeWeight(5)
            rect((width/2)-300, secondButtonY, 600, 100)
            stroke(0);strokeWeight(1)
            fill(255)
            text("Player vs. Computer", (width/2), secondButtonY+65)
        else:
            fill(255)
            rect((width/2)-300, secondButtonY, 600, 100)
            fill(0)
            text("Player vs. Computer", (width/2), secondButtonY+65)
            
        # bouton ordinateur contre ordinateur
        thirdButtonY = (height/2)+(height/5)
        if (width/2)-300 <= mouseX <= (width/2)+300 and thirdButtonY <= mouseY <= thirdButtonY+100:  # hover
            fill(0)
            stroke(255);strokeWeight(5)
            rect((width/2)-300, thirdButtonY, 600, 100)
            stroke(0);strokeWeight(1)
            fill(255)
            text("Computer vs. Computer", (width/2), thirdButtonY+65)
        else:
            fill(255)
            rect((width/2)-300, thirdButtonY, 600, 100)
            fill(0)
            text("Computer vs. Computer", (width/2), thirdButtonY+65)
        fill(255)
        stroke(0);strokeWeight(1)
        
        if mousePressed:
            if (width/2)-300 <= mouseX <= (width/2)+300 and firstButtonY <= mouseY <= firstButtonY+100:  # Joueur contre Joueur
                botMode = playerVersusBot = False

                leftPaddleY = rightPaddleY = height/2 - paddleHeight/2
                ballX, ballY = math.ceil(width/2), math.ceil(height/2)
                ballDX *= (-1)**randint(0, 1)
                ballDY *= (-1)**randint(0, 1)
                start = True
                inMenu = False
                delay(100)
            elif (width/2)-300 <= mouseX <= (width/2)+300 and secondButtonY <= mouseY <= secondButtonY+100:  # Joueur contre Ordinateur
                playerVersusBot = True
                botMode = False
                
                leftPaddleY = rightPaddleY = height/2 - paddleHeight/2
                ballX, ballY = math.ceil(width/2), math.ceil(height/2)
                ballDX *= (-1)**randint(0, 1)
                ballDY *= (-1)**randint(0, 1)
                start = True
                inMenu = False
                delay(100)
            elif (width/2)-300 <= mouseX <= (width/2)+300 and thirdButtonY <= mouseY <= thirdButtonY+100:  # Ordinateur contre Ordinateur
                playerVersusBot = False
                botMode = True
                
                leftPaddleY = rightPaddleY = height/2 - paddleHeight/2
                ballX, ballY = math.ceil(width/2), math.ceil(height/2)
                ballDX *= (-1)**randint(0, 1)
                ballDY *= (-1)**randint(0, 1)
                start = True
                inMenu = False
                delay(100)
    
    elif start:
        # ligne discontinue au centre de l'écran
        stroke_color = 255
        for i in range(0, height, 30):
            stroke(stroke_color)
            line(width/2, i, width/2, i+30)
            stroke_color = abs(stroke_color-255)
        stroke(255)
        
        # affichage du mode
        mode = "BvB" if botMode else "PvB" if playerVersusBot else "PvP"
        textAlign(LEFT)
        text(mode, 0, 40)
        textAlign(CENTER)
        
        # touche pressée
        if keyPressed:
            if key == "z":  # raquette gauche vers le haut
                leftPaddleMove = -1
            elif key == "s":  # raquette gauche vers le bas
                leftPaddleMove = 1
                
            if keyCode == UP:  # raquette droite vers le haut
                rightPaddleMove = -1
            elif keyCode == DOWN:  # raquette droite vers le bas
                rightPaddleMove = 1
            
            # pendant la partie, switcher de mode
            if key == 'v':
                botMode = playerVersusBot = False
                delay(100)
            if key == "b":
                playerVersusBot = False
                botMode = not botMode
                delay(100)
            if key == 'n':
                botMode = False
                playerVersusBot = not playerVersusBot
                delay(100)
        
        moveBall()  # bouger la balle
        drawBall()  # dessiner la balle
        
        # bouger les raquettes
        movePaddles()
        
        # faire en sorte que les raquettes ne sortent pas de l'écran
        leftPaddleY = constrain(leftPaddleY, 0, height-paddleHeight)
        rightPaddleY = constrain(rightPaddleY, 0, height-paddleHeight)
        
        # dessiner les raquettes
        drawLeftPaddle()
        drawRightPaddle()
        
        # afficher le score
        text(str(player_left_score), width/3, 60)
        text(str(player_right_score), 2*width/3, 60)
        
        # gagné !!
        if player_left_score == 10 or player_right_score == 10:
            start = False
            delay(100)
        
        # fin de la partie au clic
        if mousePressed:
            start = False
            inMenu = True
            delay(100)
    else:  # ni dans le menu, ni dans le jeu
        if player_left_score != 10 and player_right_score != 10:
            text("Left click to start game.", width/2, height/2)
        else:  # un joueur a gagné : on affiche les scores
            if player_left_score == 10:
                start = False
                text("Left won!", width/2, height/2)
                text("Left click to restart game.", width/2, height/2 + 60)
            if player_right_score == 10:
                start = False
                text("Right won!", width/2, height/2)
                text("Left click to restart game.", width/2, height/2 + 60)
            text(str(player_left_score), width/3, 60)
            text(str(player_right_score), 2*width/3, 60)
        if mousePressed:  # on réinitialise la position de la balle puis on va dans le menu
            ballDX = ballDY = 5
            ballDX *= (-1)**randint(0, 1)
            ballDY *= (-1)**randint(0, 1)
            inMenu = True
            player_left_score = player_right_score = 0
            delay(100)
        
        
def keyReleased():  # une touche a été lâchée
    global leftPaddleMove, rightPaddleMove
    if keyCode == UP:
        rightPaddleMove = 0
    if keyCode == DOWN:
        rightPaddleMove = 0
    if key == 's':
        leftPaddleMove = 0
    if key == 'z':
        leftPaddleMove = 0
    

def drawBall():  # dessiner la balle
    fill(255)
    circle(ballX, ballY, ballR)
    
    
def moveBall():  # bouger la balle
    global ballX, ballY, ballDX, ballDY, player_left_score, player_right_score, do_not_move_paddles
    
    # la balle touche les bords de l'écran à droite ou à gauche
    if ballX+ballR >= width:  # bord droit : +1 pour le joueur gauche
        ballX, ballY = math.ceil(width/2), math.ceil(height/2)
        player_left_score += 1
        ballDX = ballDY = 5
        ballDX *= (-1)**randint(0, 1)
        ballDY *= (-1)**randint(0, 1)
    if ballX-ballR <= 0:  # bord gauche : +1 pour le joueur droit
        ballX, ballY = math.ceil(width/2), math.ceil(height/2)
        player_right_score += 1
        ballDX = ballDY = 5
        ballDX *= (-1)**randint(0, 1)
        ballDY *= (-1)**randint(0, 1)
    
    # explication de la physique des raquettes (inspiré de https://gamedev.stackexchange.com/questions/147773/what-is-original-pong-behaviour)
    # on calcule le ratio entre le centre de la raquette et là où arrive la balle, et on a l'angle avec lequel la balle doit repartir.
    
    # left paddle
    if ballX-ballR <= leftPaddleX and (ballY+ballR >= leftPaddleY and ballY-ballR <= leftPaddleY+paddleHeight):
        paddleCenter = leftPaddleY + math.ceil(paddleHeight/2)
        ratio = paddleCenter/ballY
        ballDX *= -1.05  # on augmente la vitesse de la balle de 5%
        ballDY *= ratio
        do_not_move_paddles = True  # la raquette a frappé la balle, l'ordinateur peut arrêter de jouer
        
    # right paddle
    if ballX+ballR >= rightPaddleX+20 and (ballY+ballR >= rightPaddleY and ballY-ballR <= rightPaddleY+paddleHeight):
        paddleCenter = rightPaddleY + math.ceil(paddleHeight/2)
        ratio = paddleCenter/ballY
        ballDX *= -1.05  # on augmente la vitesse de la balle de 5%
        ballDY *= ratio
        do_not_move_paddles = True  # la raquette a frappé la balle, l'ordinateur peut arrêter de jouer
    
    if (width/2)-ballR <= ballX <= (width/2)+ballR:  # la balle change de camp, l'ordinateur peut de nouveau jouer
        do_not_move_paddles = False
        
    if ballY+ballR >= height or ballY-ballR <= 0:  # la balle touche un des bords haut ou bas de l'écran, elle rebondit
        ballDY *= -1
    
    # finalement, on bouge la balle
    ballX += ballDX
    ballY += ballDY
 
       
def drawLeftPaddle():  # dessiner la raquette gauche
    fill(255)
    rect(leftPaddleX, leftPaddleY, 20, paddleHeight)
  
      
def drawRightPaddle():  # dessiner la raquette droite
    fill(255)
    rect(rightPaddleX, rightPaddleY, 20, paddleHeight)
    
def movePaddles():  # bouger les raquettes
    global leftPaddleY, rightPaddleY
    if playerVersusBot:  # joueur contre ordi : on ne bouge que la raqutte droite automatiquement
        leftPaddleY += leftPaddleMove*dy  # on bouge la raquette gauche selon l'entrée utilisateur
        if not do_not_move_paddles:
            if ballX > (width/2)+ballR:  # si la balle est dans notre camp
                if not ballY-paddleHeight/2 in [rightPaddleY+a for a in range(-paddleHeight/2, paddleHeight/2)]:  # évite le tremblement de la raquette
                    if ballY-paddleHeight/2 > rightPaddleY:
                        rightPaddleY += dy
                    elif ballY-paddleHeight/2 < rightPaddleY:
                        rightPaddleY -= dy
    elif botMode:  # ordi contre ordi : on bouge les deux raquttes automatiquement
        if not do_not_move_paddles:
            if ballX < (width/2)-ballR:
                if not ballY-paddleHeight/2 in [leftPaddleY+a for a in range(-paddleHeight/2, paddleHeight/2)]:  # évite le tremblement de la raquette
                    if ballY-paddleHeight/2 > leftPaddleY:
                        leftPaddleY += dy
                    elif ballY-paddleHeight/2 < leftPaddleY:
                        leftPaddleY -= dy
            elif ballX > (width/2)+ballR:
                if not ballY-paddleHeight/2 in [rightPaddleY+a for a in range(-paddleHeight/2, paddleHeight/2)]:  # évite le tremblement de la raquette
                    if ballY-paddleHeight/2 > rightPaddleY:
                        rightPaddleY += dy
                    elif ballY-paddleHeight/2 < rightPaddleY:
                        rightPaddleY -= dy
    else:  # joueur contre joueur : on bouge les raquettes selon l'entrée utilisateur
        leftPaddleY += leftPaddleMove*dy
        rightPaddleY += rightPaddleMove*dy

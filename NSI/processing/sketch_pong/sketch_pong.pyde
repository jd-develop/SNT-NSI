import math
from random import randint
import time

leftPaddleX = 40
leftPaddleY = 0
rightPaddleX = rightPaddleY = 0
leftPaddleMove = rightPaddleMove = 0
dy = 7
do_not_move_paddles = False

paddleHeight = 150

ballR = 30
ballX, ballY = 0, 0
ballDX = ballDY = 5

player_left_score = 0
player_right_score = 0

botMode = False
playerVersusBot = False
inMenu = True
start = False


def setup():
    fullScreen()
    # size(600, 600)
    background(0)
    global leftPaddleY, rightPaddleY, rightPaddleX, ballX, ballY
    leftPaddleY = math.ceil((height / 2) - (paddleHeight / 2))
    rightPaddleY = math.ceil((height / 2) - (paddleHeight / 2))
    rightPaddleX = width - 60
    ballX, ballY = math.ceil(width/2), math.ceil(height/2)
    textSize(50)
    textAlign(CENTER)
    strokeWeight(1)
    
    
def draw():
    global rightPaddleY, leftPaddleY, ballX, ballY, ballDX, ballDY, start, player_left_score, player_right_score, leftPaddleMove, rightPaddleMove, botMode, playerVersusBot, inMenu
    background(0)
    
    if inMenu:
        # 3 boutons: joueur contre joueur, joueur contre ordinateur, ordinateur contre ordinateur
        fill(255)
        stroke(0);strokeWeight(1)
        textSize(100)
        text("PONG", width/2, 150)
        textSize(50)
        
        # bouton joueur contre joueur
        firstButtonY = (height/2)-(height/5)
        if (width/2)-300 <= mouseX <= (width/2)+300 and firstButtonY <= mouseY <= firstButtonY+100:
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
        if (width/2)-300 <= mouseX <= (width/2)+300 and secondButtonY <= mouseY <= secondButtonY+100:
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
        if (width/2)-300 <= mouseX <= (width/2)+300 and thirdButtonY <= mouseY <= thirdButtonY+100:
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
            if (width/2)-300 <= mouseX <= (width/2)+300 and firstButtonY <= mouseY <= firstButtonY+100:
                botMode = playerVersusBot = False

                leftPaddleY = rightPaddleY = height/2 - paddleHeight/2
                ballX, ballY = math.ceil(width/2), math.ceil(height/2)
                start = True
                inMenu = False
                time.sleep(0.1)
            elif (width/2)-300 <= mouseX <= (width/2)+300 and secondButtonY <= mouseY <= secondButtonY+100:
                playerVersusBot = True
                botMode = False
                
                leftPaddleY = rightPaddleY = height/2 - paddleHeight/2
                ballX, ballY = math.ceil(width/2), math.ceil(height/2)
                start = True
                inMenu = False
                time.sleep(0.1)
            elif (width/2)-300 <= mouseX <= (width/2)+300 and thirdButtonY <= mouseY <= thirdButtonY+100:
                playerVersusBot = False
                botMode = True
                
                leftPaddleY = rightPaddleY = height/2 - paddleHeight/2
                ballX, ballY = math.ceil(width/2), math.ceil(height/2)
                start = True
                inMenu = False
                time.sleep(0.1)
    
    elif start:
        # ligne discontinue au centre de l'écran
        stroke_color = 255
        for i in range(0, height, 30):
            stroke(stroke_color)
            line(width/2, i, width/2, i+30)
            stroke_color = abs(stroke_color-255)
        stroke(255)
        
        mode = "BvB" if botMode else "PvB" if playerVersusBot else "PvP"
        textAlign(LEFT)
        text(mode, 0, 40)
        textAlign(CENTER)
        
        if keyPressed:
            if key == "z":
                leftPaddleMove = -1
            elif key == "s":
                leftPaddleMove = 1
                
            if keyCode == UP:
                rightPaddleMove = -1
            elif keyCode == DOWN:
                rightPaddleMove = 1
            
            if key == 'v':
                botMode = playerVersusBot = False
                time.sleep(0.1)
            
            if key == "b":
                playerVersusBot = False
                botMode = not botMode
                time.sleep(0.1)
                
            if key == 'n':
                botMode = False
                playerVersusBot = not playerVersusBot
                time.sleep(0.1)
        
        drawBall()
        moveBall()
        
        # bouge les raquettes
        # movePaddles()
        
        leftPaddleY = constrain(leftPaddleY, 0, height-paddleHeight)
        rightPaddleY = constrain(rightPaddleY, 0, height-paddleHeight)
        drawLeftPaddle()
        drawRightPaddle()
        
        text(str(player_left_score), width/3, 60)
        text(str(player_right_score), 2*width/3, 60)
        
        if player_left_score == 10 or player_right_score == 10:
            start = False
            time.sleep(0.1)
        
        if mousePressed:
            start = False
            inMenu = True
            time.sleep(0.1)
    else:
        if player_left_score != 10 and player_right_score != 10:
            text("Left click to start game.", width/2, height/2)
        else:
            if player_left_score == 10:
                start = False
                text("Left won!", width/2, height/2)
                text("Left click to restart game.", width/2, height/2 + 60)
            if player_right_score == 10:
                start = False
                text("Right won!", width/2, height/2)
                text("Left click to restart game.", width/2, height/2 + 60)
        if mousePressed:
            ballDX = ballDY = 5
            ballDX *= (-1)**randint(0, 1)
            ballDY *= (-1)**randint(0, 1)
            ballX += ballDX
            ballY += ballDY
            inMenu = True
            player_left_score = player_right_score = 0
            time.sleep(0.1)
        
        
def keyReleased():
    global leftPaddleMove, rightPaddleMove
    if keyCode in [UP, DOWN]:
        rightPaddleMove = 0
    if key in ["s", "z"]:
        leftPaddleMove = 0
    

def drawBall():
    fill(255)
    circle(ballX, ballY, ballR)
    
    
def moveBall():
    global ballX, ballY, ballDX, ballDY, player_left_score, player_right_score, do_not_move_paddles
    ballX += ballDX
    ballY += ballDY
    
    if ballX+ballR >= width:  # player right missed: +1 for player left
        ballX, ballY = math.ceil(width/2), math.ceil(height/2)
        player_left_score += 1
        ballDX = ballDY = 5
    if ballX-ballR <= 0:  # player left missed: +1 for player right
        ballX, ballY = math.ceil(width/2), math.ceil(height/2)
        player_right_score += 1
        ballDX = ballDY = 5
    
    # explication de la physique des raquettes (inspiré de https://gamedev.stackexchange.com/questions/147773/what-is-original-pong-behaviour)
    # on calcule le ratio entre le centre de la raquette et là où arrive la balle, et on a l'angle duquel la balle doit repartir.
    
    # left paddle
    if ballX-ballR <= leftPaddleX and (ballY+ballR >= leftPaddleY and ballY-ballR <= leftPaddleY+paddleHeight):
        paddleCenter = leftPaddleY + math.ceil(paddleHeight/2)
        ratio = paddleCenter/ballY
        ballDX *= -1.05
        ballDY *= ratio
        do_not_move_paddles = True  # la raquette a frappé la balle, l'ordinateur peut arrêter de jouer
        
    # right paddle
    if ballX+ballR >= rightPaddleX+20 and (ballY+ballR >= rightPaddleY and ballY-ballR <= rightPaddleY+paddleHeight):
        paddleCenter = rightPaddleY + math.ceil(paddleHeight/2)
        ratio = paddleCenter/ballY
        ballDX *= -1.05
        ballDY *= ratio
        do_not_move_paddles = True  # la raquette a frappé la balle, l'ordinateur peut arrêter de jouer
    
    if (width/2)-ballR <= ballX <= (width/2)+ballR:  # la balle change de camp, l'ordinateur peut de nouveau jouer
        do_not_move_paddles = False
        
    if ballY+ballR >= height or ballY-ballR <= 0:
        ballDY *= -1
 
       
def drawLeftPaddle():
    fill(255)
    rect(leftPaddleX, leftPaddleY, 20, paddleHeight)
  
      
def drawRightPaddle():
    fill(255)
    rect(rightPaddleX, rightPaddleY, 20, paddleHeight)
    
def movePaddles():
    global leftPaddleY, rightPaddleY
    if mode == "PvP":
        leftPaddleY += leftPaddleMove*dy
        rightPaddleY += rightPaddleMove*dy
    elif mode == "PvB":
        leftPaddleY += leftPaddleMove*dy
        if not do_not_move_paddles:
            if ballX > (width/2)+ballR:
                if not ballY-paddleHeight/2 in [rightPaddleY+a for a in range(-paddleHeight/2, paddleHeight/2)]:  # évite le tremblement de la raquette
                    if ballY-paddleHeight/2 > rightPaddleY:
                        rightPaddleY += dy
                    elif ballY-paddleHeight/2 < rightPaddleY:
                        rightPaddleY -= dy
    else:
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

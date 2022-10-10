import math
from random import randint
import time

leftPaddleX = 40
leftPaddleY = 0
rightPaddleX = rightPaddleY = 0
leftPaddleMove = rightPaddleMove = 0
dy = 7

paddleHeight = 150

ballR = 30
ballX, ballY = 0, 0
ballDX = ballDY = 5

player_left_score = 0
player_right_score = 0

botMode = False
start = False


def setup():
    fullScreen()
    background(0)
    global leftPaddleY, rightPaddleY, rightPaddleX, ballX, ballY
    leftPaddleY = math.ceil((displayHeight / 2) - (paddleHeight / 2))
    rightPaddleY = math.ceil((displayHeight / 2) - (paddleHeight / 2))
    rightPaddleX = displayWidth - 60
    ballX, ballY = math.ceil(displayWidth/2), math.ceil(displayHeight/2)
    textSize(50)
    textAlign(CENTER)
    
    
def draw():
    global rightPaddleY, leftPaddleY, ballX, ballY, ballDX, ballDY, start, player_left_score, player_right_score, leftPaddleMove, rightPaddleMove, botMode
    background(0)
    
    stroke_color = 255
    for i in range(0, displayHeight, 30):
        stroke(stroke_color)
        line(displayWidth/2, i, displayWidth/2, i+30)
        stroke_color = abs(stroke_color-255)
    stroke(255)
    
    if keyPressed:
        if key == "z":
            leftPaddleMove = -1
        elif key == "s":
            leftPaddleMove = 1
            
        if keyCode == UP:
            rightPaddleMove = -1
        if keyCode == DOWN:
            rightPaddleMove = 1
            
        if key == "b":
            botMode = not botMode
            time.sleep(0.1)

    if mousePressed:
        if not start:
            ballDX = ballDY = 5
            ballDX *= (-1)**randint(0, 1)
            ballDY *= (-1)**randint(0, 1)
            ballX += ballDX
            ballY += ballDY
        else:
            ballX, ballY = math.ceil(displayWidth/2), math.ceil(displayHeight/2)
        start = (not start)
        player_left_score = player_right_score = 0
        time.sleep(0.1)
    
    if start:
        drawBall()
        moveBall()
    
    text(str(player_left_score), displayWidth/3, 60)
    text(str(player_right_score), 2*displayWidth/3, 60)
    
    if not botMode:
        leftPaddleY += leftPaddleMove*dy
        rightPaddleY += rightPaddleMove*dy
    else:
        leftPaddleY = rightPaddleY = ballY - paddleHeight/2
        textAlign(LEFT)
        text("botMode = True", 0, 40)
        textAlign(CENTER)
    leftPaddleY = constrain(leftPaddleY, 0, displayHeight-paddleHeight)
    rightPaddleY = constrain(rightPaddleY, 0, displayHeight-paddleHeight)
    drawLeftPaddle()
    drawRightPaddle()
    
    if player_left_score == 10:
        start = False
        text("Left won!", displayWidth/2, displayHeight/2)
    if player_right_score == 10:
        start = False
        text("Right won!", displayWidth/2, displayHeight/2)
        
        
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
    global ballX, ballY, ballDX, ballDY, player_left_score, player_right_score
    ballX += ballDX
    ballY += ballDY
    
    if ballX+ballR >= displayWidth:  # player right missed: +1 for player left
        ballX, ballY = math.ceil(displayWidth/2), math.ceil(displayHeight/2)
        player_left_score += 1
        ballDX = ballDY = 5
    if ballX-ballR <= 0:  # player left missed: +1 for player right
        ballX, ballY = math.ceil(displayWidth/2), math.ceil(displayHeight/2)
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
        
    # right paddle
    if ballX+ballR >= rightPaddleX+20 and (ballY+ballR >= rightPaddleY and ballY-ballR <= rightPaddleY+paddleHeight):
        paddleCenter = rightPaddleY + math.ceil(paddleHeight/2)
        ratio = paddleCenter/ballY
        ballDX *= -1.05
        ballDY *= ratio
        
    if ballY+ballR >= displayHeight or ballY-ballR <= 0:
        ballDY *= -1
 
       
def drawLeftPaddle():
    fill(255)
    rect(leftPaddleX, leftPaddleY, 20, paddleHeight)
  
      
def drawRightPaddle():
    fill(255)
    rect(rightPaddleX, rightPaddleY, 20, paddleHeight)

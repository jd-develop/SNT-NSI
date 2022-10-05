import math
from random import randint
import time

leftPaddleX = 10
leftPaddleY = 0
rightPaddleX = rightPaddleY = 0
dy = 7

paddleHeight = 100

ballR = 30
ballX, ballY = 0, 0
ballDX = ballDY = 5

player_left_score = 0
player_right_score = 0


start = False


def setup():
    fullScreen()
    background(0)
    global leftPaddleY, rightPaddleY, rightPaddleX, ballX, ballY
    leftPaddleY = math.ceil((displayHeight / 2) - (paddleHeight / 2))
    rightPaddleY = math.ceil((displayHeight / 2) - (paddleHeight / 2))
    rightPaddleX = displayWidth - 30
    ballX, ballY = math.ceil(displayWidth/2), math.ceil(displayHeight/2)
    textSize(50)
    textAlign(CENTER)
    
    
def draw():
    global rightPaddleY, leftPaddleY, ballX, ballY, ballDX, ballDY, start, player_left_score, player_right_score
    background(0)
    
    fill_color = 255
    for i in range(0, displayHeight, 30):
        fill(fill_color)
        line(displayWidth/2, i, displayWidth/2, i+30)
        fill_color = abs(fill_color-255)
    fill(255)
    
    if keyPressed:
        if keyCode == UP or key == 'z':
            leftPaddleY -= dy
        elif keyCode == DOWN or key == 's':
            leftPaddleY += dy
    
    if mousePressed:
        if not start:
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
    
    leftPaddleY = constrain(leftPaddleY, 0, displayHeight-paddleHeight)
    rightPaddleY = mouseY
    rightPaddleY = constrain(rightPaddleY, 0, displayHeight-paddleHeight)
    drawLeftPaddle()
    drawRightPaddle()
    
    if player_left_score == 10:
        start = False
        text("Left won!", displayWidth/2, displayHeight/2)
    if player_right_score == 10:
        start = False
        text("Right won!", displayWidth/2, displayHeight/2)
        
    

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
    if ballX-ballR <= 0:  # player left missed: +1 for player right
        ballX, ballY = math.ceil(displayWidth/2), math.ceil(displayHeight/2)
        player_right_score += 1
    if ballX-ballR <= leftPaddleX and (ballY+ballR >= leftPaddleY and ballY-ballR <= leftPaddleY+paddleHeight):
        ballDX *= -1
    if ballX+ballR >= rightPaddleX+20 and (ballY+ballR >= rightPaddleY and ballY-ballR <= rightPaddleY+paddleHeight):
        ballDX *= -1
    if ballY+ballR >= displayHeight or ballY-ballR <= 0:
        ballDY *= -1
 
       
def drawLeftPaddle():
    fill(255)
    rect(leftPaddleX, leftPaddleY, 20, paddleHeight)
  
      
def drawRightPaddle():
    fill(255)
    rect(rightPaddleX, rightPaddleY, 20, paddleHeight)

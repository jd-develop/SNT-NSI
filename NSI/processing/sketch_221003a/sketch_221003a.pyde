import math
leftPaddleX = 10
leftPaddleY = 0
rightPaddleX = 0
rightPaddleY = 0
dy = 7
ballR = 20
ballX, ballY = 0, 0

paddleHeight = 70


def setup():
    fullScreen()
    background(255)
    global leftPaddleY, rightPaddleY, rightPaddleX, ballX, ballY
    leftPaddleY = math.ceil((displayHeight / 2) - (paddleHeight / 2))
    rightPaddleY = math.ceil((displayHeight / 2) - (paddleHeight / 2))
    rightPaddleX = displayWidth - 30
    ballX, ballY = displayWidth/2, displayHeight/2
    
    
def draw():
    global rightPaddleY, leftPaddleY
    background(255)
    if keyPressed:
        if keyCode == UP or key == 'z':
            leftPaddleY -= dy
        elif keyCode == DOWN or key == 's':
            leftPaddleY += dy
    leftPaddleY = constrain(leftPaddleY, 0, displayHeight-paddleHeight)
    rightPaddleY = mouseY
    rightPaddleY = constrain(rightPaddleY, 0, displayHeight-paddleHeight)
    drawLeftPaddle()
    drawRightPaddle()
 
       
def drawLeftPaddle():
    fill(0, 0, 0)
    rect(leftPaddleX, leftPaddleY, 20, paddleHeight)
  
      
def drawRightPaddle():
    fill(0, 0, 0)
    rect(rightPaddleX, rightPaddleY, 20, paddleHeight)

def setup():
    fullScreen()
    background(255)
    
    
r, g, b = 0, 0, 0

def draw():
    if keyPressed:
        if key == 'r':
            r, g, b = 255, 0, 0
        elif key == 'g':
            r, g, b = 0, 255, 0
        elif key == 'b':
            r, g, b = 0, 0, 255
        elif key == 'n':
            r, g, b = 0, 0, 0
    
    if mousePressed:
        if mouseButton == LEFT:
            stroke(r, g, b)
            strokeWeight(2)
            line(pmouseX, pmouseY, mouseX, mouseY)
        elif mouseButton == RIGHT:
            stroke(255, 255, 255)
            fill(255, 255, 255)
            circle(mouseX, mouseY, 10)
            stroke(r, g, b)
        

def setup():
    size(600, 400)
    background(255)
    

def draw():
    if keyPressed:
        if key == 'r':
            fill(255, 0, 0)
        elif key == 'v':
            fill(0, 255, 0)
        elif key == 'b':
            fill(0, 0, 255)
        elif keyCode == UP:
            fill(0, 255, 255)
    else:
        fill(255, 0 , 255)
    ellipse(mouseX, mouseY, 50, 50)
    

def setup():
    fullScreen()
    background(255)
    
def draw():
    if mousePressed:
        if mouseButton == LEFT:
            r, g, b = 255, 0, 0
        elif mouseButton == CENTER:
            r, g, b  = 0, 255, 0
        else:
            r, g, b, = 255, 255, 0
    else:
        r, g, b = 0, 255, 255
    fill(r, g, b)
    circle(mouseX, mouseY, 50)

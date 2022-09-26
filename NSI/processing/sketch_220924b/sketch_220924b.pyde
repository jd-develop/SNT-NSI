
def setup():
    background(255)
    fullScreen()
    y = 0
    strokeWeight(displayHeight/255)
    for color_ in range(256):
        stroke(0, 0, 255-color_)
        line(0, y, displayWidth, y)
        y += displayHeight/255

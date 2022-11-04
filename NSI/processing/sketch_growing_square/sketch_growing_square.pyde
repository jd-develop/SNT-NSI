
def setup():
    fullScreen()
    background(255)

h = 100
l = 100

def draw():
    global h, l
    if h==-100:
        h = 100
        l = 100
    h -= 2
    l -= 2
    clear()
    background(255)
    rect(mouseX - h/2, mouseY - l/2, h, l)

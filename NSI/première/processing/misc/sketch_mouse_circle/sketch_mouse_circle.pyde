import math


def setup():
    # size(800, 600)
    fullScreen()
    background(255)
    
    
def draw():
    clear()
    background(255)
    distance_line_mouse = math.sqrt((width/2 - mouseX)**2 + (height/2 - mouseY)**2)
    circle(width/2, height/2, distance_line_mouse*2)
    fill(0, 0, 0)

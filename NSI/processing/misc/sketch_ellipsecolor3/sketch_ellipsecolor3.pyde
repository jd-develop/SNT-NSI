import random

def setup():
    size(1000, 650)
    background(255)
    

def draw():
    r, g, b = random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)
    fill(r, g, b)
    stroke(r, g, b)
    ellipse(mouseX, mouseY, random.randint(30, 60), random.randint(30, 60))
    

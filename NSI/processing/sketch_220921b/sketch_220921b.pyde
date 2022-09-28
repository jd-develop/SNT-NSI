import os
import os.path


def setup():
    fullScreen()
    # size(800, 600)
    background(255)
    r, g, b = 0, 0, 0
    strokeWeight(2)
    
    
r, g, b = 0, 0, 0
userprofile = os.path.expanduser("~")
print(os.path.abspath(userprofile + "\\Documents\\proc_notepad\\notepad-" + str(year()) + "-" + str(month()) + "-" + str(day()) + "-" + str(hour()) + "-" + str(minute()) + "-" + str(second()) + ".png"))


def draw():
    global r, g, b
    
    stroke(0, 0, 0)
    if r == 255:
        stroke(r, g, b)
    fill(255, 0, 0)
    square(10, 10, 50)
    
    stroke(0, 0, 0)
    if g == 255:
        stroke(r, g, b)
    fill(0, 255, 0)
    square(70, 10, 50)
    
    stroke(0, 0, 0)
    if b == 255:
        stroke(r, g, b)
    fill(0, 0, 255)
    square(130, 10, 50)
    
    stroke(0, 0, 0)
    fill(0, 0, 0)
    square(190, 10, 50)
    
    if keyPressed:
        if key == 'e':
            clear()
            background(255)
        if key == 's':
            fill(255)
            stroke(255, 255, 255)
            strokeWeight(5)
            square(10, 10, 50)
            square(70, 10, 50)
            square(130, 10, 50)
            square(190, 10, 50)
            if not os.path.exists(os.path.realpath(userprofile + "\\Documents\\proc_notepad")):
                os.mkdir(os.path.realpath(userprofile + "\\Documents\\proc_notepad"))
            save(os.path.abspath(userprofile + "\\Documents\\proc_notepad\\notepad-" + str(year()) + "-" + str(month()) + "-" + str(day()) + "-" + str(hour()) + "-" + str(minute()) + "-" + str(second()) + ".png"))
            strokeWeight(2)
    
    if mousePressed:
        if mouseButton == LEFT:
            if 10 < mouseY < 60 and 10 < mouseX < 60:
                r, g, b = 255, 0, 0
            elif 10 < mouseY < 60 and 70 < mouseX < 120:
                r, g, b = 0, 255, 0
            elif 10 < mouseY < 60 and 130 < mouseX < 180:
                r, g, b = 0, 0, 255
            elif 10 < mouseY < 60 and 190 < mouseX < 240:
                r, g, b = 0, 0, 0
            else:
                stroke(r, g, b)
                line(pmouseX, pmouseY, mouseX, mouseY)
        elif mouseButton == RIGHT:
            stroke(255, 255, 255)
            fill(255, 255, 255)
            circle(mouseX, mouseY, 50)
        elif mouseButton == CENTER:
            stroke(255, 255, 255)
            fill(255, 255, 255)
            circle(mouseX, mouseY, 200)
        

# BLOC NOTES SOUS PROCESSING

# Utilisation:
# Clic gauche sur un carré de couleur : switcher entre les valeurs 0 et 255 pour cette couleur
# Clic gauche dans la zone de dessin : dessiner
# Clic droit : gomme de diamètre 50 pixels
# Clic molette : gomme de diamètre 200 pixels
# Roue de la molette : changer la taille de la ligne (entre 2 et 402)
# Touche 'e' : effacer l'écran
# Touche 's' : sauvegarder l'image dans le dossier ~/Doccuments/processing_notepad/

import os
import os.path
from time import sleep


def setup():
    fullScreen()
    # size(800, 600)
    background(255)
    strokeWeight(2)
    
    
r, g, b = 0, 0, 0
w = 2  # la valeur de strokeWeight
userprofile = os.path.expanduser("~")  # C:\users\user\ ou /home/user/ ou /Volumes/Machintosh HD/Utilisateurs/user/

def draw():
    global r, g, b, w
    
    # on dessine les carrés correspondants aux couleurs
    # rouge
    strokeWeight(2)
    stroke(0, 0, 0)
    if r == 255:  # si la valeur de la couleur correspondante au carré est 255, on fait le contour du carré avec la couleur active
        stroke(r, g, b)
    fill(255, 0, 0)
    square(10, 10, 50)
    
    # vert
    stroke(0, 0, 0)
    if g == 255:
        stroke(r, g, b)
    fill(0, 255, 0)
    square(70, 10, 50)
    
    # bleu
    stroke(0, 0, 0)
    if b == 255:
        stroke(r, g, b)
    fill(0, 0, 255)
    square(130, 10, 50)
    
    # noir
    stroke(0, 0, 0)
    fill(0, 0, 0)
    square(190, 10, 50)
    
    if keyPressed:
        if key == 'e':  # effacer l'écran
            clear()
            background(255)
        if key == 's':  # sauvegarder l'image
            fill(255)
            stroke(255, 255, 255)
            strokeWeight(3)
            # on efface les carrés de couleurs
            square(10, 10, 50)
            square(70, 10, 50)
            square(130, 10, 50)
            square(190, 10, 50)
            # on créée éventuellement un dossier pour sauver l'imageg
            if not os.path.exists(os.path.realpath(userprofile + "\\Documents\\processing_notepad")):
                os.mkdir(os.path.realpath(userprofile + "\\Documents\\processing_notepad"))
            save(os.path.abspath(userprofile + "\\Documents\\processing_notepad\\notepad-" + str(year()) + "-" + str(month()) + "-" + str(day()) + "-" + str(hour()) + "-" + str(minute()) + "-" + str(second()) + ".png"))
            strokeWeight(2)
    
    if mousePressed:
        if mouseButton == LEFT:  # clic gauche : dessiner
            strokeWeight(w)
            if 10 < mouseY < 60 and 10 < mouseX < 60:  # clic sur le carré rouge
                r = abs(r-255)  # inverse le rouge (si il est à 255 -> |255-255|=0, si il est à 0 -> |0-255|=255)
                sleep(0.1)  # permet d'éviter de changer plusieurs fois de couleurs en un seul clic, si le clic dure trop longtemps
            elif 10 < mouseY < 60 and 70 < mouseX < 120:  # clic sur le carré vert
                g = abs(g-255)
                sleep(0.1)
            elif 10 < mouseY < 60 and 130 < mouseX < 180:  # clic sur le carré bleu
                b = abs(b-255)
                sleep(0.1)
            elif 10 < mouseY < 60 and 190 < mouseX < 240:  # clic sur le carré noir
                r, g, b = 0, 0, 0
            else:  # dessiner une ligne
                stroke(r, g, b)
                line(pmouseX, pmouseY, mouseX, mouseY)
            strokeWeight(2)
        elif mouseButton == RIGHT:  # clic droit : gomme de diamètre 50
            stroke(255, 255, 255)
            fill(255, 255, 255)
            circle(mouseX, mouseY, 50)
        elif mouseButton == CENTER:  # clic molette : gomme de diamètre 200
            stroke(255, 255, 255)
            fill(255, 255, 255)
            circle(mouseX, mouseY, 200)
            
def mouseWheel(event):  # ascenseur : on change la valeur strokeWeight de dessin
    global r, g, b, w
    e = event.getCount()
    if 2 <= w + e*10 <= 402:  # taille min: 2, taille max: 402
        w += e*10
        

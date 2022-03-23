#!/usr/bin/env python3
# -*- coding:utf-8 -*-
# ##########################################
# INFO:
# Il faut créer le dossier 'OUTPUT_TP_03-05' dans le répertoire courant pour que le code fonctionne.
# ##########################################
from PIL import Image

input_file = "pomme.jpg"  # chemin de l'image, en str

base_img = Image.open(input_file)  # image qu'on ne va pas modifier (on modifie seulement ses copies)
width, height = base_img.size  # largeur et hauteur de l'image

img1 = base_img.copy()  # on copie l'image
r, v, b = img1.getpixel((250, 300))
print(width, height)
print(r, v, b)

img1.putpixel((250, 250), (255, 0, 0))   # le pixel est au niveau du centre de la pomme, il est rouge

img1.putpixel((100, 250), (0, 0, 255))   # le pixel est à gauche sur la pomme, il est bleu
img1.save("./OUTPUT_TP_03-05/output1.png", "PNG")  # on exporte chaque image au format png sous le nom 'output(nbr).png'

# Inverser le bleu et le rouge de chaque pixel sans changer le vert.
img2 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img2.getpixel((x, y))
        img2.putpixel((x, y), (b, g, r))

img2.save('./OUTPUT_TP_03-05/output2.png', 'PNG')

# Mettre l'image en niveaux de gris avec la moyenne des couleurs
img3 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img3.getpixel((x, y))
        grey = sum([r, g, b]) // 3
        img3.putpixel((x, y), (grey, grey, grey))

img3.save('./OUTPUT_TP_03-05/output3.png', 'PNG')

# Mettre l'image en niveaux de gris avec la méthode préconisée par
img4 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img4.getpixel((x, y))
        grey = int(sum((r*0.2125, g*0.7154, b*0.0721)))  # Somme de 21.25% du rouge, 71.54% du vert et 7.21% du bleu
        img4.putpixel((x, y), (grey, grey, grey))

img4.save('./OUTPUT_TP_03-05/output4.png', 'PNG')

# négatif de l'image
img5 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img5.getpixel((x, y))
        r, g, b = 255-r, 255-g, 255-b
        img5.putpixel((x, y), (r, g, b))

img5.save('./OUTPUT_TP_03-05/output5.png', 'PNG')

# retourner l'image horizontalement
img6 = base_img.copy()
new_img = Image.new(img6.mode, img6.size)
for y in range(height):
    for x in range(width):
        r, g, b = img6.getpixel((x, y))
        new_img.putpixel((width-x-1, y), (r, g, b))

new_img.save('./OUTPUT_TP_03-05/output6.png', 'PNG')
img6 = new_img

# ##########################
# Modifications personnelles
# ##########################

# je ne saurais pas décrire simplement cette modification...
img7 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img7.getpixel((x, y))
        if b < 200:
            b = 255-b
        img7.putpixel((x, y), (r, g, b))

img7.save('./OUTPUT_TP_03-05/output7.png', 'PNG')

# pomme rouge
img8 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, b = img8.getpixel((x, y))[0], img8.getpixel((x, y))[-1]
        # on met autant dde vert que de bleu.
        # Ainsi, si c'est du blanc, ça reste du blanc. Mais s'il y a beaucoup de vert et peu de bleu
        # (comme dans la pomme), cela donnera  peu de vert et peu de bleu, ce qui rend globalement rouge.
        g = b
        img8.putpixel((x, y), (r, g, b))

img8.save('./OUTPUT_TP_03-05/output8.png', 'PNG')

# rouge à 0
img9 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img9.getpixel((x, y))
        img9.putpixel((x, y), (0, g, b))  # on supprime le rouge de l'image

img9.save('./OUTPUT_TP_03-05/output9.png', 'PNG')

# vert à 0
img10 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img10.getpixel((x, y))
        img10.putpixel((x, y), (r, 0, b))  # on supprime le vert de l'image

img10.save('./OUTPUT_TP_03-05/output10.png', 'PNG')

# bleu à 0
img11 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img11.getpixel((x, y))
        img11.putpixel((x, y), (r, g, 0))  # on supprime le bleu de l'image

img11.save('./OUTPUT_TP_03-05/output11.png', 'PNG')

# rouge à 255
img12 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img12.getpixel((x, y))
        img12.putpixel((x, y), (255, g, b))  # on met le rouge à son maximum dans l'image

img12.save('./OUTPUT_TP_03-05/output12.png', 'PNG')

# vert à 255
img13 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img13.getpixel((x, y))
        img13.putpixel((x, y), (r, 255, b))  # on met le vert à son maximum dans l'image

img13.save('./OUTPUT_TP_03-05/output13.png', 'PNG')

# bleu à 255
img14 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img14.getpixel((x, y))
        img14.putpixel((x, y), (r, g, 255))  # on met le bleu à son maximum dans l'image

img14.save('./OUTPUT_TP_03-05/output14.png', 'PNG')

# addition des deux autres couleurs pour chaque couleur
# précision : si l'addition des deux autres couleurs est supérieure à 255, on met 255
img15 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img15.getpixel((x, y))
        r, g, b = g+b if g+b <= 255 else 255, r+b if r+b <= 255 else 255, r+g if r+g <= 255 else 255
        img15.putpixel((x, y), (r, g, b))

img15.save('./OUTPUT_TP_03-05/output15.png', 'PNG')

# noir et blanc (pas de gris)
img16 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img16.getpixel((x, y))
        r, g, b = r*0.2125, g*0.7154, b*0.0721  # on met l'image en niveaux de gris
        grey = int(r+g+b)
        if grey < 175:  # si le gris est inférieur à un certain seuil, on met du blanc, sinon, on met du noir
            grey = 0
        else:
            grey = 255
        img16.putpixel((x, y), (grey, grey, grey))

img16.save('./OUTPUT_TP_03-05/output16.png', 'PNG')

# image finale, à la "Andy Warhol"
# 16 images, donc 4 images en longueur et 4 en hauteur
final_image = Image.new(base_img.mode, (width*4, height*4))  # on fabrique une image de 4*500 sur 4*500
# on répertorie toutes les images dans une liste
images = [img1, img2, img3, img4, img5, img6, img7, img8, img9, img10, img11, img12, img13, img14, img15, img16]
idx = 0  # c'est l'index qu'on va utiliser pour parcourir la liste 'images'

for y in range(0, height*4, height):  # de 0 à 500*4 de 500 en 500
    for x in range(0, width*4, width):  # de 0 à 500*4 de 500 en 500
        final_image.paste(images[idx], (x, y))  # on colle l'image à l'index 'idx' aux coordonnées xy
        idx += 1  # on augmente l'index
        if idx > len(images)-1:  # si l'index est hors de la liste, on arrête la loupe
            break

final_image.save('./OUTPUT_TP_03-05/output_final.png', "PNG")  # on sauvegarde l'image

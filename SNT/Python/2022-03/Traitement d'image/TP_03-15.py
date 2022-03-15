#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from PIL import Image

input_file = "pomme.jpg"

base_img = Image.open(input_file)
img = base_img.copy()
width, height = img.size
r, v, b = img.getpixel((250, 300))
print(width, height)
print(r, v, b)

img.putpixel((250, 250), (255, 0, 0))   # le pixel est au niveau du centre de la pomme, il est rouge

img.putpixel((100, 250), (255, 0, 0))   # le pixel est à gauche sur la pomme, il est rouge
img.save("./OUTPUT_TP_03-05/output1.png", "PNG")

# On inverse le bleu et le rouge de chaque pixel sans changer le vert.
img = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img.getpixel((x, y))
        r, b = b, r
        img.putpixel((x, y), (r, g, b))

img.save('./OUTPUT_TP_03-05/output2.png', 'PNG')

# Mettre l'image en niveaux de gris
img = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img.getpixel((x, y))
        grey = sum([r, g, b]) // 3
        img.putpixel((x, y), (grey, grey, grey))

img.save('./OUTPUT_TP_03-05/output3.png', 'PNG')

# meilleurs niveaux de gris
img = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img.getpixel((x, y))
        r, g, b = r*0.2125, g*0.7154, b*0.0721
        grey = int(r+g+b)
        img.putpixel((x, y), (grey, grey, grey))

img.save('./OUTPUT_TP_03-05/output4.png', 'PNG')

# négatif
img = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img.getpixel((x, y))
        r, g, b = 255-r, 255-g, 255-b
        img.putpixel((x, y), (r, g, b))

img.save('./OUTPUT_TP_03-05/output5.png', 'PNG')

# retourner l'image
img = base_img.copy()
new_img = Image.new(img.mode, img.size)
for y in range(height):
    for x in range(width):
        # patate
        patate = None

img.save('./OUTPUT_TP_03-05/output6.png', 'PNG')

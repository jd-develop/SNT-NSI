#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from PIL import Image

input_file = "pomme.jpg"

base_img = Image.open(input_file)
width, height = base_img.size

img1 = base_img.copy()
r, v, b = img1.getpixel((250, 300))
print(width, height)
print(r, v, b)

img1.putpixel((250, 250), (255, 0, 0))   # le pixel est au niveau du centre de la pomme, il est rouge

img1.putpixel((100, 250), (255, 0, 0))   # le pixel est à gauche sur la pomme, il est rouge
img1.save("./OUTPUT_TP_03-05/output1.png", "PNG")

# On inverse le bleu et le rouge de chaque pixel sans changer le vert.
img2 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img2.getpixel((x, y))
        img2.putpixel((x, y), (b, g, r))

img2.save('./OUTPUT_TP_03-05/output2.png', 'PNG')

# Mettre l'image en niveaux de gris
img3 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img3.getpixel((x, y))
        grey = sum([r, g, b]) // 3
        img3.putpixel((x, y), (grey, grey, grey))

img3.save('./OUTPUT_TP_03-05/output3.png', 'PNG')

# meilleurs niveaux de gris
img4 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img4.getpixel((x, y))
        r, g, b = r*0.2125, g*0.7154, b*0.0721
        grey = int(r+g+b)
        img4.putpixel((x, y), (grey, grey, grey))

img4.save('./OUTPUT_TP_03-05/output4.png', 'PNG')

# négatif
img5 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img5.getpixel((x, y))
        r, g, b = 255-r, 255-g, 255-b
        img5.putpixel((x, y), (r, g, b))

img5.save('./OUTPUT_TP_03-05/output5.png', 'PNG')

# retourner l'image
img6 = base_img.copy()
new_img = Image.new(img6.mode, img6.size)
for y in range(height):
    for x in range(width):
        r, g, b = img6.getpixel((x, y))
        new_img.putpixel((width-x-1, y), (r, g, b))

new_img.save('./OUTPUT_TP_03-05/output6.png', 'PNG')
img6 = new_img

# modifs persos
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
        g = b - 10
        img8.putpixel((x, y), (r, g, b))

img8.save('./OUTPUT_TP_03-05/output8.png', 'PNG')

# rouge à 0
img9 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img9.getpixel((x, y))
        img9.putpixel((x, y), (0, g, b))

img9.save('./OUTPUT_TP_03-05/output9.png', 'PNG')

# vert à 0
img10 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img10.getpixel((x, y))
        img10.putpixel((x, y), (r, 0, b))

img10.save('./OUTPUT_TP_03-05/output10.png', 'PNG')

# bleu à 0
img11 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img11.getpixel((x, y))
        img11.putpixel((x, y), (r, g, 0))

img11.save('./OUTPUT_TP_03-05/output11.png', 'PNG')

# rouge à 255
img12 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img12.getpixel((x, y))
        img12.putpixel((x, y), (255, g, b))

img12.save('./OUTPUT_TP_03-05/output12.png', 'PNG')

# vert à 255
img13 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img13.getpixel((x, y))
        img13.putpixel((x, y), (r, 255, b))

img13.save('./OUTPUT_TP_03-05/output13.png', 'PNG')

# bleu à 255
img14 = base_img.copy()
for y in range(height):
    for x in range(width):
        r, g, b = img14.getpixel((x, y))
        img14.putpixel((x, y), (r, g, 255))

img14.save('./OUTPUT_TP_03-05/output14.png', 'PNG')

# image finale
final_image = Image.new(base_img.mode, (500*7, 500*2))
images = [img1, img2, img3, img4, img5, img6, img7, img8, img9, img10, img11, img12, img13, img14]
idx = 0

for y in [0, 500]:
    for x in range(0, 500*7, 500):
        final_image.paste(images[idx], (x, y))
        idx += 1
        if idx > 13:
            break

final_image.save('./OUTPUT_TP_03-05/output_final.png', "PNG")

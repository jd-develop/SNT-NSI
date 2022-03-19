#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from PIL import Image
from os.path import realpath

input_file = realpath('../pomme.jpg')

with Image.open(input_file) as image:
    image = image.convert("L")
    new_image = Image.new(image.mode, image.size)
    width, height = image.size
    for x in range(width):
        for y in range(height):
            try:
                seuil = 20

                p1 = image.getpixel((x+1, y+1))
                p2 = image.getpixel((x-1, y-1))
                diff = abs(p1-p2)

                p3 = image.getpixel((x+1, y-1))
                p4 = image.getpixel((x-1, y+1))
                diff2 = abs(p3-p4)

                if diff > seuil or diff2 > seuil:
                    edge = True
                else:
                    edge = False
            except IndexError:
                edge = False

            new_image.putpixel((x, y), 255 if edge else 0)
    new_image.save('edge_detection_output.png', 'PNG')

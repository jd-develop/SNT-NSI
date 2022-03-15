#!/usr/bin/env python3
# -*- coding:utf-8 -*-
from PIL import Image, ImageFilter
from os.path import realpath

input_file = realpath('../pomme.jpg')

with Image.open(input_file) as image:
    new_image = image.filter(ImageFilter.FIND_EDGES)
    new_image.save('edge_detection_output.jpg')
    image.paste(new_image)
    image.save('edge_detection_output2.jpg')

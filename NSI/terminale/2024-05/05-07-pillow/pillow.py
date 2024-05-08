#!/usr/bin/env python3
# -*- coding:utf-8 -*-
# type: ignore
from PIL import Image
from PIL.ExifTags import TAGS, GPSTAGS
import webbrowser


def where(fichier):
    img = Image.open(fichier)
    exif_data = img._getexif()

    gps_info = None
    for k in exif_data:
        if TAGS[k] == "GPSInfo":
            gps_info = exif_data[k]
    assert gps_info is not None, "this image does not have GPSInfo exif data."

    gps_info = {GPSTAGS[k]: gps_info[k] for k in gps_info}
    north_or_south = gps_info["GPSLatitudeRef"]
    east_or_west = gps_info["GPSLongitudeRef"]
    latitude = gps_info["GPSLatitude"]
    longitude = gps_info["GPSLongitude"]
    
    if isinstance(latitude[0], tuple):  # fraction
        latitude = (a/b for (a, b) in latitude)
    if isinstance(longitude[0], tuple):  # fraction
        longitude = (a/b for (a, b) in longitude)
    
    print(latitude, north_or_south)
    print(longitude, east_or_west)

    latitude_décimale = latitude[0] + latitude[1]/60 + latitude[2]/3600
    longitude_décimale = longitude[0] + longitude[1]/60 + longitude[2]/3600
    # print(type(latitude_décimale))

    if north_or_south == "S":
        latitude *= -1
    if east_or_west == "W":
        latitude *= -1

    webbrowser.open(f"https://openstreetmap.org/?lat={float(latitude_décimale)}&lon={float(longitude_décimale)}&zoom=18")

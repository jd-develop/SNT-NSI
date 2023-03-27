import random

start_color = (0, 0, 0)
end_color = (255, 255, 255)


def setup():
    global start_color, end_color
    background(255)
    fullScreen()
    strokeWeight(displayHeight/255)
    # start_color = (255, 0, 0)
    # end_color = (0, 0, 255)
    start_color = (0, 0, 0)
    end_color = (255, 255, 255)
    
    
def draw():
    global start_color, end_color
    y = 0
    
    v = 150
    new_color = lambda x: x + (x//v)*random.randint(-5, 5) + ((255//v)-(x//v))*random.randint(-5, 5)
    
    start_color = (
        constrain(new_color(start_color[0]), 0, 255),
        constrain(new_color(start_color[1]), 0, 255),
        constrain(new_color(start_color[2]), 0, 255)
        )
    end_color = (
        constrain(new_color(end_color[0]), 0, 255),
        constrain(new_color(end_color[1]), 0, 255),
        constrain(new_color(end_color[2]), 0, 255)
        )
    
    start_r = start_color[0]
    end_r = end_color[0]
    scope_r = end_r - start_r
    r = lambda x: start_r + ((scope_r*x) // 256)
    
    start_g = start_color[1]
    end_g = end_color[1]
    scope_g = end_g - start_g
    g = lambda x: start_g + ((scope_g*x) // 256)
    
    start_b = start_color[2]
    end_b = end_color[2]
    scope_b = end_b - start_b
    b = lambda x: start_b + ((scope_b*x) // 256)
    
    for color_ in range(256):
        r_ = r(color_)
        g_ = g(color_)
        b_ = b(color_)
        constrain(r_, 0, 255)
        constrain(g_, 0, 255)
        constrain(b_, 0, 255)
        stroke(r_, g_, b_)
        line(0, y, displayWidth, y)
        y += displayHeight/255

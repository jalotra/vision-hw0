from uwimg import *
import os
import shutil

def tryit_made_figures():
    os.mkdir(os.path.join(os.getcwd(), "Tryit_Photos"))


# 1. Getting and setting pixels
def get_set_pixels(channel):
    map_of_channels = {
        0 : "NO_RED",
        1 : "NO_GREEN" ,
        2 : "NO_BLUE"
    }
    im = load_image("data/ekta_khajiar.jpg")
    for row in range(im.h):
        for col in range(im.w):
            # set_pixel takes in these params (*image, column, row, channel, value_to_set)
            if channel == 0:
                set_pixel(im, col, row, 0, 0) 
            elif channel == 1:
                set_pixel(im, col, row, 1, 0)
            elif channel == 2:
                set_pixel(im, col, row, 2, 0)
    save_image(im, "Tryit_Photos/ekta_kahijiar" + "_"  + map_of_channels[channel])

# 3. Grayscale image
def grayscaleImage():
    #im = load_image("data/colorbar.png")
    im = load_image("data/ekta_khajiar.jpg") 
    graybar = rgb_to_grayscale(im)
    save_image(graybar, "Tryit_Photos/ekta_khajiar")

# 4. Shift Image
def shiftImage():
    im = load_image("data/ekta_khajiar.jpg") 
    shift_image(im, 0, .4)
    shift_image(im, 1, .4)
    shift_image(im, 2, .4)
    save_image(im, "Tryit_Photos/ekta_shifted")

# 5. Clamp Image
# def clampImage():
#     im = load_image("data/ekta_khajiar.jpg") 
#     clamp_image(im)
#     save_image(im, "Tryit_Photos/ekta_light_fixed")

# 6-7. Colorspace and saturation
def colorspace_and_saturation():
    im = load_image("data/ekta_khajiar.jpg")
    rgb_to_hsv(im)
    # shift_image(im, 1, .2)
    # shiftImage(im)
    # hsv_to_rgb(im)
    save_image(im, "Tryit_Photos/ekta_saturated")

if __name__ == "__main__":
    if os.path.isdir(os.path.join(os.getcwd(), "Tryit_Photos")):
        shutil.rmtree(os.path.join(os.getcwd(), "Tryit_Photos"))
        tryit_made_figures()
    else:
        tryit_made_figures()
    
    #Utlity Functions been called
    # for i in range(3):
    #     get_set_pixels(i)
    # grayscaleImage()
    # shiftImage()
    # clampImage()

    colorspace_and_saturation()




#ifndef IMAGE_H
#define IMAGE_H

typedef struct{
    int w,h,c;
    float *data;
} image;


// Basic operations
float get_pixel(image im, int x, int y, int c);
void set_pixel(image im, int x, int y, int c, float v);
image copy_image(image im);
image rgb_to_grayscale(image im);
void rgb_to_hsv(image im);
void hsv_to_rgb(image im);
void shift_image(image im, int c, float v);
void clamp_image(image im);

// some functions that I defined
// namely calculate_hue, calculate_saturation, calculate_value
float calculate_hue(float a, float b , float c);
float calculate_saturation(float a, float b , float c);
float calculate_value(float a, float b , float c);


// Loading and saving
image make_image(int w, int h, int c);
image load_image(char *filename);
void save_image(image im, const char *name);
void free_image(image im);

#endif


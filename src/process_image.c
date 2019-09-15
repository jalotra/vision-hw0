#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "image.h"


/* All the help Needed*/
// Since the image is a struct that is defined like this
// typedef struct{
//     int w,h,c;           // w defines width // h defines height // c defines channels 
//     float *data;   // data points to an array that contains all the data pixels in CHW format
// }image;



// WORKS FINE
float get_pixel(image im, int x, int y, int c)
{
    // Overflows Taken care of ::
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(x > im.w) x = im.w -1;
    if(y > im.h) y = im.h -1 ;

    // TODO Fill this in
    // im struct contains *data which contains pixel values in the form of CHW(CHannel,Row, Colums)
    // im has 4 data members that are h,w,c and *data
    // int height = im_ptr->h;
    // int width = im_ptr->w;
    // int channels = im_ptr->c;
    
    int pixel_location = x + y*im.w + c*im.w*im.h;
    return im.data[pixel_location];
    // free_image(im);
}

// WORKS FINE BUT HAVE TO IMPLEMENT OVERFLOW
void set_pixel(image im, int x, int y, int c, float v)
{
    // Overflows taken care of
    if (x < 0)
        return;
    if (y < 0)
        return;
    if (x > im.w)
        return;
    if (y > im.h)
        return;
        
    // TODO Fill this in
    int pixel_location = x + y*im.w + c*im.h*im.w;
    float *pixel_value = &im.data[pixel_location];
    *pixel_value = v; 

    // free_image(im);

}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    //memcpy (dest_struct, source_struct, sizeof (*dest_struct));
    // image * copy_ptr = &copy;
    memcpy(&copy, &im, sizeof(copy));          // Not Sure if this will work

    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);        // Creates a image struct with *data contnaning 
                                                   // 1 Channel

    // Creating pointers to struct
    // First  pointer to gray image
    image * ptr_gray , * ptr_im;
    // Point to the address of the struct objects
    // Gray Image
    ptr_gray = &gray; 
    float * gray_data = ptr_gray->data;
    float(*gray_data_matrix) [im.w][im.h] = gray_data;
    // memset(gray_data_matrix, 0, sizeof gray_data_matrix); 
    // Given Image
    ptr_im = &im; 
    float * im_data = ptr_im->data;
    float(*im_data_matrix) [im.w][im.h] = im_data;


    // Define the data members of gray to be that of im:
    ptr_gray->h = ptr_im->h;
    // ptr_gray->c = ptr_im->c;
    ptr_gray->w = ptr_im->w;

    // Now we have the weighted mean like:
    //Y' = 0.299 R' + 0.587 G' + .114 B'

    // So for a given *data I have to caculate the value over the whole 3-D Matrix
    float value;
    for(int channels=0; channels < im.c ; channels++){
        if(channels == 0) {value = 0.299;}
        else if(channels == 1) {value = 0.587;}
        else if(channels == 2) {value = 0.114;}
        for(int width = 0; width < gray.w ; width++){
            for(int height = 0; height < gray.h; height++){
                (*gray_data_matrix)[width][height] +=  
                (*(*(*(im_data_matrix +channels) + width) + height))*value;
            }
        
        }
    }

    // free_image(im);
    // free_image(gray);

    return gray;
}

void shift_image(image im, int c, float v)
{
    // Shift image adds a float value v to every pixel in im.data
    // SO I can use the set pixel function 
        for(int width = 0 ; width < im.w; width++)
        {
            for(int height = 0; height < im.h ; height++)
            {
                float new_v = get_pixel(im, width, height, c) + v;
                if(new_v < 0){new_v = 0;}
                if(new_v >1){new_v = 1;}
                set_pixel(im, width, height, c, new_v);
            }
        }
    
}

// void clamp_image(image im)
// {
//     // TODO Fill this in
//     // Any pixel value that goes below 0 turn up to be zero 
//     // And any pixel value that goes above 1 turns up to be 1 
//     for(int channels = 0; channels < im.c ; channels++)
//     {
//         for(int width = 0; width < im.w; width++) 
//         {
//             for(int height = 0; height < im.h ; height++)
//             {
//                 float value_to_check = get_pixel(im, width, height, channels);
//                 if(value_to_check < 0){value_to_check = 0;}
//                 else if(value_to_check > 1){value_to_check = 1;}
//                 set_pixel(im, width, height, channels, value_to_check);
//             }
//         }
//     }
// }


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // Started working on changing rgb to hsv
    // WE HAVE THREE VARIABLES HUE,SATURATION AND VALUE
    
    // FOR VALUE 
    // V = max(r,g,b)
    
    // FOR SATURATION We see how far are the r,g,b are situation 
    // m = min(r,g,b)
    // C = V - m
    // S = C/V          // except for the black pixel or (r,g,b) ={0,0,0}

    // FOR CALCULATING HUE 
    // we ARE given the best descriptiin in readme.md
    // PLease have a look


    // CODE STARTS
    // wE START OFF WITH GETTING PIXELS FROM THE get_pixel method and 
    // calculate the differnt values from the above formulas that are
    //given

    // FINALLY REmember to replace R channel with H, the G channel with S, B channel with V

    
    for(int row = 0 ; row < im.w ; row++)
    {
        for(int height = 0 ; height < im.h ; height ++)
        {
            // Get pixel
            float r = get_pixel(im, row, height, 0);
            float g = get_pixel(im, row, height, 1);
            float b = get_pixel(im, row, height, 2);

            // Calculate value, saturation and hue
            float value = calculate_value(r,g,b);
            float saturation = calculate_saturation(r,g,b);
            float hue = calculate_hue(r,g,b);

            // CHnage values respectively
            r = hue;
            g = saturation;
            b = value;

            // FInally set_pixel 
            // definition set_pixel(image im, int x, int y, int c, float v)
            set_pixel(im, row, height, 0, r);
            set_pixel(im, row, height, 1, g);
            set_pixel(im, row, height, 2, b);
        }
    }
    



}

float calculate_value(float a, float b, float c)
{
    return three_way_max(a,b,c);
}

float calculate_saturation(float a, float b , float c)
{   
    float S;
    if(a != 0 && b != 0 && c != 0) 
    {  
        S = (three_way_max(a,b,c) - three_way_min(a,b,c))/three_way_max(a,b,c); 
    }
    else
    {
        S = 0;
    }
    
return S;
}

float calculate_hue(float r, float g, float b)
{
    float V = three_way_max(r, g, b);
    float H = 0;
    float C = three_way_max(r, g, b) - three_way_min(r, g, b);

    if(V == r) H =  (g-b)/C;
    else if(V == g) H = (b-r)/C + 2;
    else if(V == b) H = (r-g)/C + 4;
    else if (C == 0) H = 0;

    if(H < 0) H = H/6 + 1;
    else H = H/6;


return H;   
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}

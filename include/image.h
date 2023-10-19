#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <stack>
#include <unistd.h>

#include "read_obj.h"

using namespace std;

extern string path_obj;
extern string path_img;
extern string path_out_img;

typedef struct Pixel{
    int **red;
    int **green;
    int **blue;
}Pixel;

class Image{
    private:
        int height;
        int width;
        int maxcolor;
        Pixel *data;
    public:
        Image();
        ~Image();


        void create_image(int height, int width, int maxcolor);       
        void load_image(string input);
        void aloca_pixel();                                
        void save_image(string output);

        void gradient();
        void negative_image();
        void blur();
        void bresenham(int x1,int y1,int x2,int y2,int r,int g,int b);
        void paint_iterativo(int x,int y,int r2,int g2,int b2,int r,int g,int b);
        void paint_recursivo(int x,int y,int r2,int g2,int b2,int r,int g,int b);
        void mask(string filename,int r,int g, int b);
        void stamping(string stamping_file, int x, int y);
        void drawCircle(int xc, int yc, int x, int y,   int r,int g,int b);
        void circle(int xc,int yc,int raio,int r,int g,int b);

        void three_dimension();

        void get_dimensions();
        int put_pixel(int i, int j, int r,int g, int b);
        int getred(int i, int j);
        int getgreen(int i, int j);
        int getblue(int i, int j);
        int sgn(int value);
        int getHeight();
        int getwidth();
        int getMaxcolor();
};


#endif
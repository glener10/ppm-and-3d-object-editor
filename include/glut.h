#ifndef GLUT_H
#define GLUT_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "read_obj.h"

#include <iostream>
#include <math.h>
#include <time.h>
#include <unistd.h>

extern vector <Object*> Objs;

#define WIDHT_GLUT 900
#define HEIGHT_GLUT 1600

using namespace std;


//Controle de camera dinamica
extern GLfloat camera_x;
extern GLfloat camera_y;
extern GLfloat camera_z;


void display(void);
void myReshape(int w, int h);
void initflat(void);

void get_key(unsigned char key, int x, int y);
void glut_create(int argc, char **argv);
void timer(int value);

void draw_objects();


#endif
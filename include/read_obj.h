#ifndef READ_OBJ_H
#define READ_OBJ_H

#include <math.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

#define MIN 0
#define MAX 1

extern string caminho_obj;
extern string caminho_img;
extern string caminho_out_img;

typedef struct V{           //struct para os vertices dos objetos 3D
    float x;
    float y;
    float z;
}V;

typedef struct F{           //Struct para as faces dos objetos 3D
    int p0;
    int p1;
    int p2;
}F;

class Object{
    private:
        // V *VV;
        // F *FF;
        int NF;
        int NV;
        float Scale;
        float Center_x;
        float Center_y;
        float Center_z;
        float focal_distance;

        float r;
        float g;
        float b;
    public:
    
        V *VV;
        F *FF;

        Object(string input,float theta_x,float theta_y,float theta_z, float Scale, float Center_x, float Center_y, float Center_z, float focal_distance);
        Object();
        ~Object();

        void number_faces_vertices(string input);
        void read_file(string input);
        void ordena_f();
        float media_Z(float a,float b,float c);
        float cat_d();
        void td_script(string input);

        void rotation_x(float theta);
        void rotation_y(float theta);
        void rotation_z(float theta);

        int getNF();
        float getFocal_distance();
        float getScale();
        float getCenter_x();
        float getCenter_y();
        float getCenter_z();

        float getR();
        float getG();
        float getB();
};

extern vector <Object*> Objs;


#endif
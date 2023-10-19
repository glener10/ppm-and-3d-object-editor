// (C) 2021 Glener Lanes Pizzolato - glenerpizzolato@gmail.com

#include "glut.h"
#include "read_obj.h"
#include "image.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include <unistd.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define MAX_CIRCLE_RADIUS 30


GLfloat cam_x = 0;
GLfloat cam_y = 0;
GLfloat cam_z = 35;

string path_obj = ".././objects_3d/";
string path_img = ".././img/";
string path_out_img = ".././img_generate/";

float theta=0;

bool exist_image = false;

int TYPE_DISPLAY = 1;      //1 Free cam      2 Rotation

vector <Object*> Objs;

int main(int argc,char **argv){

    int menu();
    int arq_verification(string input);

    srand(time(NULL));

    Image *imagem = new Image();
    Object* aux_create;

    string aux_name;
    int aux_height, aux_width, aux_maxcolor, option, center_x, center_y, center_z, aux_x, aux_y, aux_r, aux_g, aux_b, aux_it, aux_raio, aux_r2, aux_g2, aux_b2;
    float theta_x,theta_y,theta_z, scale, aux_focal_distance;
    

    while(1){
        switch(menu()){
            case 1:
                if(exist_image == false){
                    cout << endl << "There is no image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Output File name: ";
                    cin >> aux_name;
                    imagem -> save_image(path_out_img + aux_name);
                }
            break;


            case 2:
                imagem->~Image();
                cout << endl << "Height: ";
                cin >> aux_height;
                cout << endl << "width: ";
                cin >> aux_width;
                //cout << endl << "MaxColor: ";
                //cin >> aux_maxcolor;
                cout << endl << "Creating...";
                imagem->create_image(aux_height, aux_width, 255);
                exist_image = true;
                cout << endl << "Done!" << endl;
            break;


            case 3:
                cout << endl << "Name of inputfile (It must be in the 'img' folder): ";
                cin >> aux_name;
                cout << endl << "Loading image...";
                imagem -> load_image (path_img + aux_name);
                exist_image = true;
                cout << endl << "Done!";
            break;



            case 4:
                option = 1;
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    while(option == 1){

                        cout << endl << "Object name (It must be in the 'objects_3d' folder): ";
                        cin >> aux_name;
                        if(arq_verification(path_obj + aux_name) != 1){
                            break;
                        }
                        else{
                            cout << "Rotation in X: ";
                            cin >> theta_x;
                            cout << "Rotation in Y: ";
                            cin >> theta_y;
                            cout << "Rotation in Z: ";
                            cin >> theta_z;
                            cout << "Scale: ";
                            cin >> scale;
                            cout << "Centro X: ";
                            cin >> center_x;
                            cout << "Centro Y: ";
                            cin >> center_y;
                            cout << "Focal Distance: ";
                            cin >> aux_focal_distance;
                            /*cout << "Centro Z: ";
                            cin >> center_z;*/

                            aux_create = new Object(path_obj + aux_name,theta_x,theta_y,theta_z,scale,center_x,center_y,0,aux_focal_distance);
                            Objs.push_back(aux_create);

                            cout << endl << "press (1) to add more objects: ";
                            cin >> option;
                            system("clear||cls");
                        }
                    }
                    imagem->three_dimension();
                }
            break;


            case 5:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Script Format: " << endl << "name.obj scale centerX centerY ThetaX ThetaY ThetaZ" << endl;
                    cout << endl << "Script name (It must be in the 'objects_3d' folder): ";
                    cin >> aux_name;
                    if(arq_verification(path_obj + aux_name) != 1){
                        break;
                    }
                    else{
                        cout << endl << "Reading Script file...";
                        aux_create->td_script(path_obj + aux_name);
                        imagem->three_dimension();
                        cout << endl << "Done!";
                    }
                }
            break;


            case 6:
                option = 1;
                while(option == 1){
                    cout << endl << "Object name (It must be in the 'objects_3d' folder): ";
                    cin >> aux_name;
                    if(arq_verification(path_obj + aux_name) != 1){
                        break;
                    }
                    else{
                        cout << "Rotation in X: ";
                        cin >> theta_x;
                        cout << "Rotation in Y: ";
                        cin >> theta_y;
                        cout << "Rotation in Z: ";
                        cin >> theta_z;
                        cout << "Scale: ";
                        cin >> scale;
                        cout << "Centro X: ";
                        cin >> center_x;
                        cout << "Centro Y: ";
                        cin >> center_y;

                        aux_create = new Object(path_obj + aux_name,theta_x,theta_y,theta_z,scale,center_x,center_y,0,1);
                        Objs.push_back(aux_create);

                        cout << endl << "press (1) to add more objects: ";
                        cin >> option;
                        system("clear||cls");
                    }
                }
                cout << endl << "Using the keys:" << endl;
                cout << "W - Up\nS - Down\nA - Left\nD - Right\nQ - Depth Within\nE - Depht off\n";
                glut_create(argc,argv);
            break;



            case 7:
                cout << endl << "Script Format: " << endl << "name.obj scale centerX centerY ThetaX ThetaY ThetaZ" << endl;
                cout << endl << "Script name (It must be in the 'objects_3d' folder): ";
                cin >> aux_name;
                if(arq_verification(path_obj + aux_name) != 1){
                    break;
                }
                else{
                    cout << endl << "Reading Script file...";
                    aux_create->td_script(path_obj + aux_name);
                    cout << endl << "Done!";
                    cout << endl << "Using the keys:" << endl;
                    cout << "W - Up\nS - Down\nA - Left\nD - Right\nQ - Depth Within\nE - Depht off\n";
                    glut_create(argc,argv);
                }
            break;



            case 10:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Applying gradient...";
                    imagem->gradient();
                    cout << endl << "Done!";
                }
            break;

            case 11:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Name of Stamping File (It must be in the 'img' folder): ";
                    cin >> aux_name;
                    cout << endl << "Position X to stamping: ";
                    cin >> aux_x;
                    cout << endl << "Position Y to stamping: ";
                    cin >> aux_y;
                    cout << endl << "Stamping...";
                    imagem->stamping(path_img + aux_name,aux_x,aux_y);
                    cout << endl << "Done!";
                }
            break;

            case 12:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Name of Output mask file: ";
                    cin >> aux_name;
                    cout << endl << "R: ";
                    cin >> aux_r;
                    cout << endl << "G: ";
                    cin >> aux_g;
                    cout << endl << "B: ";
                    cin >> aux_b;
                    cout << endl << "Stamping...";
                    imagem->mask(path_out_img + aux_name,aux_r,aux_g,aux_b);
                    cout << endl << "Done!";
                }
            break;

            case 13:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Number of random lines: ";
                    cin >> aux_it;
                    for(int i=0;i<aux_it;i++){
                        imagem->bresenham(rand()%imagem->getHeight(), rand()%imagem->getwidth(), rand()%imagem->getHeight(), rand()%imagem->getwidth(), rand()%imagem->getMaxcolor(),rand()%imagem->getMaxcolor(),rand()%imagem->getMaxcolor());
                    }
                }
            break;


            case 14:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Number of random Circles: ";
                    cin >> aux_it;
                    for(int i=0;i<aux_it;i++){
                        aux_raio  = rand () % MAX_CIRCLE_RADIUS;
                        aux_height = rand() % imagem->getHeight();
                        aux_width = rand() % imagem->getwidth();
                        while((aux_height + aux_raio > imagem->getHeight()) || (aux_width + aux_raio > imagem->getwidth()) || (aux_height - aux_raio < 0) || (aux_width - aux_raio < 0)){
                            aux_raio  = rand () % MAX_CIRCLE_RADIUS;
                            aux_height = rand() % imagem->getHeight();
                            aux_width = rand() % imagem->getwidth();
                        }
                        imagem->circle(aux_height,aux_width,aux_raio, rand()%imagem->getMaxcolor(), rand()%imagem->getMaxcolor(), rand()%imagem->getMaxcolor());
                    }
                }
            break;

            case 15:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Applying Blur...";
                    imagem->blur();
                    cout << endl << "Done!";
                }
            break;

            case 16:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Applying Negative effect...";
                    imagem->negative_image();
                    cout << endl << "Done!";
                }
            break;

            case 17:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Position X in image: ";
                    cin >> aux_x;
                    cout << endl << "Position Y in image: ";
                    cin >> aux_y;
                    cout << endl << "Old Pixel\nR: ";
                    cin >> aux_r;
                    cout << endl << "G: ";
                    cin >> aux_g;
                    cout << endl << "B: ";
                    cin >> aux_b;
                    cout << endl << "New Pixel\nR: ";
                    cin >> aux_r2;
                    cout << endl << "G: ";
                    cin >> aux_g2;
                    cout << endl << "B: ";
                    cin >> aux_b2;
                    imagem->paint_iterativo(aux_x,aux_y,aux_r,aux_g,aux_b,aux_r2,aux_g2,aux_b2);
                }
            break;

            case 18:
                if(exist_image == false){
                    cout << endl << "it is necessary to create an image..." << endl;
                    sleep(1);
                }
                else{
                    cout << endl << "Position X in image: ";
                    cin >> aux_x;
                    cout << endl << "Position Y in image: ";
                    cin >> aux_y;
                    cout << endl << "Old Pixel\nR: ";
                    cin >> aux_r;
                    cout << endl << "G: ";
                    cin >> aux_g;
                    cout << endl << "B: ";
                    cin >> aux_b;
                    cout << endl << "New Pixel\nR: ";
                    cin >> aux_r2;
                    cout << endl << "G: ";
                    cin >> aux_g2;
                    cout << endl << "B: ";
                    cin >> aux_b2;
                    imagem->paint_recursivo(aux_x,aux_y,aux_r,aux_g,aux_b,aux_r2,aux_g2,aux_b2);
                }
            break;



            case 30:
                for(int i=0;i<Objs.size();i++){
                    free(Objs[i]->VV);
                    free(Objs[i]->FF);
                    free(Objs[i]);
                }
                imagem->~Image();
                exist_image = false;
                //free(imagem);
            break;


            case 0:
                for(int i=0;i<Objs.size();i++){
                    free(Objs[i]->VV);
                    free(Objs[i]->FF);
                    free(Objs[i]);
                }
                imagem->~Image();
                free(imagem);
                cout << endl << "Exiting" << endl;
                exist_image = false;
                exit(1);
            break;
            
        }
    }
    return 1;
}


int menu(){
    system("clear||cls");
    int choice;
    cout << "# MENU #" << endl;
    cout << "1- Save Image" << endl;
    cout << "2- Create Image" << endl;
    cout << "3- Load Image" << endl;
    cout << "4- 3D (.obj) -> 2D (.ppm)" << endl;
    cout << "5- Script to load N .obj into a .ppm image" << endl;
    cout << "6- 3D .obj in Glut" << endl;
    cout << "7- Read Script for N .obj in Glut" << endl << endl;
    cout << "10- Gradient" << endl;
    cout << "11- Stamping" << endl;
    cout << "12- Generate Mask" << endl;
    cout << "13- Bresenham" << endl;
    cout << "14- Circle Layout" << endl;
    cout << "15- Blur" << endl;
    cout << "16- Negative_image" << endl;
    cout << "17- To Paint-Recursive" << endl;
    cout << "18- To Paint-Iterative" << endl << endl;

    cout << "30- Free image" << endl;
    cout << "0- Exit " << endl;
    cout << endl << "Choice: ";
    cin >> choice;
    system("clear||cls");
    return choice;
}


int arq_verification(string input){
    ifstream arq;
    arq.open(input);
    if(!arq.is_open()){
        cout << "Error opening file!" << endl;
        sleep(1);
        return 0;
    }
    arq.close();
    return 1;
}
#include "image.h"



//AUXS

int Image::sgn(int value){
    if (value>0) return 1;
    else if (value<0)return -1;
    return 0;
}

void Image::get_dimensions(){
    system("clear||cls");
    int control2;
    cout << "Height:" << this->height << "  width:  " << this->width << endl << "Press any key...";
    cin >> control2;
}

int Image::getred(int i, int j){
    if(i > this->height || j > this->width){
        cout << "Coordinates outside the image dimensions" << endl;
        return -1;
    }
    else{
        return this->data->red[i][j];
    }
}

int Image::getgreen(int i, int j){
    if(i > this->height || j > this->width){
        cout << "Coordinates outside the image dimensions" << endl;
        return -1;
    }
    else{
        return this->data->green[i][j];
    }
}

int Image::getblue(int i, int j){
    if(i > this->height || j > this->width){
        cout << "Coordinates outside the image dimensions" << endl;
        return -1;
    }
    else{
        return this->data->blue[i][j];
    }
}


int Image::put_pixel(int i, int j, int r,int g, int b){
    if(i > this->height || j > this->width){
        cout << "Coordinates outside the image dimensions" << endl;
        return 0;
    }
    else if(r > this->maxcolor || g > this->maxcolor || b > this->maxcolor){
        cout << "color exceds the -MaxColor- limit" << endl;
        return 0;
    }
    else{
        this->data->red[i][j] = r;
        this->data->green[i][j] = g;
        this->data->blue[i][j] = b;
        return 1;
    }
}

int Image::getHeight(){
    return this->height;
}

int Image::getwidth(){
    return this->width;
}
        
int Image::getMaxcolor(){
    return this->maxcolor;
}


#include "image.h"



Image::Image(){}
Image::~Image(){
    for(int i=0;i<height;i++){
        free(this->data->red[i]);
        free(this->data->green[i]);
        free(this->data->blue[i]);
    }
    //free(this->data);
}

void Image::aloca_pixel(){
    this->data = new Pixel;
    this->data->red = new int *[this->height];   
    this->data->green = new int *[this->height];
    this->data->blue = new int *[this->height];
    for(int i=0;i<this->height;i++){
        this->data->red[i] = new int[this->width];   
        this->data->green[i] = new int[this->width];
        this->data->blue[i] = new int[this->width];
    }
}

void Image::create_image(int height, int width, int maxcolor){
    this->height = height;
    this->width = width;
    this->maxcolor = maxcolor;

    this->aloca_pixel();

    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            this->data->red[i][j] = 255;
            this->data->blue[i][j] = 255;
            this->data->green[i][j] = 255;
        }
    }
}


void Image::load_image(string input){
    ifstream arq;
    arq.open(input);
    if(!arq.is_open()){
        cout << "Error opening file!" << endl;
        sleep(1);
    }
    else{
        char buffer;
        arq >> buffer;
        arq >> buffer;
        arq >> this->width;
        arq >> this->height;
        arq >> this->maxcolor;

        this->aloca_pixel();

        for(int i=0;i<height;i++){
            for(int j=0;j<width;j++){
                arq >> this->data->red[i][j];
                arq >> this->data->green[i][j];
                arq >> this->data->blue[i][j];
            }
        }
        arq.close();
    }
}


void Image::save_image(string output){
    ofstream arq;
    arq.open(caminho_out_img + output);
    arq << "P3\n" << this->width << " " << this->height << endl << this->maxcolor << endl;
    for(int i=0;i<this->height;i++){
        for(int j=0;j<this->width;j++){
            arq << this->data->red[i][j] << " " << this->data->green[i][j] << " " << this->data->blue[i][j] << " ";
        }
        arq << endl;
    }
}
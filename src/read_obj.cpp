#include "read_obj.h"

float rand_float(float min, float max){
    return min + (rand() / ( RAND_MAX / ( max - min) ) ) ;  
}

Object::Object(){}
Object::Object(string input,float theta_x,float theta_y,float theta_z, float Scale, float Center_x, float Center_y, float Center_z, float focal_distance){
    this->number_faces_vertices(input);
    this->read_file(input);

    if(theta_x > 0){
        this->rotation_x(theta_x);
    }
    if(theta_y > 0){
        this->rotation_y(theta_y);
    }
    if(theta_z > 0){
        this->rotation_z(theta_z);
    }
    this->Scale = Scale;
    this->Center_x = Center_x;
    this->Center_y = Center_y;
    this->Center_z = Center_z;
    this->focal_distance = focal_distance;
    this->r = rand_float(MIN,MAX);
    this->g = rand_float(MIN,MAX);
    this->b = rand_float(MIN,MAX);
}
Object::~Object(){
    free(this->VV);
    free(this->FF);
}

void Object::number_faces_vertices(string input){
    ifstream arq;
    arq.open(input);
    int cont_f=0;
    int cont_v=0;
    char letra;
    while(!arq.eof()){
        arq >> letra;
        if (letra=='f'){
            cont_f++;
        }
        else if(letra=='v'){
            cont_v++;
        }
    }
    this->NF = cont_f;
    this->NV = cont_v;
    arq.close();
}

void Object::read_file(string input){         //Le arquivo e salva no vet da struct V*
    ifstream arq;
    arq.open(input);
    this->VV = new V[this->NV];
    this->FF = new F[this->NF];
    char letra;
    int i_v=0;
    int i_f=0;
    while(!arq.eof()){
        arq >> letra;
        if (letra=='v'){
            arq >> this->VV[i_v].x;
            arq >> this->VV[i_v].y;
            arq >> this->VV[i_v].z;
            i_v++;
        }
        else if(letra == 'f'){
            arq >> this->FF[i_f].p0;
            arq >> this->FF[i_f].p1;
            arq >> this->FF[i_f].p2;
            i_f++;
        }
    }
    arq.close();
}

float Object::media_Z(float a,float b,float c){    
    return (a+b+c)/3;
}

void Object::ordena_f(){
    float MI,MJ;
    F aux;
    for(int i=0;i<this->NF;i++){
        for(int j=0;j<this->NF;j++){
            MI = media_Z(this->VV[this->FF[i].p0-1].z, this->VV[this->FF[i].p1-1].z,this->VV[this->FF[i].p2-1].z);
            MJ = media_Z(this->VV[this->FF[j].p0-1].z, this->VV[this->FF[j].p1-1].z,this->VV[this->FF[j].p2-1].z);
            if(MI > MJ){
                aux = this->FF[i];
                this->FF[i] = this->FF[j];
                this->FF[j] = aux;
            }
        }
    }
}

float Object::cat_d(){          
    float out = 99999;
    for(int i=0;i<this->NV;i++){
        if(this->VV[i].z < out){
            out = this->VV[i].z;
        }
    }
    if(out < 0){
        out *= -1;
    }
    out += 3; 
    return out;
}

void Object::rotation_x(float theta){
    for(int i=0;i<this->NV;i++){
        this->VV[i].y = (this->VV[i].y*cos(theta)) + (this->VV[i].z*sin(theta));
        this->VV[i].z = (this->VV[i].y*(-sin(theta))) + (this->VV[i].z*cos(theta));
    }
}

void Object::rotation_y(float theta){
    for(int i=0;i<this->NV;i++){
        this->VV[i].x = (this->VV[i].x*cos(theta)) + (this->VV[i].z*(-sin(theta)));
        this->VV[i].z = (this->VV[i].x*sin(theta)) + (this->VV[i].z*(cos(theta)));
    }
}

void Object::rotation_z(float theta){
    for(int i=0;i<this->NV;i++){
        this->VV[i].x = (this->VV[i].x*cos(theta)) + (this->VV[i].y*sin(theta));
        this->VV[i].y = (this->VV[i].x*(-sin(theta))) + (this->VV[i].y*cos(theta));
    }
}

int Object::getNF(){
    return this->NF;
}

float Object::getFocal_distance(){
    return this->focal_distance;
}

float Object::getScale(){
    return this->Scale;
}

float Object::getCenter_x(){
    return this->Center_x;
}

float Object::getCenter_y(){
    return this->Center_y;
}

float Object::getCenter_z(){
    return this->Center_z;
}

float Object::getR(){
    return this->r;
}
float Object::getG(){
    return this->g;
}
float Object::getB(){
    return this->b;
}

void Object::td_script(string input){
    ifstream arq;
    arq.open(input);

    string aux_name;
    float scale, center_x, center_y,theta_x, theta_y, theta_z;
    Object* aux_create;

    while(!arq.eof()){
        arq >> aux_name;
        arq >> scale;
        arq >> center_x;
        arq >> center_y;
        arq >>theta_x;
        arq >> theta_y;
        arq >> theta_z;
        aux_create = new Object(path_obj + aux_name,theta_x,theta_y,theta_z,scale,center_x,center_y,0,1);
        Objs.push_back(aux_create);
    }
    arq.close();
}
#include "image.h"

//FUNCTIONS

void Image::gradient(){
    int r,g,b;
    cout << endl << "Maxcolor = " << this->maxcolor << endl;
    cout << "Choose the intensities of red (R), green(G) and blue(B). Remember that the gradient is made from red to blue, so the green only serves to add a mixture and consequently change the colors" << endl;
    cout << "R: ";
    cin >> r;
    cout << "G: ";
    cin >> g;
    cout << "B: ";
    cin >> b;

    for(int j=0;j < this->width;j++){          //Erro nesse calculo
        for(int i=0;i < this->height;i++){
            this->data->red[i][j] = (int)(r*((double)j/this->width));
            this->data->green[i][j] = g;
            this->data->blue[i][j] = (int)(b-b*((double)j/this->width));
        }
    }
}

void Image::negative_image(){
    for(int i=0;i<this->height;i++){
        for(int j=0;j<this->width;j++){
            this->put_pixel(i,j,this->maxcolor-(this->getred(i,j)),this->maxcolor-(this->getgreen(i,j)),this->maxcolor-(this->getblue(i,j)));
        }
    }
}

void Image::blur(){
    int blur[3][3]= {{10,20,10},{20,40,20},{10,20,10}};
    int total=0;
    for (int c=0; c<3; c++){
       for (int l=0; l<3; l++){
            total+=blur[c][l];
       }
    }
    int newred=0,newgreen=0,newblue=0;
    for(int i=1;i < this->height - 2;i++){          //i -> 
        for(int j=1;j < this->width - 2;j++){
           newred = 0;
           newgreen = 0;
           newblue = 0;
           for (int c=0; c<3; c++){
                for (int l=0; l<3; l++){
                    newred += getred(i+c-1,j+l-1)*blur[c][l];
                    newgreen += getgreen(i+c-1,j+l-1)*blur[c][l];
                    newblue += getblue(i+c-1,j+l-1)*blur[c][l];
                }
            }
            this->put_pixel(i,j,newred/total,newgreen/total,newblue/total);
        }
    }
}

void Image::bresenham(int x1,int y1,int x2,int y2,int r,int g,int b){
    int dx = x2-x1;
    int dy = y2-y1;
    int dxabs = abs(dx);
    int dyabs = abs(dy);
    int sdx = this->sgn (dx);
    int sdy = this->sgn (dy);
    int x = dyabs >> 1;
    int y = dxabs >> 1;

    int px = x1;
    int py = y1;

    if(dxabs >= dyabs){
        for(int i=0;i<dxabs;i++){
            y += dyabs;
            if(y >= dxabs){
                y -= dxabs;
                py += sdy;
            }
            px += sdx;
            if((px>0 && px<this->height) && (py>0 && py<this->width)){
                this->put_pixel(px,py,r,g,b);
            }
        }
    }
    else{
        for(int i=0;i<dyabs;i++){
            x += dxabs;
            if(x >= dyabs){
                x -= dyabs;
                px += sdx;
            }
            py += sdy;
            if((px>0 && px<this->height) && (py>0 && py<this->width)){
                this->put_pixel(px,py,r,g,b);
            }
        }
    }
}

void Image::paint_iterativo(int x,int y,int r2,int g2,int b2,int r,int g,int b){    
    stack <int> stack_x;
    stack <int> stack_y;
    stack_x.push(x);
    stack_y.push(y);
    int x_aux,y_aux;
    while(!stack_x.empty()){
        x_aux = stack_x.top();
        y_aux = stack_y.top();
        this->put_pixel(x_aux,y_aux,r,g,b);
        stack_x.pop();
        stack_y.pop();
        if(x_aux+1 < this->height){
            if(this->data->red[x_aux+1][y_aux] == r2 && this->data->green[x_aux+1][y_aux] == g2 && this->data->blue[x_aux+1][y_aux] == b2){
                stack_x.push(x_aux+1);
                stack_y.push(y_aux);
            }
        }
        if(x_aux-1 >= 0){
            if(this->data->red[x_aux-1][y_aux] == r2 && this->data->green[x_aux-1][y_aux] == g2 && this->data->blue[x_aux-1][y_aux] == b2){
                stack_x.push(x_aux-1);
                stack_y.push(y_aux);
            }
        }
        if(y_aux+1 < this->width){
            if(this->data->red[x_aux][y_aux+1] == r2 && this->data->green[x_aux][y_aux+1] == g2 && this->data->blue[x_aux][y_aux+1] == b2){
                stack_x.push(x_aux);
                stack_y.push(y_aux+1);
            }
        }
        if(y_aux-1 >= 0){
            if(this->data->red[x_aux][y_aux-1] == r2 && this->data->green[x_aux][y_aux-1] == g2 && this->data->blue[x_aux][y_aux-1] == b2){
                stack_x.push(x_aux);
                stack_y.push(y_aux-1);
            }
        }
    }
}

void Image::paint_recursivo(int x,int y,int r2,int g2,int b2,int r,int g,int b){
    if(this->data->red[x][y] == r2 && this->data->green[x][y] == g2 && this->data->blue[x][y] == b2){
        this->put_pixel(x,y,r,g,b);
        if(x+1 < this->height){
            paint_recursivo(x+1,y,r2,g2,b2,r,g,b);
        }
        if(x-1 >= 0){
            paint_recursivo(x-1,y,r2,g2,b2,r,g,b);
        }
        if(y+1 < this->width){
            paint_recursivo(x,y+1,r2,g2,b2,r,g,b);
        }
        if(y-1 >= 0){
            paint_recursivo(x,y-1,r2,g2,b2,r,g,b);
        }
    }
}

void Image::mask(string filename,int r,int g, int b){
    ofstream arq;
    arq.open(caminho_out_img + filename);
    arq << "P3\n" << this->width << " " << this->height << endl << this->maxcolor << endl;

    for(int i=0;i<this->height;i++){
        for(int j=0;j<this->width;j++){
            if(r == this->data->red[i][j] && g == this->data->green[i][j] && b == this->data->blue[i][j]){
                arq << "0 ";
            }
            else{
                arq << "1 ";
            }
         }
        arq << endl;
    }
    arq.close();
}

void Image::stamping(string stamping_file, int x, int y){
    Image* aux = new Image();
    aux->load_image(caminho_img + stamping_file);
    int k=0;
    int l=0;
    for(int i=x;i<this->height;i++){
        for(int j=y;j<this->width;j++){
            if(k < aux->height && j < aux->width){
                this->data->red[i][j] = aux->data->red[k][l];
                this->data->green[i][j] = aux->data->green[k][l];
                this->data->blue[i][j] = aux->data->blue[k][l];
                l++;
            }
        }
        l=0;
        k++;
    }
}

void Image::drawCircle(int xc, int yc, int x, int y,   int r,int g,int b){
    this->put_pixel(xc+x, yc+y, r,g,b);
    this->put_pixel(xc-x, yc+y, r,g,b);
    this->put_pixel(xc+x, yc-y, r,g,b);
    this->put_pixel(xc-x, yc-y, r,g,b);
    this->put_pixel(xc+y, yc+x, r,g,b);
    this->put_pixel(xc-y, yc+x, r,g,b);
    this->put_pixel(xc+y, yc-x, r,g,b);
    this->put_pixel(xc-y, yc-x, r,g,b);
}

void Image::circle(int xc,int yc,int raio,int r,int g,int b){
    int x=0;
    int y = raio;
    int d = 3 - 2 *raio;
    this->drawCircle(xc,yc, x,y, r,g ,b);
    while(y >= x){
        x++;
        if(d>0){
            y--;
            d = d+4*(x-y)+10;
        }
        else{
            d = d+4*x+6;
            this->drawCircle(xc,yc,x,y,r,g,b);
        }
    }
}

void Image::three_dimension(){
    float xp0,yp0,xp1,yp1,xp2,yp2;
    float Nz, pt1, pt2;
    float d;

    for(int j=0; j<Objs.size();j++){
        d = Objs[j]->cat_d();
        d += Objs[j]->getFocal_distance();
        for(int i=0;i < Objs[j]->getNF()-1 ; i++){

            xp0 = (Objs[j]->getScale() * (Objs[j]->VV[Objs[j]->FF[i].p0 - 1].y / (Objs[j]->VV[Objs[j]->FF[i].p0 - 1].z + d) ));
            yp0 = (Objs[j]->getScale() * (Objs[j]->VV[Objs[j]->FF[i].p0-1].x / (Objs[j]->VV[Objs[j]->FF[i].p0 - 1].z + d) ));
            xp1 = (Objs[j]->getScale() * (Objs[j]->VV[Objs[j]->FF[i].p1 - 1].y / (Objs[j]->VV[Objs[j]->FF[i].p1 - 1].z + d) ));
            yp1 = (Objs[j]->getScale() * (Objs[j]->VV[Objs[j]->FF[i].p1-1].x / (Objs[j]->VV[Objs[j]->FF[i].p1 - 1].z + d) ));
            xp2 = (Objs[j]->getScale() * (Objs[j]->VV[Objs[j]->FF[i].p2 - 1].y / (Objs[j]->VV[Objs[j]->FF[i].p2 - 1].z + d) ));
            yp2 = (Objs[j]->getScale() * (Objs[j]->VV[Objs[j]->FF[i].p2-1].x / (Objs[j]->VV[Objs[j]->FF[i].p2 - 1].z + d) ));
            
            xp0 += Objs[j]->getCenter_x();
            yp0 += Objs[j]->getCenter_y();
            xp1 += Objs[j]->getCenter_x();
            yp1 += Objs[j]->getCenter_y();
            xp2 += Objs[j]->getCenter_x();
            yp2 += Objs[j]->getCenter_y();

            pt1 = (Objs[j]->VV[Objs[j]->FF[i].p1 - 1].y - Objs[j]->VV[Objs[j]->FF[i].p0 - 1].y) * (Objs[j]->VV[Objs[j]->FF[i].p2 - 1].x - Objs[j]->VV[Objs[j]->FF[i].p1 - 1].x);
            pt2 = (Objs[j]->VV[Objs[j]->FF[i].p1 - 1].x - Objs[j]->VV[Objs[j]->FF[i].p0 - 1].x) * (Objs[j]->VV[Objs[j]->FF[i].p2 - 1].y - Objs[j]->VV[Objs[j]->FF[i].p1 - 1].y);
            Nz = pt1 - pt2;

            if((Nz > 0) ){    
                if(xp0<0 || yp0 < 0 || xp0 < 0 || yp0 < 0 || xp1 < 0 || yp1 < 0 || xp2 < 0 || yp2 < 0 || xp0 >= this->height || yp0 >= this->width || xp1 >= this->height || yp1 >= this->width || xp2 >= this->height || yp2 >= this->width){}

                else{
                    this->bresenham((int)xp0,(int)yp0,(int)xp1,(int)yp1,0,0,0);
                    this->bresenham((int)xp2,(int)yp2,(int)xp1,(int)yp1,0,0,0);
                    this->bresenham((int)xp0,(int)yp0,(int)xp2,(int)yp2,0,0,0);
                }

            }
        }
    }

}


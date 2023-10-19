#include "glut.h"

void draw_objects (){
    glPushMatrix();
    for(int j=0;j<Objs.size();j++){
        glBegin (GL_LINES);
        glColor3f (Objs[j]->getR(), Objs[j]->getG(), Objs[j]->getB());
        for(int i=0;i<Objs[j]->getNF();i++){
            glVertex3f((Objs[j]->VV[Objs[j]->FF[i].p0 - 1].x * Objs[j]->getScale()) + Objs[j]->getCenter_x(), ((Objs[j]->VV[Objs[j]->FF[i].p0 - 1].y * Objs[j]->getScale())/**-1*/) + Objs[j]->getCenter_y(), (Objs[j]->VV[Objs[j]->FF[i].p0 - 1].z * Objs[j]->getScale()) + Objs[j]->getCenter_z());
            glVertex3f((Objs[j]->VV[Objs[j]->FF[i].p1 - 1].x * Objs[j]->getScale()) + Objs[j]->getCenter_x(), ((Objs[j]->VV[Objs[j]->FF[i].p1 - 1].y * Objs[j]->getScale())/**-1*/) + Objs[j]->getCenter_y(), (Objs[j]->VV[Objs[j]->FF[i].p1 - 1].z * Objs[j]->getScale()) + Objs[j]->getCenter_z());
            glVertex3f((Objs[j]->VV[Objs[j]->FF[i].p2 - 1].x * Objs[j]->getScale()) + Objs[j]->getCenter_x(), ((Objs[j]->VV[Objs[j]->FF[i].p2 - 1].y * Objs[j]->getScale())/**-1*/) + Objs[j]->getCenter_y(), (Objs[j]->VV[Objs[j]->FF[i].p2 - 1].z * Objs[j]->getScale()) + Objs[j]->getCenter_z());
        }
        glEnd();
    }
    glPopMatrix();
}


void timer(int value){
    theta+=1;
    if (theta >= 360) theta=0.0;
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}


void myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-10,10,-10,10,-10,10);
    gluPerspective(45,1,-10,10);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void initflat(void){
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glShadeModel (GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glFrontFace(GL_CW);    
    glCullFace(GL_FRONT);    
    glEnable(GL_CULL_FACE); 
    glClearDepth(100.0f); 
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL); 
    glDepthRange(50,-50);    

    /*glLightfv (GL_LIGHT0, GL_DIFFUSE, difusa);
    glLightfv (GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);*/

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glDepthMask(GL_TRUE);
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);      
    glEnable( GL_TEXTURE_2D);
    
    glScalef (1.0, 1.0, 1.0);

    if(TYPE_DISPLAY == 1){
        gluLookAt (cam_x,cam_y,cam_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else{
        glRotatef(theta,0.0,1.0,0.0);
    }

    draw_objects();  

    glFlush();
    glutSwapBuffers();
    glDisable(GL_TEXTURE_2D);
}


void glut_create(int argc, char **argv){
    glutInit(&argc, argv);

    glutInitWindowSize (HEIGHT_GLUT, WIDHT_GLUT);     

    glutInitWindowPosition (100, 100);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable (GL_BLEND | GL_DEPTH_TEST);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutCreateWindow ("Name");
    initflat();

    glutDisplayFunc(display);
    glutReshapeFunc(myReshape);
    if(TYPE_DISPLAY == 1){
        glutKeyboardFunc(get_key);
    }
    else{
        glutTimerFunc(10, timer, 0);
    }
    glutMainLoop();
}

void get_key(unsigned char key, int x, int y){

    float speed = 5;
    if(key == 'a'){ 
        cam_x -= speed;
    }else if(key == 'w'){ 
        cam_y += speed;
    }else if(key == 'd'){ 
        cam_x += speed;
    }else if(key == 's'){ 
        cam_y -= speed;
    }else if(key == 'q'){ 
        cam_z += speed;
    }else if(key == 'e'){ 
        cam_z -= speed;
    } 
    glutPostRedisplay();
}

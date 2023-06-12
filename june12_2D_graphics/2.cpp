#include <iostream>
#include <GL/glut.h>

#include "shared.h"

void initGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv){
    glutInit(&argc, argv); //initialiation
    glutInitWindowSize(640, 640); //basic
    glutInitWindowPosition(100, 100); //basic
    glutCreateWindow("2 Test"); //basic

    glutDisplayFunc(smartDisplay);
    glutReshapeFunc(reshape);
    initGL();

    glutMainLoop();
    return 0;
}
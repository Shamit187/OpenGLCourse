#include <iostream>
#include <GL/glut.h>
#include "shared.h"

void initGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv){
    glutInit(&argc, argv); //initialiation
    glutInitWindowSize(1000, 1000); //basic
    glutInitWindowPosition(100, 100); //basic
    glutCreateWindow("1 Test"); //basic

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();

    glutMainLoop();
    return 0;
}
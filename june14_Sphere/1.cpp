#include <iostream>
#include <GL/glut.h>
#include "shared.h"

void initGL(){
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv){
    glutInit(&argc, argv); //initialiation
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000); //basic
    glutInitWindowPosition(100, 100); //basic
    glutCreateWindow("1 Test"); //basic
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    initGL();

    glutMainLoop();
    return 0;
}
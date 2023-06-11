#include <iostream>
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(50);
    //every shape needs to be in a context
    //contexts starts with glbegin and glend
    glBegin(GL_POINTS);
        // glPointSize(100);
        // glColor3b(1,1,1);
        glVertex2d(0,0);
    glEnd();

    glFlush();
    /*
        Don't know what it does...
        but needs to call to show in display
    */
}

int main(int argc, char** argv){

    glutInit(&argc, argv); //initialiation
    glutInitWindowSize(640, 640); //basic
    glutInitWindowPosition(100, 100); //basic
    glutCreateWindow("1 Test"); //basic

    glutDisplayFunc(display);
    /*
    Every time we start displaying the window
    We call the function inside the parameter
    In this case that function is display
    ...
    For example... the program starts... window opens, display gets called
    We minimize, then open the window again... display gets called
    We resize window... window opens again... display gets called...
    pretty simple
    */

    glutMainLoop(); 
    /*
    infinite loop... 
    in a query... events are pushed... 
    mainloop takes one event from queue and runs it
    */
    return 0;
}
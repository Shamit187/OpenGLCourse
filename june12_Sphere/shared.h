#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>

#define SUBDIVISION 20
#define RADIUS 1

void reshape(GLsizei width, GLsizei height){
    if(height == 0) height = 1;

    GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;

    // Set to 2D orthographic projection with the specified clipping area
    glMatrixMode(GL_PROJECTION);      // Select the Projection matrix for operation
    glLoadIdentity();                 // Reset Projection matrix

    glViewport(0,0,width,height);

    //this assumes that initial aspect ratio is always 1...
    if(width > height)
        gluOrtho2D(-1.0*(aspectRatio), 1.0*(aspectRatio), -1.0, 1.0); // Set clipping area's left, right, bottom, top
    else
        gluOrtho2D(-1.0f, 1.0f, -1.0/aspectRatio, 1.0/aspectRatio);
}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);

    glRotatef(90.0f ,1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        for(int row = 0; row < SUBDIVISION; row++){
            for(int col = 0; col < SUBDIVISION; col++){
                GLfloat theta1 = 45 + row * (90 / SUBDIVISION);
                GLfloat theta2 = 45 + (row+1) * (90 / SUBDIVISION);
                GLfloat phi1 = -45 + col * (90 / SUBDIVISION);
                GLfloat phi2 = -45 + (col+1) * (90 / SUBDIVISION);

                GLfloat x1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat y1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat z1 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat y2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat z2 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat y3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat z3 = RADIUS * cos(M_PI * phi2/180);

                GLfloat x4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat y4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat z4 = RADIUS * cos(M_PI * phi2/180);

                
                glVertex3f(x1, y1, z1);
                
                glVertex3f(x2, y2, z2);
                
                glVertex3f(x3, y3, z3);
                
                glVertex3f(x4, y4, z4);

            }
        }
    glEnd();
    glRotatef(-90.0f ,1.0f, 0.0f, 0.0f);

    glRotatef(-90.0f ,1.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        for(int row = 0; row < SUBDIVISION; row++){
            for(int col = 0; col < SUBDIVISION; col++){
                GLfloat theta1 = 45 + row * (90 / SUBDIVISION);
                GLfloat theta2 = 45 + (row+1) * (90 / SUBDIVISION);
                GLfloat phi1 = -45 + col * (90 / SUBDIVISION);
                GLfloat phi2 = -45 + (col+1) * (90 / SUBDIVISION);

                GLfloat x1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat y1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat z1 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat y2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat z2 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat y3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat z3 = RADIUS * cos(M_PI * phi2/180);

                GLfloat x4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat y4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat z4 = RADIUS * cos(M_PI * phi2/180);

                
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);

            }
        }
    glEnd();
    glRotatef(90.0f ,1.0f, 0.0f, 0.0f);


    glRotatef(90.0f ,0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        for(int row = 0; row < SUBDIVISION; row++){
            for(int col = 0; col < SUBDIVISION; col++){
                GLfloat theta1 = 45 + row * (90 / SUBDIVISION);
                GLfloat theta2 = 45 + (row+1) * (90 / SUBDIVISION);
                GLfloat phi1 = -45 + col * (90 / SUBDIVISION);
                GLfloat phi2 = -45 + (col+1) * (90 / SUBDIVISION);

                GLfloat x1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat y1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat z1 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat y2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat z2 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat y3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat z3 = RADIUS * cos(M_PI * phi2/180);

                GLfloat x4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat y4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat z4 = RADIUS * cos(M_PI * phi2/180);

                
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);

            }
        }
    glEnd();
    glRotatef(-90.0f ,0.0f, 1.0f, 0.0f);


    glRotatef(-90.0f ,0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        for(int row = 0; row < SUBDIVISION; row++){
            for(int col = 0; col < SUBDIVISION; col++){
                GLfloat theta1 = 45 + row * (90 / SUBDIVISION);
                GLfloat theta2 = 45 + (row+1) * (90 / SUBDIVISION);
                GLfloat phi1 = -45 + col * (90 / SUBDIVISION);
                GLfloat phi2 = -45 + (col+1) * (90 / SUBDIVISION);

                GLfloat x1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat y1 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta1/180);
                GLfloat z1 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat y2 = RADIUS * sin(M_PI * phi1/180) * cos(M_PI * theta2/180);
                GLfloat z2 = RADIUS * cos(M_PI * phi1/180);

                GLfloat x3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat y3 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta2/180);
                GLfloat z3 = RADIUS * cos(M_PI * phi2/180);

                GLfloat x4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat y4 = RADIUS * sin(M_PI * phi2/180) * cos(M_PI * theta1/180);
                GLfloat z4 = RADIUS * cos(M_PI * phi2/180);

                
                glVertex3f(x1, y1, z1);
                glVertex3f(x2, y2, z2);
                glVertex3f(x3, y3, z3);
                glVertex3f(x4, y4, z4);

            }
        }
    glEnd();
    glRotatef(90.0f ,0.0f, 1.0f, 0.0f);
   /*
    glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.5f, 0.0f);
        glVertex3f(0.5f, 0.5f, 0.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);

        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, 0.0f, 0.0f);
        glVertex3f(0.7f, 0.0f, 0.2f);
        glVertex3f(0.7f, 0.5f, 0.2f);
        glVertex3f(0.5f, 0.5f, 0.0f);
    glEnd();
    */

    // vertex: 0.5 0.5 0.707107
    // vertex: 0.415627 0.415627 0.707107
    // vertex: 0.475528 0.475528 0.587785
    // vertex: 0.572061 0.572061 0.587785
    // glBegin(GL_QUADS);
    //     glColor3f(1.0f, 0.0f, 1.0f);
    //     glVertex3f(0.5f, 0.5f, 0.707107f);
    //     glVertex3f(0.415627f, 0.415627f, 0.707107f);
    //     glVertex3f(0.475528f, 0.475528f, 0.587785f);
    //     glVertex3f(0.572061f, 0.572061f, 0.587785f);
    // glEnd();

    // glBegin(GL_LINES);
    //     glVertex3f(0.0f, 0.0f, 0.0f);
    //     glVertex3f(1.0f, 1.0f, 1.0f);
    // glEnd();

    glFlush();
}
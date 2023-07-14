#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"
#include "sphere.h"
#include "octahedron.h"
#include "utility.h"
#include "cylinder.h"

void drawAxes()
{
    glLineWidth(2.0); // Set the line width for the axes

    // X-axis (red color)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();

    // Y-axis (green color)
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();

    // Z-axis (blue color)
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    /*if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }*/
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}



void display(){
    //init
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    

    gluLookAt(eyex,eyey,eyez,
              centerx,centery,centerz,
              upx,upy,upz);

    

    //object movement code
    glScalef(zoom, zoom, zoom);
    glTranslatef(-1.0f,0,0);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); 
    glRotatef(angleZ, 1.0f, 0.0f, 0.0f);
    GLfloat value = 1- 0.28* scaleSphere;
    glScalef(value,value,value);    

    //sphere generation
    drawSphere();

    //octahedron generation
    drawOctahedron();

    //cylinder generation
    drawCylinders();
    
    glScalef(1/value,1/value,1/value);
    glRotatef(-angleZ, 1.0f, 0.0f, 0.0f);
    glRotatef(-angleY, 0.0f, 1.0f, 0.0f); 
    glTranslatef(1.0f,0,0);  
    glScalef(1/zoom, 1/zoom, 1/zoom);
    
    
    glScalef(zoom, zoom, zoom);
    glTranslatef(1.0f,0,0);
    glRotatef(angleZ, 0.0f, 1.0f, 0.0f); 
    glRotatef(angleY, 1.0f, 0.0f, 0.0f);
    glScalef(value,value,value); 

    std::cout << moveSphereSide << " " << scaleSphere << " " << std::endl;
    moveSphereSide = 1.0f - moveSphereSide;
    scaleSphere = 1.0f - scaleSphere;
      
    drawSphere();

    //octahedron generation
    drawOctahedron();

    //cylinder generation
    drawCylinders();

    moveSphereSide = 1.0f - moveSphereSide;
    scaleSphere = 1.0f - scaleSphere;
    
    glFlush();
    glutSwapBuffers();
}

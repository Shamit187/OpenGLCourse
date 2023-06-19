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

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);  // Set the viewport to the new dimensions

    glMatrixMode(GL_MODELVIEW);      // Switch back to the modelview matrix
    glLoadIdentity();                // Reset the modelview matrix
}



void display(){
    //init
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //object movement code
    glScalef(zoom, zoom, zoom);
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
    
    glFlush();
    glutSwapBuffers();
}
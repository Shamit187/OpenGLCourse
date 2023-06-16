#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"
#include "sphere.h"
#include "octahedron.h"
#include "utility.h"

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

    // glMatrixMode(GL_PROJECTION);     // Switch to the projection matrix
    // glLoadIdentity();                // Reset the projection matrix

    // Set the perspective projection
    // gluPerspective(45.0, (double)width / height, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);      // Switch back to the modelview matrix
    glLoadIdentity();                // Reset the modelview matrix
}



void display(){
    auto list_of_vertex = buildUnitPositiveX(SUBDIVISION);
    auto list_of_quad = buildQuadsFromVertices(list_of_vertex, SUBDIVISION);
    GLfloat color[3] = {1.0f, 1.0f, 1.0f};
    GLfloat scale[3] = {1.0f, 1.0f, 1.0f};
    GLfloat translate[3] = {0.0f, 0.0f, 0.0f};
    GLfloat rotate[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    //init
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //object movement code
    glScalef(zoom, zoom, zoom);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); 
    glRotatef(angleZ, 1.0f, 0.0f, 0.0f);

    //sphere generation
    drawSphere();

    //octahedron generation
    drawOctahedron();

    glFlush();
    glutSwapBuffers();
}
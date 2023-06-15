#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"
#include "sphere.h"

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

void bufferClear(GLfloat* scale, GLfloat* translate, GLfloat* rotate, GLfloat* color){
    scale[0] = 1.0f; scale[1] = 1.0f; scale[2] = 1.0f;
    translate[0] = 0.0f; translate[1] = 0.0f; translate[2] = 0.0f;
    rotate[0] = 0.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 0.0f;
    color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f;
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
    // X
    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 1.0f; color[1] = 0.0f; color[2] = 0.0f;
    rotate[0] = 180.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 1.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);


    // Y
    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 5.0f; color[2] = 5.0f;
    rotate[0] = 90.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 1.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 5.0f; color[2] = 5.0f;
    rotate[0] = -90.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 1.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);


    // Z
    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
    rotate[0] = 90.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
    rotate[0] = -90.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    glFlush();
    glutSwapBuffers();
}
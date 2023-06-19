#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"
#include "utility.h"
#define OCTA_TRANSITION 0.578f

void drawOctahedronSide(GLfloat* color, GLfloat* rotate, GLfloat* scale, GLfloat* translate){
    glColor3f(color[0], color[1], color[2]);
    glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
    glTranslatef(translate[0], translate[1], translate[2]);
    glScalef(scale[0], scale[1], scale[2]);

    glBegin(GL_TRIANGLES);
        glVertex3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();

    glScalef(1/scale[0], 1/scale[1], 1/scale[2]);
    glTranslatef(-translate[0], -translate[1], -translate[2]);
    glRotatef(-rotate[0], rotate[1], rotate[2], rotate[3]);
}

void drawOctahedronGroup(GLfloat angle, int rotation_axis){
    GLfloat magic = OCTA_TRANSITION - OCTA_TRANSITION*moveSphereSide;
    GLfloat color[3] = {1.0f, 1.0f, 1.0f};
    GLfloat scale[3] = {1.0f, 1.0f, 1.0f};
    GLfloat translate[3] = {0.0f, 0.0f, 0.0f};
    GLfloat rotate[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    glRotatef(angle, rotation_axis == 1, rotation_axis == 2, rotation_axis == 3);

    scale[0] =1 - scaleSphere; scale[1] = 1 - scaleSphere; scale[2] = 1 - scaleSphere;
    color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f;
    rotate[0] = 0.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    translate[0] = magic; translate[1] = magic; translate[2] = magic;
    drawOctahedronSide(color, rotate, scale, translate);
    bufferClear(scale, translate, rotate, color);

    scale[0] =1 - scaleSphere; scale[1] = 1 - scaleSphere; scale[2] = 1 - scaleSphere;
    color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f;
    rotate[0] = 90.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    translate[0] = magic; translate[1] = magic; translate[2] = magic;
    drawOctahedronSide(color, rotate, scale, translate);
    bufferClear(scale, translate, rotate, color);

    scale[0] =1 - scaleSphere; scale[1] = 1 - scaleSphere; scale[2] = 1 - scaleSphere;
    color[0] = 1.0f; color[1] = 1.0f; color[2] = 0.0f;
    rotate[0] = 180.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    translate[0] = magic; translate[1] = magic; translate[2] = magic;
    drawOctahedronSide(color, rotate, scale, translate);
    bufferClear(scale, translate, rotate, color);

    scale[0] =1 - scaleSphere; scale[1] = 1 - scaleSphere; scale[2] = 1 - scaleSphere;
    color[0] = 1.0f; color[1] = 0.5f; color[2] = 0.0f;
    rotate[0] = -90.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    translate[0] = magic; translate[1] = magic; translate[2] = magic;
    drawOctahedronSide(color, rotate, scale, translate);
    bufferClear(scale, translate, rotate, color);

    glRotatef(-angle, rotation_axis == 1, rotation_axis == 2, rotation_axis == 3);
}

void drawOctahedron(){   
    drawOctahedronGroup(0,1);
    drawOctahedronGroup(180,3);
}

#pragma once

#include <GL/glut.h>
#include <cmath>
#include "sharedData.h"

#define CYLINDER_TRANSITION 1.415f

void drawCylinder(int subdivisions, float radius, float height) {
    // Calculate the angle between each subdivision
    float angle = 2.0f * M_PI / subdivisions;

    // Draw the sides of the cylinder
    glColor3f(0.2f, 0.2f, 0.3f);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= subdivisions; ++i) {
        float x = radius * cosf(i * angle);
        float z = radius * sinf(i * angle);

        // Top vertex
        glVertex3f(x, height / 2, z);
        // Bottom vertex
        glVertex3f(x, -height / 2, z);
    }
    glEnd();

    // Draw the top and bottom covers of the cylinder
    glColor3f(0.1f, 0.5f, 0.2f);
    glBegin(GL_TRIANGLE_FAN);
    // Top center vertex
    glVertex3f(0.0f, height / 2, 0.0f);
    for (int i = 0; i <= subdivisions; ++i) {
        float x = radius * cosf(i * angle);
        float z = radius * sinf(i * angle);

        // Top vertex
        glVertex3f(x, height / 2, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    // Bottom center vertex
    glVertex3f(0.0f, -height / 2, 0.0f);
    for (int i = subdivisions; i >= 0; --i) {
        float x = radius * cosf(i * angle);
        float z = radius * sinf(i * angle);

        // Bottom vertex
        glVertex3f(x, -height / 2, z);
    }
    glEnd();
}

void SingleCylinderGenerator(GLfloat angle, int rotation_axis){
    glRotatef(angle, rotation_axis == 1, rotation_axis == 2, rotation_axis == 3);
    glTranslatef((1 / CYLINDER_TRANSITION )*moveSphereSide,0.0f,0.0f);
    drawCylinder(SUBDIVISION * 10, scaleSphere, CYLINDER_TRANSITION* moveSphereSide);
    glTranslatef(-(1 / CYLINDER_TRANSITION )*moveSphereSide,0.0f,0.0f);
    glRotatef(-angle, rotation_axis == 1, rotation_axis == 2, rotation_axis == 3);
}

void GroupCylinderGenerator(GLfloat angle, int rotation_axis){
    glRotatef(angle, rotation_axis == 1, rotation_axis == 2, rotation_axis == 3);
    SingleCylinderGenerator(45.0f, 3);
    SingleCylinderGenerator(-45.0f, 3);
    SingleCylinderGenerator(135.0f, 3);
    SingleCylinderGenerator(-135.0f, 3);
    glRotatef(-angle, rotation_axis == 1, rotation_axis == 2, rotation_axis == 3);
}



void drawCylinders(){
    GroupCylinderGenerator(0,1);
    GroupCylinderGenerator(90,2); 
    GroupCylinderGenerator(90,1);    
}

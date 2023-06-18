#pragma once

#include <GL/glut.h>
#include <cmath>
#include "sharedData.h"

void drawCylinder(int subdivisions, float radius, float height) {
    // Calculate the angle between each subdivision
    float angle = 2.0f * M_PI / subdivisions;

    // Draw the sides of the cylinder
    glColor3f(0.0f, 0.2f, 0.3f);
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

#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"
#include "utility.h"


std::vector<float> buildUnitPositiveX(int subdivision)
{
    const float DEG2RAD = acos(-1) / 180.0f;

    std::vector<float> vertices;
    float n1[3];        // normal of longitudinal plane rotating along Y-axis
    float n2[3];        // normal of latitudinal plane rotating along Z-axis
    float v[3];         // direction vector intersecting 2 planes, n1 x n2
    float a1;           // longitudinal angle along Y-axis
    float a2;           // latitudinal angle along Z-axis

    // compute the number of vertices per row, 2^n + 1
    int pointsPerRow = (int)pow(2, subdivision) + 1;

    // rotate latitudinal plane from 45 to -45 degrees along Z-axis (top-to-bottom)
    for(unsigned int i = 0; i < pointsPerRow; ++i)
    {
        // normal for latitudinal plane
        // if latitude angle is 0, then normal vector of latitude plane is n2=(0,1,0)
        // therefore, it is rotating (0,1,0) vector by latitude angle a2
        a2 = DEG2RAD * (45.0f - 90.0f * i / (pointsPerRow - 1));
        n2[0] = -sin(a2);
        n2[1] = cos(a2);
        n2[2] = 0;

        // rotate longitudinal plane from -45 to 45 along Y-axis (left-to-right)
        for(unsigned int j = 0; j < pointsPerRow; ++j)
        {
            // normal for longitudinal plane
            // if longitude angle is 0, then normal vector of longitude is n1=(0,0,-1)
            // therefore, it is rotating (0,0,-1) vector by longitude angle a1
            a1 = DEG2RAD * (-45.0f + 90.0f * j / (pointsPerRow - 1));
            n1[0] = -sin(a1);
            n1[1] = 0;
            n1[2] = -cos(a1);

            // find direction vector of intersected line, n1 x n2
            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize direction vector
            float scale = 1 / sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            // add a vertex into array
            vertices.push_back(v[0]);
            vertices.push_back(v[1]);
            vertices.push_back(v[2]);
        }
    }

    return vertices;
}

std::vector<float> buildQuadsFromVertices(const std::vector<float>& vertices, int subdivision)
{
    std::vector<float> quads;

    // compute the number of vertices per row, 2^n + 1
    int pointsPerRow = (int)pow(2, subdivision) + 1;

    // iterate over the vertices to create quads
    for (unsigned int i = 0; i < pointsPerRow - 1; ++i)
    {
        for (unsigned int j = 0; j < pointsPerRow - 1; ++j)
        {
            // calculate indices of the current quad
            int index1 = i * pointsPerRow + j;
            int index2 = index1 + 1;
            int index3 = (i + 1) * pointsPerRow + j;
            int index4 = index3 + 1;

            // add the vertices of the quad to the quad vector
            quads.push_back(vertices[3 * index1]);
            quads.push_back(vertices[3 * index1 + 1]);
            quads.push_back(vertices[3 * index1 + 2]);

            quads.push_back(vertices[3 * index2]);
            quads.push_back(vertices[3 * index2 + 1]);
            quads.push_back(vertices[3 * index2 + 2]);

            quads.push_back(vertices[3 * index4]);
            quads.push_back(vertices[3 * index4 + 1]);
            quads.push_back(vertices[3 * index4 + 2]);

            quads.push_back(vertices[3 * index3]);
            quads.push_back(vertices[3 * index3 + 1]);
            quads.push_back(vertices[3 * index3 + 2]);
        }
    }

    return quads;
}

void generateSphereSide(const std::vector<float>& list_of_quad){
    auto size = list_of_quad.size();


    glBegin(GL_QUADS);
        for(int i = 0; i < list_of_quad.size(); i += 12){
            for(int j = 0; j < 12; j += 3 ){
                glVertex3f(list_of_quad[i+j], list_of_quad[i+j+1], list_of_quad[i+j+2]);
            }
        }
    glEnd();
}


void drawSphere(const std::vector<float>& list_of_quad, GLfloat* scale, GLfloat* translate, GLfloat* rotate, GLfloat* color){
    glRotatef(rotate[0], rotate[1], rotate[2], rotate[3]);
    glTranslatef(translate[0], translate[1], translate[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glColor3f(color[0], color[1], color[2]);
    generateSphereSide(list_of_quad);
    glScalef(1/scale[0], 1/scale[1], 1/scale[2]);
    glTranslatef(-translate[0], -translate[1], -translate[2]);
    glRotatef(-rotate[0], rotate[1], rotate[2], rotate[3]);
}

void drawSphere(){
    auto list_of_vertex = buildUnitPositiveX(SUBDIVISION);
    auto list_of_quad = buildQuadsFromVertices(list_of_vertex, SUBDIVISION);
    GLfloat color[3] = {1.0f, 1.0f, 1.0f};
    GLfloat scale[3] = {1.0f, 1.0f, 1.0f};
    GLfloat translate[3] = {0.0f, 0.0f, 0.0f};
    GLfloat rotate[4] = {0.0f, 0.0f, 0.0f, 0.0f};

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
}
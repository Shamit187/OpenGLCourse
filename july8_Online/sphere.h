#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"
#include "utility.h"

#define sqrt3 0.57735026919f


std::vector<GLfloat> sphereX(int subdivision)
{

    std::vector<GLfloat> vertices;
    GLfloat n1[3];        
    GLfloat n2[3];        
    GLfloat v[3];     
    GLfloat theta;
    GLfloat phi;
    GLfloat distance;
    GLfloat scale;
    GLfloat radius = 1.0f;

    int pointsPerRow = (int)pow(2, subdivision) + 1;

    for(unsigned int i = 0; i < pointsPerRow; ++i)
    {
        // get n2 vector (45 to -45)
        phi = (PI / 180.0f) * (45.0f - 90.0f * i / (pointsPerRow - 1));
        n2[0] = -sin(phi);
        n2[1] = cos(phi);
        n2[2] = 0;

        for(unsigned int j = 0; j < pointsPerRow; ++j)
        {
            // get n1 vector (-45 to 45)
            theta = (PI / 180.0f) * (-45.0f + 90.0f * j / (pointsPerRow - 1));
            n1[0] = -sin(theta);
            n1[1] = 0;
            n1[2] = -cos(theta);

            // n1 cross n2
            v[0] = n1[1] * n2[2] - n1[2] * n2[1];
            v[1] = n1[2] * n2[0] - n1[0] * n2[2];
            v[2] = n1[0] * n2[1] - n1[1] * n2[0];

            // normalize
            distance = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
            scale = 1 / distance;
            v[0] *= scale;
            v[1] *= scale;
            v[2] *= scale;

            // radius
            v[0] *= radius;
            v[1] *= radius;
            v[2] *= radius;

            // every 3 entry is a vertex
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
    int pointsPerRow = (int)pow(2, subdivision) + 1;
    
    for (unsigned int i = 0; i < pointsPerRow - 1; ++i){
        for (unsigned int j = 0; j < pointsPerRow - 1; ++j){
            // indexi = vertex i of a quad
            int index1 = i * pointsPerRow + j;
            int index2 = index1 + 1;
            int index3 = (i + 1) * pointsPerRow + j;
            int index4 = index3 + 1;

            // every 3 entry is a vertex
            // every 12 entry is a quad
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
        // for(int i = 0; i < list_of_quad.size(); i += 12){
        //     // i = quad number
        //     for(int j = 0; j < 12; j += 3){
        //         // j = 0, 3, 6, 9.. vertex entries of 0th quad
        //         // i+j = vertex entries of ith quad
        //         glVertex3f(list_of_quad[i+j], list_of_quad[i+j+1], list_of_quad[i+j+2]);
        //     }
        // }
        glVertex3f(sqrt3, sqrt3, sqrt3);
        glVertex3f(sqrt3, -sqrt3, sqrt3);
        glVertex3f(sqrt3, -sqrt3, -sqrt3);
        glVertex3f(sqrt3, sqrt3, -sqrt3);
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
    auto list_of_vertex = sphereX(SUBDIVISION);
    auto list_of_quad = buildQuadsFromVertices(list_of_vertex, SUBDIVISION);
    GLfloat color[3] = {1.0f, 1.0f, 1.0f};
    GLfloat scale[3] = {1.0f, 1.0f, 1.0f};
    GLfloat translate[3] = {0.0f, 0.0f, 0.0f};
    GLfloat rotate[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.7f; color[1] = 0.0f; color[2] = 0.0f;
    rotate[0] = 0.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 0.5f; color[2] = 0.5f;
    rotate[0] = 90.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.7f; color[1] = 0.0f; color[2] = 0.0f;
    rotate[0] = 180.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 0.5f; color[2] = 0.5f;
    rotate[0] = 270.0f; rotate[1] = 0.0f; rotate[2] = 1.0f; rotate[3] = 0.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
    rotate[0] = 90.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 1.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

    translate[0] += moveSphereSide;
    scale[0] *= scaleSphere; scale[1] *= scaleSphere; scale[2] *= scaleSphere;
    color[0] = 0.0f; color[1] = 0.0f; color[2] = 1.0f;
    rotate[0] = -90.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 1.0f;
    drawSphere(list_of_quad, scale, translate, rotate, color);
    bufferClear(scale, translate, rotate, color);

}




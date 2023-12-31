#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>

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
    auto x = buildUnitPositiveX(3);
    for(int i = 0; i < x.size(); i+=3)
            std::cout << "Vertex: " << x[i] << " " << x[i+1] << " " << x[i+2] << std::endl;
    int pointsPerRow = (int)pow(2, 3) + 1;
    int quads = (pointsPerRow - 1)*(pointsPerRow - 1);
    glPointSize(10);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        for(int q = 0; q < quads; q++){
            glVertex3f(x[3*q], x[3*q+1], x[3*q+2]);
        }

    glEnd();

    glFlush();
}
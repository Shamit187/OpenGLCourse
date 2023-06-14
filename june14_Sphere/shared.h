#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#define SUBDIVISION 4
GLfloat angleY = 0.0f;
GLfloat angleZ = 0.0f;
GLfloat zoom = 1.0f;

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q': // Rotate the object when 'r' key is pressed
        case 'Q':
            angleY -= 10.0f;
            glutPostRedisplay(); // Mark the window for redrawing
            break;
        case 'e': // Rotate the object when 'r' key is pressed
        case 'E':
            angleY += 10.0f;
            glutPostRedisplay(); // Mark the window for redrawing
            break;
        case 'i': // Rotate the object when 'r' key is pressed
        case 'I':
            angleZ -= 10.0f;
            glutPostRedisplay(); // Mark the window for redrawing
            break;
        case 'p': // Rotate the object when 'r' key is pressed
        case 'P':
            angleZ += 10.0f;
            glutPostRedisplay(); // Mark the window for redrawing
            break;
        case '-': // Zoom out when '-' key is pressed
            zoom += 0.1f;
            glutPostRedisplay(); // Mark the window for redrawing
            break;
        case '+': // Zoom in when '+' key is pressed
        case '=':
            zoom -= 0.1f;
            if (zoom < 0.1f)
                zoom = 0.1f;
            glutPostRedisplay(); // Mark the window for redrawing
            break;
        case 27: // ESC key
            exit(0); // Exit the program
            break;
    }
}

// generate vertices for +X face only by intersecting 2 circular planes
// (longitudinal and latitudinal) at the given longitude/latitude angles
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

void generateSphereSide(){
    auto list_of_vertex = buildUnitPositiveX(SUBDIVISION);
    auto list_of_quad = buildQuadsFromVertices(list_of_vertex, SUBDIVISION);
    auto size = list_of_quad.size();


    glBegin(GL_QUADS);
        for(int i = 0; i < list_of_quad.size(); i += 12){
            for(int j = 0; j < 12; j += 3 ){
                glVertex3f(list_of_quad[i+j], list_of_quad[i+j+1], list_of_quad[i+j+2]);
            }
        }
    glEnd();
}

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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScalef(zoom, zoom, zoom);

    //z rotation
    glRotatef(angleY, 0.0f, 1.0f, 0.0f); 
    //up-down rotation
    glRotatef(angleZ, 1.0f, 0.0f, 0.0f);

    drawAxes();
    
    // X
    glColor3d(1.0f,0.0f,0.0f);
    generateSphereSide();
    glRotatef(180.0f ,0.0f, 0.0f, 1.0f);
    generateSphereSide();
    glRotatef(-180.0f ,0.0f, 0.0f, 1.0f);

    // Y
    glColor3d(0.0f,0.7f,0.7f);
    glRotatef(90.0f ,0.0f, 0.0f, 1.0f);
    generateSphereSide();
    glRotatef(-180.0f ,0.0f, 0.0f, 1.0f);
    generateSphereSide();
    glRotatef(90.0f ,0.0f, 0.0f, 1.0f);

    // Z
    glColor3d(0.0f,0.0f,1.0f);
    glRotatef(90.0f ,0.0f, 1.0f, 0.0f);
    generateSphereSide();
    glRotatef(-180.0f ,0.0f, 1.0f, 0.0f);
    generateSphereSide();
    glRotatef(90.0f ,0.0f, 1.0f, 0.0f);

    

    glFlush();
    glutSwapBuffers();
}
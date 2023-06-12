#include <iostream>
#include <GL/glut.h>

void display() {
   glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
 
   // Define shapes enclosed within a pair of glBegin and glEnd
   glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
      glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
      glVertex2f(-0.2f, 0.7f);
      glVertex2f(-0.8f, 0.7f);
 
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(-0.7f, -0.6f);
      glVertex2f(-0.1f, -0.6f);
      glVertex2f(-0.1f,  0.0f);
      glVertex2f(-0.7f,  0.0f);
 
      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      glVertex2f(-0.9f, -0.7f);
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2f(-0.5f, -0.7f);
      glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
      glVertex2f(-0.5f, -0.3f);
      glColor3f(1.0f, 1.0f, 1.0f); // White
      glVertex2f(-0.9f, -0.3f);
   glEnd();
 
   glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.1f, -0.6f);
      glVertex2f(0.7f, -0.6f);
      glVertex2f(0.4f, -0.1f);
 
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(0.3f, -0.4f);
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(0.9f, -0.4f);
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.6f, -0.9f);
   glEnd();
 
   glBegin(GL_POLYGON);            // These vertices form a closed polygon
      glColor3f(1.0f, 1.0f, 0.0f); // Yellow
      glVertex2f(0.4f, 0.2f);
      glVertex2f(0.6f, 0.2f);
      glVertex2f(0.7f, 0.4f);
      glVertex2f(0.6f, 0.6f);
      glVertex2f(0.4f, 0.6f);
      glVertex2f(0.3f, 0.4f);
   glEnd();
 
   glFlush();  // Render now
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

void QUAD(GLfloat length, GLfloat width){
    glBegin(GL_QUADS);
        glVertex2f(-length/2, -width/2);
        glVertex2f( length/2, -width/2);
        glVertex2f( length/2,  width/2);
        glVertex2f(-length/2,  width/2);
    glEnd();
}

void smartQuad(GLfloat length, GLfloat width, GLfloat objectX, GLfloat objectY, GLfloat angle){
    glTranslatef(objectX, objectY, 0.0f);
    glRotatef(angle,0.0f, 0.0f, 1.0f);
    QUAD(0.5f, 0.5f);
    glRotatef(-angle,0.0f, 0.0f, 1.0f);
    glTranslatef(-objectX, -objectY, 0.0f);
}

void smartDisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    // glMatrixMode(GL_MODELVIEW);      // To operate on Model-View matrix
    // glLoadIdentity();                // Reset the model-view matrix
    glPushMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);
    smartQuad(0.5f, 0.5f, 0.5f, 0.0f, 45.0f);

    glColor3f(1.0f, 1.0f, 0.0f);
    smartQuad(0.5f, 0.5f, -0.5f, 0.0f, 45.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    smartQuad(0.5f, 0.5f, 0.0f, 0.5f, 45.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    smartQuad(0.5f, 0.5f, 0.0f, -0.5f, 45.0f);

    glFlush();
}
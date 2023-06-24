#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <chrono>
#include <cstring>

#define PI 3.14159265
#define HALO_TRAIL 40

GLfloat pendulumAngle = 0.0f;
GLfloat pendulumLength = 0.5f;
struct pendulumData {
    GLfloat length;
    GLfloat angle;
    GLfloat radius;
    GLfloat intensity;
};
pendulumData pendulumList[HALO_TRAIL];

void drawPendulum(GLfloat length, GLfloat angle, GLfloat radius, GLfloat intensity)
{
    glLineWidth(10.0);
    if(intensity == 1.0f){
        glColor3f(1.0 * intensity, 1.0 * intensity, 1.0 * intensity);
        glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(length * sin(angle * PI / 180.0), -length * cos(angle * PI / 180.0));
        glEnd();

        glRotatef(angle, 0, 0, 1);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 60){
            float theta1 = i * PI / 180.0;
            float theta2 = (i + 1) * PI / 180.0;
            glVertex2f(0.05 * cos(theta1), 0.05 * sin(theta1));
            glVertex2f(0.05 * cos(theta2), 0.05 * sin(theta2));
        }
        glEnd();
        glRotatef(-angle, 0, 0, 1);
    }

    glTranslatef(length * sin(angle * PI / 180.0), -length * cos(angle * PI / 180.0), 0);
    glColor3f(1.0 * intensity, 1.0 * intensity, 1.0 * intensity);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 5){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.1 * radius * cos(theta1), 0.1 * radius * sin(theta1));
        glVertex2f(0.1 * radius * cos(theta2), 0.1 * radius * sin(theta2));
    }
    glEnd();

    if(intensity == 1.0f){
        glColor3f(1.0, 0, 0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5){
            float theta1 = i * PI / 180.0;
            float theta2 = (i + 1) * PI / 180.0;
            glVertex2f(0.02 * cos(theta1), 0.02 * sin(theta1));
            glVertex2f(0.02 * cos(theta2), 0.02 * sin(theta2));
        }
        glEnd();
    }
    glTranslatef(-length * sin(angle * PI / 180.0), length * cos(angle * PI / 180.0), 0);
    
}

void drawClock(GLfloat hour, GLfloat minute, GLfloat second)
{
    // Draw clock face
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 360; i += 1){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(0.5 * cos(theta1), 0.5 * sin(theta1));
        glVertex2f(0.5 * cos(theta2), 0.5 * sin(theta2));
        glColor3f(0, 0, 0);
        glVertex2f(0, 0);
    }
    glEnd();

    glLineWidth(10.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 6)
    {
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.5 * cos(theta1), 0.5 * sin(theta1));
        glVertex2f(0.5 * cos(theta2), 0.5 * sin(theta2));
    }
    glEnd();

    // Draw the minute notch
    glLineWidth(3.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 6)
    {
        float theta = i * PI / 180.0;
        glVertex2f(0.5 * cos(theta), 0.5 * sin(theta));
        glVertex2f(0.48 * cos(theta), 0.48 * sin(theta));
    }
    glEnd();

    // Draw the hour notch
    glLineWidth(5.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 30)
    {
        float theta = i * PI / 180.0;
        glVertex2f(0.5 * cos(theta), 0.5 * sin(theta));
        glVertex2f(0.45 * cos(theta), 0.45 * sin(theta));
    }
    glEnd();

    // Draw hour hand
    glRotatef(-hour, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(10);
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 0.2);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 60){
        float theta = i * PI / 180.0;
        glVertex2f(0.04 * cos(theta), 0.04 * sin(theta));
    }
    glEnd();

    glRotatef(hour, 0.0, 0.0, 1.0);
    

    // Draw minute hand
    glRotatef(-minute, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3);
    glBegin(GL_LINES);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.0, 0.3);
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i += 60){
        float theta = i * PI / 180.0;
        glVertex2f(0.03 * cos(theta), 0.03 * sin(theta));
    }
    glEnd();

    glRotatef(minute, 0.0, 0.0, 1.0);

    // Draw second hand
    glRotatef(-second, 0.0, 0.0, 1.0);
    glLineWidth(2);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 60){
        float theta = i * PI / 180.0;
        glVertex2f(0.02 * cos(theta), 0.02 * sin(theta));
    }
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 0.4);
    glEnd();
    glRotatef(second, 0.0, 0.0, 1.0);
}

void display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer
        // glLoadIdentity();

    time_t currentTime = std::time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int hour = (localTime->tm_hour)%12;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    GLfloat secondAngle = second * 6;
    GLfloat minuteAngle = minute * 6 + secondAngle * 6 / (GLfloat)360;
    GLfloat hourAngle = hour * 30 + minuteAngle * 30 / (GLfloat)360;
    
    glTranslatef(0.0f, -0.3f, 0.0f);
        for(int i = 0 ; i < HALO_TRAIL; i++){
            drawPendulum(pendulumList[i].length, pendulumList[i].angle, pendulumList[i].radius, pendulumList[i].intensity);
        }
        
        glColor3f(1.0, 0.0, 0.0);
        glLineWidth(3);
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,0.095);
        glEnd();

        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 5)
        {
            float theta = i * PI / 180.0;
            glVertex2f(0.02 * cos(theta), 0.02 * sin(theta));
        }
        glEnd();
    glTranslatef(0.0f, 0.3f, 0.0f);

    glTranslatef(0.0f, 0.3f, 0.0f);
        drawClock(hourAngle, minuteAngle, secondAngle);
    glTranslatef(0.0f, -0.3f, 0.0f);

    glFlush();
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

void timer(int value)
{
    auto millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    millisec_since_epoch %= 2000;
    GLfloat currentTime = millisec_since_epoch / 1000.0f;
    GLfloat angle = 0.0f;
    GLfloat angularVelocity = 180.0f;
    GLfloat phase = 45.0f;
    GLfloat amplitude = 30.0f;
    
    for(int i = 0; i < HALO_TRAIL; i++){
        angle = angularVelocity * currentTime + phase + ((GLfloat)i) * 2;
        angle = fmod(angle, 360.0f);
        pendulumAngle = amplitude * cos(angle * PI / 180.0f);

        pendulumList[i].intensity = (GLfloat)i/(GLfloat)HALO_TRAIL;
        pendulumList[i].length = pendulumLength;
        pendulumList[i].radius = (GLfloat)i/(GLfloat)HALO_TRAIL;
        pendulumList[i].angle = pendulumAngle;
    }
    pendulumList[HALO_TRAIL - 1].intensity = 1.0f;

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

void startAtProperTime(int value){
    for(int i = 0; i < HALO_TRAIL; i++){
        pendulumList[i] = pendulumData{0,0,0,0};
    }
    auto millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    millisec_since_epoch %= 1000;
    while(millisec_since_epoch != 0){
        millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        millisec_since_epoch %= 1000;
    }
    glutTimerFunc(0, timer, 0);
}

void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Analog Clock");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, startAtProperTime, 0);
    glutMainLoop();

    return 0;
}

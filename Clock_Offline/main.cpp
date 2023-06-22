#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <iostream>
#include <chrono>
#include <cstring>

#define PI 3.14159265

GLfloat pendulumAngle = 0.0f;
GLfloat pendulumLength = 0.5f;

void drawPendulum()
{
    glLineWidth(10.0);
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(pendulumLength * sin(pendulumAngle * PI / 180.0), -pendulumLength * cos(pendulumAngle * PI / 180.0));
    glEnd();

    glTranslatef(pendulumLength * sin(pendulumAngle * PI / 180.0), -pendulumLength * cos(pendulumAngle * PI / 180.0), 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.1 * cos(theta1), 0.1 * sin(theta1));
        glVertex2f(0.1 * cos(theta2), 0.1 * sin(theta2));
    }
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.05 * cos(theta1), 0.05 * sin(theta1));
        glVertex2f(0.05 * cos(theta2), 0.05 * sin(theta2));
    }
    glEnd();
    glTranslatef(-pendulumLength * sin(pendulumAngle * PI / 180.0), pendulumLength * cos(pendulumAngle * PI / 180.0), 0);
    
}

void drawClock(GLfloat hour, GLfloat minute, GLfloat second)
{
    // Draw clock face
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 360; i += 1){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glColor3f(0, 0, 0);
        glVertex2f(0.5 * cos(theta1), 0.5 * sin(theta1));
        glVertex2f(0.5 * cos(theta2), 0.5 * sin(theta2));
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(0, 0);
    }
    glEnd();

    glLineWidth(3.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 1)
    {
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.5 * cos(theta1), 0.5 * sin(theta1));
        glVertex2f(0.5 * cos(theta2), 0.5 * sin(theta2));
    }
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 1)
    {
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.49 * cos(theta1), 0.49 * sin(theta1));
        glVertex2f(0.49 * cos(theta2), 0.49 * sin(theta2));
    }
    glEnd();

    // Draw the minute notch
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
    glColor3f(1.0, 0.0, 0.0);
    GLfloat hourWeight = 0.03f;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 90; i += 5)
    {
        float theta = i * PI / 180.0;
        glVertex2f(hourWeight - hourWeight * cos(theta), hourWeight * sin(theta));
    }
    glVertex2f(hourWeight, hourWeight);
    glVertex2f(0.0, 0.2);
    glVertex2f(-hourWeight, hourWeight);

    for (int i = 85; i >= 0; i -= 5)
    {
        float theta = i * PI / 180.0;
        glVertex2f(-hourWeight + hourWeight * cos(theta), hourWeight * sin(theta));
    }
    glEnd();
    glTranslatef(0, 0.17, 0);

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 30){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        
        glVertex2f(0.03 * cos(theta1), 0.03 * sin(theta1));
        glVertex2f(0.03 * cos(theta2), 0.03 * sin(theta2));
    }
    glEnd();
    glTranslatef(0, -0.17, 0);

    glRotatef(hour, 0.0, 0.0, 1.0);
    

    // Draw minute hand
    glRotatef(-minute, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    GLfloat minuteWeight = 0.02f;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 90; i += 5)
    {
        float theta = i * PI / 180.0;
        glVertex2f(minuteWeight - minuteWeight * cos(theta), minuteWeight * sin(theta));
    }
    glVertex2f(minuteWeight, minuteWeight);
    glVertex2f(0.0, 0.3);
    glVertex2f(-minuteWeight, minuteWeight);

    for (int i = 85; i >= 0; i -= 5)
    {
        float theta = i * PI / 180.0;
        glVertex2f(-minuteWeight + minuteWeight * cos(theta), minuteWeight * sin(theta));
    }
    glEnd();
    glRotatef(minute, 0.0, 0.0, 1.0);

    // Draw second hand
    glRotatef(-second, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 60){
        float theta1 = i * PI / 180.0;
        float theta2 = (i + 1) * PI / 180.0;
        glVertex2f(0.02 * cos(theta1), 0.02 * sin(theta1));
        glVertex2f(0.02 * cos(theta2), 0.02 * sin(theta2));
    }
    glEnd();

    glColor3f(1,1,1);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 360; i += 60){
        float theta = i * PI / 180.0;
        glVertex2f(0,0);
        glVertex2f(0.02 * cos(theta), 0.02 * sin(theta));
    }
    glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 0.4);
    glEnd();
    glRotatef(second, 0.0, 0.0, 1.0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    time_t currentTime = std::time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int hour = (localTime->tm_hour)%12;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    GLfloat hourAngle = hour * 30;
    GLfloat minuteAngle = minute * 6;
    GLfloat secondAngle = second * 6;

    glTranslatef(0.0f, 0.3f, 0.0f);
    drawClock(hourAngle, minuteAngle, secondAngle);
    glTranslatef(0.0f, -0.3f, 0.0f);
    glTranslatef(0.0f, -0.2f, 0.0f);
    drawPendulum();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 0.0, 1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
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
    angle = angularVelocity * currentTime + phase;
    angle = fmod(angle, 360.0f);
    pendulumAngle = amplitude * cos(angle * PI / 180.0f);
    
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

void startAtProperTime(int value){
    auto millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    millisec_since_epoch %= 1000;
    while(millisec_since_epoch != 0){
        millisec_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        millisec_since_epoch %= 1000;
    }
    glutTimerFunc(0, timer, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Analog Clock");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, startAtProperTime, 0);
    glutMainLoop();

    return 0;
}

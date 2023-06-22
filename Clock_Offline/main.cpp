#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <iostream>

#define PI 3.14159265

GLfloat pendulumLength = 0.4;  // Length of the pendulum arm
GLfloat pendulumAngle = 45.0;  // Initial angle of the pendulum
GLfloat pendulumAngularVelocity = 0.0;  // Angular velocity of the pendulum
GLfloat pendulumAcceleration = -9.8 / pendulumLength * sin(pendulumAngle * PI / 180.0);  // Acceleration of the pendulum

void drawPendulum()
{
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);  // Top of the pendulum
    glVertex2f(pendulumLength * sin(pendulumAngle * PI / 180.0), -pendulumLength * cos(pendulumAngle * PI / 180.0));  // Bottom of the pendulum
    glEnd();
}

void drawClock(GLfloat hour, GLfloat minute, GLfloat second)
{
    int i;

    // Draw clock face
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    for (i = 0; i < 360; i += 1)
    {
        float theta = i * PI / 180.0;
        glVertex2f(0.5 * cos(theta), 0.5 * sin(theta));
    }
    glEnd();

    // Draw hour hand
    glRotatef(-hour, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 0.2);
    glEnd();
    glRotatef(hour, 0.0, 0.0, 1.0);

    // Draw minute hand
    glRotatef(-minute, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, 0.3);
    glEnd();
    glRotatef(minute, 0.0, 0.0, 1.0);

    // Draw second hand
    glRotatef(-second, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glLineWidth(1.0);
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

    // Position the clock
    glTranslatef(0.5, 0.5, 0.0);

    // Rotate the clock based on current time
    time_t currentTime = std::time(NULL);
    struct tm *localTime = localtime(&currentTime);
    int hour = (localTime->tm_hour)%12;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;
    // std::cout << hour << " " << minute << " " << second << std::endl;
    // std::cout << pendulumAngle << " " << pendulumLength << std::endl;

    GLfloat hourAngle = hour * 30;
    GLfloat minuteAngle = minute * 6;
    GLfloat secondAngle = second * 6;

    // Draw the clock
    drawClock(hourAngle, minuteAngle, secondAngle);
    drawPendulum();

    glFlush();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value)
{
    pendulumAngularVelocity += pendulumAcceleration * 0.01;
    pendulumAngle += pendulumAngularVelocity * 0.01;

    

    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Analog Clock");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}

#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q': 
        case 'Q':
            angleY -= 5.0f;
            if(angleY < 0) angleY = 355;
            glutPostRedisplay();
            break;
        
        case 'e':
        case 'E':
            angleY += 5.0f;
            if(angleY > 360) angleY = 5;
            glutPostRedisplay();
            break;

        case 'i':
        case 'I':
            angleZ -= 5.0f;
            if(angleZ < 0) angleZ = 355;
            glutPostRedisplay();
            break;
            
        case 'p':
        case 'P':
            angleZ += 5.0f;
            if(angleZ > 360) angleZ = 5;
            glutPostRedisplay();
            break;

        case '-': 
        case '_': 
            zoom += 0.1f;
            if (zoom > 2.0f) zoom = 2.0f;
            glutPostRedisplay();
            break;

        case '+': 
        case '=':
            zoom -= 0.1f;
            if (zoom < 0.1f) zoom = 0.1f;
            glutPostRedisplay();
            break;

        case '.': 
        case '>': 
            if (scaleSphere <= 0.01f) break;

            scaleSphere -= 0.01f;
            moveSphereSide += 0.01f;
            glutPostRedisplay();
            break;

        case ',': 
        case '<':
            if(scaleSphere == 1.0f) break;
            if(moveSphereSide == 0.0f) break;

            moveSphereSide -= 0.01f;
            scaleSphere += 0.01f;

            glutPostRedisplay();
            break;

        case 27: // ESC key
            exit(0); // Exit the program
            break;
    }
}

#pragma once

#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include "sharedData.h"

void keyboard(unsigned char key, int x, int y)
{
    GLfloat directionx = centerx - eyex;
    GLfloat directiony = centery - eyey;
    GLfloat directionz = centerz - eyez;
    GLfloat newDirectionx = 0.0f;
    GLfloat newDirectiony = 0.0f;
    GLfloat newDirectionz = 0.0f;
    GLfloat cosTheta = 0.99875026039f;
    GLfloat sinTheta = 0.04997916927f;

    switch (key)
    {
        // Rotate Camera Left Right (Y axis based rotation)
        case '1':
            newDirectionx = directionx * cosTheta + directionz * sinTheta;
            newDirectiony = directiony;
            newDirectionz = - directionx * sinTheta + directionz * cosTheta;
            centerx = eyex + newDirectionx;
            centery = eyey + newDirectiony;
            centerz = eyez + newDirectionz;
            break;
        case '2':
            newDirectionx = directionx * cosTheta - directionz * sinTheta;
            newDirectiony = directiony;
            newDirectionz = directionx * sinTheta + directionz * cosTheta;
            centerx = eyex + newDirectionx;
            centery = eyey + newDirectiony;
            centerz = eyez + newDirectionz;
            break;
        // Rotate Camera Up Down (X axis based rotation)
        case '3':
            newDirectionx = directionx;
            newDirectiony = directiony * cosTheta + directionz * sinTheta;
            newDirectionz = - directiony * sinTheta + directionz * cosTheta;
            centerx = eyex + newDirectionx;
            centery = eyey + newDirectiony;
            centerz = eyez + newDirectionz;
            break;
        case '4':
            newDirectionx = directionx;
            newDirectiony = directiony * cosTheta - directionz * sinTheta;
            newDirectionz = directiony * sinTheta + directionz * cosTheta;
            centerx = eyex + newDirectionx;
            centery = eyey + newDirectiony;
            centerz = eyez + newDirectionz;
            break;
        // Rotate Camera look axis. (Z axis based rotation)
        case '5':
            newDirectionx = upx * cosTheta + upy * sinTheta;
            newDirectiony = - upx * sinTheta + upy * cosTheta;
            upx = newDirectionx;
            upy = newDirectiony;
            break;
        case '6':
            newDirectionx = upx * cosTheta - upy * sinTheta;
            newDirectiony = upx * sinTheta + upy * cosTheta;
            upx = newDirectionx;
            upy = newDirectiony;
            break;

        // Bonus Control
        case 'w':
        case 'W':
            directionx = -centerx + eyex;
            directiony = -centery + eyey;
            directionz = -centerz + eyez;
            newDirectionx = directionx;
            newDirectiony = directiony * cosTheta + directionz * sinTheta;
            newDirectionz = - directiony * sinTheta + directionz * cosTheta;
            eyex = centerx + newDirectionx;
            eyey = centery + newDirectiony;
            eyez = centerz + newDirectionz;
        
        case 's':
        case 'S':
            directionx = -centerx + eyex;
            directiony = -centery + eyey;
            directionz = -centerz + eyez;
            newDirectionx = directionx;
            newDirectiony = directiony * cosTheta - directionz * sinTheta;
            newDirectionz = directiony * sinTheta + directionz * cosTheta;
            eyex = centerx + newDirectionx;
            eyey = centery + newDirectiony;
            eyez = centerz + newDirectionz;

        // Control Object Mobement
        case 'a': 
        case 'A':
            angleY -= 5.0f;
            if(angleY < 0) angleY = 355;
            break;
        
        case 'd':
        case 'D':
            angleY += 5.0f;
            if(angleY > 360) angleY = 5;
            break;

        case 'i':
        case 'I':
            angleZ -= 5.0f;
            if(angleZ < 0) angleZ = 355;
            break;
            
        case 'p':
        case 'P':
            angleZ += 5.0f;
            if(angleZ > 360) angleZ = 5;
            break;

        // Control Camera zoom in and zoom out
        case '-': 
        case '_': 
            zoom += 0.1f;
            if (zoom > 2.0f) zoom = 2.0f;
            break;

        case '+': 
        case '=':
            zoom -= 0.1f;
            if (zoom < 0.1f) zoom = 0.1f;
            break;

        // Control Object morphing
        case '.': 
        case '>': 
            if (scaleSphere <= 0.01f) break;

            scaleSphere -= 0.01f;
            moveSphereSide += 0.01f;
            break;

        case ',': 
        case '<':
            if(scaleSphere == 1.0f) break;
            if(moveSphereSide == 0.0f) break;

            moveSphereSide -= 0.01f;
            scaleSphere += 0.01f;

            break;

        case 27: // ESC key
            exit(0); // Exit the program
            break;
    }
    glutPostRedisplay();
}

void specialKey(int key, int x,int y) {

    GLfloat controlSpeed = 0.08;
    switch (key) {
        case GLUT_KEY_LEFT:
            eyex += controlSpeed;
            centerx += controlSpeed;
            break;
        case GLUT_KEY_RIGHT:
            eyex -= controlSpeed;
            centerx -= controlSpeed;
            break;
        case GLUT_KEY_UP:
            eyez += controlSpeed;
            centerz += controlSpeed;
            break;
        case GLUT_KEY_DOWN:
            eyez -= controlSpeed;
            centerz -= controlSpeed;
            break;
        case GLUT_KEY_PAGE_DOWN:
            eyey += controlSpeed;
            centery += controlSpeed;
            break;
        case GLUT_KEY_PAGE_UP:
            eyey -= controlSpeed;
            centery -= controlSpeed;
        default:
            return;
    }
    glutPostRedisplay();    // Post a paint request to activate display()
}

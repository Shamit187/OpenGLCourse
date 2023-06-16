#pragma once
#include <GL/glut.h>

void bufferClear(GLfloat* scale, GLfloat* translate, GLfloat* rotate, GLfloat* color){
    scale[0] = 1.0f; scale[1] = 1.0f; scale[2] = 1.0f;
    translate[0] = 0.0f; translate[1] = 0.0f; translate[2] = 0.0f;
    rotate[0] = 0.0f; rotate[1] = 0.0f; rotate[2] = 0.0f; rotate[3] = 0.0f;
    color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f;
}
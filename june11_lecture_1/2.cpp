#include <iostream>
#include <GL/glut.h>

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    /*
    In OpenGL, `glClear(GL_COLOR_BUFFER_BIT)` is a function call 
    used to clear the color buffer of the current rendering context. 
    The color buffer stores the final pixel color values that will be 
    displayed on the screen or rendered to a framebuffer.

    When you call `glClear(GL_COLOR_BUFFER_BIT)`, it indicates that 
    you want to discard the current contents of the color buffer and 
    set all the pixels to a specific color. By default, the color is 
    set to black, but you can change it using `glClearColor()`.

    This function is typically called at the beginning of each frame 
    rendering cycle to ensure that the color buffer is cleared before 
    drawing new objects or scenes. It's essential because it helps 
    prevent artifacts or remnants from previous frames appearing in 
    the current frame.

    By clearing the color buffer, you provide a clean canvas to render 
    your new frame without any interference from previous frames.
    */


}
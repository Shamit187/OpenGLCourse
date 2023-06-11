#include <iostream>
#include <GL/glut.h>

void initGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    /*
    he code glClearColor(0.0f, 0.0f, 0.0f, 1.0f) in OpenGL is 
    used to set the clear color for the color buffer. The 
    function glClearColor() takes four parameters representing 
    the red, green, blue, and alpha components of the clear color, 
    respectively.

    In this specific code snippet, the clear color is set to black. 
    Each component (red, green, blue, and alpha) is set to 0.0f, 
    which represents the minimum intensity for each color channel. 
    The alpha component is set to 1.0f, indicating full opacity.

    By calling glClearColor() and specifying the desired clear 
    color, you are setting the color that will be used to clear 
    the color buffer when you call glClear(GL_COLOR_BUFFER_BIT). 
    In this case, when you clear the color buffer, all pixels will 
    be set to black with full opacity.
    */
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

    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex2f(-0.8f, 0.1f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.2f, 0.7f);
        glVertex2f(-0.8f, 0.7f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-0.7f, -0.6f);
        glVertex2f(-0.1f, -0.6f);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(-0.7f, 0.0f);

        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(-0.9f, -0.7f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.5f, -0.7f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(-0.5f, -0.3f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.9f, -0.3f);
    glEnd();

    glFlush();

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("2");
    glutInitWindowSize(320,320);
    glutInitWindowPosition(50,50);
    glutDisplayFunc(display);
    initGL();
    glutMainLoop();
    return 0;
}
#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

static int make_resources(void)
{
    return 1;
}

static void idle(void)
{
}

static void render(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("LightBend");
    glutDisplayFunc(&render);
    glutIdleFunc(&idle);
	if (!make_resources()) {
        fprintf(stderr, "Failed to load resources\n");
        return 1;
    }

    glutMainLoop();
    return 0;
}
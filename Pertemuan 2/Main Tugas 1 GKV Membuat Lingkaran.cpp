// Nama			: MOHAMMAD IMRON ROSYADI
// NIM			: 24060123140204
// Kelas/Lab	: C/C1

#include <GL/glut.h>
#include <math.h>

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    glPushMatrix();
    #define PI 3.1415926535898
    GLint circle_points = 100;
    int i;
    float angle;
    float scale = 0.5f; // Faktor skala untuk memperkecil lingkaran
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
        for (i = 0; i < circle_points; i++) {
            angle = 2 * PI * i / circle_points;
            glVertex2f(scale * cos(angle), scale * sin(angle));
        }
    glEnd();
    glPopMatrix();
    glFlush();
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Lingkaran Kecil");
    glutDisplayFunc(RenderScene);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glutMainLoop();
    return 0;
}


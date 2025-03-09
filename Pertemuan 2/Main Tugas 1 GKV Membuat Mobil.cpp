// Nama			: MOHAMMAD IMRON ROSYADI
// NIM			: 24060123140204
// Kelas/Lab	: C/C1

#include <GL/glut.h>
#include <math.h>

const double PI = 3.141592653;
const int JUMLAH_TITIK = 60;
const int RADIUS_BAN  = 600;
const int RADIUS_VELG = 200;
const int RADIUS_MATAHARI = 400;

// **Prosedur untuk menggambar lingkaran berwarna**
void drawCircle(float centerX, float centerY, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float sudut = i * (2.0f * PI / JUMLAH_TITIK);
        float x = centerX + radius * cos(sudut);
        float y = centerY + radius * sin(sudut);
        glVertex2f(x / 50.0f, y / 50.0f);
    }
    glEnd();
}

// **Prosedur untuk menggambar matahari**
void drawSun() {
    // **Bola matahari (kuning)**
    drawCircle(40.0f * 50.0f, 40.0f * 50.0f, RADIUS_MATAHARI, 1.0f, 1.0f, 0.0f);

    // **Sinar matahari (garis radial)**
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; i++) {
        float sudut = i * (2.0f * PI / 12);
        float x1 = 40.0f * 50.0f + (RADIUS_MATAHARI + 100) * cos(sudut);
        float y1 = 40.0f * 50.0f + (RADIUS_MATAHARI + 100) * sin(sudut);
        float x2 = 40.0f * 50.0f + (RADIUS_MATAHARI + 400) * cos(sudut);
        float y2 = 40.0f * 50.0f + (RADIUS_MATAHARI + 400) * sin(sudut);
        glVertex2f(x1 / 50.0f, y1 / 50.0f);
        glVertex2f(x2 / 50.0f, y2 / 50.0f);
    }
    glEnd();
}

// **Prosedur untuk menggambar ban dan velg dengan jari-jari**
void drawWheelWithSpokes(float centerX, float centerY) {
    drawCircle(centerX, centerY, RADIUS_BAN, 0.0f, 0.0f, 0.0f);  // Ban luar (hitam)
    drawCircle(centerX, centerY, RADIUS_VELG, 0.5f, 0.5f, 0.5f);  // Velg (abu-abu)

    // **Jari-jari velg (garis radial)**
    glColor3f(0.7f, 0.7f, 0.7f);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float sudut = i * (2.0f * PI / 8);
        float x1 = centerX + 50 * cos(sudut);
        float y1 = centerY + 50 * sin(sudut);
        float x2 = centerX + RADIUS_VELG * cos(sudut);
        float y2 = centerY + RADIUS_VELG * sin(sudut);
        glVertex2f(x1 / 50.0f, y1 / 50.0f);
        glVertex2f(x2 / 50.0f, y2 / 50.0f);
    }
    glEnd();
}

// **Prosedur untuk menggambar latar belakang (langit dan tanah)**
void drawBackground() {
    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-60.0f, -60.0f);
        glVertex2f( 60.0f, -60.0f);
        glVertex2f( 60.0f,  60.0f);
        glVertex2f(-60.0f,  60.0f);
    glEnd();

    glColor3f(0.9f, 0.8f, 0.6f);
    glBegin(GL_QUADS);
        glVertex2f(-60.0f, -60.0f);
        glVertex2f( 60.0f, -60.0f);
        glVertex2f( 60.0f, -40.0f);
        glVertex2f(-60.0f, -40.0f);
    glEnd();
}

// **Prosedur untuk menggambar rangka utama monster truck**
void drawChassis() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-25.0f, -15.0f);
        glVertex2f(-25.0f, -5.0f);
        glVertex2f( 25.0f, -5.0f);
        glVertex2f( 25.0f, -15.0f);
        glVertex2f( 20.0f, -20.0f);
        glVertex2f(-20.0f, -20.0f);
    glEnd();
}

// **Prosedur untuk menggambar kabin**
void drawCabin() {
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-15.0f, -5.0f);
        glVertex2f(  5.0f, -5.0f);
        glVertex2f(  5.0f,  5.0f);
        glVertex2f(-10.0f,  5.0f);
        glVertex2f(-15.0f,  0.0f);
    glEnd();
}

// **Prosedur untuk menggambar kaca depan**
void drawWindshield() {
    glColor3f(0.2f, 0.4f, 0.8f);
    glBegin(GL_POLYGON);
        glVertex2f(-12.0f, -3.0f);
        glVertex2f(  3.0f, -3.0f);
        glVertex2f(  3.0f,  3.0f);
        glVertex2f(-9.0f,  3.0f);
        glVertex2f(-12.0f,  0.0f);
    glEnd();

    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-12.0f, 0.0f);
        glVertex2f(-9.0f, 3.0f);
        glVertex2f(-6.0f, -3.0f);
    glEnd();
}

// **Prosedur untuk menggambar lampu**
void drawHeadlight() {
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-25.0f, -10.0f);
        glVertex2f(-23.0f, -10.0f);
        glVertex2f(-23.0f, -8.0f);
        glVertex2f(-25.0f, -8.0f);
    glEnd();
}

// **Prosedur untuk menggambar knalpot**
void drawExhaust() {
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(6.0f, -5.0f);
        glVertex2f(8.0f, -5.0f);
        glVertex2f(8.0f, 6.0f);
        glVertex2f(6.0f, 6.0f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(8.0f, 3.0f);
        glVertex2f(10.0f, 3.0f);
        glVertex2f(10.0f, 6.0f);
        glVertex2f(8.0f, 6.0f);
    glEnd();
}

// **Prosedur untuk menggambar suspensi**
void drawSuspension() {
    glLineWidth(15.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex2f( 20.0f, -15.0f);
        glVertex2f( 30.0f, -40.0f);
        glVertex2f(-20.0f, -15.0f);
        glVertex2f(-30.0f, -40.0f);
    glEnd();
}

void tampil() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    drawBackground();
    drawSun();
    drawChassis();
    drawCabin();
    drawWindshield();
    drawHeadlight();
    drawExhaust();
    drawSuspension();
    drawWheelWithSpokes( 30.0f * 50.0f, -40.0f * 50.0f);
    drawWheelWithSpokes(-30.0f * 50.0f, -40.0f * 50.0f);
    glPopMatrix();
    glFlush();
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    gluOrtho2D(-60.0, 60.0, -60.0, 60.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Monster Truck Gurun Pasir");
    init();
    glutDisplayFunc(tampil);
    glutMainLoop();
    return 0;
}

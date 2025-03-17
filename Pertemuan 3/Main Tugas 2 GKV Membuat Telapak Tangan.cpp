#include <GL/glut.h>
#include <stdlib.h>

// --- Variabel untuk sendi lengan ---
static int shoulder = 0; // rotasi bahu
static int elbow    = 0; // rotasi siku
static int wrist    = 0; // rotasi pergelangan tangan

// --- Variabel untuk jari (empat jari: index, middle, ring, little) ---
// Masing-masing jari memiliki dua sendi: base (proksimal) dan tip (distal)
static int fingerBase[4] = {0, 0, 0, 0};
static int fingerTip[4]  = {0, 0, 0, 0};

// --- Variabel untuk ibu jari ---
static int thumbBase = 0;
static int thumbTip  = 0;

// --- Konstanta untuk geometri tangan ---
const float palmWidth   = 0.8f;   // lebar telapak
const float palmHeight  = 0.5f;   // tinggi telapak
const float palmDepth   = 0.2f;   // kedalaman telapak

const float fingerProximal = 0.3f;   // panjang segmen proksimal jari
const float fingerDistal   = 0.2f;   // panjang segmen distal jari
const float fingerThickness = 0.08f; // ketebalan jari

// Fungsi inisialisasi OpenGL
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

// Fungsi untuk menggambar lengan, telapak, dan tangan
void drawArmAndHand(void) {
    glPushMatrix();
    // ----------------------------
    // 1. Lengan Atas
    // ----------------------------
    // Asumsikan sendi bahu berada di titik (-1,0,0)
    glTranslatef(-1.0f, 0.0f, 0.0f);
    glRotatef((GLfloat)shoulder, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);

    // Gambar lengan atas sebagai kubus yang diskalakan (memanjang sumbu x)
    glPushMatrix();
    glScalef(2.0f, 0.4f, 0.4f);
    glutWireCube(1.0);
    glPopMatrix();

    // ----------------------------
    // 2. Lengan Bawah
    // ----------------------------
    glTranslatef(1.0f, 0.0f, 0.0f);      // berpindah ke sendi siku
    glRotatef((GLfloat)elbow, 0.0f, 0.0f, 1.0f);
    glTranslatef(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(2.0f, 0.4f, 0.4f);
    glutWireCube(1.0);
    glPopMatrix();

    // ----------------------------
    // 3. Pergelangan Tangan & Telapak
    // ----------------------------
    glTranslatef(1.0f, 0.0f, 0.0f);      // berpindah ke sendi pergelangan tangan
    glRotatef((GLfloat)wrist, 0.0f, 0.0f, 1.0f);

    // Tempatkan telapak sehingga sisi bawahnya berimpit dengan pergelangan tangan.
    // Karena glutWireCube memiliki pusat di tengahnya, kita geser ke atas sebesar palmHeight/2.
    glPushMatrix();
    glTranslatef(0.0f, palmHeight/2, 0.0f);

    // Gambar telapak tangan sebagai sebuah kubus yang diskalakan
    glPushMatrix();
    glScalef(palmWidth, palmHeight, palmDepth);
    glutWireCube(1.0);
    glPopMatrix();

    // ----------------------------
    // 4. Empat Jari (Index, Middle, Ring, Little)
    // ----------------------------
    // Posisi basis jari relatif terhadap pusat telapak (sumbu lokal)
    // Kita atur jari-jari di sepanjang sisi atas telapak (y = palmHeight/2) dengan posisi x berbeda.
    float fingerPosX[4] = { -0.25f, -0.08f, 0.08f, 0.25f };
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        // Pindah ke posisi basis jari (sisi atas telapak)
        glTranslatef(fingerPosX[i], palmHeight/2, 0.0f);
        // Rotasi pada sendi proksimal jari
        glRotatef((GLfloat)fingerBase[i], 0.0f, 0.0f, 1.0f);
        // Gambar segmen proksimal jari
        glPushMatrix();
        glTranslatef(fingerProximal/2, 0.0f, 0.0f);
        glScalef(fingerProximal, fingerThickness, fingerThickness);
        glutWireCube(1.0);
        glPopMatrix();
        // Pindah ke ujung segmen proksimal
        glTranslatef(fingerProximal, 0.0f, 0.0f);
        // Rotasi pada sendi distal jari
        glRotatef((GLfloat)fingerTip[i], 0.0f, 0.0f, 1.0f);
        // Gambar segmen distal jari
        glPushMatrix();
        glTranslatef(fingerDistal/2, 0.0f, 0.0f);
        glScalef(fingerDistal, fingerThickness, fingerThickness);
        glutWireCube(1.0);
        glPopMatrix();
        glPopMatrix();
    }

    // ----------------------------
    // 5. Ibu Jari
    // ----------------------------
    glPushMatrix();
    // Tempatkan ibu jari pada sisi kiri bawah telapak (untuk tangan kanan, ibu jari terletak di sisi kiri)
    glTranslatef(-palmWidth/2, palmHeight/4, 0.0f);
    // Rotasi ibu jari pada sendi proksimal
    glRotatef((GLfloat)thumbBase, 0.0f, 0.0f, 1.0f);
    // Gambar segmen proksimal ibu jari
    glPushMatrix();
    glTranslatef(fingerProximal/2, 0.0f, 0.0f);
    glScalef(fingerProximal, fingerThickness, fingerThickness);
    glutWireCube(1.0);
    glPopMatrix();
    // Pindah ke ujung segmen proksimal
    glTranslatef(fingerProximal, 0.0f, 0.0f);
    // Rotasi pada sendi distal ibu jari
    glRotatef((GLfloat)thumbTip, 0.0f, 0.0f, 1.0f);
    // Gambar segmen distal ibu jari
    glPushMatrix();
    glTranslatef(fingerDistal/2, 0.0f, 0.0f);
    glScalef(fingerDistal, fingerThickness, fingerThickness);
    glutWireCube(1.0);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix(); // selesai dengan telapak dan jari
    glPopMatrix(); // selesai dengan seluruh transformasi lengan & tangan
}

// Fungsi display: menggambar seluruh scene
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // Atur kamera dengan gluLookAt
    gluLookAt(0.0, 0.0, 10.0,   // posisi kamera
              0.0, 0.0, 0.0,    // titik pusat pandang
              0.0, 1.0, 0.0);   // vektor up
    drawArmAndHand();
    glutSwapBuffers();
}

// Fungsi reshape
void reshape(int w, int h) {
    if(h == 0) h = 1;
    glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w/(GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Fungsi keyboard untuk menggerakkan sendi-sendi
// --- Kontrol:
// Lengan:
//   's' / 'S' : putar bahu (positif/negatif)
//   'e' / 'E' : putar siku
//   'w' / 'W' : putar pergelangan tangan
//
// Jari (empat jari):
//   Untuk jari ke-1 (misal: index):
//      Base: '1' naik, '!' turun
//      Tip : '2' naik, '@' turun
//   Jari ke-2 (middle):
//      Base: '3' naik, '#' turun
//      Tip : '4' naik, '$' turun
//   Jari ke-3 (ring):
//      Base: '5' naik, '%' turun
//      Tip : '6' naik, '^' turun
//   Jari ke-4 (little):
//      Base: '7' naik, '&' turun
//      Tip : '8' naik, '*' turun
//
// Ibu jari:
//      Base: '9' naik, '(' turun
//      Tip : '0' naik, ')' turun
//
// Escape (ESC) untuk keluar
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // --- Kontrol Lengan ---
        case 's': shoulder = (shoulder + 5) % 360; break;
        case 'S': shoulder = (shoulder - 5) % 360; break;
        case 'e': elbow = (elbow + 5) % 360; break;
        case 'E': elbow = (elbow - 5) % 360; break;
        case 'w': wrist = (wrist + 5) % 360; break;
        case 'W': wrist = (wrist - 5) % 360; break;

        // --- Kontrol Jari (empat jari) ---
        // Jari ke-1 (Index)
        case '1': fingerBase[0] = (fingerBase[0] + 5) % 360; break;
        case '!': fingerBase[0] = (fingerBase[0] - 5) % 360; break;
        case '2': fingerTip[0] = (fingerTip[0] + 5) % 360; break;
        case '@': fingerTip[0] = (fingerTip[0] - 5) % 360; break;
        // Jari ke-2 (Middle)
        case '3': fingerBase[1] = (fingerBase[1] + 5) % 360; break;
        case '#': fingerBase[1] = (fingerBase[1] - 5) % 360; break;
        case '4': fingerTip[1] = (fingerTip[1] + 5) % 360; break;
        case '$': fingerTip[1] = (fingerTip[1] - 5) % 360; break;
        // Jari ke-3 (Ring)
        case '5': fingerBase[2] = (fingerBase[2] + 5) % 360; break;
        case '%': fingerBase[2] = (fingerBase[2] - 5) % 360; break;
        case '6': fingerTip[2] = (fingerTip[2] + 5) % 360; break;
        case '^': fingerTip[2] = (fingerTip[2] - 5) % 360; break;
        // Jari ke-4 (Little)
        case '7': fingerBase[3] = (fingerBase[3] + 5) % 360; break;
        case '&': fingerBase[3] = (fingerBase[3] - 5) % 360; break;
        case '8': fingerTip[3] = (fingerTip[3] + 5) % 360; break;
        case '*': fingerTip[3] = (fingerTip[3] - 5) % 360; break;

        // --- Kontrol Ibu Jari ---
        case '9': thumbBase = (thumbBase + 5) % 360; break;
        case '(': thumbBase = (thumbBase - 5) % 360; break;
        case '0': thumbTip = (thumbTip + 5) % 360; break;
        case ')': thumbTip = (thumbTip - 5) % 360; break;

        case 27: // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tangan dengan Jari-Jari");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

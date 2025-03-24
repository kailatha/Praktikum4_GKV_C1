
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


float angle=0.0, deltaAngle = 0.0, ratio;
float x=0.0f,y=1.75f,z=15.0f; // posisi awal kamera
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int bitmapHeight=12;


void Reshape(int w1, int h1){
// Fungsi reshape
if(h1 == 0) h1 = 1;
w = w1;
h = h1;
ratio = 1.0f * w / h;
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0, 0, w, h);
gluPerspective(45,ratio,0.1,1000);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(
x, y, z,
x + lx,y + ly,z + lz,
0.0f,1.0f,0.0f);
}

void orientMe(float ang){
// Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
lx = sin(ang);
lz = -cos(ang);
glLoadIdentity();
gluLookAt(x, y, z,
x + lx,y + ly,z + lz,
0.0f,1.0f,0.0f);
}

void moveMeFlat(int i){
// Fungsi ini untuk maju mundur kamera
x = x + i*(lx)*0.05;
z = z + i*(lz)*0.05;
glLoadIdentity();

gluLookAt(x, y, z,
x + lx,y + ly,z + lz,
0.0f,1.0f,0.0f);
}

void Grid() {
    const float Z_MIN = -50, Z_MAX = 50;
    const float X_MIN = -50, X_MAX = 50;
    const float Y_POSITION = -0.2; 
    
    // Tambahkan alas berwarna hijau
    glColor3f(0.2, 0.8, 0.2); // Warna hijau
    glBegin(GL_QUADS);
        glVertex3f(X_MIN, Y_POSITION, Z_MIN);
        glVertex3f(X_MIN, Y_POSITION, Z_MAX);
        glVertex3f(X_MAX, Y_POSITION, Z_MAX);
        glVertex3f(X_MAX, Y_POSITION, Z_MIN);
    glEnd();
}


void Ban(float posX, float posY, float posZ) {
    // Ban luar (hitam)
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Warna hitam
    glTranslatef(posX, posY, posZ);
    glRotatef(180, 0, 1, 0);
    glutSolidTorus(0.2f, 0.41f, 20, 20);
    glPopMatrix();
    
    // Velg (perak)
    glPushMatrix();
    glColor3f(0.7f, 0.7f, 0.7f); // Warna perak
    glTranslatef(posX, posY, posZ);
    glRotatef(180, 0, 1, 0);
    glutSolidTorus(0.1f, 0.2f, 16, 16);
    
    // Pusat velg
    glColor3f(0.7f, 0.7f, 0.7f);
    glutSolidSphere(0.1f, 12, 12);
    
    // Jari-jari velg
    glColor3f(0.7f, 0.7f, 0.7f);
    for (int i = 0; i < 5; i++) {
        glPushMatrix();
        glRotatef(i * 72, 0, 0, 1);
        glTranslatef(0.3f, 0.0f, 0.0f);
        glScalef(0.6f, 0.1f, 0.05f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
}

void Mobil()
{
    // Badan bawah mobil (chassis)
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f);// Warna pink
    glTranslatef(0.0f, 0.5f, 0.0f);
    glScalef(5.0f, 0.5f, 2.4f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Badan tengah mobil
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f); // Warna pink
    glTranslatef(0.0f, 1.0f, 0.0f);
    glScalef(4.5f, 0.6f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bagian depan (kap mesin)
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f); // Warna pink
    glTranslatef(1.8f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
        // Bagian atas kap
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(-1.8f, 0.2f, -1.1f);
        glVertex3f(-1.8f, 0.2f, 1.1f);
        
        // Bagian depan kap
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(0.7f, -0.3f, -1.1f);
        glVertex3f(0.7f, -0.3f, 1.1f);
        
        // Sisi kanan kap
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(-1.8f, 0.2f, 1.1f);
        glVertex3f(-1.8f, -0.3f, 1.1f);
        glVertex3f(0.7f, -0.3f, 1.1f);
        
        // Sisi kiri kap
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(-1.8f, 0.2f, -1.1f);
        glVertex3f(-1.8f, -0.3f, -1.1f);
        glVertex3f(0.7f, -0.3f, -1.1f);
    glEnd();
    glPopMatrix();
    
     // Bagian belakang mobil (trunk)
    glPushMatrix();
    glColor3f(1.0f, 0.5f, 0.9f); // Warna pink
    glTranslatef(-1.8f, 0.8f, 0.0f);
    glBegin(GL_QUADS);
        // Bagian atas
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(-0.7f, 0.2f, -1.1f);
        glVertex3f(-0.7f, 0.2f, 1.1f);
        
        // Bagian belakang
        glVertex3f(-0.7f, 0.2f, 1.1f);
        glVertex3f(-0.7f, 0.2f, -1.1f);
        glVertex3f(-0.7f, -0.3f, -1.1f);
        glVertex3f(-0.7f, -0.3f, 1.1f);
        
        // Sisi kanan
        glVertex3f(-0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, 0.2f, 1.1f);
        glVertex3f(0.7f, -0.3f, 1.1f);
        glVertex3f(-0.7f, -0.3f, 1.1f);
        
        // Sisi kiri
        glVertex3f(-0.7f, 0.2f, -1.1f);
        glVertex3f(0.7f, 0.2f, -1.1f);
        glVertex3f(0.7f, -0.3f, -1.1f);
        glVertex3f(-0.7f, -0.3f, -1.1f);
    glEnd();
    glPopMatrix();
    
    // Kabin mobil
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Warna hitam
    glTranslatef(0.0f, 1.7f, 0.0f);
    glBegin(GL_QUADS);
        // Atap
        glVertex3f(-1.5f, 0.4f, 1.0f);
        glVertex3f(-1.5f, 0.4f, -1.0f);
        glVertex3f(1.0f, 0.4f, -1.0f);
        glVertex3f(1.0f, 0.4f, 1.0f);
        
        // Depan kaca (windshield)
        glVertex3f(1.0f, 0.4f, 1.0f);
        glVertex3f(1.0f, 0.4f, -1.0f);
        glVertex3f(1.8f, -0.7f, -1.0f);
        glVertex3f(1.8f, -0.7f, 1.0f);
        
        // Belakang kaca
        glVertex3f(-1.5f, 0.4f, 1.0f);
        glVertex3f(-1.5f, 0.4f, -1.0f);
        glVertex3f(-1.8f, -0.7f, -1.0f);
        glVertex3f(-1.8f, -0.7f, 1.0f);
        
        // Kiri kaca
        glVertex3f(-1.5f, 0.4f, -1.0f);
        glVertex3f(1.0f, 0.4f, -1.0f);
        glVertex3f(1.8f, -0.7f, -1.0f);
        glVertex3f(-1.8f, -0.7f, -1.0f);
        
        // Kanan kaca
        glVertex3f(-1.5f, 0.4f, 1.0f);
        glVertex3f(1.0f, 0.4f, 1.0f);
        glVertex3f(1.8f, -0.7f, 1.0f);
        glVertex3f(-1.8f, -0.7f, 1.0f);
    glEnd();
    glPopMatrix();
    
    // Panggil fungsi Ban untuk keempat ban
    Ban(1.8f, 0.35f, 1.2f);  // Depan kanan
    Ban(1.8f, 0.35f, -1.2f); // Depan kiri
    Ban(-1.8f, 0.35f, 1.2f); // Belakang kanan
    Ban(-1.8f, 0.35f, -1.2f); // Belakang kiri
    
    // Lampu depan kanan
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
    glTranslatef(2.5f, 0.6f, 0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Lampu depan kiri
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Warna kuning
    glTranslatef(2.5f, 0.6f, -0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Grille depan
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Warna hitam
    glTranslatef(2.5f, 0.6f, 0.0f);
    glScalef(0.1f, 0.2f, 1.0f);
    glutSolidCube(1.0f);
    
    // Tambahan detail pada grille
    glColor3f(0.7f, 0.7f, 0.7f); // Warna perak
    for (int i = -4; i <= 4; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, i * 0.1f);
        glScalef(1.1f, 0.8f, 0.03f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }
    glPopMatrix();
    
    // Lampu belakang kanan
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
    glTranslatef(-2.5f, 0.6f, 0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Lampu belakang kiri
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Warna merah
    glTranslatef(-2.5f, 0.6f, -0.8f);
    glScalef(0.15f, 0.15f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bumper depan
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); // Warna abu-abu gelap
    glTranslatef(2.5f, 0.3f, 0.0f);
    glScalef(0.2f, 0.3f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Bumper belakang
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); // Warna abu-abu gelap
    glTranslatef(-2.5f, 0.3f, 0.0f);
    glScalef(0.2f, 0.3f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    
    // Knalpot
    glPushMatrix();
    glColor3f(0.5f, 0.5f, 0.5f); // Warna perak
    glTranslatef(-2.6f, 0.3f, -0.6f);
    glRotatef(90, 0, 1, 0);
    GLUquadricObj *quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.06, 0.06, 0.3, 10, 10);
    glPopMatrix();
}

void Pohon3D(float posX, float posY, float posZ, float scale) {
    // Batang pohon
    glPushMatrix();
    glTranslatef(posX, posY, posZ);
    glScalef(scale, scale, scale);
    
    // Batang utama
    glColor3f(0.55f, 0.27f, 0.07f); // Warna coklat
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    GLUquadricObj *quadratic = gluNewQuadric();
    gluCylinder(quadratic, 0.2, 0.15, 1.5, 12, 12);
    glPopMatrix();
    
    // Daun pohon (bentuk kerucut)
    glColor3f(0.0f, 0.5f, 0.0f); // Warna hijau
    
    // Lapisan daun bawah
    glPushMatrix();
    glTranslatef(0.0f, 0.7f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.8, 1.0, 12, 12);
    glPopMatrix();
    
    // Lapisan daun tengah
    glPushMatrix();
    glTranslatef(0.0f, 1.2f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.6, 0.8, 12, 12);
    glPopMatrix();
    
    // Lapisan daun atas
    glPushMatrix();
    glTranslatef(0.0f, 1.6f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(0.4, 0.6, 12, 12);
    glPopMatrix();
    
    glPopMatrix();
}

void display() {
    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaAngle) {
        angle += deltaAngle;
        orientMe(angle);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    Grid();
    
    Mobil();
    
    Pohon3D(-5.0f, 0.0f, -8.0f, 1.0f);   // Pohon di kiri belakang
    Pohon3D(5.0f, 0.0f, -7.0f, 1.2f);    // Pohon di kanan belakang
    Pohon3D(-7.0f, 0.0f, 7.0f, 0.8f);    // Pohon di kiri depan
    Pohon3D(8.0f, 0.0f, 5.0f, 1.5f);     // Pohon di kanan depan
    Pohon3D(0.0f, 0.0f, -15.0f, 2.0f);   // Pohon besar jauh di belakang
    Pohon3D(-12.0f, 0.0f, -3.0f, 1.3f);  // Pohon tambahan di kiri
    Pohon3D(10.0f, 0.0f, -10.0f, 0.9f);  // Pohon kecil di kanan belakang
    
    glutSwapBuffers();
    glFlush();
}

void pressKey(int key, int x, int y) {

    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.005f; break; 
        case GLUT_KEY_RIGHT : deltaAngle = 0.005f; break; 
        case GLUT_KEY_UP : deltaMove = 1; break;
        case GLUT_KEY_DOWN : deltaMove = -1; break;
    }
}

void releaseKey(int key, int x, int y) {
switch (key) {
case GLUT_KEY_LEFT :
if (deltaAngle < 0.0f)
deltaAngle = 0.0f;
break;
case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
deltaAngle = 0.0f;
break;
case GLUT_KEY_UP : if (deltaMove > 0)
deltaMove = 0;
break;
case GLUT_KEY_DOWN : if (deltaMove < 0)
deltaMove = 0;
break;
}
}
// Variable untuk pencahayaan

const GLfloat light_ambient[] = { 0.5f, 0.5f, 0.5f, 0.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 20.0f, 10.0f, 1.0f };
const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

void lighting(){
// Fungsi mengaktifkan pencahayaan
glEnable(GL_DEPTH_TEST);
glDepthFunc(GL_LESS);
glEnable(GL_LIGHT0);
glEnable(GL_NORMALIZE);
glEnable(GL_COLOR_MATERIAL);
glEnable(GL_LIGHTING);
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void init(void){
    // Atur warna background menjadi biru langit
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Warna biru langit (sky blue)
    
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // Aktifkan transparansi
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

//Fungsi Main
int main(int argc, char **argv){
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
glutInitWindowPosition(100,100);
glutInitWindowSize(640,480);
glutCreateWindow("3D Mobil Lighting");
glutIgnoreKeyRepeat(1); 
glutSpecialFunc(pressKey);
glutSpecialUpFunc(releaseKey);
glutDisplayFunc(display);

glutIdleFunc(display); 

glutReshapeFunc(Reshape);
lighting();
init();
glutMainLoop();
return(0);
}

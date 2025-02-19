#include <GL/freeglut.h>
#include <stdlib.h>

int winWidth = 800, winHeight = 600;

void drawPyramid() {
    glBegin(GL_TRIANGLES);
    // Face frontal: vertices: (0,1,0), (-1,-1,1) e (1,-1,1)
    glNormal3f(0.0f, 0.447f, 0.894f);
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Face direita: vertices: (0,1,0), (1,-1,1) e (1,-1,-1)
    glNormal3f(0.894f, 0.447f, 0.0f);
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Face de trás: vertices: (0,1,0), (1,-1,-1) e (-1,-1,-1)
    glNormal3f(0.0f, 0.447f, -0.894f);
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Face esquerda: vertices: (0,1,0), (-1,-1,-1) e (-1,-1,1)
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    // Base
    glBegin(GL_QUADS);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
}

void drawCube() {
    glutSolidCube(2.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int vpWidth = winWidth / 3;
    int vpHeight = winHeight / 2;

    // Viewport da esquerda
    glViewport(0, winHeight - vpHeight, vpWidth, vpHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    drawPyramid();

    // Viewport central
    glViewport(vpWidth, winHeight - vpHeight, vpWidth, vpHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 0.0, -1.0);
    glColor3f(0.0, 1.0, 0.0);
    drawPyramid();

    // Viewport da direita
    glViewport(2 * vpWidth, winHeight - vpHeight, vpWidth, vpHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 0.0, 0.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    drawPyramid();

    glViewport(0, 0, winWidth, winHeight / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)winWidth/(winHeight/2), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 8.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Cubo
    glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        glColor3f(1.0, 1.0, 0.0);
        drawCube();
    glPopMatrix();

    // Pirâmide
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        glColor3f(1.0, 0.0, 1.0);
        drawPyramid();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, winWidth, winHeight);
}

void initGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // ativa iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // define os parâmetros da luz
    GLfloat lightAmbient[]  = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat lightSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat lightPosition[] = {0.0f, 5.0f, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    // permite que as cores definidas com glColor sejam aplicadas aos materiais
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // define propriedades especulares do material e coeficiente de brilho
    GLfloat mat_specular[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Atividade: Iluminação");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();

    glutMainLoop();
    return 0;
}

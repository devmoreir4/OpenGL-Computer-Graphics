#include <GL/freeglut.h>
#include <stdlib.h>

int winWidth = 800, winHeight = 600;

void drawPyramid() {
    glBegin(GL_TRIANGLES);
    // face frontal
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    // face direita
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    // face de tr�s
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    // face esquerda
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    // base (quadril�tero)
    glBegin(GL_QUADS);
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

    // PARTE 1: objeto em 3 viewports com proje��o ORTOGR�FICA

    int vpWidth = winWidth / 3;
    int vpHeight = winHeight / 2;

    // viewport da esquerda: c�mera em posi��o (5,5,5)
    glViewport(0, winHeight - vpHeight, vpWidth, vpHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0); // proje��o ortogr�fica
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0,   // posi��o da c�mera
              0.0, 0.0, 0.0,   // alvo
              0.0, 1.0, 0.0);  // up

    glColor3f(1.0, 0.0, 0.0);
    drawPyramid();

    // viewport central: vista de cima
    glViewport(vpWidth, winHeight - vpHeight, vpWidth, vpHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 0.0,   // posi��o da c�mera
              0.0, 0.0, 0.0,   // alvo
              0.0, 0.0, -1.0); // up (vetor up para diferenciar a vista)
    glColor3f(0.0, 1.0, 0.0);
    drawPyramid();

    // viewport da direita: vista lateral
    glViewport(2 * vpWidth, winHeight - vpHeight, vpWidth, vpHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 0.0, 0.0,   // posi��o da c�mera
              0.0, 0.0, 0.0,   // alvo
              0.0, 1.0, 0.0);  // up
    glColor3f(0.0, 0.0, 1.0);
    drawPyramid();

    // PARTE 2: dois objetos com proje��o PERSPECTIVA

    glViewport(0, 0, winWidth, winHeight / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)winWidth/(winHeight/2), 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // definindo uma c�mera p/ ver ambos os objetos
    gluLookAt(0.0, 3.0, 8.0,   // posi��o da c�mera
              0.0, 0.0, 0.0,   // alvo
              0.0, 1.0, 0.0);  // up

    // cubo
    glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        glColor3f(1.0, 1.0, 0.0);
        drawCube();
    glPopMatrix();

    // pir�mide
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        glColor3f(1.0, 0.0, 1.0);
        drawPyramid();
    glPopMatrix();

    glutSwapBuffers();
}

// fun��o reshape: atualiza as dimens�es da janela e as vari�veis globais
void reshape(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, winWidth, winHeight);
}

void initGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // double buffering, RGBA e buffer de profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Atividade: Viewports e Projecao");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();

    glutMainLoop();
    return 0;
}

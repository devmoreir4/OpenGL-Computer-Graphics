#include <GL/freeglut.h>
#include <iostream>

using namespace std;

int selectedObject = 1; // 1: Cubo, 2: Pir�mide
int transformation = 0; // 0: Nenhuma, 1: Transla��o, 2: Escala, 3: Rota��o, 4: Reflex�o, 5: Cisalhamento
float angle = 0.0f; // �ngulo de rota��o

void drawCube() {
    glutSolidCube(1.0);
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // Face frontal
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    // Face direita
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);

    // Face esquerda
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Face traseira
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);

    glEnd();

    glBegin(GL_QUADS);
    // Base da pir�mide
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 3.0,  // Posi��o da c�mera
              0.0, 0.0, 0.0,  // Ponto para onde olha
              0.0, 1.0, 0.0); // Dire��o "up"

    // transforma��es
    switch (transformation) {
        case 1: glTranslatef(1.0f, 0.0f, 0.0f); break;
        case 2: glScalef(1.5f, 1.5f, 1.5f); break;
        case 3: glRotatef(angle, 0.0f, 1.0f, 0.0f); break;
        case 4: glScalef(-1.0f, 1.0f, 1.0f); break;
        case 5: {
            GLfloat shearMatrix[16] = {
                1.0f, 0.5f, 0.0f, 0.0f,
                0.5f, 1.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
            };
            glMultMatrixf(shearMatrix);
            break;
        }
    }

    if (selectedObject == 1) drawCube();
    else drawPyramid();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float)w / (float)h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, ratio, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void menu(int option) {
    if (option == 6) exit(0);
    transformation = option;
    glutPostRedisplay();
}

void objectMenu(int option) {
    selectedObject = option;
    glutPostRedisplay();
}

void timer(int value) {
    angle += 1.0f;
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transforma��es 3D");

    glEnable(GL_DEPTH_TEST);

    // menus
    int transformationMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Transla��o", 1);
    glutAddMenuEntry("Escala", 2);
    glutAddMenuEntry("Rota��o", 3);
    glutAddMenuEntry("Reflex�o", 4);
    glutAddMenuEntry("Cisalhamento", 5);
    glutAddMenuEntry("Sair", 6);

    int objectMenuID = glutCreateMenu(objectMenu);
    glutAddMenuEntry("Cubo", 1);
    glutAddMenuEntry("Pir�mide", 2);

    glutCreateMenu(menu);
    glutAddSubMenu("Selecionar Objeto", objectMenuID);
    glutAddSubMenu("Transforma��es", transformationMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}

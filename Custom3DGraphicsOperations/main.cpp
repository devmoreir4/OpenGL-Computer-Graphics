#include <GL/freeglut.h>
#include <iostream>

using namespace std;

int selectedObject = 1; // 1: Cubo, 2: Pirâmide
int transformation = 0; // 0: Nenhuma, 1: Translação, 2: Escala, 3: Rotação, 4: Reflexão, 5: Cisalhamento
float angle = 0.0f; // Ângulo de rotação

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
    // Base da pirâmide
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, 3.0,  // Posição da câmera
              0.0, 0.0, 0.0,  // Ponto para onde olha
              0.0, 1.0, 0.0); // Direção "up"

    // transformações
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
    glutCreateWindow("Transformações 3D");

    glEnable(GL_DEPTH_TEST);

    // menus
    int transformationMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Translação", 1);
    glutAddMenuEntry("Escala", 2);
    glutAddMenuEntry("Rotação", 3);
    glutAddMenuEntry("Reflexão", 4);
    glutAddMenuEntry("Cisalhamento", 5);
    glutAddMenuEntry("Sair", 6);

    int objectMenuID = glutCreateMenu(objectMenu);
    glutAddMenuEntry("Cubo", 1);
    glutAddMenuEntry("Pirâmide", 2);

    glutCreateMenu(menu);
    glutAddSubMenu("Selecionar Objeto", objectMenuID);
    glutAddSubMenu("Transformações", transformationMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}

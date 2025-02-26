#include <GL/freeglut.h>
#include <stdlib.h>

int winWidth = 800, winHeight = 600;
float angle = 0.0f;

void initGL() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Habilitar iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[]     = { 0.0f, 5.0f, 5.0f, 1.0f };
    GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat lightSpecular[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);
        // Face frontal
        glNormal3f(0.0f, 0.4472f, 0.8944f);
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        // Face direita
        glNormal3f(0.8944f, 0.4472f, 0.0f);
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        // Face traseira
        glNormal3f(0.0f, 0.4472f, -0.8944f);
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        // Face esquerda
        glNormal3f(-0.8944f, 0.4472f, 0.0f);
        glVertex3f( 0.0f,  1.0f,  0.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    glBegin(GL_QUADS);
        // Base
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
}

void drawSphere() {
    // glutSolidSphere(raio, slices, stacks)
    glutSolidSphere(1.0, 40, 40);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configurar projeção perspectiva
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)winWidth / (float)winHeight, 1.0, 100.0);

    // Configurar a visualização
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 8.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Rotacionar a cena
    glRotatef(angle, 0.0f, 1.0f, 0.0f);

    // Objeto com renderização de intensidade constante (flat shading)
    glPushMatrix();
        glTranslatef(-2.0f, 0.0f, 0.0f);
        glShadeModel(GL_FLAT);
        glColor3f(1.0, 0.0, 0.0); // red
        drawPyramid();
    glPopMatrix();

    // Objeto com renderização Gouraud (smooth shading)
    glPushMatrix();
        glTranslatef(2.0f, 0.0f, 0.0f);
        glShadeModel(GL_SMOOTH);
        glColor3f(0.0, 0.0, 1.0); // blue
        drawSphere();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, winWidth, winHeight);
}

void idle() {
    angle += 0.2f;
    if (angle > 360.0f)
        angle -= 360.0f;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Renderização: Intensidade Constante e Gouraud");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    initGL();
    glutMainLoop();
    return 0;
}

#include <GL/freeglut.h>
#include <stdlib.h>

enum ObjectType {
    OBJ_CUBE,
    OBJ_PYRAMID
};

ObjectType currentObject = OBJ_CUBE;

float accumTranslateX = 0.0f, accumTranslateY = 0.0f, accumTranslateZ = 0.0f;
float accumScaleX = 1.0f, accumScaleY = 1.0f, accumScaleZ = 1.0f;
float accumRotationAngle = 0.0f; // em graus
float shearFactor = 0.0f;        // fator de cisalhamento em X com relacao a Y
bool reflectFlag = false;        // se true, aplica reflexao no eixo X

void drawCube() {
    glutSolidCube(1.0);
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);
    // face frontal
    glVertex3f( 0.0f,  1.0f,  0.0f); // vertice superior
    glVertex3f(-1.0f, -1.0f,  1.0f); // base esquerda
    glVertex3f( 1.0f, -1.0f,  1.0f); // base direita

    // face direita
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // face de tras
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // face esquerda
    glVertex3f( 0.0f,  1.0f,  0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();

    // base (quadrilatero)
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // config camera
    gluLookAt(3.0, 3.0, 5.0,   // posicao do olho
              0.0, 0.0, 0.0,   // para onde olhar
              0.0, 1.0, 0.0);  // vetor "up"

    glPushMatrix();

    // transformacoes acumuladas
    glTranslatef(accumTranslateX, accumTranslateY, accumTranslateZ);
    glRotatef(accumRotationAngle, 0.0f, 1.0f, 0.0f);
    glScalef(accumScaleX, accumScaleY, accumScaleZ);

    // se ativa, inverte o eixo X
    if(reflectFlag) {
        glScalef(-1.0f, 1.0f, 1.0f);
    }

    // aplica o cisalhamento se o fator for diferente de zero
    if(shearFactor != 0.0f) {
        GLfloat shearMatrix[16] = {
            1.0f, shearFactor, 0.0f, 0.0f,
            0.0f, 1.0f,       0.0f, 0.0f,
            0.0f, 0.0f,       1.0f, 0.0f,
            0.0f, 0.0f,       0.0f, 1.0f
        };
        glMultMatrixf(shearMatrix);
    }

    switch(currentObject) {
        case OBJ_CUBE:
            drawCube();
            break;
        case OBJ_PYRAMID:
            drawPyramid();
            break;
    }
    glPopMatrix();

    glutSwapBuffers();
}

// mudancas no tamanho da janela
void reshape(int w, int h) {
    if(h == 0) h = 1; // evita divisao por zero
    float aspect = (float)w / h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void objectMenu(int option) {
    currentObject = (ObjectType) option;
    glutPostRedisplay();
}

void transformMenu(int option) {
    switch(option) {
        case 1: // translacao
            accumTranslateX += 0.2f;
            accumTranslateY += 0.2f;
            break;
        case 2: // escala
            accumScaleX *= 1.1f;
            accumScaleY *= 1.1f;
            accumScaleZ *= 1.1f;
            break;
        case 3: // rotacao
            accumRotationAngle += 15.0f;
            break;
        case 4: // reflexao (toggle)
            reflectFlag = !reflectFlag;
            break;
        case 5: // cisalhamento
            shearFactor += 0.1f;
            break;
        case 6: // reset
            accumTranslateX = accumTranslateY = accumTranslateZ = 0.0f;
            accumScaleX = accumScaleY = accumScaleZ = 1.0f;
            accumRotationAngle = 0.0f;
            shearFactor = 0.0f;
            reflectFlag = false;
            break;
    }
    glutPostRedisplay();
}

void mainMenu(int option) {
    if(option == 0)
        exit(0);
}

void initGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    // double buffering, modo RGBA e profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformacoes 3D Acumulativas");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();

    // submenu objeto
    int submenu_object = glutCreateMenu(objectMenu);
    glutAddMenuEntry("Cubo", OBJ_CUBE);
    glutAddMenuEntry("Piramide", OBJ_PYRAMID);

    // submenu transformacoes acumulativas
    int submenu_transform = glutCreateMenu(transformMenu);
    glutAddMenuEntry("Translacao", 1);
    glutAddMenuEntry("Escala", 2);
    glutAddMenuEntry("Rotacao", 3);
    glutAddMenuEntry("Reflexao", 4);
    glutAddMenuEntry("Cisalhamento", 5);
    glutAddMenuEntry("Reset", 6);

    // main menu
    glutCreateMenu(mainMenu);
    glutAddSubMenu("Selecionar Objeto", submenu_object);
    glutAddSubMenu("Transformacoes Acumulativas", submenu_transform);
    glutAddMenuEntry("Sair", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}

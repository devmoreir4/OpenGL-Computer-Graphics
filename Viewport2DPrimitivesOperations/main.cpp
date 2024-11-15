#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

struct Ponto {
    float x, y;
};

Ponto ponto = { -0.5f, 0.5f }; // Ponto inicial
Ponto linha[2] = { { -0.5f, -0.5f }, { 0.5f, -0.5f } }; // Linha inicial
Ponto poligono[4] = { { 0.0f, 0.0f }, { 0.2f, 0.0f }, { 0.2f, 0.2f }, { 0.0f, 0.2f } }; // Polígono inicial

Ponto pontoAlterado = ponto;
Ponto linhaAlterada[2] = { linha[0], linha[1] };
Ponto poligonoAlterado[4] = { poligono[0], poligono[1], poligono[2], poligono[3] };

// Desenhar primitivas
void desenhaPonto(const Ponto& p) {
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2f(p.x, p.y);
    glEnd();
}

void desenhaLinha(const Ponto linha[]) {
    glBegin(GL_LINES);
    glVertex2f(linha[0].x, linha[0].y);
    glVertex2f(linha[1].x, linha[1].y);
    glEnd();
}

void desenhaPoligono(const Ponto poligono[], int numVertices) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; i++) {
        glVertex2f(poligono[i].x, poligono[i].y);
    }
    glEnd();
}

// Funções de transformação
void transladar(Ponto objeto[], int numVertices, float tx, float ty) {
    for (int i = 0; i < numVertices; i++) {
        objeto[i].x += tx;
        objeto[i].y += ty;
    }
}

void rotacionar(Ponto objeto[], int numVertices, float angulo) {
    float rad = angulo * M_PI / 180.0f;
    for (int i = 0; i < numVertices; i++) {
        float xNovo = objeto[i].x * cos(rad) - objeto[i].y * sin(rad);
        float yNovo = objeto[i].x * sin(rad) + objeto[i].y * cos(rad);
        objeto[i].x = xNovo;
        objeto[i].y = yNovo;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Viewport esquerda: Figuras originais
    glViewport(0, 0, 250, 500);
    glColor3f(1.0, 0.0, 0.0);
    desenhaPonto(ponto);
    glColor3f(0.0, 1.0, 0.0);
    desenhaLinha(linha);
    glColor3f(0.0, 0.0, 1.0);
    desenhaPoligono(poligono, 4);

    glViewport(250, 0, 700, 600);
    glColor3f(1.0, 0.0, 0.0);
    desenhaPonto(pontoAlterado);
    glColor3f(0.0, 1.0, 0.0);
    desenhaLinha(linhaAlterada);
    glColor3f(0.0, 0.0, 1.0);
    desenhaPoligono(poligonoAlterado, 4);

    glFlush();
}

void inicializar() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void menuContexto(int option) {
    if (option == 1) {
        transladar(linhaAlterada, 2, 0.2f, 0.0f);  // Translação para a direita
        transladar(poligonoAlterado, 4, 0.2f, 0.0f);  // Translação para a direita
        transladar(&pontoAlterado, 1, 0.2f, 0.0f);  // Translação do ponto
    } else if (option == 2) {
        rotacionar(linhaAlterada, 2, 45.0f);  // Rotação de 45 graus
        rotacionar(poligonoAlterado, 4, 45.0f);  // Rotação de 45 graus
        rotacionar(&pontoAlterado, 1, 45.0f);  // Rotação do ponto
    }

    glutPostRedisplay(); // Redesenha as viewports
}

void criaMenu() {
    glutCreateMenu(menuContexto);
    glutAddMenuEntry("Transladar", 1);
    glutAddMenuEntry("Rotacionar", 2);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        criaMenu();
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(850, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformações com Viewports");

    inicializar();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

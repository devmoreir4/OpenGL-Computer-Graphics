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

void escalar(Ponto objeto[], int numVertices, float sx, float sy) {
    for (int i = 0; i < numVertices; i++) {
        objeto[i].x *= sx;
        objeto[i].y *= sy;
    }
}

void cisalhar(Ponto objeto[], int numVertices, float shearX, float shearY) {
    for (int i = 0; i < numVertices; i++) {
        float xNovo = objeto[i].x + shearX * objeto[i].y;
        float yNovo = objeto[i].y + shearY * objeto[i].x;
        objeto[i].x = xNovo;
        objeto[i].y = yNovo;
    }
}

void espelhar(Ponto objeto[], int numVertices, bool eixoX, bool eixoY) {
    for (int i = 0; i < numVertices; i++) {
        if (eixoX) {
            objeto[i].y = -objeto[i].y;
        }
        if (eixoY) {
            objeto[i].x = -objeto[i].x;
        }
    }
}

// Desenhar as duas viewports
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Viewport esquerda: Figuras originais
    glViewport(0, 0, 250, 500);
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    desenhaPonto(ponto);
    glColor3f(0.0, 1.0, 0.0); // Verde
    desenhaLinha(linha);
    glColor3f(0.0, 0.0, 1.0); // Azul
    desenhaPoligono(poligono, 4);

    // Viewport direita: Figuras transformadas
    glViewport(250, 0, 250, 500);
    glColor3f(1.0, 0.0, 0.0); // Vermelho
    desenhaPonto(pontoAlterado);
    glColor3f(0.0, 1.0, 0.0); // Verde
    desenhaLinha(linhaAlterada);
    glColor3f(0.0, 0.0, 1.0); // Azul
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
        // Aplica translação
        transladar(linhaAlterada, 2, 0.2f, 0.0f);  // Translação para a direita
        transladar(poligonoAlterado, 4, 0.2f, 0.0f);  // Translação para a direita
    } else if (option == 2) {
        // Aplica rotação
        rotacionar(linhaAlterada, 2, 45.0f);  // Rotação de 45 graus
        rotacionar(poligonoAlterado, 4, 45.0f);  // Rotação de 45 graus
    } else if (option == 3) {
        // Aplica escala
        escalar(poligonoAlterado, 4, 1.5f, 1.5f);  // Escala de 1.5x
        escalar(linhaAlterada, 2, 1.5f, 1.5f);  // Escala de 1.5x
    } else if (option == 4) {
        // Aplica cisalhamento
        cisalhar(poligonoAlterado, 4, 0.2f, 0.0f);  // Cisalhamento X
        cisalhar(linhaAlterada, 2, 0.2f, 0.0f);  // Cisalhamento X
    } else if (option == 5) {
        // Aplica espelhamento
        espelhar(poligonoAlterado, 4, true, false);  // Espelhamento no eixo Y
        espelhar(linhaAlterada, 2, true, false);  // Espelhamento no eixo Y
    }

    glutPostRedisplay();
}

void criaMenu() {
    glutCreateMenu(menuContexto);
    glutAddMenuEntry("Transladar", 1);
    glutAddMenuEntry("Rotacionar", 2);
    glutAddMenuEntry("Escalar", 3);
    glutAddMenuEntry("Cisalhar", 4);
    glutAddMenuEntry("Espelhar", 5);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformações com Viewports");

    inicializar();
    criaMenu();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

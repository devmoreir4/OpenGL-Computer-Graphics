#include <iostream>
#include <cmath>
#include <vector>
#include <GL/glut.h>

using namespace std;

struct Ponto {
    float x, y;
};

vector<Ponto> objeto;
int opcao = 0;

void desenhaObjeto() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);

    for (auto &ponto : objeto) {
        glVertex2f(ponto.x, ponto.y);
    }

    glEnd();
    glFlush();
}

void transladar(float tx, float ty) {
    for (auto &ponto : objeto) {
        ponto.x += tx;
        ponto.y += ty;
    }
    desenhaObjeto();
}

void rotacionar(float angulo) {
    float rad = angulo * M_PI / 180.0;
    for (auto &ponto : objeto) {
        float xNovo = ponto.x * cos(rad) - ponto.y * sin(rad);
        float yNovo = ponto.x * sin(rad) + ponto.y * cos(rad);
        ponto.x = xNovo;
        ponto.y = yNovo;
    }
    desenhaObjeto();
}

void escalar(float sx, float sy) {
    for (auto &ponto : objeto) {
        ponto.x *= sx;
        ponto.y *= sy;
    }
    desenhaObjeto();
}

void menu(int opcao) {
    switch (opcao) {
        case 1:
            transladar(0.1, 0.1);
            break;
        case 2:
            rotacionar(45);
            break;
        case 3:
            escalar(1.5, 1.5);
            break;
    }
}

// inicializar a janela e o objeto
void inicializar() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -2.0, 2.0);

    glColor3f(0.0, 0.0, 0.0);
}

void criarTriangulo() {
    objeto.push_back({-0.5, -0.5});
    objeto.push_back({0.5, -0.5});
    objeto.push_back({0.0, 0.5});
}

void criarQuadrado() {
    objeto.push_back({-0.5, -0.5});
    objeto.push_back({0.5, -0.5});
    objeto.push_back({0.5, 0.5});
    objeto.push_back({-0.5, 0.5});
}

void criarPentagono() {
    objeto.push_back({0.0, 0.5});
    objeto.push_back({0.5, 0.15});
    objeto.push_back({0.3, -0.4});
    objeto.push_back({-0.3, -0.4});
    objeto.push_back({-0.5, 0.15});
}

int main(int argc, char** argv) {
    int escolha;

    cout << "Escolha um desenho p/ exibir:"<<endl;
    cout << "1. Triangulo"<<endl;
    cout << "2. Quadrado"<<endl;
    cout << "3. Pentagono"<<endl;
    cout << "Digite sua escolha (1-3): ";
    cin >> escolha;

    switch (escolha) {
        case 1:
            criarTriangulo();
            break;
        case 2:
            criarQuadrado();
            break;
        case 3:
            criarPentagono();
            break;
        default:
            cout << "Escolha invalida! Usando triangulo como padrao."<<endl;
            criarTriangulo();
            break;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformações 2D");

    inicializar();

    glutCreateMenu(menu);
    glutAddMenuEntry("Transladar", 1);
    glutAddMenuEntry("Rotacionar", 2);
    glutAddMenuEntry("Escalar", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(desenhaObjeto);
    glutMainLoop();
    return 0;
}

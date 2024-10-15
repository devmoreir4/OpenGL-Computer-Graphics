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
float corR = 0.0, corG = 0.0, corB = 0.0;

void desenhaObjeto() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);

    glColor3f(corR, corG, corB);

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

void cisalhar(float shearX, float shearY) {
    for (auto &ponto : objeto) {
        float xNovo = ponto.x + shearX * ponto.y;
        float yNovo = ponto.y + shearY * ponto.x;
        ponto.x = xNovo;
        ponto.y = yNovo;
    }
    desenhaObjeto();
}

void espelhar(bool eixoX, bool eixoY) {
    for (auto &ponto : objeto) {
        if (eixoX) {
            ponto.y = -ponto.y;
        }
        if (eixoY) {
            ponto.x = -ponto.x;
        }
    }
    desenhaObjeto();
}

void mudarCor(float red, float green, float blue) {
    corR = red;
    corG = green;
    corB = blue;
    desenhaObjeto(); // redesenha com a nova cor
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
        case 4:
            mudarCor(1.0, 0.0, 0.0); // red
            break;
        case 5:
            mudarCor(0.0, 1.0, 0.0); // green
            break;
        case 6:
            mudarCor(0.0, 0.0, 1.0); // blue
            break;
        case 7:
            cisalhar(0.5, 0.0); // cisalhamento no eixo X
            break;
        case 8:
            cisalhar(0.0, 0.5); // cisalhamento no eixo Y
            break;
        case 9:
            espelhar(true, false); // espelhar no eixo X
            break;
        case 10:
            espelhar(false, true); // espelhar no eixo Y
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
    glutAddMenuEntry("Cor: Vermelho", 4);
    glutAddMenuEntry("Cor: Verde", 5);
    glutAddMenuEntry("Cor: Azul", 6);
    glutAddMenuEntry("Cisalhar X", 7);
    glutAddMenuEntry("Cisalhar Y", 8);
    glutAddMenuEntry("Espelhar X", 9);
    glutAddMenuEntry("Espelhar Y", 10);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(desenhaObjeto);
    glutMainLoop();
    return 0;
}

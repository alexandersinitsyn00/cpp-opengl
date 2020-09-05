#include <stdio.h>
#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "include/GL/freeglut.h"

const int colorsCount = 4;
float colors[colorsCount][3]{
    {0, 0, 0},
    {1, 1, 1},
    {0, 0, 1},
    {1, 0, 0}
};
int currColor = 0;

void Display() {
    // Очистка буффера цвета 
    glClearColor(0.22, 0.88, 0.11, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Включение теста глубины 
    glEnable(GL_DEPTH_TEST);

    // Установка камеры
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

    // Отрисовка чайника 
    glColor3f(colors[currColor][0], colors[currColor][1], colors[currColor][2]);
    glutWireTeapot(1.0);

    // Смена переднего и заднего буффера
    glutSwapBuffers();
}

void Reshape(int w, int h) {
    // Установка области просмотра
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Установка матрицы проекции с правильным аспектом
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(25.0, (float)w / h, 0.2, 70.0);
}

void Simulation(int v) {
    // При необходимости перерисовать окно
    glutPostRedisplay();
    glutTimerFunc(20, Simulation, 0);
}

void KeyBoardColorChange(unsigned char key, int x, int y) {
    if (++currColor == colorsCount) { currColor = 0; }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(400, 400);
    glutCreateWindow("lab1");
    
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyBoardColorChange);
    glutTimerFunc(20, Simulation, 0);

    glutMainLoop();

    return 0;
}
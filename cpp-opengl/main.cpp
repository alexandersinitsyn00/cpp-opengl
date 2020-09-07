#include <stdio.h>
#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "GL//freeglut.h"
#include "GraphicObject.h"

const int graphicObjectsCount = 4;
GraphicObject graphicObjects[4];

vec3 colors[graphicObjectsCount]{
    vec3(0, 0, 0),
    vec3(1, 1, 1),
    vec3(0, 0, 1),
    vec3(1, 0, 0)
};

vec3 positions[graphicObjectsCount]{
    vec3(3, 0, 0),
    vec3(-3, 0, 0),
    vec3(0, 0, 3),
    vec3(0, 0, -3)
};

float angles[graphicObjectsCount] {180, 0, 90, 270};

void Display() {
    // Очистка буффера цвета 
    glClearColor(0.22, 0.88, 0.11, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Включение теста глубины 
    glEnable(GL_DEPTH_TEST);

    // Установка камеры
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(10, 10, 15, 0, 0, 0, 0, 1, 0);

    // Выводим чайники
    for (size_t i = 0; i < graphicObjectsCount; i++)
    {
        graphicObjects[i].draw();
    }

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

void KeyBoardFunc(unsigned char key, int x, int y) {
    printf("Key code: %i\n", (unsigned int)key);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(700, 600);
    glutCreateWindow("lab2");
    
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(KeyBoardFunc);
    glutTimerFunc(20, Simulation, 0);

    for (size_t i = 0; i < graphicObjectsCount; i++)
    {
        graphicObjects[i].setAngle(angles[i]);
        graphicObjects[i].setPosition(positions[i]);
        graphicObjects[i].setColor(colors[i]);
    }

    glutMainLoop();

    return 0;
}
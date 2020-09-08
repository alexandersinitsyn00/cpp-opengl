#include <stdio.h>
#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "GL//freeglut.h"
#include "GraphicObject.h"
#include "Camera.h"

Camera camera;
vec3 cameraPosition = vec3(10, 10, 15);
const float cameraFullRotateTime = 4.0;

const int graphicObjectsCount = 4;
GraphicObject graphicObjects[graphicObjectsCount];
vec3 colors[graphicObjectsCount]{
    vec3(0, 0, 0),
    vec3(1, 1, 1),
    vec3(0, 0, 1),
    vec3(1, 0, 0)
};
vec3 graphicObjectsPositions[graphicObjectsCount]{
    vec3(3, 0, 0),
    vec3(-3, 0, 0),
    vec3(0, 0, 3),
    vec3(0, 0, -3)
};
float angles[graphicObjectsCount] {180, 0, 90, 270};

float simulationTime = 0.0;

float getSimulationTime() {
    static LARGE_INTEGER oldValue;
    LARGE_INTEGER newValue;
    LARGE_INTEGER freq;

    QueryPerformanceCounter(&newValue);
    QueryPerformanceFrequency(&freq);
    float time = (float) (newValue.QuadPart - oldValue.QuadPart) / freq.QuadPart;
    QueryPerformanceCounter(&oldValue);
    return time;
}

void Display() {
    // Счетчик количества кадров
    char title[20];
    sprintf_s(title, "FPS: %i", (int) (1 / simulationTime));
    glutSetWindowTitle(title);

    // Очистка буффера цвета 
    glClearColor(0.22, 0.88, 0.11, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Включение теста глубины 
    glEnable(GL_DEPTH_TEST);

    // Установка камеры
    camera.apply();

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

void Simulation() {
    // Определение времени, прошедшего с последней симуляции 
    simulationTime = getSimulationTime();

    static float cameraUpDown = 0;
    static float cameraLeftRight = 0;
    static float cameraRadius = camera.getRadius();

    // Обработка нажатий клавиш
    if (GetAsyncKeyState(0x25))
    {
        printf("Left arrow\n");
        cameraLeftRight += 360.0 / (cameraFullRotateTime / simulationTime);
        if (cameraLeftRight > 360)
            cameraLeftRight -= 360;
        camera.rotateLeftRight(cameraLeftRight);
    }
    if (GetAsyncKeyState(0x27))
    {
        printf("Right arrow\n");
        cameraLeftRight -= 360.0 / (cameraFullRotateTime / simulationTime);
        if (cameraLeftRight < 360)
            cameraLeftRight += 360;
        camera.rotateLeftRight(cameraLeftRight);
    }
    if (GetAsyncKeyState(0x26))
    {
        printf("Up arrow\n");
        cameraUpDown += 360.0 / (cameraFullRotateTime / simulationTime);
        if (cameraUpDown > 85)
            cameraUpDown = 85;
        camera.rotateUpDown(cameraUpDown);
    }
    if (GetAsyncKeyState(0x28))
    {
        printf("Down arrow\n");
        cameraUpDown -= 360.0 / (cameraFullRotateTime / simulationTime);
        if (cameraUpDown < 5)
            cameraUpDown = 5;
        camera.rotateUpDown(cameraUpDown);
    }
    if (GetAsyncKeyState(0x53))
    {
        printf("S key\n");
        cameraRadius += 35.0 / (cameraFullRotateTime / simulationTime);
        if (cameraRadius > 50)
            cameraRadius = 50;
        camera.zoomInOut(cameraRadius);
    }
    if (GetAsyncKeyState(0x57))
    {
        printf("W key\n");
        cameraRadius -= 35.0 / (cameraFullRotateTime / simulationTime);
        if (cameraRadius < 10)
            cameraRadius = 10;
        camera.zoomInOut(cameraRadius);
    }


    // При необходимости перерисовать окно
    glutPostRedisplay();
    glutIdleFunc(Simulation);
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(700, 600);
    glutCreateWindow("lab3");
    
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(Simulation);

    camera.setPosition(cameraPosition);

    for (size_t i = 0; i < graphicObjectsCount; i++)
    {
        graphicObjects[i].setAngle(angles[i]);
        graphicObjects[i].setPosition(graphicObjectsPositions[i]);
        graphicObjects[i].setColor(colors[i]);
    }

    glutMainLoop();

    return 0;
}
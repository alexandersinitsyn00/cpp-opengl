#pragma once

#include <stdio.h>
#include <Windows.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include "GL/freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace glm;

class Camera
{
public:
	Camera();
	Camera(vec3 position);
	Camera(float x, float y, float z);

	void setPosition(vec3 position);
	vec3 getPosition();

	float getRadius();
	void rotateLeftRight(float degree);
	void rotateUpDown(float degree);
	void zoomInOut(float distance);

	void apply();
private:
	vec3 position;
	float radius;
	float XZAngle;
	float XYAngle;
private:
	void calculateRadius();
	void calculateAngles();
	void recalculatePosition();
};


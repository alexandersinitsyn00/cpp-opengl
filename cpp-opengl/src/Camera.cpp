#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(vec3 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
	calculateRadius();
	calculateAngles();
	rotateLeftRight(0);
	rotateUpDown(0);
}

Camera::Camera(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	calculateRadius();
	calculateAngles();
	rotateLeftRight(0);
	rotateUpDown(0);
}

void Camera::setPosition(vec3 position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
	calculateRadius();
	calculateAngles();
	rotateLeftRight(0);
	rotateUpDown(0);
}

vec3 Camera::getPosition()
{
	return position;
}

float Camera::getRadius()
{
	return radius;
}

void Camera::rotateLeftRight(float degree)
{
	XZAngle = radians(degree);
	recalculatePosition();
}

void Camera::rotateUpDown(float degree)
{
	XYAngle = radians(degree);
	recalculatePosition();
}

void Camera::zoomInOut(float distance)
{
	radius = distance;
	recalculatePosition();
}

void Camera::apply()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1.0, 0);
}

void Camera::calculateRadius()
{
	radius = sqrt(pow(position.x, 2) + pow(position.y, 2) + pow(position.z, 2));
}

void Camera::calculateAngles()
{
	XZAngle = acos(position.x / radius);
	XYAngle = acos(pow(position.x, 2) + pow(position.z, 2) / pow(radius, 2));
}

void Camera::recalculatePosition()
{
	float newRadius = radius * cos(XYAngle);
	position.x = newRadius * cos(XZAngle);
	position.z = newRadius * sin(XZAngle);
	position.y = radius * sin(XYAngle);
}

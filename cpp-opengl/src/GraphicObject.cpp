#include "GraphicObject.h"
#pragma once

GraphicObject::GraphicObject()
{
	modelMatrix[0] = 1.0;
	modelMatrix[5] = 1.0;
	modelMatrix[10] = 1.0;
	modelMatrix[15] = 1.0;
}

void GraphicObject::setPosition(vec3& position)
{
	this->position.x = position.x;
	this->position.y = position.y;
	this->position.z = position.z;
	
	recalculateModelMatrix();
}

vec3 GraphicObject::getPosition()
{
	return position;
}

void GraphicObject::setAngle(float grad)
{
	this->angle = grad * pi<float>() / 180;

	recalculateModelMatrix();
}

float GraphicObject::getAngle()
{
	return angle;
}

void GraphicObject::setColor(vec3& color)
{
	this->color.r = color.r;
	this->color.g = color.g;
	this->color.b = color.b;
}

vec3 GraphicObject::getColor()
{
	return color;
}

void GraphicObject::draw()
{
	glPushMatrix();

	glMultMatrixf(modelMatrix);

	glColor3f(color.r, color.g, color.b);
    glutWireTeapot(1.0);

	glPopMatrix();
}

void GraphicObject::recalculateModelMatrix()
{
	modelMatrix[12] = position.x;
	modelMatrix[13] = position.y;
	modelMatrix[14] = position.z;

	modelMatrix[0] = cos(angle);
	modelMatrix[2] = -sin(angle);
	modelMatrix[8] = sin(angle);
	modelMatrix[10] = cos(angle);
}

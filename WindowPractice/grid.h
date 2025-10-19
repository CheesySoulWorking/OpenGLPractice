#pragma once

#include<GL/glew.h>
#include<Windows.h>
#include "matrix4.h"
#include "camera.h"

struct OpenGLResourcesGrid {
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint shaderProgram = 0;

	Matrix4 worldMatrix;
	Matrix4 getWorldMatrix();
};

OpenGLResourcesGrid InitGrid();

void DrawGrid(const OpenGLResourcesGrid& grid, HDC hdc, Camera& camera, Matrix4& projectionMatrix);
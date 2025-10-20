#pragma once
#include<GL/glew.h>
#include<Windows.h>
#include "matrix4.h"
#include "camera.h"

struct OpenGLResources {
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint VBOColors = 0;
	GLuint shaderProgram = 0;

	Matrix4 worldMatrix;
	Matrix4 getWorldMatrix();
};

OpenGLResources InitTriangle(const char* vertexShaderSource, const char* fragmentShaderSource);

void DrawTriangle(const OpenGLResources& glr, HDC hdc, Camera &camera, Matrix4 &projectionMatrix, float &time);
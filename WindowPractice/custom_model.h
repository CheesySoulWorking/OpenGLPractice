#pragma once
#include <GL/glew.h>
#include <Windows.h>
#include "matrix4.h"
#include "camera.h"
#include "model.h"

struct OpenGLModel {
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint VBOColors = 0;
	GLuint VBONormals = 0;
	GLuint shaderProgram = 0;

	Matrix4 worldMatrix;
	Matrix4 getWorldMatrix();
};

OpenGLModel InitModel(Model& model, const char* vertexShaderSource, const char* fragmentShaderSource);

void DrawModel(const OpenGLModel& glr, HDC hdc, Camera& camera, Matrix4& projectionMatrix, float& time, Vector3& directionalLIghtDir);
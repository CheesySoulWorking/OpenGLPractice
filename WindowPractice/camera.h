#pragma once
#include "vector3.h"
#include "matrix4.h"
#include "vector4.h"

struct Camera {
	float cameraYaw;
	Vector3 cameraPosition = Vector3();
	Matrix4 cameraWorldMatrix = Matrix4();

	Camera(float cameraYaw = 0, Vector3 cameraPosition = Vector3());

	Matrix4 getViewMatrix();
	Vector4 getForward();

	// Need to implement cross product for Vector4
	void lookAt(Vector4 targetPosition);
	Vector4 getPosition();
};
#pragma once
#include "vector4.h"

struct Matrix4 {
	float elements[16];

	Matrix4();

	Matrix4 clone();
	Matrix4& copy(Matrix4& m);
	float getElement(int row, int column);

	Matrix4& set(
		float n11, float n12, float n13, float n14,
		float n21, float n22, float n23, float n24,
		float n31, float n32, float n33, float n34,
		float n41, float n42, float n43, float n44
	);

	Matrix4& multiplyScalar(float scalar);
	Vector4 multiplyVector(Vector4 vec);
	Matrix4& multiply(Matrix4& rightSideMatrix);
	Matrix4& preMultiply(Matrix4& leftSideMatrix);
	Matrix4& makeIdentity();
	Matrix4& makeScale(float x, float y, float z);
	Matrix4& makeRotationX(float degrees);
	Matrix4& makeRotationY(float degrees);
	Matrix4& makeRotationZ(float degrees);
	Matrix4& makePerspective(int fovy, float aspect, float near, float far);
	Matrix4& makeOrthographic(float left, float right, float top, float bottom, float near, float far);
	Matrix4& makeTranslation(float arg1, float arg2, float arg3);
	float determinant();
	Matrix4& transpose();
	Matrix4& inverse();
};
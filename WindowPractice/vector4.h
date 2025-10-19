#pragma once

struct Vector4 {
	float x, y, z, w;

	Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

	Vector4& set(float x, float y, float z, float w);
	Vector4 clone();
	Vector4& copy(Vector4 vec);
	Vector4& negate();
	Vector4& add(Vector4& vec);
	Vector4& subtract(Vector4& vec);
	Vector4& multiplyScalar(float scalar);
	float length();
	float lengthSqr();
	Vector4& normalize();
	float dot(Vector4& other);
	Vector4 fromTo(Vector4& fromPoint, Vector4& toPoint);
	Vector4& rescale(float newScale);
	float angle(Vector4& vec1, Vector4& vec2);
	Vector4 project(Vector4& vectorToProject, Vector4& otherVector);
	Vector4 cross(Vector4 v1, Vector4 v2);
};
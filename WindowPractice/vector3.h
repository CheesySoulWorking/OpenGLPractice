#pragma once

struct Vector3 {
	float x, y, z;

	Vector3(float x = 0, float y = 0, float z = 0);

	void set(float x, float y, float z);
	Vector3 clone();
	Vector3& copy(Vector3 vec);
	Vector3& negate();
	Vector3& add(Vector3 &vec);
	Vector3& subtract(Vector3 &vec);
	Vector3& multiplyScalar(float scalar);
	float length();
	float lengthSqr();
	Vector3& normalize();
	float dot(Vector3 &other);
	Vector3 fromTo(Vector3 &fromPoint, Vector3 &toPoint);
	Vector3& rescale(float newScale);
	float angle(Vector3 &vec1, Vector3 &vec2);
	Vector3 project(Vector3& vectorToProject, Vector3& otherVector);
};
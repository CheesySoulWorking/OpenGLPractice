#include "vector3.h"
#include <math.h>

Vector3::Vector3(float newX, float newY, float newZ) {
	this->x = newX;
	this->y = newY;
	this->z = newZ;
	return;
}

void Vector3::set(float newX, float newY, float newZ) {
	this->x = newX;
	this->y = newY;
	this->z = newZ;
	return;
}

Vector3 Vector3::clone() {
	Vector3 newVec(x, y, z);
	return newVec;
}

Vector3& Vector3::copy(Vector3 vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	return *this;
}

Vector3& Vector3::negate() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
	return *this;
}

Vector3& Vector3::add(Vector3 &vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return *this;
}

Vector3& Vector3::subtract(Vector3 &vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return *this;
}

Vector3& Vector3::multiplyScalar(float scalar) {
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

float Vector3::length() {
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
}

float Vector3::lengthSqr() {
	return (this->x * this->x) + (this->y * this->y) + (this->z * this->z);
}

Vector3& Vector3::normalize() {
	this->multiplyScalar(1 / this->length());
	return *this;
}

float Vector3::dot(Vector3 &other) {
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
}

Vector3 Vector3::fromTo(Vector3& fromPoint, Vector3& toPoint) {
	return toPoint.clone().subtract(fromPoint);;
}

Vector3& Vector3::rescale(float newScale) {
	const float magnitude = this->length();
	if (magnitude > 0) {
		this->normalize();
		this->multiplyScalar(newScale);
	}
	return *this;
}

float Vector3::angle(Vector3& vec1, Vector3& vec2) {
	const float dotProd = vec1.dot(vec2);
	const float radAngle = acos(dotProd / (vec1.length() * vec2.length()));
	return (radAngle * 180) / 3.14159;
}

Vector3 Vector3::project(Vector3& vectorToProject, Vector3& otherVector) {
	Vector3 other01 = otherVector.clone().normalize();
	float projectionLength = vectorToProject.dot(other01);
	return other01.multiplyScalar(projectionLength);
}
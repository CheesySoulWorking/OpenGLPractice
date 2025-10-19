#include "vector4.h"
#include <math.h>

Vector4::Vector4(float newX, float newY, float newZ, float newW) {
	this->x = newX;
	this->y = newY;
	this->z = newZ;
	this->w = newW;
	return;
}

Vector4& Vector4::set(float newX, float newY, float newZ, float newW) {
	this->x = newX;
	this->y = newY;
	this->z = newZ;
	this->w = newW;
	return *this;
}

Vector4 Vector4::clone() {
	Vector4 newVec(x, y, z, w);
	return newVec;
}

Vector4& Vector4::copy(Vector4 vec) {
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
	return *this;
}

Vector4& Vector4::negate() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
	this->w = -this->w;
	return *this;
}

Vector4& Vector4::add(Vector4& vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
	return *this;
}

Vector4& Vector4::subtract(Vector4& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->z -= vec.w;
	return *this;
}

Vector4& Vector4::multiplyScalar(float scalar) {
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	this->w *= scalar;
	return *this;
}

float Vector4::length() {
	return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w, this->w));
}

float Vector4::lengthSqr() {
	return (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w, this->w);
}

Vector4& Vector4::normalize() {
	const float len = this->length();
	const double EPSILON = 1e-8;
	
	if (len >= EPSILON) {
		this->multiplyScalar(1 / len);
	}

	return *this;
}

float Vector4::dot(Vector4& other) {
	return (this->x * other.x) + (this->y * other.y) + (this->z * other.z) + (this->w * other.w);
}

Vector4 Vector4::fromTo(Vector4& fromPoint, Vector4& toPoint) {
	return toPoint.clone().subtract(fromPoint);;
}

Vector4& Vector4::rescale(float newScale) {
	const float magnitude = this->length();
	if (magnitude > 0) {
		this->normalize();
		this->multiplyScalar(newScale);
	}
	return *this;
}

float Vector4::angle(Vector4& vec1, Vector4& vec2) {
	const float dotProd = vec1.dot(vec2);
	const float radAngle = acos(dotProd / (vec1.length() * vec2.length()));
	return (radAngle * 180) / 3.14159;
}

Vector4 Vector4::project(Vector4& vectorToProject, Vector4& otherVector) {
	Vector4 other01 = otherVector.clone().normalize();
	float projectionLength = vectorToProject.dot(other01);
	return other01.multiplyScalar(projectionLength);
}

Vector4 Vector4::cross(Vector4 v1, Vector4 v2) {
	return Vector4(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x,
		0
	);
}
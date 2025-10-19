#include "camera.h"
#include "vector4.h"

Camera::Camera(float cameraYaw, Vector3 cameraPosition) {
	this->cameraYaw = cameraYaw;
	this->cameraPosition.copy(cameraPosition);
	this->cameraWorldMatrix = Matrix4();
}

Matrix4 Camera::getViewMatrix() {
	return this->cameraWorldMatrix.clone().inverse();
}

Vector4 Camera::getForward() {
	const float* e = this->getViewMatrix().elements;

	Vector4 zVector = Vector4(e[8], e[9], e[10], e[11]);
	Vector4 negZVector = zVector.clone().negate();
	Vector4 forward = negZVector.normalize();

	return forward;
}

void Camera::lookAt(Vector4 targetPos) {
    const Vector4 worldUp = Vector4(0, 1, 0, 0);

    this->cameraWorldMatrix.makeIdentity();
	Vector4 cameraPos = Vector4(this->cameraPosition.x, this->cameraPosition.y, this->cameraPosition.z, 1);

    const Vector4 forward = targetPos.clone().subtract(cameraPos).normalize();
	//Vector4 forward = this->getForward();
    const Vector4 right = Vector4().cross(forward, worldUp).normalize();
    const Vector4 up = Vector4().cross(right, forward);

    float *e = this->cameraWorldMatrix.elements;
    e[0] = right.x; e[1] = up.x; e[2] = -forward.x; e[3] = cameraPos.x;
    e[4] = right.y; e[5] = up.y; e[6] = -forward.y; e[7] = cameraPos.y;
    e[8] = right.z; e[9] = up.z; e[10] = -forward.z; e[11] = cameraPos.z;
    e[12] = 0; e[13] = 0; e[14] = 0; e[15] = 1;

	/*e[0] = right.x;    e[4] = right.y;    e[8] = right.z;    e[12] = this->cameraPosition.x;
	e[1] = up.x;       e[5] = up.y;       e[9] = up.z;       e[13] = this->cameraPosition.y;
	e[2] = -forward.x; e[6] = -forward.y; e[10] = -forward.z; e[14] = this->cameraPosition.z;
	e[3] = 0;          e[7] = 0;          e[11] = 0;          e[15] = 1;*/
	
	return;
}

Vector4 Camera::getPosition() {
	return Vector4(
		this->cameraWorldMatrix.elements[3],
		this->cameraWorldMatrix.elements[7],
		this->cameraWorldMatrix.elements[11],
		1
	);
}
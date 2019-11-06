#include "Camera.hpp"

Camera::Camera(mat::Vec3 pos, mat::Vec3 up, float yaw, float pitch)
: pos(pos),
  front(mat::Vec3(0.0f, 0.0f, -1.0f)),
  worldUp(up),
  yaw(yaw),
  pitch(pitch),
  movementSpeed(MOVEMENT_SPEED),
  mouseSensitivity(MOUSE_SENSITIVITY),
  zoom(45.0f),
  _startPos(pos),
  _startYaw(yaw),
  _startPitch(pitch) {
	updateCameraVectors();
}

Camera::Camera(Camera const &src) {
	*this = src;
}

Camera::~Camera() {
}

Camera &Camera::operator=(Camera const &rhs) {
	if (this != &rhs) {
		pos = rhs.pos;
		front = rhs.front;
		up = rhs.up;
		right = rhs.right;
		worldUp = rhs.worldUp;
		yaw = rhs.yaw;
		pitch = rhs.pitch;
		movementSpeed = rhs.movementSpeed;
		mouseSensitivity = rhs.mouseSensitivity;
		zoom = rhs.zoom;
	}
	return *this;
}

mat::Mat4 Camera::getViewMatrix() const {
	return mat::lookAt(pos, pos + front);
}

void Camera::processKeyboard(CamMovement direction, float dtTime) {
	float	velocity;

	velocity = movementSpeed * dtTime;
	if (direction == CamMovement::Forward)
		pos = pos + front * velocity;
	if (direction == CamMovement::Backward)
		pos = pos - front * velocity;
	if (direction == CamMovement::Left)
		pos = pos - right * velocity;
	if (direction == CamMovement::Right)
		pos = pos + right * velocity;
	if (direction == CamMovement::Up)
		pos = pos + mat::Vec3(0, 1, 0) * velocity;
	if (direction == CamMovement::Down)
		pos = pos - mat::Vec3(0, 1, 0) * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch) {
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// constrain pitch to avoid screen flip
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
	if (zoom >= 1.0f && zoom <= 45.0f)
		zoom -= yOffset;
	if (zoom <= 1.0f)
		zoom = 1.0f;
	if (zoom >= 45.0f)
		zoom = 45.0f;
}

void Camera::updateCameraVectors() {
	mat::Vec3 nFront;

	nFront.x = cos(mat::radians(yaw)) * cos(mat::radians(pitch));
	nFront.y = sin(mat::radians(pitch));
	nFront.z = sin(mat::radians(yaw)) * cos(mat::radians(pitch));

	front = mat::normalize(nFront);

	right = mat::normalize(mat::cross(front, worldUp));
	up = mat::normalize(mat::cross(right, front));
}

void Camera::resetPosition() {
	pos = _startPos;
	yaw = _startYaw;
	pitch = _startPitch;

	updateCameraVectors();
}

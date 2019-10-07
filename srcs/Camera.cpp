#include "Camera.hpp"

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch)
: pos(pos),
  front(glm::vec3(0.0f, 0.0f, -1.0f)),
  worldUp(up),
  yaw(yaw),
  pitch(pitch),
  movementSpeed(2.5f),
  mouseSensitivity(0.1f),
  zoom(45.0f) {
	updateCameraVectors();
}

Camera::Camera(Camera const &src) {
	*this = src;
}

Camera::~Camera() {
}

Camera &Camera::operator=(Camera const &rhs) {
	if (this != &rhs)
		;
	return *this;
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(pos, pos + front, up);
}

void Camera::processKeyboard(CamMovement direction, float dtTime) {
	float	velocity;

	velocity = movementSpeed * dtTime;
	if (direction == CamMovement::Forward)
		pos += front * velocity;
	if (direction == CamMovement::Backward)
		pos -= front * velocity;
	if (direction == CamMovement::Left)
		pos -= right * velocity;
	if (direction == CamMovement::Right)
		pos += right * velocity;
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
	glm::vec3 front;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

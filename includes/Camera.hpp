#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "humanGL.hpp"
# include "glm/gtc/matrix_transform.hpp"

enum class CamMovement {
	Forward,
	Backward,
	Left,
	Right
};

class Camera {
	public:
		Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = \
		glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		Camera(Camera const &src);
		virtual ~Camera();

		Camera &operator=(Camera const &rhs);

		glm::mat4 getViewMatrix() const;
		void processKeyboard(CamMovement direction, float dtTime);
		void processMouseMovement(float xOffset, float yOffset, bool \
		constrainPitch = true);
		void processMouseScroll(float yOffset);

		glm::vec3	pos;
		glm::vec3	front;
		glm::vec3	up;
		glm::vec3	right;
		glm::vec3	worldUp;

		float		yaw;
		float		pitch;

		float		movementSpeed;
		float		mouseSensitivity;
		float		zoom;
	private:
		void updateCameraVectors();
};

#endif

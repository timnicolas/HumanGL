#include "humanGL.hpp"
#include <iostream>
#include <chrono>

static u_int8_t	firstTwoCall = 2;
static float lastAnimationSpeed = 1;
static bool isPause = false;

void toggleCursor(GLFWwindow *window) {
	static bool enable = false;

	enable = !enable;
	if (enable)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void updateAnimationSpeed(GLFWwindow *window, float offset) {
	float		animationSpeed;
	tWinUser	*winU;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);

	animationSpeed = (isPause) ? lastAnimationSpeed : winU->animationSpeed;

	animationSpeed += offset;
	if (animationSpeed < SPEED_MIN)
		animationSpeed = SPEED_MIN;
	if (animationSpeed > SPEED_MAX)
		animationSpeed = SPEED_MAX;
	if (isPause) {
		lastAnimationSpeed = animationSpeed;
	}
	else {
		lastAnimationSpeed = winU->animationSpeed;
		winU->animationSpeed = animationSpeed;
	}
}

void togglePause(GLFWwindow *window) {
	tWinUser	*winU;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);

	isPause = !isPause;
	if (isPause) {
		lastAnimationSpeed = winU->animationSpeed;
		winU->animationSpeed = 0;
	}
	else
		winU->animationSpeed = lastAnimationSpeed;
}

/*
	called every frame
*/
void	processInput(GLFWwindow *window)
{
	tWinUser	*winU;
	float		crntFrame;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);
	crntFrame = glfwGetTime();
	winU->dtTime = crntFrame - winU->lastFrame;
	winU->lastFrame = crntFrame;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
	glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        winU->cam->processKeyboard(CamMovement::Forward, winU->dtTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
	glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        winU->cam->processKeyboard(CamMovement::Backward, winU->dtTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
	glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        winU->cam->processKeyboard(CamMovement::Left, winU->dtTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ||
	glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        winU->cam->processKeyboard(CamMovement::Right, winU->dtTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        winU->cam->processKeyboard(CamMovement::Up, winU->dtTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        winU->cam->processKeyboard(CamMovement::Down, winU->dtTime);
    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        updateAnimationSpeed(window, SPEED_OFFSET_KEY);
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS
	|| glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        updateAnimationSpeed(window, -SPEED_OFFSET_KEY);
}

void	keyCb(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	tWinUser	*winU = (tWinUser *)glfwGetWindowUserPointer(window);

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		toggleCursor(window);

	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		for (auto it = winU->models->begin(); it != winU->models->end(); it++) {
			(*it)->isDrawMesh() = !(*it)->isDrawMesh();
		}
	}

	if (key == GLFW_KEY_N && action == GLFW_PRESS) {
		for (auto it = winU->models->begin(); it != winU->models->end(); it++) {
			(*it)->isDrawCube() = !(*it)->isDrawCube();
		}
	}

	if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
		for (auto it = winU->models->begin(); it != winU->models->end(); it++) {
			(*it)->loadNextAnimation();
		}
	}

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		togglePause(window);
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		isPause = false;
		lastAnimationSpeed = 1;
		winU->animationSpeed = 1;
		winU->cam->resetPosition();
	}
}

void	scrollCb(GLFWwindow *window, double xOffset, double yOffset) {
	(void)xOffset;
	// edit animation speed
	updateAnimationSpeed(window, yOffset * SPEED_OFFSET_SCROLL);
}

void	mouseCb(GLFWwindow *window, double xPos, double yPos)
{
	tWinUser		*winU;
	static float	lastX = SCREEN_W / 2.0;
	static float	lastY = SCREEN_H / 2.0;
	float			xOffset;
	float			yOffset;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);

	if (firstTwoCall) {
		lastX = xPos;
		lastY = yPos;
		--firstTwoCall;
	}

	xOffset = xPos - lastX;
	// reversed since y-coordinates go from bottom to top
	yOffset = lastY - yPos;
	winU->cam->processMouseMovement(xOffset, yOffset);

	lastX = xPos;
	lastY = yPos;
}

void	frambuffResizeCb(GLFWwindow *window, int width, int height)
{
	tWinUser	*winU;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);
	winU->width = width;
	winU->height = height;
	glViewport(0, 0, width, height);
}

bool	initWindow(GLFWwindow **window, const char *name, tWinUser *winU)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Could not start glfw3\n");
		return (false);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); // anti aliasing
	*window = glfwCreateWindow(SCREEN_W, SCREEN_H, name, NULL, NULL);
	if (!(*window))
	{
		fprintf(stderr, "Fail to create glfw3 window\n");
		glfwTerminate();
		return (false);
	}
	glfwMakeContextCurrent(*window);

	glfwSetFramebufferSizeCallback(*window, frambuffResizeCb);
	glfwSetCursorPosCallback(*window, mouseCb);
	glfwSetKeyCallback(*window, keyCb);
	glfwSetScrollCallback(*window, scrollCb);

	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE); // anti aliasing
	glEnable(GL_CULL_FACE); // face culling

	glfwSetWindowUserPointer(*window, winU);
	return (true);
}

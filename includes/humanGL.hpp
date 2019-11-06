#ifndef HUMANGL_HPP
# define HUMANGL_HPP

# include "Camera.hpp"
# include "Model.hpp"
# include <vector>

#define SPEED_MIN 0
#define SPEED_MAX 10
#define SPEED_OFFSET_SCROLL 0.005
#define SPEED_OFFSET_KEY 0.02

typedef struct	sWinUser
{
	std::vector<Model*> *models;
	Camera		*cam;
	float		dtTime;
	float		lastFrame;
	float		width;
	float		height;
	float		animationSpeed;
}				tWinUser;

bool	initWindow(GLFWwindow **window, const char *name, tWinUser *winU);
void	processInput(GLFWwindow *window);

/* define error function */
GLenum checkError_(const char *file, int line);
void checkErrorExit_(const char *file, int line);
#define checkError() checkError_(__FILE__, __LINE__)
#define checkErrorExit() checkErrorExit_(__FILE__, __LINE__)

#endif

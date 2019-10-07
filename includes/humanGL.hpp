#ifndef HUMANGL_HPP
# define HUMANGL_HPP

# include "Camera.hpp"

typedef struct	sWinUser
{
	Camera		*cam;
	float		dtTime;
	float		lastFrame;
	float		width;
	float		height;
}				tWinUser;

bool	initWindow(GLFWwindow **window, const char *name, tWinUser *winU);
void	processInput(GLFWwindow *window);

/* define error function */
GLenum checkError_(const char *file, int line);
void checkErrorExit_(const char *file, int line);
#define checkError() checkError_(__FILE__, __LINE__)
#define checkErrorExit() checkErrorExit_(__FILE__, __LINE__)

#endif

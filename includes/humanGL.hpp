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

#endif

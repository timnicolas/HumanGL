#include "humanGL.hpp"
#include <iostream>

/*
	called every frame
*/
void	process_input(GLFWwindow *window)
{
	t_win_user	*win_u;
	float		crnt_frame;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	crnt_frame = glfwGetTime();
	win_u->dt_time = crnt_frame - win_u->last_frame;
	win_u->last_frame = crnt_frame;
}

void	key_cb(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void	mouse_cb(GLFWwindow *window, double x_pos, double y_pos)
{
	static float	last_x = SCREEN_W / 2.0;
	static float	last_y = SCREEN_H / 2.0;
	static bool		first_mouse = true;

	(void)window;
	if (first_mouse)
	{
		last_x = x_pos;
		last_y = y_pos;
		first_mouse = false;
	}
	// std::cout << "mouse pos: {" << last_x << ", " << last_y << "}" \
	// << " => {" << x_pos << ", " << y_pos << "}" << std::endl;
	last_x = x_pos;
	last_y = y_pos;
}

void	frambuff_resize_cb(GLFWwindow *window, int width, int height)
{
	t_win_user	*win_u;

	win_u = (t_win_user *)glfwGetWindowUserPointer(window);
	win_u->width = width;
	win_u->height = height;
	glViewport(0, 0, width, height);
}

bool	init_window(GLFWwindow **window, const char *name, t_win_user *win_u)
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
	*window = glfwCreateWindow(SCREEN_W, SCREEN_H, name, NULL, NULL);
	if (!(*window))
	{
		fprintf(stderr, "Fail to create glfw3 window\n");
		glfwTerminate();
		return (false);
	}
	glfwMakeContextCurrent(*window);

	glfwSetFramebufferSizeCallback(*window, frambuff_resize_cb);
	glfwSetCursorPosCallback(*window, mouse_cb);
	glfwSetKeyCallback(*window, key_cb);

	glEnable(GL_DEPTH_TEST);

	glfwSetWindowUserPointer(*window, win_u);
	return (true);
}

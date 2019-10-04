#ifndef HUMANGL_HPP
# define HUMANGL_HPP

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# include <string>
# include <iostream>

# include <glm/glm.hpp> // !!!!!!!!! NEED TO REMOVE LATER

# define SCREEN_W 800
# define SCREEN_H 600

typedef struct	s_win_user
{
	float		dt_time;
	float		last_frame;
	float		width;
	float		height;
}				t_win_user;

bool	init_window(GLFWwindow **window, const char *name, t_win_user *win_u);
void	process_input(GLFWwindow *window);

#endif
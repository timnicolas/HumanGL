#include "Shader.hpp"
#include "defines.hpp"

bool	init_window(GLFWwindow **window, const char *name)
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
	glEnable(GL_DEPTH_TEST);
	return (true);
}

int main(void) {
	GLFWwindow	*window;

	if (!init_window(&window, "humanGl"))
		return (1);

	try
	{
		Shader sh1("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}

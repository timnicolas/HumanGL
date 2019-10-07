#include "humanGL.hpp"
#include "Shader.hpp"

void	game_loop(GLFWwindow *window) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// drawing here

		glfwSwapBuffers(window);
		glfwPollEvents();
		checkErrorExit();  // check if there is an error in the main loop
	}
}

int main(void) {
	GLFWwindow	*window;
	t_win_user	win_u;

	if (!init_window(&window, "humanGl", &win_u))
		return (1);
	checkErrorExit();

	try
	{
		Shader sh1("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");
		checkErrorExit();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	game_loop(window);
	checkErrorExit();

	return 0;
}

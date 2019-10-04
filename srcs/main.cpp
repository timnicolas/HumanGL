#include "humanGL.hpp"
#include "Shader.hpp"
#include "Model.hpp"
#include "glm/gtc/matrix_transform.hpp"

void	game_loop(GLFWwindow *window, Shader &sh, Model &objModel) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// temporary code, just to test model object
		glm::mat4	view = glm::mat4(1.0f);
        glm::mat4	projection = glm::mat4(1.0f);
		glm::mat4	model = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_W / (float)SCREEN_H, 0.1f, 100.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        sh.setMat4("projection", projection);
        sh.setMat4("view", view);
		sh.setMat4("model", model);

		objModel.draw(sh);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(int argc, char const **argv) {
	GLFWwindow	*window;
	t_win_user	win_u;

	if (argc != 2) {
		std::cout << "usage: ./humanGL modelFile\n" << std::endl;
		return (1);
	}

	if (!init_window(&window, "humanGl", &win_u))
		return (1);

	try
	{
		Shader sh1("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");

		Model	model(argv[1]);

		game_loop(window, sh1, model);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}

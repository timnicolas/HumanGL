#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "glm/gtc/matrix_transform.hpp"

void	game_loop(GLFWwindow *window, Camera &cam, Shader &sh, Model &objModel) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view matrix
		glm::mat4 view = cam.getViewMatrix();
        sh.setMat4("view", view);
		// projection matrix
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_W / (float)SCREEN_W, 0.1f, 100.0f);
        sh.setMat4("projection", projection);
		// model matrix
		glm::mat4	model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		sh.setMat4("model", model);

		// draw the model
		objModel.draw(sh);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main(int argc, char const **argv) {
	GLFWwindow	*window;
	t_win_user	win_u;
	Camera		cam(glm::vec3(0.0f, 0.0f, 3.0f));

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

		game_loop(window, cam, sh1, model);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}

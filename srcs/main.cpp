#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "glm/gtc/matrix_transform.hpp"

void	gameLoop(GLFWwindow *window, Camera &cam, Shader &sh, Model &objModel) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		sh.use();
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

bool	init(GLFWwindow **window, const char *name, tWinUser *winU, Camera *cam) {
	winU->cam = cam;
	winU->dtTime = 0.0f;
	winU->lastFrame = 0.0f;
	winU->width = SCREEN_W;
	winU->height = SCREEN_H;

	if (!initWindow(window, name, winU))
		return (false);
	return (true);
}

int		main(int argc, char const **argv) {
	GLFWwindow	*window;
	tWinUser	winU;
	Camera		cam(glm::vec3(0.0f, 0.0f, 3.0f));

	if (argc != 2) {
		std::cout << "usage: ./humanGL modelFile\n" << std::endl;
		return (1);
	}

	if (!init(&window, "humanGl", &winU, &cam))
		return (1);

	try
	{
		Shader sh1("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");

		Model	model(argv[1]);

		gameLoop(window, cam, sh1, model);

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}

#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include <chrono>
#include <unistd.h>

void	gameLoop(GLFWwindow *window, Camera &cam, Shader &sh, Model &objModel) {
	tWinUser	*winU;
	std::chrono::milliseconds time_start;
	bool firstLoop = true;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	while (!glfwWindowShouldClose(window)) {
		time_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// enable the shader before setting uniform
		sh.use();

		// view matrix
		mat::Mat4	view = cam.getViewMatrix();
        sh.setMat4("view", view);
		// projection matrix
		mat::Mat4	projection = mat::perspective(mat::radians(cam.zoom), winU->width / winU->height, 0.1f, 100.0f);
        sh.setMat4("projection", projection);
		// model matrix
		mat::Mat4	model = mat::Mat4(1.0f);
		model = model.translate(mat::Vec3(0.0f, -1.75f, 0.0f));
		model = model.scale(mat::Vec3(0.2f, 0.2f, 0.2f));
		sh.setMat4("model", model);

		// draw the model
		objModel.draw(sh);

		glfwSwapBuffers(window);
		glfwPollEvents();

		std::chrono::milliseconds time_loop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - time_start;
		if (time_loop.count() > LOOP_TIME) {
			#if DEBUG == true
				if (!firstLoop)
					std::cout << "loop slow -> " << time_loop.count() << "ms / " << LOOP_TIME << "ms (" << FPS << "fps)\n";
			#endif
		}
		else {
			usleep((LOOP_TIME - time_loop.count()) * 1000);
		}
		firstLoop = false;
	}
	glfwDestroyWindow(window);
	glfwPollEvents();
	glfwTerminate();
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
	Camera		cam(mat::Vec3(0.0f, 0.0f, 3.0f));

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
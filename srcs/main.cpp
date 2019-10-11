#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include <chrono>
#include <unistd.h>

void	setupDirLight(Shader &sh) {
	sh.use();

	sh.setVec3("dirLight.direction", -0.2f, -0.8f, -0.6f);
	sh.setVec3("dirLight.ambient", 0.5, 0.5, 0.5);
	sh.setVec3("dirLight.diffuse", 0.99f, 0.98f, 0.94f);
	sh.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
}

void	gameLoop(GLFWwindow *window, Camera &cam, Shader &sh, Model &objModel) {
	tWinUser	*winU;
	std::chrono::milliseconds time_start;
	bool firstLoop = true;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);

	sh.use();
	// projection matrix
	mat::Mat4	projection = mat::perspective(mat::radians(cam.zoom), winU->width / winU->height, 0.1f, 100.0f);
	sh.setMat4("projection", projection);

	glClearColor(0.11373f, 0.17647f, 0.27059f, 1.0f);
	setupDirLight(sh);
	while (!glfwWindowShouldClose(window)) {
		time_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// enable the shader before setting uniform
		sh.use();

		// view matrix
		mat::Mat4	view = cam.getViewMatrix();
        sh.setMat4("view", view);

        sh.setVec3("viewPos", cam.pos.x, cam.pos.y, cam.pos.z);

		objModel.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		// fps
		std::chrono::milliseconds time_loop = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - time_start;
		if (time_loop.count() > LOOP_TIME) {
			#if DEBUG == true
				if (!firstLoop)
					std::cerr << "loop slow -> " << time_loop.count() << "ms / " << LOOP_TIME << "ms (" << FPS << "fps)\n";
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

		Model	model(argv[1], sh1);

		gameLoop(window, cam, sh1, model);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}
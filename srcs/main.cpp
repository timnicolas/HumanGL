#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include "Environnement.hpp"
#include <chrono>
#include <unistd.h>

void	setupDirLight(Shader &sh) {
	sh.use();

	sh.setVec3("dirLight.direction", -0.2f, -0.8f, -0.6f);
	sh.setVec3("dirLight.ambient", 0.5, 0.5, 0.5);
	sh.setVec3("dirLight.diffuse", 0.99f, 0.98f, 0.94f);
	sh.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
}

void	gameLoop(GLFWwindow *window, Camera &cam, Shader &envSh, Shader &sh, Shader &cubeSh, Environnement &env, std::vector<Model*> &models) {
	tWinUser	*winU;
	std::chrono::milliseconds time_start;
	bool firstLoop = true;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);

	// projection matrix
	mat::Mat4	projection = mat::perspective(mat::radians(cam.zoom), winU->width / winU->height, 0.1f, 100.0f);

	envSh.use();
	envSh.setMat4("projection", projection);

	sh.use();
	sh.setMat4("projection", projection);

	cubeSh.use();
	cubeSh.setMat4("projection", projection);

	glClearColor(0.11373f, 0.17647f, 0.27059f, 1.0f);
	setupDirLight(sh);
	setupDirLight(cubeSh);
	while (!glfwWindowShouldClose(window)) {
		time_start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view matrix
		mat::Mat4	view = cam.getViewMatrix();

		mat::Mat4	skyView = view;
		skyView[0][3] = 0;  // remove translation for the skybox
		skyView[1][3] = 0;
		skyView[2][3] = 0;
		envSh.use();
		envSh.setMat4("view", skyView);

		sh.use();
		sh.setMat4("view", view);
		sh.setVec3("viewPos", cam.pos.x, cam.pos.y, cam.pos.z);

		cubeSh.use();
		cubeSh.setMat4("view", view);
		cubeSh.setVec3("viewPos", cam.pos.x, cam.pos.y, cam.pos.z);

		env.draw();

		// to move model, change matrix: objModel.getModel()
		for (u_int32_t i=0; i < models.size(); i++) {
			models[i]->draw();
		}

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
}

bool	init(GLFWwindow **window, const char *name, tWinUser *winU, Camera *cam) {
	winU->cam = cam;
	winU->dtTime = 0.0f;
	winU->lastFrame = 0.0f;
	winU->width = SCREEN_W;
	winU->height = SCREEN_H;
	winU->animationSpeed = 1.0f;

	if (!initWindow(window, name, winU))
		return (false);
	return (true);
}

int		main(int argc, char const **argv) {
	GLFWwindow	*window;
	tWinUser	winU;
	Camera		cam(mat::Vec3(0.0f, 0.0f, 3.0f));

	if (argc < 2) {
		std::cout << "usage: ./humanGL modelFile\n" << std::endl;
		return (1);
	}

	if (!init(&window, "humanGl", &winU, &cam))
		return (1);

	try {
		Shader envShader("shaders/env_vs.glsl", "shaders/env_fs.glsl");
		Shader basicShader("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");
		Shader cubeShader("shaders/cube_vs.glsl", "shaders/basic_fs.glsl");

		Environnement env(envShader);

		std::vector<Model*> models = std::vector<Model*>();
		Model	*model;
		for (int i=1; i < argc; i++) {
			std::cout << "loading " << argv[i] << std::endl;
			model = new Model(argv[i], basicShader, cubeShader, winU.animationSpeed, winU.dtTime);
			models.push_back(model);
		}

		// repartition of all models
		float step = 1.5;
		float posX = -(static_cast<float>(models.size()) / 2.0) * step + step / 2;
		for (u_int32_t i=0; i < models.size(); i++) {
			mat::Vec3 pos = mat::Vec3(posX, 0, 0);
			models[i]->getModel() = models[i]->getModel().translate(pos);
			posX += step;
		}

		winU.models = &models;

		gameLoop(window, cam, envShader, basicShader, cubeShader, env, models);

		for (u_int32_t i=0; i < models.size(); i++) {
			delete models[i];
		}
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
	}
	glfwDestroyWindow(window);
	glfwPollEvents();
	glfwTerminate();

	return 0;
}

#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
#include "Matrix.hpp"
#include "Skybox.hpp"
#include <chrono>
#include <unistd.h>

void	setupDirLight(Shader &sh) {
	sh.use();

	sh.setVec3("dirLight.direction", -0.2f, -0.8f, -0.6f);
	sh.setVec3("dirLight.ambient", 0.4f, 0.4f, 0.4f);
	sh.setVec3("dirLight.diffuse", 1.5f, 1.5f, 1.5f);
	sh.setVec3("dirLight.specular", 1, 1, 1);
}

void	gameLoop(GLFWwindow *window, Camera &cam, Shader &skyboxSh, Shader &modelSh, Shader &cubeSh, Skybox &skybox, std::vector<Model*> &models) {
	tWinUser	*winU;
	std::chrono::milliseconds time_start;
	bool firstLoop = true;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);

	// projection matrix
	mat::Mat4	projection = mat::perspective(mat::radians(cam.zoom), winU->width / winU->height, 0.1f, 100.0f);

	skyboxSh.use();
	skyboxSh.setMat4("projection", projection);

	modelSh.use();
	modelSh.setMat4("projection", projection);

	cubeSh.use();
	cubeSh.setMat4("projection", projection);

	glClearColor(0.11373f, 0.17647f, 0.27059f, 1.0f);
	setupDirLight(modelSh);
	setupDirLight(cubeSh);
	checkError();
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
		skyboxSh.use();
		skyboxSh.setMat4("view", skyView);

		modelSh.use();
		modelSh.setMat4("view", view);
		modelSh.setVec3("viewPos", cam.pos.x, cam.pos.y, cam.pos.z);

		cubeSh.use();
		cubeSh.setMat4("view", view);
		cubeSh.setVec3("viewPos", cam.pos.x, cam.pos.y, cam.pos.z);


		// to move model, change matrix: objModel.getModel()
		for (u_int32_t i=0; i < models.size(); i++) {
			models[i]->draw();
		}

		skybox.draw();  // draw shader

		glfwSwapBuffers(window);
		glfwPollEvents();
		checkError();

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

void	usage() {
	std::cout << "Usage: ./humanGL <modelfile.fbx, ...>" << std::endl;
	std::cout << "Commands:" << std::endl;
	std::cout << "\t-> speed control (-+ mouse-scroll)" << std::endl;
	std::cout << "\t-> fps control (wasd|arrow & mouse)" << std::endl;
	std::cout << "\t-> move up/down (ed)" << std::endl;
	std::cout << "\t-> play/pause (p)" << std::endl;
	std::cout << "\t-> show/hide model: (m)" << std::endl;
	std::cout << "\t-> show/hide bones: (n)" << std::endl;
	std::cout << "\t-> enable/disable cursor (space)" << std::endl;
	std::cout << "\t-> load next animation (enter)" << std::endl;
	std::cout << "\t-> reset position and speed (r)" << std::endl;
	std::cout << "\t-> quit (escape)" << std::endl;
}

int		main(int argc, char const **argv) {
	GLFWwindow	*window;
	tWinUser	winU;
	Camera		cam(mat::Vec3(0.0f, 0.0f, 3.0f));

	if (argc < 2) {
		usage();
		return (1);
	}

	if (!init(&window, "humanGl", &winU, &cam))
		return (1);

	try {
		Shader skyboxShader("shaders/skybox_vs.glsl", "shaders/skybox_fs.glsl");
		Shader modelShader("shaders/model_vs.glsl", "shaders/model_fs.glsl");
		Shader cubeShader("shaders/cube_vs.glsl", "shaders/cube_fs.glsl");

		Skybox skybox(skyboxShader);

		std::vector<Model*> models = std::vector<Model*>();
		Model	*model;
		for (int i=1; i < argc; i++) {
			std::cout << "loading " << argv[i] << std::endl;
			model = new Model(argv[i], modelShader, cubeShader, winU.animationSpeed, winU.dtTime);
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

		gameLoop(window, cam, skyboxShader, modelShader, cubeShader, skybox, models);

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

#include "humanGL.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Model.hpp"
// #include "glm/gtc/matrix_transform.hpp"
#include "Matrix.hpp"

void	gameLoop(GLFWwindow *window, Camera &cam, Shader &sh, Model &objModel) {
	tWinUser	*winU;

	winU = (tWinUser *)glfwGetWindowUserPointer(window);
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
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
	}

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

// int		main(int argc, char const **argv) {
// 	GLFWwindow	*window;
// 	tWinUser	winU;
// 	Camera		cam(mat::Vec3(0.0f, 0.0f, 3.0f));

// 	if (argc != 2) {
// 		std::cout << "usage: ./humanGL modelFile\n" << std::endl;
// 		return (1);
// 	}

// 	if (!init(&window, "humanGl", &winU, &cam))
// 		return (1);

// 	try
// 	{
// 		Shader sh1("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");

// 		Model	model(argv[1]);

// 		gameLoop(window, cam, sh1, model);
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}

// 	return 0;
// }

#include <glm/glm.hpp>

void    printMat4(glm::mat4 &mat) {
    std::cout << "(" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << "    " << mat[j][i];
        }
        std::cout << std::endl;
    }
    std::cout << ")" << std::endl;
}

void    printMat4(mat::Mat4 &mat) {
    std::cout << "(" << std::endl;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << "    " << mat[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << ")" << std::endl;
}

int		main(void) {
	glm::mat4	glmprojection = glm::perspective(mat::radians(45), (float)SCREEN_W / SCREEN_H, 0.1f, 100.0f);
	mat::Mat4	matprojection = mat::perspective(mat::radians(45), (float)SCREEN_W / SCREEN_H, 0.1f, 100.0f);

	glm::mat4	glmlook = glm::lookAt(glm::vec3(1, 0, 4), glm::vec3(5, 5, 1), glm::vec3(0, 1, 0));
	mat::Mat4	matlook = mat::lookAt(mat::Vec3(1, 0, 4), mat::Vec3(5, 5, 1));

	// printMat4(glmprojection);
	// printMat4(matprojection);
	printMat4(glmlook);
	printMat4(matlook);
	return 0;
}
#include "Shader.hpp"

int main(int ac, char **av) {
	Shader sh1("shaders/basic_vs.glsl", "shaders/basic_fs.glsl");

	(void)ac;
	(void)av;
	return 0;
}

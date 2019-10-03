#include "Shader.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath, \
const char *geometryPath) {
}

Shader::Shader(Shader const &src) {
	*this = src;
}

Shader::~Shader() {
}

Shader &Shader::operator=(Shader const &rhs) {
	if (this != &rhs)
		;
	return *this;
}

void	Shader::use() {
	glUseProgram(id);
}
void	Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}
void	Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}
void	Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void	Shader::setVec2(const std::string &name, float x, float y) const {
	glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
void	Shader::setVec3(const std::string &name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void	Shader::setVec4(const std::string &name, float x, float y, float z, float w) {
	glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

#include "Skybox.hpp"
#include "lib/stb_image.h"

const float Skybox::_vertices[] = {
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

Skybox::Skybox(Shader &sh) :
_shader(sh) {
	std::vector<std::string> skyboxFaces = {
		"skybox/right.jpg",  // right
		"skybox/left.jpg",  // left
		"skybox/top.jpg",  // up
		"skybox/bottom.jpg",  // down
		"skybox/front.jpg",  // front
		"skybox/back.jpg",  // back
	};
	load(skyboxFaces);

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), &_vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Skybox::Skybox(Skybox const &src) :
_shader(src.getShader()) {
	*this = src;
}

Skybox::~Skybox() {
}

Skybox &Skybox::operator=(Skybox const &rhs) {
	if (this != &rhs) {
		_textureID = getTextureID();
		_vao = getVao();
		_vbo = getVbo();
	}
	return *this;
}

void Skybox::load(std::vector<std::string> &faces) {
	_shader.use();

    glGenTextures(1, &_textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
			GLenum format;
			if (nrChannels == 1) {
				format = GL_RED;
			}
			else if (nrChannels == 3) {
				format = GL_RGB;
			}
			else if (nrChannels == 4) {
				format = GL_RGBA;
			}
			std::cout << _textureID << " " << width << " " << height << " " << nrChannels << std::endl;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, nrChannels, width, height, 0, nrChannels, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::draw() {
	glDepthMask(GL_FALSE);
	_shader.use();
	glBindVertexArray(_vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _textureID);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(_vertices) / sizeof(_vertices[0]));
	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
}

Shader		&Skybox::getShader() { return _shader; }
Shader		&Skybox::getShader() const { return _shader; }
uint32_t	Skybox::getTextureID() const { return _textureID; }
uint32_t	Skybox::getVao() const { return _vao; }
uint32_t	Skybox::getVbo() const { return _vbo; }

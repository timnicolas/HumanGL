#include "Environnement.hpp"
#include "lib/stb_image.h"

const float Environnement::_skyboxVertices[] = {
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

Environnement::Environnement(Shader &sh) :
_shader(sh) {
	std::vector<std::string> skyBoxFaces = {
		"skybox/cc_rt.tga",  // right
		"skybox/cc_lf.tga",  // left
		"skybox/cc_up.tga",  // up
		"skybox/cc_dn.tga",  // down
		"skybox/cc_ft.tga",  // front
		"skybox/cc_bk.tga",  // back
	};
	loadSkyBox(skyBoxFaces);

	glGenVertexArrays(1, &_skyboxVao);
	glGenBuffers(1, &_skyboxVbo);

	glBindVertexArray(_skyboxVao);
	glBindBuffer(GL_ARRAY_BUFFER, _skyboxVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_skyboxVertices), _skyboxVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

Environnement::Environnement(Environnement const &src) :
_shader(src.getShader()) {
	*this = src;
}

Environnement::~Environnement() {
}

Environnement &Environnement::operator=(Environnement const &rhs) {
	if (this != &rhs) {
		_skyboxTextureID = getSkyboxTextureID();
		_skyboxVao = getSkyboxVao();
		_skyboxVbo = getSkyboxVbo();
	}
	return *this;
}

void Environnement::loadSkyBox(std::vector<std::string> &faces) {
	_shader.use();

    glGenTextures(1, &_skyboxTextureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureID);

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
			std::cout << _skyboxTextureID << " " << width << " " << height << " " << nrChannels << std::endl;
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

void Environnement::draw() {
	glDepthMask(GL_FALSE);
	_shader.use();
	glBindVertexArray(_skyboxVao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureID);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(_skyboxVertices) / sizeof(_skyboxVertices[0]));
	glDepthMask(GL_TRUE);
	glBindVertexArray(0);
}

Shader		&Environnement::getShader() { return _shader; }
Shader		&Environnement::getShader() const { return _shader; }
uint32_t	Environnement::getSkyboxTextureID() const { return _skyboxTextureID; }
uint32_t	Environnement::getSkyboxVao() const { return _skyboxVao; }
uint32_t	Environnement::getSkyboxVbo() const { return _skyboxVbo; }

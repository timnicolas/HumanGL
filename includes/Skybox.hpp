#pragma once

#include <string>
#include <vector>
#include "Shader.hpp"

#define SKYBOX_START "skybox/"
#define SKYBOX_EXT ".jpg"
/*
name:
SKYBOX_START right SKYBOX_EXT
SKYBOX_START left SKYBOX_EXT
SKYBOX_START top SKYBOX_EXT
SKYBOX_START bottom SKYBOX_EXT
SKYBOX_START front SKYBOX_EXT
SKYBOX_START back SKYBOX_EXT
*/

class Skybox {
	public:
		explicit Skybox(Shader &sh);
		Skybox(Skybox const &src);
		virtual ~Skybox();

		Skybox &operator=(Skybox const &rhs);

		void load(std::vector<std::string> &faces);
		void draw();

		Shader		&getShader();
		Shader		&getShader() const;
		uint32_t	getTextureID() const;
		uint32_t	getVao() const;
		uint32_t	getVbo() const;
	protected:
	private:
		Shader		&_shader;
		uint32_t	_textureID;
		uint32_t	_vao;
		uint32_t	_vbo;

		static const float _vertices[];
};

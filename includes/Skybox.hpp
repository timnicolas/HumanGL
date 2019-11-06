#pragma once

#include <string>
#include <vector>
#include "Shader.hpp"

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

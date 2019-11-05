#pragma once

#include <string>
#include <vector>
#include "Shader.hpp"

class Environnement {
	public:
		explicit Environnement(Shader &sh);
		Environnement(Environnement const &src);
		virtual ~Environnement();

		Environnement &operator=(Environnement const &rhs);

		void loadSkyBox(std::vector<std::string> &faces);
		void draw();

		Shader		&getShader();
		Shader		&getShader() const;
		uint32_t	getSkyboxTextureID() const;
		uint32_t	getSkyboxVao() const;
		uint32_t	getSkyboxVbo() const;
	protected:
	private:
		Shader		&_shader;
		uint32_t	_skyboxTextureID;
		uint32_t	_skyboxVao;
		uint32_t	_skyboxVbo;

		static const float _skyboxVertices[];
};

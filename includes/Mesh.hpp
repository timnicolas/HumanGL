#ifndef MESH_HPP
# define MESH_HPP

#include "humanGL.hpp"
#include "Shader.hpp"
#include <vector>

enum class TextureT {
	difuse,
	specular,
};

static const std::string	g_text_type[] =
{
	"diffuse",
	"specular"
};

struct Vertex {
	glm::vec3	pos;
	glm::vec3	norm;
	glm::vec2	texCoords;
};

struct Texture {
	u_int32_t	id;
	TextureT	type;
};

class Mesh {
	public:
		Mesh(std::vector<Vertex> vertices, std::vector<u_int32_t> indices, \
		std::vector<Texture> textures);
		Mesh(Mesh const &src);
		virtual ~Mesh();

		Mesh &operator=(Mesh const &rhs);

		void	Draw(Shader shader) const;

		std::vector<Vertex>		vertices;
		std::vector<u_int32_t>	indices;
		std::vector<Texture>	textures;
	private:
        void	setupMesh();

        u_int32_t	_vao;
        u_int32_t	_vbo;
        u_int32_t	_ebo;
};

#endif

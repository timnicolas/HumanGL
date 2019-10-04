#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u_int32_t> indices, \
std::vector<Texture> textures)
:	vertices(vertices),
	indices(indices),
	textures(textures)
{
	setupMesh();
}

Mesh::Mesh(Mesh const &src) {
	*this = src;
}

Mesh::~Mesh() {
}

Mesh &Mesh::operator=(Mesh const &rhs) {
	if (this != &rhs)
		;
	return *this;
}

void	Mesh::draw(Shader &shader) const {
	u_int32_t	diffuseId;
	u_int32_t	specularId;
	std::string	nb;

	diffuseId = 0;
	specularId = 0;

	for (u_int16_t i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		if (textures[i].type == TextureT::difuse)
			nb = std::to_string(++diffuseId);
		else if (textures[i].type == TextureT::specular)
			nb = std::to_string(++specularId);

		shader.setInt(("texture_" + g_text_type[static_cast<int>(textures[i].type)] + nb).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// drawing mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Mesh::setupMesh() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int32_t), &indices[0], GL_STATIC_DRAW);

	// vertex pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
	// vertex norm
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, norm));
	// vertex textCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

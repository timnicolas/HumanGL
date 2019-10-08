#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u_int32_t> indices, \
std::vector<Texture> textures)
:	vertices(vertices),
	indices(indices),
	textures(textures)
{
	_setupMesh();
}

Mesh::Mesh(Mesh const &src) {
	*this = src;
}

Mesh::~Mesh() {
}

Mesh &Mesh::operator=(Mesh const &rhs) {
	if (this != &rhs) {
		vertices = rhs.vertices;
		indices = rhs.indices;
		textures = rhs.textures;
		_vao = rhs.getVao();
		_vbo = rhs.getVbo();
		_ebo = rhs.getEbo();
	}
	return *this;
}

void	Mesh::draw(Shader &shader) const {
	u_int32_t	diffuseId;
	u_int32_t	specularId;
	std::string	nb;

	diffuseId = 0;
	specularId = 0;

	shader.use();
	for (u_int16_t i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		if (textures[i].type == TextureT::difuse)
			nb = std::to_string(++diffuseId);
		else if (textures[i].type == TextureT::specular)
			nb = std::to_string(++specularId);

		shader.setInt(("texture_" + gTextType[static_cast<int>(textures[i].type)] + nb).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	// drawing mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Mesh::_setupMesh() {
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int32_t), &indices[0], GL_STATIC_DRAW);

	void *dataoffsetVec3 = &(((mat::Vec3 *)0)->_data);
	void *dataoffsetVec2 = &(((mat::Vec2 *)0)->_data);
	size_t vec3size = sizeof(mat::Vec3);
	// vertex pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)dataoffsetVec3);
	// vertex norm
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(static_cast<char*>(dataoffsetVec3) + vec3size));
	// vertex textCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(static_cast<char*>(dataoffsetVec2) + vec3size * 2));

    glBindVertexArray(0);
}

u_int32_t	Mesh::getVao() const {
	return _vao;
}
u_int32_t	Mesh::getVbo() const {
	return _vbo;
}
u_int32_t	Mesh::getEbo() const {
	return _ebo;
}

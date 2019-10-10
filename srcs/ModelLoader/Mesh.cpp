#include "Mesh.hpp"

Mesh::Mesh(std::vector<VertexMat> vertices, std::vector<u_int32_t> indices, \
std::vector<Texture> textures, Material material)
:	vertices(vertices),
	indices(indices),
	textures(textures),
	material(material)
{}

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
		material = rhs.material;
		_vao = rhs.getVao();
		_vbo = rhs.getVbo();
		_ebo = rhs.getEbo();
	}
	return *this;
}

void	Mesh::draw(Shader &sh) const {
	bool	diffuseText = false;
	bool	specularText = false;

	sh.use();
	for (u_int16_t i = 0; i < textures.size(); ++i) {
		glActiveTexture(GL_TEXTURE0 + i);

		if (textures[i].type == TextureT::difuse && !diffuseText) {
			diffuseText = true;
			sh.setBool("material.diffuse.isTexture", true);
			sh.setInt("material.diffuse.texture", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (textures[i].type == TextureT::specular && !specularText) {
			specularText = true;
			sh.setBool("material.specular.isTexture", true);
			sh.setInt("material.specular.texture", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
	}
	glActiveTexture(GL_TEXTURE0);

	if (!diffuseText) {
		sh.setBool("material.diffuse.isTexture", false);
		sh.setVec3("material.diffuse.color", material.diffuse);
	}
	if (!specularText) {
		sh.setBool("material.specular.isTexture", false);
		sh.setVec3("material.specular.color", material.specular);
	}
	sh.setFloat("material.shininess", material.shininess);

	// drawing mesh
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Mesh::setupMesh() {
	// create real vertex object to send to the bufferData in openGL
	std::vector<Vertex> vert;
	for (size_t i=0; i < vertices.size(); i++) {
		Vertex v = Vertex{
			vertices[i].pos.x, vertices[i].pos.y, vertices[i].pos.z,
			vertices[i].norm.x, vertices[i].norm.y, vertices[i].norm.z,
			vertices[i].texCoords.x, vertices[i].texCoords.y,
			{vertices[i].bonesID[0], vertices[i].bonesID[1], vertices[i].bonesID[2], vertices[i].bonesID[3]},
			{vertices[i].bonesW[0], vertices[i].bonesW[1], vertices[i].bonesW[2], vertices[i].bonesW[3]}
		};
		vert.push_back(v);
	}

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(Vertex), &(vert[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u_int32_t), &indices[0], GL_STATIC_DRAW);

	// vertex pos
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, posx));
	// vertex norm
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normx));
	// vertex textCoords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoordsx));
	// vertex bones IDs
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, NUM_BONES_PER_VERTEX, GL_INT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bonesID));
	// vertex bones weight
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, NUM_BONES_PER_VERTEX, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, bonesW));

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

// add a bone ID ad weight to model
void Mesh::addBoneData(u_int32_t boneID, float weight, u_int32_t vertexID) {
	for (u_int32_t i = 0; i < NUM_BONES_PER_VERTEX; ++i) {
		// if the vertex bone weight as not been set
		if (vertices[vertexID].bonesW[i] == 0.0f) {
			vertices[vertexID].bonesID[i] = boneID;
			vertices[vertexID].bonesW[i] = weight;
			return;
		}
	}
	// std::cerr << "too many bones in Mesh -> max: " << NUM_BONES_PER_VERTEX << "\n";
}